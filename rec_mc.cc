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
#include "LHAASOEventRec.h"

void DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist);
double DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi);
double AngleDistInSphericalCoordinates(double azi0, double zen0, double azi1, double zen1);//input:rad    return:deg

int main(int argc, char *argv[])
{
	time_t t0 = time(0);
	std::cout<< "begin: "<<t0 << std::endl;

	char Name1[300]="root://eos01.ihep.ac.cn/";

	LHEvent* km2aevent = new LHEvent();
	LHRecEvent* km2arec = new LHRecEvent();
	WFCTARec* wfctarec = new WFCTARec();
	LHAASOEventRec* lhaasorec = new LHAASOEventRec();

	int iEvent, iUse;
	double energy;
	double Xmax;

	double pe_4255;
	double pe_5321;
	double pe_4604;
	double pe_5602;

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
	double DistanceToXmax_K;
	double DistSourceToMean_K;
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
	char outfilename[300];
	strcpy(outfilename,Name1);
	strcat(outfilename,argv[2]);
	TFile *rootfile = TFile::Open(outfilename,"recreate");
	TTree *recevent = new TTree("recevent","recevent Tree");
	recevent->Branch("iEvent", &iEvent, "iEvent/I");
	recevent->Branch("iUse", &iUse, "iUse/I");
	recevent->Branch("energy", &energy, "energy/D");
	recevent->Branch("Xmax", &Xmax, "Xmax/D");

	//ipm0:4255(152.153416,25.084607) sipm1:5321(152.151202,25.081988) distance:0.002783
	recevent->Branch("pe_4255", &pe_4255, "pe_4255/D");
	recevent->Branch("pe_5321", &pe_5321, "pe_5321/D");
	//sipm0:4604(146.581438,30.157750) sipm1:5602(146.580415,30.141740) distance:0.016018
	recevent->Branch("pe_4604", &pe_4604, "pe_4604/D");
	recevent->Branch("pe_5602", &pe_5602, "pe_5602/D");

	recevent->Branch("KM2ARec", &km2arec);

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
	recevent->Branch("DistanceToXmax_K", &DistanceToXmax_K, "DistanceToXmax_K/D");
	recevent->Branch("DistSourceToMean_K", &DistSourceToMean_K, "DistSourceToMean_K/D");
	recevent->Branch("Dist_W", &Dist_W, "Dist_W/D");
	recevent->Branch("Dist_K", &Dist_K, "Dist_K/D");
	recevent->Branch("TriggerTel_Num", &TriggerTel_Num, "TriggerTel_Num/I");

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
			Xmax = wfctamc_evt->Xmax;

			//km2a rec///////////////////////////////////////////////////////
			{
				G4KM2A_Reconstruction::GetInstance(km2a_array)->eventrecline(km2a_evt,km2arec);
			}

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

			// tube pe compare
			pe_4255 = 0;
			pe_5321 = 0;
			pe_4604 = 0;
			pe_5602 = 0;
			for(int ii=0; ii<wfctamc_evt->TubeID.size(); ii++)
			{
				if(4255==wfctamc_evt->TubeID.at(ii))
					pe_4255 = wfctamc_evt->TubeSignalInTriggerWindow.at(ii);
				if(5321==wfctamc_evt->TubeID.at(ii))
					pe_5321 = wfctamc_evt->TubeSignalInTriggerWindow.at(ii);
				if(4604==wfctamc_evt->TubeID.at(ii))
					pe_4604 = wfctamc_evt->TubeSignalInTriggerWindow.at(ii);
				if(5602==wfctamc_evt->TubeID.at(ii))
					pe_5602 = wfctamc_evt->TubeSignalInTriggerWindow.at(ii);
			}


			//combine rec///////////////////////////////////////////////////////////
			RpW=-1000;
			DeltaW = -1000;
			Dist_W = -1000;
			Dist_Core2line_W = -1000;
			SourceMiss_W = -1000;
			SourceMiss_K = -1000;
			DistanceToXmax_K = -1000;
			DistSourceToMean_K = -1000;
			DCorexW = -1000;
			DCoreyW = -1000;

			RpK=-1000;
			DeltaK = -1000;
			Dist_K = -1000;
			Dist_Core2line_K = -1000;
			//wfcta&km2a combine rec
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
				DistanceToXmax_K = lhaasorec->GetDistanceToXmax(MainTel, MeanZen, sourcezen, corex_k, corey_k);
				DistSourceToMean_K = lhaasorec->GetDistSourceToMean(MeanZen, MeanAzi, sourcezen, sourceazi);

				Dist_K = TMath::DegToRad()*AngleDistInSphericalCoordinates(MeanAzi, MeanZen, sourceazi, sourcezen);//input:rad    return:deg
			}

			recevent->Fill();

			//printf("-----------------------------\n");
		}
		delete wfctamc_evt;
		delete km2a_evt;
		infile->Close();
	}
	printf("Rec Finished\n");

	rootfile->cd();
	recevent->Write();
	rootfile->Close();


	delete km2aevent;
	delete km2arec;
	delete wfctarec;
	delete lhaasorec;

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
