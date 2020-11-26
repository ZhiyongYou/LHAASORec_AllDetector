#include <iostream>
#include <stdio.h>
#include "TMath.h"
#include "WFCTAMap.h"

double GetSiPMDist(double azi0, double zen0, double azi1, double zen1);//input:rad    return:deg

int main(int argc, char *argv[])
{
	time_t t0 = time(0);
	std::cout<< "begin: "<<t0 << std::endl;

	double distance, azi1, zen1, azi0, zen0;
	for(int ii=0;ii<6144;ii++)
	{
		int SIPM0 = ii;
		WFCTAMap::Instance()->GetSipmAZ(SIPM0, azi0, zen0);
		for(int jj=ii+1;jj<6144;jj++){
			int SIPM1 = jj;
			WFCTAMap::Instance()->GetSipmAZ(SIPM1, azi1, zen1);
			distance = GetSiPMDist(azi0,zen0,azi1,zen1); // input:rad    return:deg
			//if(distance<=WFCTAMap::Instance()->GetMAXDIST() && groupclean.at(jj)==0 && timeclean.at(jj)!=0)  {groupclean.at(jj)=1;cnt++;}
			if(distance<0.02)
				printf("sipm0:%d(%lf,%lf) sipm1:%d(%lf,%lf) distance:%lf\n",SIPM0, azi0*TMath::RadToDeg(), zen0*TMath::RadToDeg(), SIPM1, azi1*TMath::RadToDeg(), zen1*TMath::RadToDeg(), distance);
		}
	}

	time_t t1 = time(0);
	std::cout<< "end: "<<t1 << std::endl;
	std::cout<< "used: "<< t1-t0<< std::endl;
	return 0;
}

double GetSiPMDist(double azi0, double zen0, double azi1, double zen1)//input:rad    return:deg
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
	//        //return sqrt((azi0-azi1)*(azi0-azi1)+(zen0-zen1)*(zen0-zen1));
}
