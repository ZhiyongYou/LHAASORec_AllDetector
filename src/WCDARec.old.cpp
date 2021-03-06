#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TNtupleD.h"
/*by zengzk*/
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include "TMinuit.h"
#include <cmath>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <TGraph.h>
#include <TF2.h>
#include "TROOT.h"
#include "TRandom.h"
#include "TMinuit.h"
#include "TStyle.h"
#include "TPad.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"
#include <cmath>

/* by zengzk*/

using namespace std;

//////////////////////////////
Double_t cell_water_eff[900]={-1.};//

static Double_t top50_x=0;
static Double_t core_x_check=0;
static Double_t core_y_check=0;
static Double_t top50_y=0;
static Double_t top50_z=0.5;
static Double_t even_x=0;
static Double_t even_y=0;
static Double_t odd_x=0;
static Double_t odd_y=0;
long long int kN30=0;

Double_t dirl=0,dirm=0,dirn=0;

Double_t xc,yc,zc;
Double_t zxc=0,zyc=0;
Double_t  _ksx=0.;
Double_t  _ksy=0.;
Double_t  _ksz=0.;
Double_t  _ksq=0.;
char buf[201];

/*sort  by zengzk*/
const int Nn=4000;// sort Npe
int a[Nn];
struct event{
	Double_t kvx;
	Double_t kvy;
	Double_t kvz;
	Double_t kvq;
	Double_t kvigcell;

};
event s[Nn];
int comp(const event &s1,const event &s2){
	return s1.kvq>s2.kvq;
}

const int tNn=4000;// sort time
int ta[tNn];
struct tevent{
	Double_t kvx;
	Double_t kvy;
	Double_t kvz;
	Double_t kvq;
	Double_t kvtp;
	Double_t kvigcell;


};
tevent ts[tNn];
int tcomp(const tevent &ts1,const tevent &ts2){
	return ts1.kvtp<ts2.kvtp;
}


const int sNn=4000;// sort skdcore
int sa[Nn];
struct Sevent{
	Double_t skdcore;
	Double_t skvx;
	Double_t skvy;
	Double_t skvz;
	Double_t skvq;
	Double_t skvigcell;

};
Sevent ss[sNn];
int scomp(const Sevent &ss1,const Sevent &ss2){
	return ss1.skdcore>ss2.skdcore;
}
/*nkg by zengzk */

static  TMinuit *wcda_minuit=new TMinuit(4);
static Double_t r[5000];
static Double_t ElPosx[5000];
static Double_t ElPosy[5000];
static Double_t ElData[5000];
static Double_t _size,_age;
static Double_t _cx,_cy;
static int NHIT;
static Double_t zChi2;

Double_t   vcore_like[8]={0};

Double_t  fme(Double_t *x, Double_t *p)
{
	Double_t  r=x[0];
	Double_t  RM = 36. ; //Moliere radius (m)
	Double_t  tmp =  2.;
	tmp *= TMath::Pi();
	tmp *= TMath::Gamma(p[0]-0.1);
	tmp *= TMath::Gamma(3.1 - 2. * p[0]);
	Double_t cs = TMath::Gamma(3. - p[0]) / tmp;
	Double_t a = p[0] - 2.1;
	Double_t b = p[0] - 3.;
	Double_t rho =p[1]*cs * pow(r/RM,a) * pow(r/RM+1.,b) / (RM*RM);
	return rho;
}

Double_t NKGlike(Double_t r, Double_t s,Double_t ne)
{
	Double_t  RM = 36. ; //Moliere radius (m)
	Double_t  tmp =  2.;
	tmp *= TMath::Pi();
	tmp *= TMath::Gamma(s-0.1);
	tmp *= TMath::Gamma(3.1 - 2. * s);
	Double_t cs = TMath::Gamma(3 - s) / tmp;
	Double_t a = s - 2.1;
	Double_t b = s - 3.;
	Double_t rho = ne*cs * pow(r/RM,a) * pow(r/RM+1.,b) / (RM*RM);
	return rho;
}



Double_t CNKGlike(Double_t cr, Double_t s,Double_t ne)
{
	Double_t  RM = 36. ; //Moliere radius (m)
	Double_t  tmp =  2.;
	tmp *= TMath::Pi();
	tmp *= TMath::Gamma(s-0.1);
	tmp *= TMath::Gamma(3.1 - 2. * s);
	Double_t cs = TMath::Gamma(3 - s) / tmp;
	Double_t a = s - 2.1;
	Double_t b = s - 3.;
	Double_t rho = ne*cs * pow(cr/RM,a) * pow(cr/RM+1.,b) / (RM*RM);
	return rho;
}

/*static void NKG_FUNC(int &npar, Double_t *gin, Double_t &f,Double_t *par, int iflag)
 * {
 *   Double_t s=par[0];
 *     Double_t ne=par[1];
 *       Double_t cx=par[2];
 *         Double_t cy=par[3];
 *           Double_t llf=0;
 *           for(int i=0;i<NHIT;i++)
 *           {
 *             r[i]=sqrt(pow(ElPosx[i]-cx,2)+pow(ElPosy[i]-cy,2));
 *               llf+=(NKGlike(r[i],s,ne)-ElData[i])*(NKGlike(r[i],s,ne)-ElData[i])/ElData[i];
 *
 *                //cout<<"Chi2: "<<s<<" "<<ne<<" "<<NKGlike(r[i],s,ne)<<" "<<r[i]<<" "<<ElData[i]<<endl;
 *
 *                }
 *                  f=llf;
 *                   zChi2=llf;
 *                     _age=s;
 *                       _size=ne;
 *                       }*/

static void NKG_FUNCL(int &npar, Double_t *gin, Double_t &f,Double_t *par, int iflag)
{
	Double_t s=par[0];
	Double_t ne=par[1];
	Double_t cx=par[2];
	Double_t cy=par[3];
	Double_t llf=0,llf1=0;
	Double_t p1=0;
	Double_t p2=0;
	for(int i=0;i<NHIT;i++)
	{
		r[i]=sqrt(pow(ElPosx[i]-cx,2)+pow(ElPosy[i]-cy,2)-pow((ElPosx[i]-cx)*dirl+(ElPosy[i]-cy)*dirm,2.));//  dir 
		llf1+=(NKGlike(r[i],s,ne)-ElData[i])*(NKGlike(r[i],s,ne)-ElData[i])/ElData[i];

		p1+=NKGlike(r[i],s,ne);
		p2+=ElData[i]*log(NKGlike(r[i],s,ne));
		llf+=p1-p2;
	}

	f=llf;
	_age=s;
	_size=ne;
	zChi2=llf1;
}

void core_likelihood( ){

	wcda_minuit->mncler();
	_age=1.;
	_size=kN30;
	_cx=top50_x;
	_cy=top50_y;

	int _flag=0;
	Double_t arglist[10];
	arglist[0]=-1;
	wcda_minuit->mnexcm("SET PRINT",arglist,1,_flag);
	wcda_minuit->mnexcm("SET NOWarnings",arglist,1,_flag);
	wcda_minuit->mnparm(0,"age",_age, 0.05,0,0,_flag);
	wcda_minuit->mnparm(1,"size",_size,0.01*kN30,0,0,_flag);
	wcda_minuit->mnparm(2,"cx",_cx,0.5,0,0,_flag);
	wcda_minuit->mnparm(3,"cy",_cy,0.5,0,0,_flag);

	wcda_minuit->SetFCN(NKG_FUNCL);

	arglist[0]=1;
	wcda_minuit->mnexcm("CALL FCN",arglist,1,_flag);
	arglist[0]=1000;//loop
	arglist[1]=0.0001;//tolerance 
	wcda_minuit->mnexcm("SIMPLEX",arglist,0,_flag);
	wcda_minuit->mnexcm("MIGRAD",arglist,0,_flag);
	wcda_minuit->mnscan();


	cout<<"result:"<<endl;
	wcda_minuit->GetParameter(0,vcore_like[0], vcore_like[1]);
	wcda_minuit->GetParameter(1,vcore_like[2], vcore_like[3]);
	wcda_minuit->GetParameter(2,vcore_like[4], vcore_like[5]);
	wcda_minuit->GetParameter(3,vcore_like[6], vcore_like[7]);
	cout<<vcore_like[0]<<" "<<vcore_like[2]<<endl;
	cout<<vcore_like[4]<<" "<<vcore_like[6]<<endl;
	Double_t amin,edm,errdef;
	Int_t nvpar,nparx,icstat;
	gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);//cout<<" check: "<<amin<<" "<<" "<<nvpar<<endl;
}



