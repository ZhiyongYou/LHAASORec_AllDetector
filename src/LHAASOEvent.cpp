#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "TMath.h"
#include "LHAASOEvent.h"

using namespace std;

ClassImp(LHAASOEvent);
LHAASOEvent* LHAASOEvent::_Head=0;
TTree* LHAASOEvent::_Tree=0;
const char* LHAASOEvent::_Name="LHAASOEvent";
TBranch* LHAASOEvent::bAll=0;

LHAASOEvent::LHAASOEvent():TObject()
{
	//iSipm.resize(MAXPMT);
	//SipmPe.resize(MAXPMT);
	//SipmT.resize(MAXPMT);
	isipm.resize(MAXPMT);
	sipmpe.resize(MAXPMT);
	sipmt.resize(MAXPMT);
	sipmbase.resize(MAXPMT);
	sipmbaserms.resize(MAXPMT);
	cellig.resize(WCDASIZE);
	cellpe.resize(WCDASIZE);
	cellt.resize(WCDASIZE);
	hitid.resize(KM2ASIZE);
	hitpart.resize(KM2ASIZE);
	hitt.resize(KM2ASIZE);
	hitmode.resize(KM2ASIZE);

}

LHAASOEvent::~LHAASOEvent()
{

}

void LHAASOEvent::EventInitial()
{
	for(int i=0;i<6;i++)
	{
		rbTime[i]=0;
		rbtime[i]=0;
		status[i]=-1;
		telTrigger[i] = 0;
	}
	rabbitTime=0;
	rabbittime=0;
	//iSipm.clear();
	//SipmPe.clear();
	//SipmT.clear();
	isipm.clear();
	sipmpe.clear();
	sipmt.clear();
	sipmbase.clear();
	sipmbaserms.clear();
	//wcda
	IsWcdaEvent=0;
	deltaTwcda=-10000;
	nhitplus=0;
	iwcdaevt=0;
	cellig.clear();
	cellpe.clear();
	cellt.clear();
	//km2a
	IsKm2aEvent=0;
	deltaTkm2a=-10000;
	hitid.clear();
	hitpart.clear();
	hitt.clear();
	hitmode.clear();
	km2a_mjd=0;
	km2a_xc=-10000;
	km2a_yc=-10000;
	km2a_phi=-10000;
	km2a_theta=-10000;
}

void LHAASOEvent::WcdaInitial()
{
	//wcda
	IsWcdaEvent=0;
	deltaTwcda=-10000;
	nhitplus=0;
	iwcdaevt=0;
	cellig.clear();
	cellpe.clear();
	cellt.clear();
}
void LHAASOEvent::Km2aInitial()
{
	//km2a
	IsKm2aEvent=0;
	deltaTkm2a=-10000;
	hitid.clear();
	hitpart.clear();
	hitt.clear();
	hitmode.clear();
	km2a_mjd=0;
	km2a_xc=-10000;
	km2a_yc=-10000;
	km2a_phi=-10000;
	km2a_theta=-10000;
}


void LHAASOEvent::SetWFCTAEvent(int tel, 
		long long Rb_Time,
		double Rb_time,
		long long rb_Time, 
		double rb_time, 
		long long dt, 
		std::vector<int> &sipm, 
		std::vector<double> &sipmPe, 
		std::vector<double> &sipmT,
		std::vector<int> sipmBase,
		std::vector<int> sipmBaserms)
{
	int ISIPM=0;
	rbTime[tel-1] = Rb_Time;//single tel Time
	rbtime[tel-1] = Rb_time;//single tel time
	rabbitTime = rb_Time;//event Time
	rabbittime = rb_time;//event time
	for(int ii=0;ii<sipm.size();ii++)
	{
		ISIPM = (tel-1)*1024 + sipm.at(ii);
		isipm.push_back(ISIPM);
		sipmpe.push_back(sipmPe.at(ii));
		sipmt.push_back(sipmT.at(ii)+dt);
		sipmbase.push_back(sipmBase.at(ii));
		sipmbaserms.push_back(sipmBaserms.at(ii));
	}
}

void LHAASOEvent::SetWCDAEvent(int iswcdaevent, 
		int Nhitplus,
		double DeltaTwcda,
		long long dt,
		ULong64_t Iwcdaevt, 
		std::vector<int> &cellIg, 
		std::vector<double> &cellPe, 
		std::vector<double> &cellT)
{
	IsWcdaEvent = iswcdaevent;
	nhitplus = Nhitplus;
	deltaTwcda = DeltaTwcda+dt;
	iwcdaevt = Iwcdaevt;
	for(int ii=0;ii<cellIg.size();ii++)
	{
		cellig.push_back(cellIg.at(ii));
		cellpe.push_back(cellPe.at(ii));
		cellt.push_back(cellT.at(ii));
	}
}

void LHAASOEvent::SetKM2AEvent(	int iskm2aevent, 
		float km2a_Mjd,
		double DeltaTkm2a,
		long long dt,
		float km2a_Xc, 
		float km2a_Yc, 
		float km2a_Phi, 
		float km2a_Theta, 
		std::vector<int> &hitId, 
		std::vector<double> &hitPart, 
		std::vector<double> &hitT, 
		std::vector<int> &hitMode)
{
	IsKm2aEvent = iskm2aevent;
	km2a_mjd = km2a_Mjd;
	deltaTkm2a = DeltaTkm2a+dt;
	km2a_xc = km2a_Xc;
	km2a_yc = km2a_Yc;
	km2a_phi = km2a_Phi;
	km2a_theta = km2a_Theta;
	for(int ii=0;ii<hitId.size();ii++)
	{
		hitid.push_back(hitId.at(ii));
		hitpart.push_back(hitPart.at(ii));
		hitt.push_back(hitT.at(ii));
		hitmode.push_back(hitMode.at(ii));
	}
}


void LHAASOEvent::SetTriggerTel(int tel, int trig)
{
	telTrigger[tel-1] = trig;
}
void LHAASOEvent::SetSlcStatus(int tel,int slc_status)
{
	status[tel-1] = slc_status;
}

int LHAASOEvent::goodWeather()
{
	int weather=0;
	for(int i=0;i<6;i++)
	{
		weather += (status[i]%100)/10;
	}
	if(6==weather)
		return 1;
	else
		return 0;
}













