#ifndef LHAASOEVENT_H
#define LHAASOEVENT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "TTree.h"
#include "TBranch.h"
#include "TObject.h"

const int MAXPMT=6144;
const int WCDASIZE=3120;
const int KM2ASIZE=1500;

//class LHAASOEvent : public TSelector
class LHAASOEvent : public TObject
{
	protected:
		static LHAASOEvent* _Head;
		static TTree* _Tree;
		static const char * _Name;
		static TBranch* bAll;

	public:
		int telTrigger[6];
		long long rbTime[6];
		double rbtime[6];
		long long rabbitTime;
		double rabbittime;
		int status[6];
		//wfcta
		//std::vector<int> iSipm;
		//std::vector<double> SipmPe;
		//std::vector<double> SipmT;
		std::vector<int> isipm;
		std::vector<double> sipmpe;
		std::vector<double> sipmt;
		std::vector<int> sipmbase;
		std::vector<int> sipmbaserms;
		//wcda
		int IsWcdaEvent;
		double deltaTwcda; 
		int nhitplus;
		unsigned long int iwcdaevt;
		std::vector<int> cellig;
		std::vector<double> cellpe;
		std::vector<double> cellt;
		//km2a
		int IsKm2aEvent;
		double deltaTkm2a;
		std::vector<int> hitid;
		std::vector<double> hitpart;
		std::vector<double> hitt;
		std::vector<int> hitmode;
		float km2a_mjd;
		float km2a_xc;
		float km2a_yc;
		float km2a_phi;
		float km2a_theta;

	public:
		LHAASOEvent();
		~LHAASOEvent();
		void EventInitial();
		void WcdaInitial();
		void Km2aInitial();

		Long64_t RabbitTime() { return rabbitTime; }
		Double_t Rabbittime() { return rabbittime; }

//		void MergeWFCTAInfo();
		void SetWFCTAEvent(int tel, 
				long long Rb_Time,
				double Rb_time,
				long long rb_Time, 
				double rb_time, 
				long long dt, 
				std::vector<int> &sipm, 
				std::vector<double> &sipmPe, 
				std::vector<double> &sipmT, 
				std::vector<int> sipmBase,
				std::vector<int> sipmBaserms);
		void SetWCDAEvent(int iswcdaevent, 
				int Nhitplus, 
				double DeltaTwcda, 
				long long dt,
				ULong64_t Iwcdaevt, 
				std::vector<int> &cellIg, 
				std::vector<double> &cellPe, 
				std::vector<double> &cellT);
		void SetKM2AEvent(int iskm2aevent, 
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
				std::vector<int> &hitMode);

		void SetTriggerTel(int tel, int trig);
		void SetSlcStatus(int tel,int slc_status);
		int goodWeather();

		ClassDef(LHAASOEvent,1);
};

//ClassImp(LHAASOEvent);

#endif // LHAASOEVENT_H