//////////////////////////////////////////////////////////////////

void DealWCDAEvent(const std::vector<int>& cell_ig, const std::vector<double>& cell_pe, const std::vector<double>& cell_t,
		std::vector<double>& wcda_clean_x, std::vector<double>& wcda_clean_y, std::vector<double>& wcda_clean_pe,
		std::vector<int>& wcda_clean_ig, std::vector<double>& wcda_clean_t, double *evrec)
{
	wcda_clean_x.clear();
	wcda_clean_y.clear();
	wcda_clean_pe.clear();
	wcda_clean_ig.clear();
	wcda_clean_t.clear();
	int i,j,k;
	/*by zengzk*/
	/*  igcell  -->  x y z*/

	Double_t big1_pmtx_igcell[900];
	Double_t big1_pmty_igcell[900];
	Double_t big1_pmtz_igcell[900];

#include "big1posconf.h"

	/*water_eff*/
	int itmp_igcell;
	Double_t tmp_water_eff;
	ifstream water_eff_txt;
	water_eff_txt.open("/workfs/ybj/yinlq/LHAASO/Match/RecLHAASO_v5/water_eff/2020/0110.txt");

	while (water_eff_txt.getline(buf,200)) {
		sscanf(buf,"%d %lf\n",&itmp_igcell, &tmp_water_eff);
		cell_water_eff[itmp_igcell]=tmp_water_eff;
		/*  if(itmp_igcell>890)  cout<<"charming water_eff="<<itmp_igcell<<" "<<tmp_water_eff<<endl;*/
	}
	water_eff_txt.close();


	//Double_t evrec[70]={-999.}; //information
	int nhit=0;//NNEEWW

	/*core g/p En */
	Double_t  clustering_q=0,  clustering_rq=0,  clustering=0;

	Double_t kvx[3000]={0}, kvy[3000]={0},kvz[3000]={0},kvq[3000]={0},kvigcell[3000]={-1},kvtp[3000]={-999};
	Double_t nskvx[3000]={0}, nskvy[3000]={0},nskvz[3000]={0},nskvq[3000]={0},nskvigcell[3000]={-1};
	Double_t nkvx[3000]={0}, nkvy[3000]={0},nkvz[3000]={0},nkvq[3000]={0},nkvigcell[3000]={-1};

	Double_t sskvx[3000]={0}, sskvy[3000]={0},sskvz[3000]={0},sskvq[3000]={0},sskvtp[3000]={0},sskvigcell[3000]={-1};
	Double_t skvx[3000]={0}, skvy[3000]={0},skvz[3000]={0},skvq[3000]={0},skvtp[3000]={0},skvigcell[3000]={-1};

	Double_t skdcore[5000]={0};
	long long int kN10=0, kN20=0, kN40out=0, kNall=0;
	int npmt10=0,npmt20=0,npmt30=0,npmt40out=0,npmtall=0;
	int N_Top10rate=0, N_Top50rate=0;
	int N_secCore2=0;
	int N_secCore4=0;
	int N_secCore6=0;
	int N_secCore8=0;
	int N_secCore10=0;
	Double_t MaxX=0,MaxY=0,MaxQ=0;
	int k_nfit=0;

	Double_t peBA_same_igFlag[1000]={0};
	Double_t peBD_same_igFlag[1000]={0};
	Double_t dr[3000]={0},dq[3000]={0};
	int nnhit=0;
	double SUM=0;

	/*rec direction */
	Double_t theta_first=0,phi_first=0;
	Double_t p_theta=0, p_phi=0,Q1=0,Q2=0;
	Double_t c_theta=0, c_phi=0, cone_factor=0;
	Double_t d_theta=0, d_phi=0,ch2_sigma=0;
	int d_nhit=0,d_nhit1=0;

	Double_t tp_trig=0;
	Double_t sort_tp_trig=0;
	Double_t time_trig_evt=0;
	long long int  t_all=0,t_q_all=0;

	Double_t z_dx[3000]={0}, z_dy[3000]={0},z_dz[3000]={0},z_dq[3000]={0},z_digcell[3000]={-1},z_dt[2000]={-99};
	int nhit_no_ap=0;

	Double_t  l_z=0,m_z=0,n_z=0,zt_theta=0,zt_phi=0;

	Double_t t_par[5]={0};//filter1
	Double_t tt_par[5]={0};//filter2
	Double_t ttt_par[5]={0};//planefit
	Double_t tttt_par[5]={0};//coin fit
	Double_t ttttt_par[6]={0};//2d planefit

	Double_t fff8_par[8]={0};
	Double_t fff9_par[9]={0};
	Double_t ff10_par[10]={0};
	//Double_t ff101_par[10]={0};

	/*rec direction by cone factor*/
	Double_t cf_x[3000]={0}, cf_y[3000]={0},cf_z[3000]={0},cf_q[3000]={0},cf_igcell[3000]={-1},cf_t[2000]={-99};
	int nhit_pfilter=0;
	int nhit_pnoise=0;
	Double_t  core_x,core_y,core_z;

	//TH2F *pos2 = new TH2F("position_absolute",buf,40,-100,100,40,-100,100);

	TH1D *htp1 =new TH1D("htp1","htp1",200,-500,500);

	TH2D *http = new TH2D("http","http",32,-80,80,32,-80,80);

	TF2 *ff = new TF2 ("ff","sin(1.*[0])*cos(1.*[1])*x+sin(1.*[0])*sin(1.*[1])*y+[2]", -75, 75, -75, 75);
	// TH3D *httpp = new TH3D("httpp","httpp",160,-80,80,160,-80,80,100,0,1);

	TH2D *htp10 = new TH2D("htp10","htp10",32,-80,80,32,-80,80);
	//TH2D *htp11 = new TH2D("htp11","htp11",32,-80,80,32,-80,80);
	TF2 *ff10 = new TF2("ff10", "sin(1.*[0])*cos(1.*[1])*x+sin(1.*[0])*sin(1.*[1])*y+[6]*[5]*sqrt((x-[2])*(x-[2])+(y-[3])*(y-[3]))+[7]", -75, 75, -75, 75);
	//TF2 *ff101 = new TF2("ff101", "sin(1.*[0])*cos(1.*[1])*x+sin(1.*[0])*sin(1.*[1])*y+[6]*[5]*sqrt((x-[2])*(x-[2])+(y-[3])*(y-[3]))+[7]", -75, 75, -75, 75);


	/*by zengzk£*/

	/// Get event tree in the input file
	/// para for wcda
	int nhitplus;




	/*  by   zengzk  */
	////////////////////////////////////
	///////        wcda rec           ////
	///////////////////////////////////////


	nhit = cell_pe.size();




	//cout<<"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
	//pos2->Reset();
	int  kigcell=-1;
	for(int i=0;i< cell_pe.size();i++){//get x y z q t igcell

		kvq[i] = cell_pe[i];
		kvtp[i] = cell_t[i];
		kvigcell[i] = kigcell = cell_ig[i];

		kvq[i] = kvq[i] * cell_water_eff[kigcell];//water_eff

		kvx[i] = big1_pmtx_igcell[kigcell];
		kvy[i] = big1_pmty_igcell[kigcell];
		kvz[i] = big1_pmtz_igcell[kigcell];
		/*Q-T*/
		kvtp[i]=kvtp[i]-(20*pow(kvq[i],-0.1)+10*pow(kvq[i],-0.08)-24.2);//Q-T  tp=tp-(20*pow(q,-0.1)+10*pow(q,-0.08)-24.2);  //by gaob

		SUM=kvq[i]+SUM;


	}


	for (int tzi=0;tzi<nhit;tzi++)
	{
		ts[tzi].kvtp=kvtp[tzi];
		ts[tzi].kvq=kvq[tzi];
		ts[tzi].kvx=kvx[tzi];
		ts[tzi].kvy=kvy[tzi];
		ts[tzi].kvz=kvz[tzi];/*cout<<ts[tzi].kvtp<<endl;*/
		ts[tzi].kvigcell=kvigcell[tzi];
	}
	sort(ts,ts+tNn,tcomp);

	double sort_t_all=0.01,sort_t_q_all=0.01;
	int    sort_t_i=0;
	int    N_hit_noap=700;

	if (nhit<900){N_hit_noap=nhit*4./5.;}

	/*get time with weight*/
	for (int i=0;i<tNn;i++){
		if(ts[i].kvtp>0&&sort_t_i>10)
		{
			sort_t_all= pow(ts[i].kvq,2) * ts[i].kvtp  + sort_t_all;
			sort_t_q_all=pow(ts[i].kvq,2)  + sort_t_q_all;
			/*cout<<"  "<<ts[i].kvq<<"   "<<ts[i].kvtp<<endl;*/
			if (sort_t_i> N_hit_noap){cout<<" OOOOOOOOOOOO "<<sort_t_i<<endl;break;}
		}

		if (ts[i].kvtp>0){sort_t_i=sort_t_i+1;}

	}

	sort_tp_trig=1.*sort_t_all/sort_t_q_all;

	/*get mean time*/
	for (int i=0;i<nhit;i++){
		t_all=kvtp[i]  * pow(kvq[i],2)+ t_all;
		t_q_all=pow(kvq[i],2) + t_q_all;
	}

	tp_trig=1.*t_all/t_q_all;
	/*cout<<" sort time  tp "<<sort_tp_trig<<" mean  tp== "<<tp_trig<<endl;*/

	/*you can get good signal without afterpurlse!*/

	http->Reset();
	int tj=0;
	double add_time=600;
	for (int i=0;i<nhit;i++){
		if( kvtp[i]>(sort_tp_trig-add_time) && kvtp[i]<(sort_tp_trig+add_time) ){
			z_dx[tj]=kvx[i];//in m
			z_dy[tj]=kvy[i];
			z_dz[tj]=kvz[i];
			z_dq[tj]=kvq[i];
			z_dt[tj]=kvtp[i];
			z_digcell[tj]=kvigcell[i];
			if (z_dq[tj]>0.5&&z_dq[tj]<2500){http->Fill(z_dx[tj],z_dy[tj],z_dt[tj]/3.3356);}

			tj=tj+1;
		}
	}


	nhit_no_ap=tj;


	/*you  need check   the nhit_no_ap.*/
	ff->SetParameter(0,0.5);
	ff->SetParameter(1,0.5);
	ff->SetParLimits(1,-6.3,6.3);
	ff->SetParameter(2,sort_tp_trig);


	TCanvas * ctemp = new TCanvas("ctemp","ctemp",800,800);
	http->Fit("ff", "QWM");
	ff->GetParameters(t_par);
	/*cout<<"Fit    par=="<<t_par[0]<<" "<<t_par[1]<<"   "<<t_par[2]<<"   "<<tp_trig<<endl;//ok!*/

	l_z=0, m_z=0, n_z=0;
	l_z=sin(1.*t_par[0])*cos(1.*t_par[1]);
	m_z=sin(1.*t_par[0])*sin(1.*t_par[1]);
	n_z=cos(1.*t_par[0]);

	if (n_z<0){l_z=l_z*(-1.);m_z=m_z*(-1.);n_z=n_z*(-1.);}

	cout<<"check  lmn "<<l_z<<" "<<m_z<<"  "<<n_z<<endl;
	/*theta*/
	theta_first=acos(n_z/1.)/3.1415926*180.;
	if(theta_first>90.){theta_first=180-abs(theta_first);}

	/*phi*/
	phi_first=atan(1.*m_z/l_z)/3.1415926*180.;
	if(l_z>0)  phi_first=phi_first+180.;
	if(phi_first>360.) phi_first=phi_first-360;
	if(phi_first<0.)   phi_first=phi_first+360;

	cout<<"plane fit =="<<theta_first<<"  "<<phi_first<<endl;


	Double_t trig_t0=t_par[2]*3.3356;

	t_par[0]=sin(1.*theta_first/180.*3.1415926)*cos(1.*phi_first/180.*3.1415926);
	t_par[1]=sin(1.*theta_first/180.*3.1415926)*sin(1.*phi_first/180.*3.1415926);
	t_par[2]=t_par[2];

	/*check plant_fit    now   filter  noise  -30ns~30ns*/
	Double_t diff_time=0;
	Double_t fit_time=0;

	int cf_i=0;
	int cf_ii=0;

	htp1->Reset();
	for (int i=0;i<nhit_no_ap;i++){
		fit_time=t_par[0]*z_dx[i]+t_par[1]*z_dy[i]+t_par[2];
		diff_time=t_par[0]*z_dx[i]+t_par[1]*z_dy[i]+t_par[2]-z_dt[i]/3.3356;
		htp1->Fill(diff_time);//htp2->Fill(fit_time);
	}


	TF1 *g = new TF1("m1","gaus",-1000, 1000);htp1->Fit(g,"R+");
	Q1=g->GetParameter(1);//mean
	Q2=g->GetParameter(2);//sigma
	cout<<"Gaus=="<<Q1<<" sigma == "<<Q2<<endl;
	Double_t noise_down=Q1-2*Q2; //change 2.5*Q2 to 2*Q2 by yzy, after check between this program and /afs/ihep.ac.cn/users/w/wcdaplusrec/scratchfs/wcdaplusrec/zenzk/wcdaRec_joint_crab/rec/wcdamatch_recon.cc
	Double_t noise_up=Q1+2*Q2;  //change 2.5*Q2 to 2*Q2 by yzy, after check between this program and /afs/ihep.ac.cn/users/w/wcdaplusrec/scratchfs/wcdaplusrec/zenzk/wcdaRec_joint_crab/rec/wcdamatch_recon.cc

	if(Q2==0) {Q2 = 600;}  //new add by yzy, after check between this program and /afs/ihep.ac.cn/users/w/wcdaplusrec/scratchfs/wcdaplusrec/zenzk/wcdaRec_joint_crab/rec/wcdamatch_recon.cc

	for (int i=0;i<3000;i++){

		kvx[i]=0;
		kvy[i]=0;
		kvq[i]=0;
		kvtp[i]=0;
		kvigcell[i]=0;
	}

	//pos21->Reset();
	for (int i=0;i<nhit_no_ap;i++){
		fit_time=t_par[0]*z_dx[i]+t_par[1]*z_dy[i]+t_par[2];
		diff_time=t_par[0]*z_dx[i]+t_par[1]*z_dy[i]+t_par[2]-z_dt[i]/3.3356;
		if(diff_time>=(noise_down-2.5*Q2)&&diff_time<=(noise_up+2.5*Q2)){//+-50ns   -->  core  En  GP
			//if(diff_time>=(noise_down+1*Q2)&&diff_time<=(noise_up-1*Q2)){//+-50ns   -->  core  En  GP

			kvx[cf_ii]=z_dx[i];
			kvy[cf_ii]=z_dy[i];
			kvz[cf_ii]=z_dz[i];
			kvq[cf_ii]=z_dq[i];
			kvtp[cf_ii]=z_dt[i];
			kvigcell[cf_ii]=z_digcell[i];

			skvx[cf_ii]=z_dx[i];
			skvy[cf_ii]=z_dy[i];
			skvz[cf_ii]=z_dz[i];
			skvq[cf_ii]=z_dq[i];
			skvtp[cf_ii]=z_dt[i];
			skvigcell[cf_ii]=z_digcell[i];

			sskvx[cf_ii]=z_dx[i];
			sskvy[cf_ii]=z_dy[i];
			sskvz[cf_ii]=z_dz[i];
			sskvq[cf_ii]=z_dq[i];
			sskvtp[cf_ii]=z_dt[i];
			sskvigcell[cf_ii]=z_digcell[i];
			//pos2->Fill(kvx[cf_ii],kvy[cf_ii],kvq[cf_ii]/25.);//
			wcda_clean_x.push_back(kvx[cf_ii]);
			wcda_clean_y.push_back(kvy[cf_ii]);
			wcda_clean_pe.push_back(kvq[cf_ii]);
			wcda_clean_ig.push_back(kvigcell[cf_ii]);
			wcda_clean_t.push_back(kvtp[cf_ii]);


			cf_ii=cf_ii+1;
		}
		if(diff_time>=noise_down&&diff_time<=noise_up) {//2.5sigma   -->direction

			cf_x[cf_i]=z_dx[i];//in meter
			cf_y[cf_i]=z_dy[i];
			cf_z[cf_i]=z_dz[i];
			cf_q[cf_i]=z_dq[i];
			cf_igcell[cf_i]=z_digcell[i];
			cf_t[cf_i]=z_dt[i];//in ns
			cf_i=cf_i+1;

		}
		}
		nhit_pfilter=cf_i;
		nhit_pnoise=cf_ii;

		//	if (nhit_pfilter<20) //change by yzy, after check between this program and /afs/ihep.ac.cn/users/w/wcdaplusrec/scratchfs/wcdaplusrec/zenzk/wcdaRec_joint_crab/rec/wcdamatch_recon.cc
		if (nhit_pfilter<0.4*nhit||nhit_pfilter<20){
			if(nhit>10){  //added by yzy
				//			dir_flag = 10;  //added by yzy
				/*int*/
				for (int i=0;i<1000;i++){

					kvx[i]=0;
					kvy[i]=0;
					kvq[i]=0;
					kvtp[i]=0;
					kvigcell[i]=0;

					skvx[i]=0;
					skvy[i]=0;
					skvq[i]=0;
					skvtp[i]=0;
					skvigcell[i]=0;

					sskvx[i]=0;
					sskvy[i]=0;
					sskvq[i]=0;
					sskvtp[i]=0;
					sskvigcell[i]=0;

					cf_x[i]=0;
					cf_y[i]=0;
					cf_z[i]=0;
					cf_q[i]=0;
					cf_igcell[i]=0;
					cf_t[i]=0;
				}

				for (int ii=0;ii<nhit_no_ap;ii++){
					kvx[ii]=z_dx[ii];
					kvy[ii]=z_dy[ii];
					kvz[ii]=z_dz[ii];
					kvq[ii]=z_dq[ii];
					kvtp[ii]=z_dt[ii];
					kvigcell[ii]=z_digcell[ii];

					skvx[ii]=z_dx[ii];
					skvy[ii]=z_dy[ii];
					skvz[ii]=z_dz[ii];
					skvq[ii]=z_dq[ii];
					skvtp[ii]=z_dt[ii];
					skvigcell[ii]=z_digcell[ii];

					sskvx[ii]=z_dx[ii];
					sskvy[ii]=z_dy[ii];
					sskvz[ii]=z_dz[ii];
					sskvq[ii]=z_dq[ii];
					sskvtp[ii]=z_dt[ii];
					sskvigcell[ii]=z_digcell[ii];

					cf_x[ii]=z_dx[ii];//in meter
					cf_y[ii]=z_dy[ii];
					cf_z[ii]=z_dz[ii];
					cf_q[ii]=z_dq[ii];
					cf_igcell[ii]=z_digcell[ii];
					cf_t[ii]=z_dt[ii];//in ns   
				}

				nhit_pnoise=nhit_no_ap+1;
				nhit_pfilter=nhit_no_ap;

			}
		}

		cout<<"the  number of nhit=="<<nhit<<" nhit_no_ap=="<<nhit_no_ap<<" nhit_pnosie== "<<nhit_pnoise<<" nhit_pfilter== "<<nhit_pfilter<<endl;

		/*rec core by equal core!  */
		for (int zi=0;zi<nhit_pnoise;zi++)
		{
			s[zi].kvq=kvq[zi];
			s[zi].kvx=kvx[zi];
			s[zi].kvy=kvy[zi];
			s[zi].kvz=kvz[zi];
			s[zi].kvigcell=kvigcell[zi];
		}
		sort(s,s+Nn,comp);

		Double_t sm_R=0;
		_ksx=0.;
		_ksy=0.;
		_ksz=0.;
		_ksq=0.;
		/*top 5~50  -->core */




		MaxX=s[0].kvx;MaxY=s[0].kvy;MaxQ=s[0].kvq;

		for (int zi=5;zi<50;zi++){
			_ksx += s[zi].kvx*pow(s[zi].kvq,1);
			_ksy += s[zi].kvy*pow(s[zi].kvq,1);
			_ksz += s[zi].kvz*pow(s[zi].kvq,1);
			_ksq += pow(s[zi].kvq,1);
		}

		zxc=xc=top50_x=_ksx/_ksq;
		zyc=yc=top50_y=_ksy/_ksq;
		cout<< "xxxxxxxxxxxccccc: "<<xc << "yyyyyyyyyyyyyyycccc: "<<yc<<endl;

		_ksx=0.;
		_ksy=0.;
		_ksz=0.;
		_ksq=0.;

		/*core _Rm_for30_iter*/
		int iter;
		for(iter=0;iter<50;iter++){

			int zii=0;
			if(iter<5){zii=5;}
			for (int zi=zii;zi<nhit_pnoise;zi++)//rec nhit
			{
				if(iter<1){  kN30 =kN30+s[zi].kvq;}
				sm_R=sqrt(pow(75-abs(xc),2)+pow(75-abs(yc),2));if(sm_R<5){break;}
				Double_t     R11=sqrt((s[zi].kvx-xc)*(s[zi].kvx-xc)+(s[zi].kvy-yc)*(s[zi].kvy-yc));

				if (s[zi].kvq>=0.3&&R11<=sm_R&&R11<106) {//75*1.414
					double   w  = 0;
					/*if(abs(s[zi].kvx)>(2*abs(xc)-75+iter)&&abs(s[zi].kvy)>(2*abs(yc)-75+iter)){w=exp(-0.5*pow(R11/(50.-iter),2));}*/
					/* if(abs(s[zi].kvx)>(abs(xc)-25)&&abs(s[zi].kvy)>(abs(yc)-25)) */
					if(abs(s[zi].kvx-xc)<75-abs(xc)&&abs(s[zi].kvy-yc)<75-abs(yc)){
						w=exp(-0.5*pow(R11/(60.-iter),2));
						_ksx += s[zi].kvx*pow(s[zi].kvq,1)*w;
						_ksy += s[zi].kvy*pow(s[zi].kvq,1)*w;
						_ksz += s[zi].kvz*pow(s[zi].kvq,1)*w;
						_ksq += pow(s[zi].kvq,1)*w;
					}
				}
			}

			if (_ksq>0) {xc=zxc;yc=zyc;zxc = _ksx/_ksq;zyc = _ksy/_ksq;}

			if (sqrt(pow(xc-zxc,2)+pow(yc-zyc,2))<0.2){cout<<"HHHHHHHHHHHHH"<<iter<<endl;break;}
		}//iter

		xc=top50_x=zxc;
		yc=top50_y=zyc;
		top50_z=_ksz/_ksq;
		cout<< "22222222xxxxxxxxxxxccccc: "<<xc << "yyyyyyyyyyyyyyycccc: "<<yc<<"iter: "<<iter<<endl;


		_ksx=0.;
		_ksy=0.;
		_ksz=0.;
		_ksq=0.;

		int iter2=0;
		for (int i=0;i<30;i++){

			int zii=1;
			if(i<5){zii=5;}
			for (int zi=zii;zi<nhit_pnoise;zi++)//rec   equal  core
			{
				if (zi==0){MaxX=s[zi].kvx;MaxY=s[zi].kvy;MaxQ=s[zi].kvq;}

				if (xc*xc>=yc*yc){sm_R=75-abs(xc);}     //equal  core 
				else {sm_R=75-abs(yc);}

				sm_R=sqrt(pow(75-abs(xc),2)+pow(75-abs(yc),2));if(sm_R<5){break;}
				Double_t     R11=sqrt((s[zi].kvx-xc)*(s[zi].kvx-xc)+(s[zi].kvy-yc)*(s[zi].kvy-yc));
				if (s[zi].kvq>=0.3&&R11<=sm_R&&R11<106) {
					/* if(abs(s[zi].kvx)<(abs(xc)+sm_R)&&abs(s[zi].kvx)>(abs(xc)-sm_R)&&abs(s[zi].kvy)<(abs(yc)+sm_R)&&abs(s[zi].kvy)>(abs(yc)-sm_R)){*/
					if(abs(s[zi].kvx-xc)<75-abs(xc)&&abs(s[zi].kvy-yc)<75-abs(yc)){
						double   w  = 0;
						w=exp(-0.5*pow(R11/(40.-i),2));
						_ksx += s[zi].kvx*pow(s[zi].kvq,1)*w;
						_ksy += s[zi].kvy*pow(s[zi].kvq,1)*w;
						_ksz += s[zi].kvz*pow(s[zi].kvq,1)*w;//cout<<s[zi].kvz<<endl;//ok!
						_ksq += pow(s[zi].kvq,1)*w;
					}
				}
				}

				if (_ksq>0) {xc=zxc;yc=zyc;zxc = _ksx/_ksq;zyc = _ksy/_ksq;}
				if (sqrt(pow(xc-zxc,2)+pow(yc-zyc,2))<0.1){cout<<"H1H1H1H1H1H1H1H1H1HHHH=="<<i<<endl;iter2=i;break;}

			}
			if (_ksq>0){zxc = _ksx/_ksq; zyc = _ksy/_ksq;top50_z=_ksz/_ksq*1.;}

			xc=top50_x=zxc;
			yc=top50_y=zyc;
		cout<< "333333333333xxxxxxxxxxxccccc: "<<xc << "yyyyyyyyyyyyyyycccc: "<<yc<<endl;


			core_x_check=top50_x;
			core_y_check=top50_y;

			if (abs(top50_x)>60||abs(top50_y)>60) // if top50_x or rop50_y bigger than 75, will not worked in to this branch, zzk:60
			{
				int zj=0;
				for (int ii=5;ii<nhit_pnoise;ii++){

					double    R11=sqrt(pow(s[ii].kvx-xc,2)+pow(s[ii].kvy-yc,2));
					if (R11<80) {//75*1.414
						ElPosx[zj]= s[ii].kvx;
						ElPosy[zj]= s[ii].kvy;
						ElData[zj]= s[ii].kvq/25.;
						zj=zj+1;
					}
				}
				NHIT=zj;
				core_likelihood( );

				cout<<"core  fit result: "<<endl;
				cout<<"nkgcore fit xc="<<vcore_like[4]<<endl;  //x 
				cout<<"nkgcore fit yc="<<vcore_like[6]<<endl;//y
				cout<<"  kN30=="<<kN30<<endl;

				if((pow(vcore_like[4],2)+pow(vcore_like[6],2) ) > (pow(top50_x,2)+pow(top50_y,2))&&sqrt(pow(vcore_like[4],2)+pow(vcore_like[6],2)) <120.)
				{
					top50_x=vcore_like[4];
					top50_y=vcore_like[6];
				}

			}

		cout<< "444444444444xxxxxxxxxxxccccc: "<<top50_x << "yyyyyyyyyyyyyyycccc: "<<top50_y<<endl;

			/*Direction  by  zengzk      //~80ns*/
			core_x=top50_x;
			core_y=top50_y;

			Double_t  time_core=0;
			time_core=(t_par[0]*core_x+t_par[1]*core_y+t_par[2])*3.3356;


			htp10->Reset();
			//htp11->Reset();
			int iii=0;


			int iiter;
			int for_iiter=0;
			int recFlag=-99;
			int wt=1;
			for(int mj=0;mj<1;mj++){
				int i,j,k,nus,nus1;
				double Flag=0;
				double dt,w,the,phi,dirl,dirm,dirn,dr,c[4];
				double x,y,z,dx,dy,dz,sigma;

				double d_l=l_z,d_m=m_z,d_n=n_z;
				double alpha=0.02*3.3356;//Proton   Gamma0.025

				TMatrixD a(4,4);
				TVectorD b(4),r(4);
				//by yzy ,different 
				//			r[0]=l_z;
				//			r[1]=m_z;
				//			r[3]=trig_t0;

				r[0]=0; //added by yzy
				r[1]=0;//added by yzy
				r[3]=0;//added by yzy
				if(l_z*l_z+m_z*m_z>1){r[0]=0; r[1]=0;}
				cout<<l_z<<"  "<<m_z<<endl;
				dirl=sin(theta_first/180*3.1415926)*cos(phi_first/180*3.1415926);
				dirm=sin(theta_first/180*3.1415926)*sin(phi_first/180*3.1415926);
				dirn=cos(theta_first/180*3.1415926);

				//			for( iiter=0;iiter<100;iiter++){ //check by yzy, iiter < 50
				for( iiter=0;iiter<50;iiter++){ //added by yzy, iiter < 50
					nus=0;
					sigma=0;
					nus1=0;

					for(i=0;i<4;i++){
						for(j=0;j<4;j++)a[i][j]=0;
						b[i]=0;
					}
					nus=0; sigma=0;nus1=0;
					for(i=0; i<nhit_pnoise; i++){
						if(kvq[i]<2500&&kvq[i]>0.5){
							dx = kvx[i]-top50_x;
							dy = kvy[i]-top50_y;
							dz = kvz[i]-top50_z;
							dr  = (dx*dx+dy*dy+dz*dz-pow(dx*dirl+dy*dirm+dz*dirn,2.));
							if(dr<0)dr=0;
							dr =sqrt(dr);

							if(iiter==0)w=1.;
							else{
								dt = kvtp[i]-(r[0]*kvx[i]/0.2998+r[1]*kvy[i]/0.2998+dirn*kvz[i]/0.2998+r[3]);
								double d1=-10;  //added by yzy
								double d2=20; //added by yzy
								if (nhit_pnoise<10000){d2=12.5+5.*(nhit_pnoise+100.)/400; //added by yzy
								}
								if(dt>d2||dt<d1){ //added by yzy
									double wt1=abs(dt-d1); //added by yzy
									double wt2=abs(dt-d2); //added by yzy
									double wwt=wt1;if(wt1>=wt2){wwt=wt2;} //added by yzy
									w  = exp(-0.5*pow(wwt/10.,2)); //added by yzy
								} //added by yzy
								//before change							if(dt>35||dt<-20) //???
								//before change								//if(dt>0||dt<-20))/
								//before change								w  = exp(-0.5*pow(dt/(5.+wt*5),2));  //check by yzy, different
								else w=1;
								sigma +=dt*dt;
							}
							nus1++;
							if(w==1)  nus++;
							c[0] = kvx[i]*w/0.2998;
							c[1] = kvy[i]*w/0.2998;
							c[2] = 0.;
							//  c[2] =  kvz[i]*w/0.2998; /
							c[3] = 1.*w;
							for(k=0;k<4;k++){
								for(j=0;j<4;j++) a[j][k] +=c[j]*c[k];
								b[k] += (kvtp[i]-alpha*dr+dirn*kvz[i]/0.2998)*w*c[k];
							}
						}//if
					}//for nhit_pnoise
					//solve the equation/

					recFlag=-99;
					if(nus1<4){recFlag=recFlag+100;break;}//  event bad!/
					TDecompSVD svd(a);///a* r =b
					Bool_t ok;
					r = svd.Solve(b,ok);
					if(!ok) {recFlag=recFlag+200;break;}// NO!/
					if((r[0]*r[0]+r[1]*r[1])>1){  //~12%/
						printf(" ConicalFit >1: iter=%d Nhit=%d %lf %lf %lf tp=%lf %lf %lf\n",iter,nus,r[0],r[1],r[3],trig_t0,d_l,d_m);
						recFlag=recFlag+1000;
						Flag=0.5;
						/* break;*/
					}
					if(ok){
						Flag=1;
						sigma =sqrt(sigma/(nhit_pnoise-3.));
						dirl=r[0];
						dirm=r[1];
						dirn=sqrt(1-(r[0]*r[0]+r[1]*r[1]));
					}
					double dir_resolution=100;
					dir_resolution=acos((dirl*d_l)+(dirm*d_m)+(dirn*d_n))/3.1415926*180;
					if (dir_resolution<0.001&&dir_resolution>-0.001)
					{
						//					if(nhit_pnoise/nus<1.8&&nus>3&&iiter<90)break;
						if(nus>=1&&nhit_pnoise/nus<1.8&&nus>3&&iiter<50&&iiter>3)break;  //changed by yzy
						if(wt>2){wt=1;}
						wt=wt+1;
						iiter=0;
						for_iiter=for_iiter+1;
						if(for_iiter>10){break;}
					}
					d_l=dirl;
					d_m=dirm;
					d_n=dirn;

				}/////////////////////////////////for iiter
				/*get the direction*/
				phi = -10.;  the = -10.;
				r[0]=dirl;
				r[1]=dirm;
				dt = r[0]*r[0] + r[1]*r[1];
				cout<<" for_iiter="<<for_iiter<<"wt= "<<wt<<" r[0]="<<r[0]<<" dirl=  "<<dirl<<"r[1]="<<r[1]<<" dirm= "<<dirm<<endl;

				if(Flag>0. && dt<=1. && dt>=0.){
					cout<<"Good"<<endl;
					the = asin(sqrt(dt));
					phi = atan2(r[1],r[0]);
					phi = phi -3.1415926;
					if(phi<0.) phi += 3.1415926*2.;


					d_theta=the/3.1415926*180.;
					d_phi=phi/3.1415926*180.;
					d_nhit=nus;
					d_nhit1=nus1;
					ch2_sigma=sigma;
					for(int i=0;i<100;i++){
						if(d_phi>360.){
							d_phi=d_phi-360.;
							if(d_phi>=-0.01&&d_phi<360.1){break;}
						}

					}
					cout<<"////////////"<<endl;
					cout<<" the== "<<the/3.1415926*180.<<" phi== "<<phi/3.1415926*180.<<" ch2_sigma=="<<ch2_sigma<<endl;
					cout<<" nus== "<<nus<<"   iiter== "<<iiter<<" nhit_pnoise==  "<<nhit_pnoise<<endl;
					cout<<"///////////"<<endl;
					cout<<"///////////"<<endl;
			}
		}//for mj

		/*problem   nus<4  &  sigma>400     rate==620/5342.~12%*--->ConicalFit >1: */
		if (d_theta<0.1){  //befor change
//		if (d_theta<0.1||(dir_flag>0&&d_theta<1.5))  //changed by yzy
//			d_theta=30.; //added by yzy
//			dir_flag=dir_flag+100; //added by yzy
			for (int i=0;i<nhit_pfilter;i++){
				if(cf_q[i]>2.&&cf_q[i]<2500){
					htp10->Fill(cf_x[i],cf_y[i],cf_t[i]/3.3356);
					//htp11->Fill(cf_x[i],cf_y[i],cf_t[i]/3.3356);
					iii=iii+1;
				}

			}

			nhit_pfilter=iii;
			Double_t pf_cosT=cos(theta_first/180*3.1415926);
			ff10->SetParameter(0,theta_first*3.1415926/180.);
			ff10->SetParameter(1,phi_first*1./180*3.1415926);
			ff10->SetParameter(7,time_core/3.3356);
			ff10->SetParameter(6,0.025);
			ff10->SetParLimits(6,0.025,0.025);//cone angle ~0~9degree
			ff10->SetParameter(2,core_x);
			ff10->SetParLimits(2,core_x,core_x);
			ff10->SetParameter(3,core_y);
			ff10->SetParLimits(3,core_y,core_y);
			ff10->SetParameter(5,pf_cosT);
			ff10->SetParLimits(5,pf_cosT,pf_cosT);
			htp10->Fit("ff10","QWM");
			ff10->GetParameters(ff10_par);
			l_z=0;m_z=0;n_z=0;
			l_z=sin(1.*ff10_par[0])*cos(1.*ff10_par[1]);
			m_z=sin(1.*ff10_par[0])*sin(1.*ff10_par[1]);
			n_z=cos(1.*ff10_par[0]);
			if (n_z<0){l_z=l_z*(-1.);m_z=m_z*(-1.);n_z=n_z*(-1.);}
			cout<<"check  phi  "<<l_z<<" "<<m_z<<"  "<<n_z<<endl;

			/*theta*/
			zt_theta=acos(n_z/1.)/3.1415926*180.;
			if(zt_theta>90){zt_theta=180-abs(zt_theta);}
			/*phi*/
			zt_phi=atan(1.*m_z/l_z)/3.1415926*180.;
			if(l_z>0)  zt_phi=zt_phi+180.;

			if(zt_phi>360.) zt_phi=zt_phi-360;
			if(zt_phi<0.) zt_phi=zt_phi+360;


			d_theta=zt_theta;
			d_phi=zt_phi;


		}



		/*delta angle*/
		Double_t zTheta_odd=0,zPhi_odd=0,dirl_odd=0,dirm_odd=0,dirn_odd=0;
		Double_t zTheta_even=0,zPhi_even=0,dirl_even=0,dirm_even=0,dirn_even=0;


		zTheta_even=d_theta/180.*3.14159;
		zPhi_even=d_phi/180.*3.14159;

		dirl_odd=sin(zTheta_odd)*cos(zPhi_odd);
		dirm_odd=sin(zTheta_odd)*sin(zPhi_odd);
		dirn_odd=cos(zTheta_odd);



		dirl_even=sin(zTheta_even)*cos(zPhi_even);
		dirm_even=sin(zTheta_even)*sin(zPhi_even);
		dirn_even=cos(zTheta_even);
		Double_t direction_Resolution=0;

		direction_Resolution=acos((dirl_odd*dirl_even)+(dirm_odd*dirm_even)+(dirn_odd*dirn_even))/3.1415926*180;

		cout<<"  "<< zTheta_odd<<"  "<<zTheta_even<<" "<<zPhi_odd<<"  "<<zPhi_even<<" "<<direction_Resolution<<endl;




		for (int zi=0;zi<Nn;zi++)
		{
			s[zi].kvx=0;
			s[zi].kvy=0;
			s[zi].kvz=0;
			s[zi].kvq=0;
		}
		/*you can get a new shower  with filter   l^2+m^2+n^2==1 */
		Double_t zTheta=d_theta/180.*3.14159, zPhi=d_phi/180.*3.14159;

		dirl=sin(zTheta)*cos(zPhi);
		dirm=sin(zTheta)*sin(zPhi);
		dirn=cos(zTheta);

		Double_t dx,dy,dz;
		nnhit=0;
		for (int i=0;i<3000;i++){
			kvx[i]=0;
			kvy[i]=0;
			kvq[i]=0;
			skvx[i]=0;
			skvy[i]=0;
			skvq[i]=0;
		}

		for (int i=0;i<nhit_pnoise;i++){

			dx = sskvx[i]-top50_x;
			dy = sskvy[i]-top50_y;
			dq[nnhit] =sskvq[i];
			dz = 0;
			dr[nnhit] = sqrt(dx*dx+dy*dy+dz*dz-pow(dx*dirl+dy*dirm,2.));

			kvx[nnhit]=sskvx[i];
			kvy[nnhit]=sskvy[i];
			kvz[nnhit]=0;
			kvq[nnhit]=sskvq[i];

			skvx[nnhit]=sskvx[i];
			skvy[nnhit]=sskvy[i];
			skvz[nnhit]=0;
			skvq[nnhit]=sskvq[i];
			skvigcell[nnhit]=sskvigcell[i];

			nnhit=nnhit+1;

		}
		for (int zi=0;zi<nnhit;zi++)
		{
			s[zi].kvq=kvq[zi];
			s[zi].kvx=kvx[zi];
			s[zi].kvy=kvy[zi];
			s[zi].kvz=kvz[zi];
			s[zi].kvigcell=kvigcell[zi];
		}
		sort(s,s+Nn,comp);


		/*you  can add  equal  core && core resolution  by even & odd!*/
		sm_R=0;
		/*by even*/
		_ksx=0.;
		_ksy=0.;
		_ksz=0.;
		_ksq=0.;
		for (int zi=0;zi<nnhit;zi++)//rec top 2~150
		{
			if(int(s[zi].kvigcell)%2==0){

				if (xc*xc>=yc*yc){sm_R=75-abs(xc);}     //equal  core   start!
				else {sm_R=75-abs(yc);}
				Double_t     R11=sqrt((s[zi].kvx-xc)*(s[zi].kvx-xc)+(s[zi].kvy-yc)*(s[zi].kvy-yc));
				if (s[zi].kvq>=1&&R11<=sm_R) {
					_ksx += s[zi].kvx*pow(s[zi].kvq,2);
					_ksy += s[zi].kvy*pow(s[zi].kvq,2);
					_ksz += s[zi].kvz*pow(s[zi].kvq,2);
					_ksq += pow(s[zi].kvq,2);
				}
			}
		}
		even_x=_ksx/_ksq;even_y = _ksy/_ksq;
		/*by odd*/
		_ksx=0.;
		_ksy=0.;
		_ksz=0.;
		_ksq=0.;
		for (int zi=0;zi<nnhit;zi++)//rec top 2~150
		{
			if(int(s[zi].kvigcell)%2==1){

				if (xc*xc>=yc*yc){sm_R=75-abs(xc);}     //equal  core   start!
				else {sm_R=75-abs(yc);}
				Double_t     R11=sqrt((s[zi].kvx-xc)*(s[zi].kvx-xc)+(s[zi].kvy-yc)*(s[zi].kvy-yc));
				if (s[zi].kvq>=1&&R11<=sm_R) {
					_ksx += s[zi].kvx*pow(s[zi].kvq,2);
					_ksy += s[zi].kvy*pow(s[zi].kvq,2);
					_ksz += s[zi].kvz*pow(s[zi].kvq,2);
					_ksq += pow(s[zi].kvq,2);
				}
			}
		}

		odd_x=_ksx/_ksq;odd_y = _ksy/_ksq;
		/*you  can Rec Energy*/
		npmt10=0;
		npmt20=0;
		npmt30=0;
		npmt40out=0;
		npmtall=0;
		kN30=0;
		for (int i=0;i<nnhit;i++)
		{
			Double_t discore=dr[i];
			clustering_rq=dr[i]*kvq[i]+clustering_rq;
			clustering_q=kvq[i]+clustering_q;
			discore=sqrt(pow(kvx[i]-core_x_check,2)+pow(kvy[i]-core_y_check,2));
			/*if(core_y_check-top50_y==0)cout<<core_y_check<<" "<<top50_y<<"  "<<endl;*/
			if (discore<=10){kN10 +=kvq[i];npmt10=npmt10+1;}
			if (discore<=20){kN20 +=kvq[i];npmt20=npmt20+1;}
			if (discore<=30){kN30 +=kvq[i];npmt30=npmt30+1;}
			if (discore>=40){kN40out +=kvq[i];npmt40out=npmt40out+1;}
			if (discore<=300){kNall +=kvq[i];npmtall=npmtall+1;}
		} //cout<<"kN10=="<<kN10<<" kN20=="<<kN20<<" kN30=="<<kN30<<" kNall=="<<kNall<<endl;

		clustering=1.*clustering_rq/clustering_q;


		for (int i=0;i<nnhit;i++)
		{

			skdcore[i]=dr[i];

		}

		for (int szi=0;szi<nnhit;szi++)//2->1
		{
			ss[szi].skdcore=skdcore[szi];
			ss[szi].skvq=skvq[szi];
			ss[szi].skvx=skvx[szi];
			ss[szi].skvy=skvy[szi];
			ss[szi].skvz=skvz[szi];
			ss[szi].skvigcell=skvigcell[szi];

		}
		sort(ss,ss+sNn,scomp);

		N_secCore2=0;
		N_secCore4=0;
		N_secCore6=0;
		N_secCore8=0;
		N_secCore10=0;
		for (int szi=10;szi<sNn;szi++)
		{

			Double_t average4=0.25*(ss[szi-2].skvq+ss[szi-1].skvq+ss[szi+1].skvq+ss[szi+2].skvq);
			if (0.5*ss[szi].skvq>=average4){N_secCore2=N_secCore2+1;}
			if (0.25*ss[szi].skvq>=average4){N_secCore4=N_secCore4+1;}
			if (ss[szi].skvq>=6*average4){N_secCore6=N_secCore6+1;}
			if (0.125*ss[szi].skvq>=average4){N_secCore8=N_secCore8+1;}
			if (0.1*ss[szi].skvq>=average4){N_secCore10=N_secCore10+1;}
			if (szi>(nnhit-10)){break;}
		}

		cout<<" nhit= "<<nhit<<"    N_secCore2=="<<N_secCore2<<"      N_secCore4=="<<N_secCore4<<"      N_secCore10=="<<N_secCore10<<endl;


		N_Top50rate=0;
		N_Top10rate=0;
		for(int zi=0;zi<=nnhit;zi++)
		{
			Double_t rate_R=sqrt((s[zi].kvx-core_x_check)*(s[zi].kvx-core_x_check)+(s[zi].kvy-core_y_check)*(s[zi].kvy-core_y_check));
			if (zi<10&&rate_R<=25) {N_Top10rate=N_Top10rate+1;}
			if (rate_R<=25){N_Top50rate=N_Top50rate+1;}
			if (s[zi].kvq<=0){break;}
		}

		cout<<"  N_Top50rate= "<<N_Top50rate<<" N_Top10rate="<<N_Top10rate<<endl;

		/*cout<<"NKG  start"<<endl;*/
		evrec[0]=nhit;
		evrec[1]=nhit_no_ap;   //filter  afterpluse
		evrec[2]=nhit_pnoise;  //plane fit  5 sigma
		evrec[3]=nhit_pfilter; //cone fit 2.5sigma
		evrec[4]=theta_first;
		evrec[5]=phi_first;
		evrec[6]=c_theta;
		evrec[7]=c_phi;
		evrec[8]=cone_factor;

		evrec[9]=top50_z;
		evrec[10]=top50_x;
		evrec[11]=top50_y;
		evrec[12]=kN10;
		evrec[13]=kN20;
		evrec[14]=kN30;
		evrec[15]=kNall;
		evrec[16]=kN40out;
		evrec[17]=N_Top10rate;
		evrec[18]=N_Top50rate;
		evrec[19]=MaxX;
		evrec[20]=MaxY;
		evrec[21]=MaxQ;
		evrec[22]=npmt10;
		evrec[23]=npmt20;
		evrec[24]=npmt30;
		evrec[25]=npmtall;
		evrec[26]=npmt40out;
		evrec[27]=N_secCore2;
		evrec[28]=N_secCore4;
		evrec[29]=N_secCore6;
		evrec[30]=N_secCore8;
		evrec[31]=N_secCore10;
		evrec[32]=k_nfit;//plantfit  
		evrec[33]=vcore_like[4];  //x 
		evrec[34]=vcore_like[6];//y
		evrec[35]=vcore_like[0];//s
		evrec[36]=vcore_like[2];//Ne
		evrec[37]=l_z;

		evrec[38]=m_z;
		evrec[39]=n_z;
		evrec[40]=zChi2;
		evrec[41]=NHIT;//NDF
		evrec[42]=t_par[0];
		evrec[43]=t_par[1];
		evrec[44]=even_x;
		evrec[45]=even_y;
		evrec[46]=odd_x;
		evrec[47]=odd_y;
		evrec[48]=direction_Resolution;
		evrec[49]=tp_trig;
		evrec[50]=sort_tp_trig;
		evrec[51]=clustering;
		evrec[52]=Q1;
		evrec[53]=Q2;
		//evrec[54]=core_dis;//the dis zham & zzk
		evrec[55]=iter;//iter1 num
		evrec[56]=d_theta;
		evrec[57]=d_phi;
		evrec[58]=d_nhit;//w==1 num
		evrec[60]=core_x_check;//iter  1
		evrec[61]=core_y_check;//iter  1
		evrec[62]=iter2;//iter2 num
		evrec[63]=ch2_sigma;//ch2 d_direction
		evrec[64]=d_nhit1;
		evrec[65]=iiter;
		evrec[66]=recFlag;
		evrec[67]=wt;
		evrec[68]=for_iiter;
		evrec[69]=SUM;

		/*gStyle->SetOptStat(0);
		  TCanvas *c1= new TCanvas("c1","c1",600,600);
		  c1->Divide(1,1);
		  c1->cd(1);gPad->Clear(); gPad->SetLogz();
		  pos2->Draw("COLZ");
		  TLine *l111 =new TLine(top50_x,top50_y-8,top50_x,top50_y+8);
		  l111->SetLineWidth(8);
		  l111->SetLineColor(kRed);
		  l111->Draw("same");

		  TLine *l211 =new TLine(top50_x-8,top50_y,top50_x+8,top50_y);
		  l211->SetLineColor(kRed);
		  l211->SetLineWidth(8);
		  l211->Draw("same");

		  TLine *l11110 =new TLine(core_x_check,core_y_check-15,core_x_check,core_y_check+15);
		  l11110->SetLineWidth(8);
		  l11110->SetLineColor(kBlack);
		  l11110->Draw("same");

		  TLine *l21110 =new TLine(core_x_check-15,core_y_check,core_x_check+15,core_y_check);
		  l21110->SetLineColor(kBlack);
		  l21110->SetLineWidth(6);
		  l21110->Draw("same");

		  TLine *lz111 =new TLine(xc_old,yc_old-8,xc_old,yc_old+8);
		  lz111->SetLineWidth(8);
		  lz111->SetLineColor(kGreen);
		  lz111->Draw("same");

		  TLine *lz211 =new TLine(xc_old-8,yc_old,xc_old+8,yc_old);
		  lz211->SetLineColor(kGreen);
		  lz211->SetLineWidth(8);
		  lz211->Draw("same");

		  pos2->GetXaxis()->SetTitle("x (m)");
		  pos2->GetXaxis()->CenterTitle();
		  pos2->GetYaxis()->CenterTitle();
		  pos2->GetYaxis()->SetTitle("y (m)");
		  pos2->GetYaxis()->SetTitleOffset(0.8);

		  pos2->GetZaxis()->SetRangeUser(0.001,200);


		  TLine *l1 =new TLine(-45,-75,-45,75);
		  TLine *l2 =new TLine(-15,-75,-15,75);
		  TLine *l3 =new TLine(15,-75,15,75);
		  TLine *l4 =new TLine(45,-75,45,75);

		  TLine *l5 =new TLine(-75,-45,75,-45);
		  TLine *l6 =new TLine(-75,-15,75,-15);
		  TLine *l7 =new TLine(-75,15,75,15);
		  TLine *l8 =new TLine(-75,45,75,45);

		  l1->Draw();l1->SetLineStyle(3);l1->SetLineColor(1);l1->SetLineWidth(2);
		  l2->Draw();l2->SetLineStyle(3);l2->SetLineColor(1);l2->SetLineWidth(2);
		  l3->Draw();l3->SetLineStyle(3);l3->SetLineColor(1);l3->SetLineWidth(2);
		  l4->Draw();l4->SetLineStyle(3);l4->SetLineColor(1);l4->SetLineWidth(2);
		  l5->Draw();l5->SetLineStyle(3);l5->SetLineColor(1);l5->SetLineWidth(2);
		  l6->Draw();l6->SetLineStyle(3);l6->SetLineColor(1);l6->SetLineWidth(2);
		  l7->Draw();l7->SetLineStyle(3);l7->SetLineColor(1);l7->SetLineWidth(2);
		  l8->Draw();l8->SetLineStyle(3);l8->SetLineColor(1);l8->SetLineWidth(2);
		  c1->SaveAs(Form("core_dis==%0.1lf_nhit%d_shower.pdf",core_dis,nhit));}

*/

		//*********inint**
		for (int zi=0;zi<Nn;zi++)
		{
			s[zi].kvx=0;
			s[zi].kvy=0;
			s[zi].kvz=0;
			s[zi].kvq=0;
			s[zi].kvigcell=-1;
		}

		for (int zi=0;zi<tNn;zi++)
		{
			ts[zi].kvx=0;
			ts[zi].kvy=0;
			ts[zi].kvz=0;
			ts[zi].kvq=0;
			ts[zi].kvtp=0;
			ts[zi].kvigcell=-1;
		}


		for (int szi=0;szi<sNn;szi++)
		{
			ss[szi].skdcore=0;
			ss[szi].skvx=0;
			ss[szi].skvy=0;
			ss[szi].skvz=0;
			ss[szi].skvq=0;
		}

		kN10=0;
		kN20=0;
		kN30=0;
		kN40out=0;
		kNall=0;

		nhit_no_ap=0;nhit_pfilter=0;nhit_pnoise=0;
		p_theta=0;p_phi=0;c_theta=0;c_phi=0;cone_factor=0;//  error now!nhit=0,nnhit=0;
		d_theta=0;d_phi=0;d_nhit=0;d_nhit1=0;

		npmt10=0;
		npmt20=0;
		npmt30=0;
		npmt40out=0;
		npmtall=0;

		top50_x=0;
		top50_y=0;
		top50_z=0;
		SUM=0;

		N_Top50rate=0;
		N_Top10rate=0;
		MaxX=0;
		MaxY=0;
		MaxQ=0;
		N_secCore2=0;
		N_secCore4=0;
		N_secCore6=0;
		N_secCore8=0;
		N_secCore10=0;

		clustering_q=0;
		clustering_rq=0;
		clustering=0;
		delete ctemp;
		//delete pos2;
		delete htp1;
		delete http;
		delete ff; 
		delete htp10;
		//delete htp11;
		delete ff10;
		//delete ff101; 
		delete g;
		///////////////////////////////////////////
		//    wcda  Reconstruction    ending     //
		///////////////////////////////////////////
}


//}

