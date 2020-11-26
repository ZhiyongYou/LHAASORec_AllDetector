#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "TMath.h"
#include "LaserEvent.h"

using namespace std;

ClassImp(LaserEvent);
LaserEvent* LaserEvent::_Head=0;
TTree* LaserEvent::_Tree=0;
const char* LaserEvent::_Name="LaserEvent";
TBranch* LaserEvent::bAll=0;
const int LaserEvent::MAXPMT=6144;

LaserEvent::LaserEvent():TObject()
{
	//iSipm.resize(MAXPMT);
	//SipmPe.resize(MAXPMT);
	//SipmT.resize(MAXPMT);
	isipm.resize(MAXPMT);
	sipmpe.resize(MAXPMT);
	sipmt.resize(MAXPMT);
	sipmbase.resize(MAXPMT);
	sipmbaserms.resize(MAXPMT);

}

LaserEvent::~LaserEvent()
{

}

void LaserEvent::EventInitial()
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
}

void LaserEvent::SetWFCTAEvent(int tel, 
		long long Rb_Time,
		double Rb_time,
		long long rb_Time, 
		double rb_time, 
		long long dt, 
		std::vector<int> &sipm, 
		std::vector<double> &sipmPe, 
		std::vector<double> &sipmT, 
		std::vector<int> &sipmBase,
		std::vector<int> &sipmBaserms)
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


void LaserEvent::SetTriggerTel(int tel, int trig)
{
	telTrigger[tel-1] = trig;
}
void LaserEvent::SetSlcStatus(int tel,int slc_status)
{
	status[tel-1] = slc_status;
}

int LaserEvent::goodWeather()
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














