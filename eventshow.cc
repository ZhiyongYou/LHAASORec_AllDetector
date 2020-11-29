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
#include "WCDAMcEvent.h"
#include "WCDAEventRec.h"
#include "WCDARec.h"
#include "LHAASOEventShow.h"
#include "LHAASOEventRec.h"

LHAASOEventShow* lhaasoeventshow = new LHAASOEventShow();
LHAASOEventRec* lhaasorec = new LHAASOEventRec();

void DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist);
double DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi);
void DrawEventShowMap(LHAASOEventShow* lhaaso_event_show);

int main(int argc, char *argv[])
{
	time_t t0 = time(0);
	std::cout<< "begin: "<<t0 << std::endl;
	DrawEventShowMap(lhaasoeventshow);

	char Name1[300]="root://eos01.ihep.ac.cn/";
	char infilename[300];
	strcpy(infilename,Name1);
	strcat(infilename,argv[1]);
	TFile *infile = TFile::Open(infilename);
	//TFile *infile = TFile::Open(argv[1]);
	if(!infile) {
		printf("%s does not exist\n",argv[1]);
		return 0;
	}
	if(infile->IsZombie()||infile->GetEND()<50) {
		printf("%s file error!!\n",argv[1]);
		infile->Close();
		return 0;
	}

	TTree *cosmic_tree = (TTree *)infile->Get("event");
	if(cosmic_tree==nullptr) {
		printf("%s is null file\n",argv[1]);
		infile->Close();
		return 0;
	}
	std::cout << argv[1] << " read succeed" << std::endl;

	LHAASOEvent *lhaaso_evt = new LHAASOEvent();
	WCDAEventRec *wcdarecevent = new WCDAEventRec();
	int RawTel[20];
	cosmic_tree->SetBranchAddress("LHAASOEvent", &lhaaso_evt);
	cosmic_tree->SetBranchAddress("WCDAEventRec", &wcdarecevent);
	cosmic_tree->SetBranchAddress("RawTel", RawTel);
	long n_cosmics = cosmic_tree->GetEntries();
	std::cout << "All Events: " << n_cosmics <<std::endl;


	double evrec[70];
	LHEvent* km2aevent = new LHEvent();
	LHRecEvent* km2arec = new LHRecEvent();
	WFCTARec* wfctarec = new WFCTARec();
	WCDARec* wcdarec = new WCDARec();
	//wcdarec->SetWaterEff();
	wcdarec->SetWaterEff(argv[3]);

	double wcda_nhit_sm;
	double wcdaMaxPe;

	int MainTel;
	int Npix;
	double Size;
	double MeanAzi, MeanZen;
	double MeanX, MeanY;
	double Length, Width;
	double SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W;
	double Rp;
	double DeltaW;
	double SourceMiss_W;
	double SourceMiss_K;

	int tel1=6;
	int tel2=5;

	long drawRbT = 1579957671;
	double drawRbt = 156001600;
	//loop events
	int km2a_array=5;
	for(int iEntry=0;iEntry<n_cosmics;iEntry++)
	{
		//if(iEntry!=10727) continue;
		cosmic_tree->GetEntry(iEntry);
		//if(!(lhaaso_evt->rabbitTime==drawRbT && lhaaso_evt->rabbittime==drawRbt))	continue;
		//if(iEntry!=61470)	continue;  //20202250
		//if(iEntry!=40719)	continue;  //20202250
		//if(iEntry!=9914)	continue;  //20202050
		//if(iEntry!=11956)	continue;  //20202330
		//if(iEntry!=26615)	continue;  //20202020
		//if(iEntry!=66452)	continue;  //20202020
		//if(!(RawTel[tel1-1]!=0&&RawTel[tel2-1]!=0)){continue;}
		//if(RawTel[tel1-1]==0){continue;}

		//km2a rec///////////////////////////////////////////////////////
		if(lhaaso_evt->IsKm2aEvent!=0)
		{
			km2aevent->Initcsz();
			double hitsize = lhaaso_evt->hitid.size();
			for(int j=0; j<hitsize; j++){
				int id = lhaaso_evt->hitid[j];
				double t = lhaaso_evt->hitt[j];
				double pe = lhaaso_evt->hitpart[j];
				int mode = lhaaso_evt->hitmode[j];
				if(mode==0) { km2aevent->AddHitE(id,t,pe,0); }
				else if(mode==1) { km2aevent->AddHitM(id,t,pe,0); }
			}
			G4KM2A_Reconstruction::GetInstance(km2a_array)->eventrecline(km2aevent,km2arec);
		}
		double corex_km2a = -km2arec->rec_y;
		double corey_km2a = km2arec->rec_x;
		double rec_sourcezen_km2a = km2arec->rec_theta;
		double rec_sourceazi_km2a = ( km2arec->rec_phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->rec_phi-90*TMath::DegToRad() : km2arec->rec_phi+270*TMath::DegToRad();

		//wcda calc
		for(int i=0;i<70;i++)
		{
			evrec[i] = -1000;
		}
		//lhaasorec->WCDACalc();
		std::vector<double> wcda_clean_x;
		std::vector<double> wcda_clean_y;
		std::vector<double> wcda_clean_pe;
		std::vector<int> wcda_clean_ig;
		std::vector<double> wcda_clean_t;
		printf("wcda rec ---------------------------------------------------------------------------------------------------------->\n");
		if(lhaaso_evt->IsWcdaEvent)
		{
			//wcdarec new class
			TCanvas *c_wcda = new TCanvas("c_wcda", "c_wcda", 800,800);  //the lastest canvas, fits in wcdarec will draw on this canvas
			wcdarec->Init();
			wcdarec->SetWCDAEvent(lhaaso_evt->cellig,lhaaso_evt->cellpe,lhaaso_evt->cellt);
			wcdarec->AfterPulseClean();
			wcdarec->TimeResidualClean();
			wcdarec->CoreReconstruction();
			wcdarec->DirectionReconstruction();
			wcdarec->OddAndEven();
			wcdarec->RecEnergy();
			wcdarec->GetRecResult(evrec);
			wcdarec->GetHits(wcda_clean_x, wcda_clean_y, wcda_clean_pe, wcda_clean_ig, wcda_clean_t);
			wcda_nhit_sm = lhaaso_evt->nhitplus;
			wcdaMaxPe = wcdarec->GetMaxPe();
			delete c_wcda;
			/*
			//use info from zhm
			evrec[1] = wcdarecevent->nhit;
			evrec[10] = wcdarecevent->xc1 / 100;
			evrec[11] = wcdarecevent->yc1 / 100;
			evrec[15] = wcdarecevent->npec;
			evrec[57] = wcdarecevent->azic;
			evrec[56] = wcdarecevent->zenc;
			*/
//			DealWCDAEvent(lhaaso_evt->cellig,lhaaso_evt->cellpe,lhaaso_evt->cellt, wcda_clean_x,wcda_clean_y,wcda_clean_pe,wcda_clean_ig,wcda_clean_t,evrec);
		}
		printf("wcda rec <==========================================================================================================\n");

		//wfcta calc
		wfctarec->SetWFCTAEvent(lhaaso_evt->isipm, lhaaso_evt->sipmpe, lhaaso_evt->sipmt);
		wfctarec->TimeClean(100);
		wfctarec->IslandClean();
		wfctarec->CalcMainTel(4);
		wfctarec->GetEventMapOnFocus(wfctarec->GetMainTel(), corex_km2a, corey_km2a, rec_sourceazi_km2a, rec_sourcezen_km2a);
		wfctarec->MergeEvent();
		//wfctarec->GroupClean();
		//wfctarec->IslandClean();
		wfctarec->CalcHillas();
		wfctarec->CalcSDP();

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
		double SDP_GLine_X_km2a = wfctarec->GetSDP_GLine_X_km2a();
		double SDP_GLine_Y_km2a = wfctarec->GetSDP_GLine_Y_km2a();
		double SDP_G_Angle_K = TMath::ATan2(SDP_GLine_Y_km2a, SDP_GLine_X_km2a);
		int TriggerTel_Num = wfctarec->GetTriggerTel_Num();
		//if(Npix<80||Npix>200)
		//	continue;

		

		Rp=-1000;
		DeltaW = -1000;
		SourceMiss_W = -1000;
		SourceMiss_K = -1000;
		double ar_zen_w = -1000;
		double ar_azi_w = -1000;
		double dist_core2line = 0;
		if(lhaaso_evt->IsWcdaEvent!=0)
		{
			double tel_x, tel_y;
			WFCTAMap::Instance()->GetTelXY(MainTel, tel_x, tel_y);

			double corex_w = evrec[10];
			double corey_w = evrec[11];
			double wcda_ang=29.36;//deg
			double wcda1_cen_x=-47.50;//m
			double wcda1_cen_y=-80;//m
			//turn core from wcda to lhaaso coordinate
			double DCoreX = corex_w*cos(wcda_ang*TMath::DegToRad()) - corey_w*sin(wcda_ang*TMath::DegToRad()) + wcda1_cen_x;
			double DCoreY = corex_w*sin(wcda_ang*TMath::DegToRad()) + corey_w*cos(wcda_ang*TMath::DegToRad()) + wcda1_cen_y;

			double azi = evrec[57]+29.36;
			double zen = evrec[56];
			ar_zen_w = zen;
			ar_azi_w = azi - 360*round(azi/360);
			double DSourceZen = ar_zen_w*TMath::DegToRad();
			double DSourceAzi = ar_azi_w*TMath::DegToRad();
			Rp = DistPointToLine(DCoreX, DCoreY, tel_x, tel_y, DSourceZen, DSourceAzi);

			double tel_x_w, tel_y_w;
			WFCTAMap::Instance()->GetTelXYinWCDA1(MainTel, tel_x_w, tel_y_w);
			DistPointToLine(corex_w, corey_w, tel_x_w, tel_y_w, SDP_GLine_X_wcda, SDP_GLine_Y_wcda, dist_core2line);
			DeltaW = asin( dist_core2line / sqrt(pow(tel_x_w-corex_w,2)+pow(tel_y_w-corey_w,2)) );

			SourceMiss_W = lhaasorec->GetSourceMiss(MainTel, MeanX, MeanY, wfctarec->GetDelta(), DSourceZen, DSourceAzi);
		}

		double RpK=-1000;
		double DeltaK = -1000;
		double Dist_K = -1000;
		double Dist_Core2line_K = -1000;
		double sourcezen_km2a;
		double sourceazi_km2a;
		if(lhaaso_evt->IsKm2aEvent!=0)
		{
			double tel_x, tel_y;
			WFCTAMap::Instance()->GetTelXY(MainTel, tel_x, tel_y);
			double corex_k = -km2arec->rec_y;
			double corey_k = km2arec->rec_x;
			sourcezen_km2a = km2arec->rec_theta;
			sourceazi_km2a = ( km2arec->rec_phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->rec_phi-90*TMath::DegToRad() : km2arec->rec_phi+270*TMath::DegToRad();
			RpK = DistPointToLine(corex_k,corey_k, tel_x,tel_y, sourcezen_km2a,sourceazi_km2a);

			double dist_core2line = 0;
			DistPointToLine(corex_k, corey_k, tel_x, tel_y, SDP_GLine_X_km2a, SDP_GLine_Y_km2a, dist_core2line);
			DeltaK = asin( dist_core2line / sqrt(pow(tel_x-corex_k,2)+pow(tel_y-corey_k,2)) );
			Dist_Core2line_K = dist_core2line;

			double km2a_DeltaX = corex_k - tel_x;
			double km2a_DeltaY = corey_k - tel_y;
			double Core_Tel_Angle_K = TMath::ATan2(km2a_DeltaY, km2a_DeltaX);

			SourceMiss_K = lhaasorec->GetSourceMiss(MainTel, MeanX, MeanY, wfctarec->GetDelta(), sourcezen_km2a, sourceazi_km2a);

			//Dist_K = TMath::DegToRad()*AngleDistInSphericalCoordinates(MeanAzi, MeanZen, sourceazi_km2a, sourcezen_km2a);//input:rad    return:deg
		}

		int do_flag=0;
		/*
		if(!(Npix>40&&evrec[25]>300
				&&SDP_G_Angle_W*57.3>10&&SDP_G_Angle_W*57.3<80&&Rp>50&&Rp<150
				&&abs(evrec[10])<60&&abs(evrec[11])<60&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
				&&lhaaso_evt->nhitplus>3&&Length/Width>1.4&&wcdaMaxPe>4000))
		{continue;}
		*/
		//if(!(lhaaso_evt->IsKm2aEvent!=0&&Npix>40&&(SDP_G_Angle_W*57.3>120||SDP_G_Angle_W*57.3<-20)
		//			&&RpK>50&&RpK<150&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
		//			&&Length/Width>3&&Length/Width<10&&km2arec->NfiltE>20&&DeltaK*57.3>10))
		//if(!(lhaaso_evt->IsKm2aEvent!=0&&Npix>40&&(SDP_G_Angle_W*57.3>120||SDP_G_Angle_W*57.3<-30)
		//			&&RpK>50&&RpK<150&&abs(MeanY*57.3)<5&&abs(MeanX*57.3)<5&&MeanAzi*57.3>20&&MeanAzi*57.3<165
		//			&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&DeltaK*57.3>6&&km2arec->NpE1/km2arec->NpE2>3))  //WFCTA和KM2A判断都是好事例，但是不知道为什么delta就是很差
		/*
		if(lhaaso_evt->IsKm2aEvent!=0&&Npix>40&&(SDP_G_Angle_W*57.3>120||SDP_G_Angle_W*57.3<-30)
					&&RpK>50&&RpK<150&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
					&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3&&DeltaK*57.3>6&&TriggerTel_Num>1)  //KM2A判断都好事例，但是WFCTA重建不好
					//&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3))  //KM2A判断都好事例，但是WFCTA重建不好
		{	do_flag=1;}
		*/
		/*
		if(!(lhaaso_evt->IsWcdaEvent!=0&&Npix>50&&Npix<1000&&evrec[25]>500&&lhaaso_evt->nhitplus>3
				&&SDP_G_Angle_W*57.3>10&&SDP_G_Angle_W*57.3<80&&Rp>30&&Rp<150
				&&abs(evrec[10])<60&&abs(evrec[11])<60&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
				&&Length/Width>1.4&&wcdaMaxPe>4000 && DeltaW*57.3<1))
		{	continue;}
		*/

		if(lhaaso_evt->IsKm2aEvent!=0&&Npix>50&&(SDP_G_Angle_W*57.3>120||SDP_G_Angle_W*57.3<-30)
					&&RpK>50&&RpK<150&&abs(MeanY*57.3)<6&&MeanAzi*57.3>20&&MeanAzi*57.3<165
					&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3&&DeltaK*57.3<2)  //KM2A判断都好事例，但是WFCTA重建不好
					//&&Length/Width>2&&Length/Width<10&&km2arec->NfiltE>20&&km2arec->NpE1/km2arec->NpE2>3))  //KM2A判断都好事例，但是WFCTA重建不好
		{	do_flag=1;}
		if(!do_flag)
			continue;

		std::vector<int> clean_sipm;
		std::vector<double> clean_pe;
		std::vector<double> clean_t;
		//wfctarec->GetCleanImage(clean_sipm, clean_pe, clean_t);
		wfctarec->GetRawImage(clean_sipm, clean_pe, clean_t);
		std::vector<int> clean_focus_sipm;
		std::vector<double> clean_focus_pe;
		std::vector<double> clean_focus_x;
		std::vector<double> clean_focus_y;
		//wfctarec->GetCleanImageOnFocus(MainTel, clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
		wfctarec->GetRawImageOnFocus(MainTel, clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
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
			if(lhaaso_evt->telTrigger[i]!=0)
				v_triggerTel.push_back(i+1);
		}

		lhaasoeventshow->SetCosmicInfo(lhaaso_evt->rabbitTime, lhaaso_evt->rabbittime, 0, "test", v_triggerTel);
		lhaasoeventshow->SetWFCTAInfo(MainTel, Size, Npix, MeanX, MeanY, MeanAzi, MeanZen, Length, Width, DDelta, 
				SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W, SDP_GLine_X_wcda, SDP_GLine_Y_wcda, SDP_G_Angle_W, SDP_GLine_X_km2a, SDP_GLine_Y_km2a, SDP_G_Angle_K);
		lhaasoeventshow->SetWCDAInfo(evrec[15], int(evrec[1]), evrec[10], evrec[11], Rp, ar_azi_w*TMath::DegToRad(), ar_zen_w*TMath::DegToRad(), DeltaW, SourceMiss_W, dist_core2line);
		lhaasoeventshow->SetKM2AInfo(km2arec->NfiltE, km2arec->NpE1, km2arec->NfiltM, km2arec->NuM1, corex_km2a, corey_km2a, RpK, sourceazi_km2a, sourcezen_km2a, DeltaK, SourceMiss_K, Dist_Core2line_K);

		lhaasoeventshow->DrawWFCTA(clean_sipm, clean_pe, clean_t);
		lhaasoeventshow->DrawWCDA(wcda_clean_x, wcda_clean_y, wcda_clean_pe);
		lhaasoeventshow->DrawKM2AEvent(*km2aevent,"clean");
		lhaasoeventshow->DrawCoreKm2a(corex_km2a, corey_km2a);
		lhaasoeventshow->DrawSG_Line_Km2a(MainTel, wfctarec->GetSDP_GLine_X_km2a(), wfctarec->GetSDP_GLine_Y_km2a());
		lhaasoeventshow->DrawWFCTA_F(clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
		lhaasoeventshow->DrawEventAlongSDP(slice_coords, slice_pe, slice_pix);

		lhaasoeventshow->DrawEventInfo(0);

		lhaasoeventshow->lhaasocanvas->Print(Form("%s/cosmicTime_%ld+%.9lf_iEntry_%d.lhaaso.pdf(", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry),"pdf");
		lhaasoeventshow->wcdacanvas->Print(Form("%s/cosmicTime_%ld+%.9lf_iEntry_%d.lhaaso.pdf", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry),"pdf");
		lhaasoeventshow->km2acanvas->Print(Form("%s/cosmicTime_%ld+%.9lf_iEntry_%d.lhaaso.pdf", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry),"pdf");
		lhaasoeventshow->wfctacanvas_focus->Print(Form("%s/cosmicTime_%ld+%.9lf_iEntry_%d.lhaaso.pdf)", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry),"pdf");

		lhaasoeventshow->wcdacanvas->SaveAs(Form("%s/wcda/cosmicTime_%ld+%.9lf_iEntry_%d.wcda.png", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry));
		lhaasoeventshow->wfctacanvas_focus->SaveAs(Form("%s/wfcta_focus/cosmicTime_%ld+%.9lf_iEntry_%d.wfcta_focus.png", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry));
		lhaasoeventshow->km2acanvas->SaveAs(Form("%s/km2a/cosmicTime_%ld+%.9lf_iEntry_%d.km2a.png", argv[2], lhaaso_evt->rabbitTime,lhaaso_evt->rabbittime/1000000000,iEntry));


	}

	delete lhaaso_evt;
	delete wcdarecevent;
	delete km2aevent;
	delete km2arec;
	delete wfctarec;
	delete lhaasoeventshow;
	delete lhaasorec;
	delete wcdarec;

	infile->Close();

	time_t t1 = time(0);
	std::cout<< "end: "<<t1 << std::endl;
	std::cout<< "used: "<< t1-t0<< std::endl;
	return 0;
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
