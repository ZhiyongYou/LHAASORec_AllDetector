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
#include "LHAASOEventRec.h"

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

int main(int argc, char *argv[])
{
	time_t t0 = time(0);
	std::cout<< "begin: "<<t0 << std::endl;
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


	//	   LHAASORecEvent* lhaasorecevent= new LHAASORecEvent();
	double evrec[70];
	double wcdaMaxPe;

	LHEvent* km2aevent = new LHEvent();
	LHRecEvent* km2arec = new LHRecEvent();
	WFCTARec* wfctarec = new WFCTARec();
	WCDARec* wcdarec = new WCDARec();
	wcdarec->SetWaterEff(argv[3]);
	LHAASOEventRec* lhaasorec = new LHAASOEventRec();

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
	int RecordTel_Num;
	char outfilename[300];
	strcpy(outfilename,Name1);
	strcat(outfilename,argv[2]);
	//TFile *infile = TFile::Open(argv[1]);
	TFile *rootfile = TFile::Open(outfilename,"recreate");
	TTree *recevent = new TTree("recevent","recevent Tree");
	recevent->Branch("rabbitTime",&lhaaso_evt->rabbitTime);
	recevent->Branch("rabbittime",&lhaaso_evt->rabbittime);
	recevent->Branch("IsWcdaEvent",&lhaaso_evt->IsWcdaEvent);
	recevent->Branch("IsKm2aEvent",&lhaaso_evt->IsKm2aEvent);
	recevent->Branch("nhitplus",&lhaaso_evt->nhitplus);
	//recevent->Branch("LHAASORecEvent", &lhaasorecevent);
	//recevent->Branch("WCDAEventRec", &wcdarecevent);
	recevent->Branch("KM2ARec", &km2arec);
	recevent->Branch("RawTel",RawTel,"RawTel[6]/I");
	recevent->Branch("evrec",evrec,"evrec[70]/D");
	recevent->Branch("wcdaMaxPe",&wcdaMaxPe,"wcdaMaxPe/D");

	recevent->Branch("MainTel", &MainTel, "MainTel/I");
	recevent->Branch("Npix", &Npix, "Npix/I");
	recevent->Branch("Size", &Size, "Size/D");
	recevent->Branch("MeanZen", &MeanZen, "MeanZen/D");
	recevent->Branch("MeanAzi", &MeanAzi, "MeanAzi/D");
	recevent->Branch("MeanX", &MeanX, "MeanX/D");
	recevent->Branch("MeanY", &MeanY, "MeanY/D");
	recevent->Branch("Length", &Length, "Length/D");
	recevent->Branch("Width", &Width, "Width/D");
	recevent->Branch("SDP_GLine_X_wcda", &SDP_GLine_X_wcda, "SDP_GLine_X_wcda/D");
	recevent->Branch("SDP_GLine_Y_wcda", &SDP_GLine_Y_wcda, "SDP_GLine_Y_wcda/D");
	recevent->Branch("SDP_G_Angle_W", &SDP_G_Angle_W, "SDP_G_Angle_W/D");
	recevent->Branch("Core_Tel_Angle_W", &Core_Tel_Angle_W, "Core_Tel_Angle_W/D");
	recevent->Branch("SDP_GLine_X_km2a", &SDP_GLine_X_km2a, "SDP_GLine_X_km2a/D");
	recevent->Branch("SDP_GLine_Y_km2a", &SDP_GLine_Y_km2a, "SDP_GLine_Y_km2a/D");
	recevent->Branch("SDP_G_Angle_K", &SDP_G_Angle_K, "SDP_G_Angle_K/D");
	recevent->Branch("Core_Tel_Angle_K", &Core_Tel_Angle_K, "Core_Tel_Angle_K/D");
	recevent->Branch("RpW", &RpW, "RpW/D");
	recevent->Branch("DeltaW", &DeltaW, "DeltaW/D");
	recevent->Branch("Dist_Core2line_W", &Dist_Core2line_W, "Dist_Core2line_W/D");
	recevent->Branch("SourceMiss_W", &SourceMiss_W, "SourceMiss_W/D");
	recevent->Branch("DCorexW", &DCorexW, "DCorexW/D");
	recevent->Branch("DCoreyW", &DCoreyW, "DCoreyW/D");
	recevent->Branch("RpK", &RpK, "RpK/D");
	recevent->Branch("DeltaK", &DeltaK, "DeltaK/D");
	recevent->Branch("Dist_Core2line_K", &Dist_Core2line_K, "Dist_Core2line_K/D");
	recevent->Branch("SourceMiss_K", &SourceMiss_K, "SourceMiss_K/D");
	recevent->Branch("Dist_W", &Dist_W, "Dist_W/D");
	recevent->Branch("Dist_K", &Dist_K, "Dist_K/D");
	recevent->Branch("TriggerTel_Num", &TriggerTel_Num, "TriggerTel_Num/I");
	recevent->Branch("RecordTel_Num", &RecordTel_Num, "RecordTel_Num/I");

	int tel1=6;
	int tel2=4;

	//loop events
	int km2a_array=5;
	for(int iEntry=0;iEntry<n_cosmics;iEntry++)
	{
		cosmic_tree->GetEntry(iEntry);
		//if(!(RawTel[tel1-1]!=0&&RawTel[tel2-1]!=0)){continue;}
		//if(RawTel[tel1-1]==0){continue;}
		for(int i=0;i<70;i++)
		{
			evrec[i] = -1000;
		}
		printf("iSipm.size():%d\n",lhaaso_evt->isipm.size());
		printf("ientry:%d\n",iEntry);
		//std::cerr<< "ientry: "<< iEntry<< std::endl;

		//wcda rec///////////////////////////////////////////////////////
		std::vector<double> wcda_clean_x;
		std::vector<double> wcda_clean_y;
		std::vector<double> wcda_clean_pe;
		std::vector<int> wcda_clean_ig;
		std::vector<double> wcda_clean_t;
		printf("wcda rec ---------------------------------------------------------------------------------------------------------->\n");
		if(lhaaso_evt->IsWcdaEvent)
		{
			//wcdarec new class
			wcdarec->Init();
			wcdarec->SetWCDAEvent(lhaaso_evt->cellig,lhaaso_evt->cellpe,lhaaso_evt->cellt);
			wcdarec->AfterPulseClean();
			wcdarec->TimeResidualClean();
			wcdarec->CoreReconstruction();
			wcdarec->DirectionReconstruction();
			wcdarec->OddAndEven();
			wcdarec->RecEnergy();
			wcdarec->GetRecResult(evrec);
			wcdaMaxPe = wcdarec->GetMaxPe();

			/*
			//use info from zhm
			evrec[1] = wcdarecevent->nhit;
			evrec[10] = wcdarecevent->xc1 / 100;
			evrec[11] = wcdarecevent->yc1 / 100;
			evrec[15] = wcdarecevent->npec;
			evrec[57] = wcdarecevent->azic;
			evrec[56] = wcdarecevent->zenc;
			*/
			//DealWCDAEvent(lhaaso_evt->cellig,lhaaso_evt->cellpe,lhaaso_evt->cellt, wcda_clean_x,wcda_clean_y,wcda_clean_pe,wcda_clean_ig,wcda_clean_t,evrec);
		}
		printf("wcda rec <==========================================================================================================\n");

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

		//wfcta rec//////////////////////////////////////////////////////
		//set events
		wfctarec->SetWFCTAEvent(lhaaso_evt->isipm, lhaaso_evt->sipmpe, lhaaso_evt->sipmt);
		wfctarec->TimeClean(100);
		wfctarec->IslandClean();
		wfctarec->CalcMainTel(5);
		wfctarec->MergeEvent();
		//wfctarec->GroupClean();
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
		SDP_GLine_X_wcda = wfctarec->GetSDP_GLine_X_wcda();
		SDP_GLine_Y_wcda = wfctarec->GetSDP_GLine_Y_wcda();
		SDP_G_Angle_W = TMath::ATan2(SDP_GLine_Y_wcda, SDP_GLine_X_wcda);
		SDP_GLine_X_km2a = wfctarec->GetSDP_GLine_X_km2a();
		SDP_GLine_Y_km2a = wfctarec->GetSDP_GLine_Y_km2a();
		SDP_G_Angle_K = TMath::ATan2(SDP_GLine_Y_km2a, SDP_GLine_X_km2a);
		TriggerTel_Num = wfctarec->GetTriggerTel_Num();
		RecordTel_Num=0;
		for(int i=0;i<20;i++)
		{
			RecordTel_Num += RawTel[i];
		}

		//combine rec///////////////////////////////////////////////////////////
		RpW=-1000;
		DeltaW = -1000;
		Dist_W = -1000;
		Dist_Core2line_W = -1000;
		SourceMiss_W = -1000;
		SourceMiss_K = -1000;
		DCorexW = -1000;
		DCoreyW = -1000;
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
			double ar_zen_w = zen;
			double ar_azi_w = azi - 360*round(azi/360);
			double DSourceZen = ar_zen_w*TMath::DegToRad();
			double DSourceAzi = ar_azi_w*TMath::DegToRad();
			RpW = DistPointToLine(DCoreX, DCoreY, tel_x, tel_y, DSourceZen, DSourceAzi);

			DCorexW = DCoreX;
			DCoreyW = DCoreY;
			double dist_core2line = 0;
			double tel_x_w, tel_y_w;
			WFCTAMap::Instance()->GetTelXYinWCDA1(MainTel, tel_x_w, tel_y_w);
			DistPointToLine(corex_w, corey_w, tel_x_w, tel_y_w, SDP_GLine_X_wcda, SDP_GLine_Y_wcda, dist_core2line);
			DeltaW = asin( dist_core2line / sqrt(pow(tel_x_w-corex_w,2)+pow(tel_y_w-corey_w,2)) );
			Dist_Core2line_W = dist_core2line;

			double wcda_DeltaX = corex_w - tel_x_w;
			double wcda_DeltaY = corey_w - tel_y_w;
			Core_Tel_Angle_W = TMath::ATan2(wcda_DeltaY, wcda_DeltaX);
			
			SourceMiss_W = lhaasorec->GetSourceMiss(MainTel, MeanX, MeanY, wfctarec->GetDelta(), DSourceZen, DSourceAzi);

			Dist_W = TMath::DegToRad()*AngleDistInSphericalCoordinates(MeanAzi, MeanZen, DSourceAzi, DSourceZen);//input:rad    return:deg
		}
		RpK=-1000;
		DeltaK = -1000;
		Dist_K = -1000;
		Dist_Core2line_K = -1000;
		if(lhaaso_evt->IsKm2aEvent!=0)
		{
			double tel_x, tel_y;
			WFCTAMap::Instance()->GetTelXY(MainTel, tel_x, tel_y);
			double corex_k = -km2arec->rec_y;
			double corey_k = km2arec->rec_x;
			double sourcezen = km2arec->rec_theta;
			double sourceazi = ( km2arec->rec_phi + 270*TMath::DegToRad() ) > 360*TMath::DegToRad() ? km2arec->rec_phi-90*TMath::DegToRad() : km2arec->rec_phi+270*TMath::DegToRad();
			RpK = DistPointToLine(corex_k,corey_k, tel_x,tel_y, sourcezen,sourceazi);

			double dist_core2line = 0;
			DistPointToLine(corex_k, corey_k, tel_x, tel_y, SDP_GLine_X_km2a, SDP_GLine_Y_km2a, dist_core2line);
			DeltaK = asin( dist_core2line / sqrt(pow(tel_x-corex_k,2)+pow(tel_y-corey_k,2)) );
			Dist_Core2line_K = dist_core2line;

			double km2a_DeltaX = corex_k - tel_x;
			double km2a_DeltaY = corey_k - tel_y;
			Core_Tel_Angle_K = TMath::ATan2(km2a_DeltaY, km2a_DeltaX);

			SourceMiss_K = lhaasorec->GetSourceMiss(MainTel, MeanX, MeanY, wfctarec->GetDelta(), sourcezen, sourceazi);

			Dist_K = TMath::DegToRad()*AngleDistInSphericalCoordinates(MeanAzi, MeanZen, sourceazi, sourcezen);//input:rad    return:deg
		}

		recevent->Fill();
		//		lhaasorecevent->EventInitial();

		printf("-----------------------------\n");
	}

	rootfile->cd();
	recevent->Write();
	rootfile->Close();
	delete lhaasorec;
	delete lhaaso_evt;
	delete wcdarecevent;
	//	delete lhaasorecevent;
	delete km2aevent;
	delete km2arec;
	delete wfctarec;
	delete wcdarec;

	infile->Close();

	time_t t1 = time(0);
	std::cout<< "end: "<<t1 << std::endl;
	std::cout<< "used: "<< t1-t0<< std::endl;
	return 0;
}

