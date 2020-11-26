#include "astro.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "TFile.h"
#include "TTree.h"

#include "G4KM2A_Reconstruction.h"
#include "WFCTARec.h"
#include "CollectIntensity.h"
#include "WFCTAMap.h"
#include "astro.h"
#include "LHAASOEvent.h"
#include "LaserEvent.h"
#include "WFCTAMcEvent.h"
#include "WCDAMcEvent.h"
#include "WCDAEventRec.h"
#include "WCDARec.h"
#include "LHAASOEventShow.h"
#include "LHAASOEventRec.h"

LHAASOEventShow* lhaasoeventshow = new LHAASOEventShow();
LHAASOEventRec* lhaasorec = new LHAASOEventRec();


void FindRunandFile(char* filename, std::string& runnum, std::string& filenum);
void DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist);
double DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi);
double AngleDistInSphericalCoordinates(double azi0, double zen0, double azi1, double zen1);//input:rad    return:deg
void DrawEventShowMap(LHAASOEventShow* lhaaso_event_show);

int main(int argc, char *argv[])
{
	time_t t0 = time(0);
	std::cout<< "begin: "<<t0 << std::endl;
	DrawEventShowMap(lhaasoeventshow);

	char Name1[300]="root://eos01.ihep.ac.cn/";

	LHRecEvent* km2arec = new LHRecEvent();
	WFCTARec* wfctarec = new WFCTARec();
	LHAASOEventRec* lhaasorec = new LHAASOEventRec();

	int iEvent, iUse;
	double energy;
	int MainTel;
	int Npix;
	double Size;
	double MeanAzi, MeanZen;
	double MeanX, MeanY;
	double Length, Width;
	double SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W;
	double Core_Tel_Angle_W;
	double SourceMiss_W;
	double SDP_GLine_X_km2a, SDP_GLine_Y_km2a, SDP_G_Angle_K;
	double Core_Tel_Angle_K;
	double SourceMiss_K;
	double RpW;
	double DeltaW;
	double Dist_Core2line_W;
	double DCorexW;
	double DCoreyW;
	double RpK;
	double DeltaK;
	double Dist_Core2line_K;
	double Dist_W;
	double Dist_K;
	int TriggerTel_Num;

	int tel1=6;
	int tel2=4;


	printf("Begin Rec ...\n");
	std::ifstream infilelist;
	infilelist.open(argv[1]);
	while(infilelist.good())
	{
		char sTemp[500];
		infilelist.getline(sTemp,500);
		char infilename[500];
		int i = sscanf(sTemp,"%s", &infilename);
		if(i<=0){continue;}

		std::string runnum;
		std::string filenum;
		FindRunandFile(infilename, runnum,filenum);
		//read in root file
		char infilename_xrootd[500];
		strcpy(infilename_xrootd,Name1);
		strcat(infilename_xrootd,infilename);
		TFile *infile = TFile::Open(infilename_xrootd);
		//TFile *infile = TFile::Open(argv[1]);
		if(!infile) {	printf("%s does not exist\n",infilename);	continue;	}
		if(infile->IsZombie()||infile->GetEND()<50) {	printf("%s file error!!\n",infilename);	infile->Close();	continue;	}

		TTree *cosmic_tree = (TTree *)infile->Get("Tree");
		if(cosmic_tree==nullptr) {	printf("%s is null file\n",infilename);	infile->Close();	continue;	}
		std::cout << infilename << " read succeed" << std::endl;

		WFCTAMcEvent* wfctamc_evt = new WFCTAMcEvent();
		LHEvent* km2a_evt = new LHEvent();
		cosmic_tree->SetBranchAddress("km2a", &km2a_evt);
		cosmic_tree->SetBranchAddress("wfcta", &wfctamc_evt);
		long n_cosmics = cosmic_tree->GetEntries();
		std::cout << "All Events: " << n_cosmics <<std::endl;

		//loop events
		int km2a_array=5;
		for(int iEntry=0;iEntry<n_cosmics;iEntry++)
		{
			cosmic_tree->GetEntry(iEntry);
			//printf("ientry:%d\n",iEntry);
			//std::cerr<< "ientry: "<< iEntry<< std::endl;
			//raw info
			iEvent = wfctamc_evt->iEvent;
			iUse = wfctamc_evt->iUse;
			energy = wfctamc_evt->energy;
			//if(!(10000==iEvent&&10==iUse))	continue;

			//km2a rec///////////////////////////////////////////////////////
			{
				G4KM2A_Reconstruction::GetInstance(km2a_array)->eventrecline(km2a_evt,km2arec);
			}
			double corex_km2a = -km2arec->rec_y;
			double corey_km2a = km2arec->rec_x;

			//wfcta rec//////////////////////////////////////////////////////
			//set events
			std::vector<int> isipm; isipm.clear();
			std::vector<double> sipmpe; sipmpe.clear();
			std::vector<double> sipmt; sipmt.clear();
			for(int ii=0; ii<wfctamc_evt->TubeID.size(); ii++)
			{
				isipm.push_back( wfctamc_evt->TubeID.at(ii) );
				sipmpe.push_back( wfctamc_evt->TubeSignalInTriggerWindow.at(ii) );
				sipmt.push_back( wfctamc_evt->TubeTriggerTime.at(ii) * 20 );
			}
			wfctarec->SetWFCTAMcEvent(isipm, sipmpe, sipmt);
			//rec
			wfctarec->TimeClean(100);
			wfctarec->IslandClean();
			wfctarec->CalcMainTel(1);
			//          //wfctarec->GroupClean();
			double prim_sourcezen_km2a = km2arec->theta;
			double prim_sourceazi_km2a = ( km2arec->phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->phi-90*TMath::DegToRad() : km2arec->phi+270*TMath::DegToRad();
			wfctarec->GetEventMapOnFocus(wfctarec->GetMainTel(), -km2arec->corey, km2arec->corex, prim_sourceazi_km2a, prim_sourcezen_km2a);
			wfctarec->MergeEvent();
			wfctarec->CalcHillas();
			wfctarec->CalcSDP();
			//wfctarec->GetEventMapOnFocus( wfctarec->GetMainTel() );

			MainTel = wfctarec->GetMainTel();
			Npix = wfctarec->GetNpix();
			Size = wfctarec->GetSize();
			MeanAzi = wfctarec->GetMeanAzi();
			MeanZen = wfctarec->GetMeanZen();
			MeanX = wfctarec->GetMeanX();
			MeanY = wfctarec->GetMeanY();
			Length = wfctarec->GetLength();
			Width = wfctarec->GetWidth();
			double DDelta = wfctarec->GetDelta();
			SDP_GLine_X_wcda = wfctarec->GetSDP_GLine_X_wcda();
			SDP_GLine_Y_wcda = wfctarec->GetSDP_GLine_Y_wcda();
			SDP_G_Angle_W = TMath::ATan2(SDP_GLine_Y_wcda, SDP_GLine_X_wcda);
			SDP_GLine_X_km2a = wfctarec->GetSDP_GLine_X_km2a();
			SDP_GLine_Y_km2a = wfctarec->GetSDP_GLine_Y_km2a();
			SDP_G_Angle_K = TMath::ATan2(SDP_GLine_Y_km2a, SDP_GLine_X_km2a);
			TriggerTel_Num = wfctarec->GetTriggerTel_Num();

			//combine rec///////////////////////////////////////////////////////////
			RpW=-1000;
			DeltaW = -1000;
			Dist_W = -1000;
			Dist_Core2line_W = -1000;
			SourceMiss_W = -1000;
			SourceMiss_K = -1000;
			DCorexW = -1000;
			DCoreyW = -1000;

			RpK=-1000;
			DeltaK = -1000;
			Dist_K = -1000;
			Dist_Core2line_K = -1000;
			double sourcezen_km2a;
			double sourceazi_km2a;
			double raw_sourcezen_km2a;
			double raw_sourceazi_km2a;
			//wfcta&km2a combine rec
			{
				double tel_x, tel_y;
				WFCTAMap::Instance()->GetTelXY(MainTel, tel_x, tel_y);
				//double corex_k = -km2arec->rec_y;
				//double corey_k = km2arec->rec_x;
				double corex_k = -km2arec->corey;
				double corey_k = km2arec->corex;
				//sourcezen_km2a = km2arec->rec_theta;
				//sourceazi_km2a = ( km2arec->rec_phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->rec_phi-90*TMath::DegToRad() : km2arec->rec_phi+270*TMath::DegToRad();
				sourcezen_km2a = km2arec->theta;
				sourceazi_km2a = ( km2arec->phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->phi-90*TMath::DegToRad() : km2arec->phi+270*TMath::DegToRad();
				raw_sourcezen_km2a = km2arec->theta;
				raw_sourceazi_km2a = ( km2arec->phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->phi-90*TMath::DegToRad() : km2arec->phi+270*TMath::DegToRad();
				RpK = DistPointToLine(corex_k,corey_k, tel_x,tel_y, sourcezen_km2a,sourceazi_km2a);

				double dist_core2line = 0;
				DistPointToLine(corex_k, corey_k, tel_x, tel_y, SDP_GLine_X_km2a, SDP_GLine_Y_km2a, dist_core2line);
				DeltaK = asin( dist_core2line / sqrt(pow(tel_x-corex_k,2)+pow(tel_y-corey_k,2)) );
				Dist_Core2line_K = dist_core2line;

				double km2a_DeltaX = corex_k - tel_x;
				double km2a_DeltaY = corey_k - tel_y;
				Core_Tel_Angle_K = TMath::ATan2(km2a_DeltaY, km2a_DeltaX);

				SourceMiss_K = lhaasorec->GetSourceMiss(MainTel, MeanX, MeanY, wfctarec->GetDelta(), sourcezen_km2a, sourceazi_km2a);

				Dist_K = TMath::DegToRad()*AngleDistInSphericalCoordinates(MeanAzi, MeanZen, sourceazi_km2a, sourcezen_km2a);//input:rad    return:deg
			}

			int do_flag=0;
			if(Npix>30&&km2arec->NpE2>30&&(km2arec->corex<1.3*km2arec->corey-310.||km2arec->corex<-1.*(1./2)*km2arec->corey-175.)
					&&sqrt(pow((-1*km2arec->corey+86),2)+pow((km2arec->corex+180),2))>50
					&&sqrt(pow((-1*km2arec->corey+86),2)+pow((km2arec->corex+180),2))<160&&Npix>30&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165&&Length/Width>2&&DeltaK*57.3>10)
			{
				do_flag=1;
			}
			/*
			if(Npix>50&&(SDP_G_Angle_W*57.3>120||SDP_G_Angle_W*57.3<-30)
					&&RpK>50&&RpK<150&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
					&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3&&TriggerTel_Num>1)  //KM2A判断都好事例，但是WFCTA重建不好
				//&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3))  //KM2A判断都好事例，但是WFCTA重建不好
			{   do_flag=1;}
			*/
			//if(!do_flag)
			//	continue;

			/*
			//temp get clean image on 1# telescope
			wfctarec->SetWFCTAMcEvent(isipm, sipmpe, sipmt);
			//rec
			wfctarec->TimeClean(100);
			wfctarec->IslandClean();
			wfctarec->CalcMainTel(1);
			//          //wfctarec->GroupClean();
			wfctarec->CalcHillas();
			wfctarec->CalcSDP();
			*/

			std::vector<int> clean_sipm;
			std::vector<double> clean_pe;
			std::vector<double> clean_t;
			wfctarec->GetCleanImage(clean_sipm, clean_pe, clean_t);
			//wfctarec->GetRawImage(clean_sipm, clean_pe, clean_t);
			std::vector<int> clean_focus_sipm;
			std::vector<double> clean_focus_pe;
			std::vector<double> clean_focus_x;
			std::vector<double> clean_focus_y;
			//wfctarec->GetCleanImageOnFocus(1, clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
			wfctarec->GetCleanImageOnFocus(MainTel, clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
			//wfctarec->GetRawImageOnFocus(MainTel, clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
			std::vector<int> sipm_isipm;
			std::vector<double> sipm_pe;
			std::vector<double> sipm_t;
			std::vector<double> sipm_coords;
			std::vector<double> slice_pe;
			std::vector<double> slice_t;
			std::vector<int> slice_pix;
			std::vector<double> slice_coords;
			wfctarec->GetCoordsOnSDP(sipm_isipm, sipm_pe, sipm_t, sipm_coords, slice_pe, slice_t, slice_pix, slice_coords);

			std::vector<int> v_triggerTel;
			v_triggerTel.clear();
			for(int i=0;i<6;i++){
				if(wfctamc_evt->TelTrigger[i]!=0)
					v_triggerTel.push_back(i+1);
			}

			lhaasoeventshow->SetCosmicInfo(wfctamc_evt->iEvent, wfctamc_evt->iUse, 0, "test", v_triggerTel);
			lhaasoeventshow->SetWFCTAInfo(MainTel, Size, Npix, MeanX, MeanY, MeanAzi, MeanZen, Length, Width, DDelta,
					SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W, SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W, SDP_GLine_X_km2a, SDP_GLine_Y_km2a, SDP_G_Angle_K);
			//lhaasoeventshow->SetWCDAInfo(evrec[15], int(evrec[1]), evrec[10], evrec[11], Rp, ar_azi_w*TMath::DegToRad(), ar_zen_w*TMath::DegToRad(), DeltaW, SourceMiss_W, dist_core2line);
			//lhaasoeventshow->SetKM2AInfo(km2arec->NfiltE, km2arec->NpE1, km2arec->NfiltM, km2arec->NuM1, corex_km2a, corey_km2a, RpK, sourceazi_km2a, sourcezen_km2a, DeltaK, SourceMiss_K, Dist_Core2line_K);
			lhaasoeventshow->SetKM2AInfo(km2arec->NfiltE, km2arec->NpE1, km2arec->NfiltM, km2arec->NuM1, -km2arec->corey, km2arec->corex, RpK, raw_sourceazi_km2a, raw_sourcezen_km2a, DeltaK, SourceMiss_K, Dist_Core2line_K);

			lhaasoeventshow->DrawWFCTA(clean_sipm, clean_pe, clean_t);
			//lhaasoeventshow->DrawWCDA(wcda_clean_x, wcda_clean_y, wcda_clean_pe);
			lhaasoeventshow->DrawKM2AEvent(*km2a_evt,"clean");
			lhaasoeventshow->DrawCoreKm2a(corex_km2a, corey_km2a);
			lhaasoeventshow->DrawSG_Line_Km2a(MainTel, wfctarec->GetSDP_GLine_X_km2a(), wfctarec->GetSDP_GLine_Y_km2a());
			lhaasoeventshow->DrawWFCTA_F(clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
			lhaasoeventshow->DrawEventAlongSDP(slice_coords, slice_pe, slice_pix);

			lhaasoeventshow->DrawEventInfo(0);
			lhaasoeventshow->lhaasocanvas->Print(Form("%s/%s_%s_iEvent_%d+%d_iEntry_%d.lhaaso.pdf(", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry),"pdf");
			//lhaasoeventshow->wcdacanvas->Print(Form("%s/%s_%s_iEvent_%ld+%.9lf_iEntry_%d.lhaaso.pdf", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry),"pdf");
			lhaasoeventshow->km2acanvas->Print(Form("%s/%s_%s_iEvent_%d+%d_iEntry_%d.lhaaso.pdf", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry),"pdf");
			lhaasoeventshow->wfctacanvas_focus->Print(Form("%s/%s_%s_iEvent_%d+%d_iEntry_%d.lhaaso.pdf)", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry),"pdf");

			//lhaasoeventshow->wcdacanvas->SaveAs(Form("%s/wcda/%s_%s_iEvent_%d+%d_iEntry_%d.wcda.png", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry));
			lhaasoeventshow->wfctacanvas_focus->SaveAs(Form("%s/wfcta_focus/%s_%s_iEvent_%d+%d_iEntry_%d.wfcta_focus.png", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry));
			lhaasoeventshow->km2acanvas->SaveAs(Form("%s/km2a/%s_%s_iEvent_%d+%d_iEntry_%d.km2a.png", argv[2], runnum.c_str(), filenum.c_str(), wfctamc_evt->iEvent,wfctamc_evt->iUse,iEntry));

		}
		delete wfctamc_evt;
		delete km2a_evt;
		infile->Close();
	}
	printf("Rec Finished\n");



	delete km2arec;
	delete wfctarec;
	delete lhaasorec;

	time_t t1 = time(0);
	std::cout<< "end: "<<t1 << std::endl;
	std::cout<< "used: "<< t1-t0<< std::endl;
	return 0;
}

void FindRunandFile(char* filename, std::string& runnum, std::string& filenum)
{
	std::string s_filename = filename;
	size_t posrunnum = s_filename.find("/run", 0);
	size_t posfilenum = s_filename.find("wfcta-km2a", 0);
	runnum = s_filename.substr(posrunnum+1,6);
	filenum = s_filename.substr(posfilenum,16);
	//printf("%s %s\n",runnum.c_str(), filenum.c_str());
}

void DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist)
{
	double k = v_y / v_x;
	double b = p_y0 - k*p_x0;
	dist = abs(k*p_x-p_y+b) / sqrt(1+pow(k,2));
}

double DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi)
{
	int i;
	double dx,dy,u[3],v[3];
	double L,rp,temp,psi;
	dx=corex-telx;
	dy=corey-tely;
	u[0]=sin(zen)*cos(azi);
	u[1]=sin(zen)*sin(azi);
	u[2]=cos(zen);
	L=sqrt(dx*dx+dy*dy);
	v[0]=dx/L; v[1]=dy/L; v[2]=0.;
	temp=0.;
	for(i=0;i<3;i++) temp +=-(u[i]*v[i]);
	psi=acos(temp);
	rp=L*sin(psi);
	return rp;
}

double AngleDistInSphericalCoordinates(double azi0, double zen0, double azi1, double zen1)//input:rad    return:deg
{
	double m0,n0,l0;
	double m1,n1,l1;

	m0 = sin(zen0)*cos(azi0);
	n0 = sin(zen0)*sin(azi0);
	l0 = cos(zen0);
	m1 = sin(zen1)*cos(azi1);
	n1 = sin(zen1)*sin(azi1);
	l1 = cos(zen1);
	double Mod0=sqrt(m0*m0+n0*n0+l0*l0);
	double Mod1=sqrt(m1*m1+n1*n1+l1*l1);

	double delta = (m0*m1+n0*n1+l0*l1)/(Mod0*Mod1);
	if(delta>1) delta = 1;
	if(delta<-1) delta = -1;
	delta = acos(delta)*TMath::RadToDeg();
	//printf("delta::::::::%.3lf\n",delta);
	return delta;
	//return sqrt((azi0-azi1)*(azi0-azi1)+(zen0-zen1)*(zen0-zen1));
}

void DrawEventShowMap(LHAASOEventShow* lhaaso_event_show)
{
	//draw wfcta map
	lhaaso_event_show->DrawWFCTAMap();
	//set wcda map
	Double_t big1_pmtx_igcell[900];
	Double_t big1_pmty_igcell[900];
	Double_t big1_pmtz_igcell[900];
#include "big1posconf.h"
	lhaaso_event_show->SetWCDAMap(big1_pmtx_igcell,big1_pmty_igcell,big1_pmtz_igcell);
	//draw km2a map
	Double_t ed_x[3600]={0};
	Double_t ed_y[3600]={0};
	Double_t ed_z[3600]={0};
	Double_t md_x[1800]={0};
	Double_t md_y[1800]={0};
	Double_t md_z[1800]={0};
	FILE *km2a_map_fp;
	int edid,mdid;
	double edx,edy,edz,mdx,mdy,mdz;
	km2a_map_fp = fopen("/workfs/ybj/youzhiyong/LHAASO/EventShow/WFCTAEvtShow/include/ED_pos_half.txt","r");
	fscanf(km2a_map_fp,"Rotation -30 deg zeroZ 4400");
	while(!feof(km2a_map_fp)) {
		fscanf(km2a_map_fp,"%d %lf %lf %lf\n",&edid,&edx,&edy,&edz);
		ed_x[edid] = edx;
		ed_y[edid] = edy;
		ed_z[edid] = edz;
	}
	fclose(km2a_map_fp);
	km2a_map_fp = fopen("/workfs/ybj/youzhiyong/LHAASO/EventShow/WFCTAEvtShow/include/MD_pos_half.txt","r");
	fscanf(km2a_map_fp,"zeroZ 4400");
	while(!feof(km2a_map_fp)) {
		fscanf(km2a_map_fp,"%d %lf %lf %lf\n",&mdid,&mdx,&mdy,&mdz);
		if(mdid==0){break;}
		md_x[mdid] = mdx;
		md_y[mdid] = mdy;
		md_z[mdid] = mdz;
	}
	fclose(km2a_map_fp);
	lhaaso_event_show->SetKM2AMap(ed_x,ed_y,ed_z,md_x,md_y,md_z);
	lhaaso_event_show->DrawKM2AMap();
	//draw wfcta focus map
	lhaaso_event_show->DrawWFCTAFocusMap();
}
