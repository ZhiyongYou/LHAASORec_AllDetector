#ifndef LASEREVENT_H
#define LASEREVENT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "TTree.h"
#include "TBranch.h"
#include "TObject.h"

//class LaserEvent : public TSelector
class LaserEvent : public TObject
{
	protected:
		static const int MAXPMT; //!
		static LaserEvent* _Head;
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

		//std::vector<int> iSipm;
		//std::vector<double> SipmPe;
		//std::vector<double> SipmT;
		std::vector<int> isipm;
		std::vector<double> sipmpe;
		std::vector<double> sipmt;
		std::vector<int> sipmbase;
		std::vector<int> sipmbaserms;

	public:
		LaserEvent();
		~LaserEvent();
		void EventInitial();

		Long64_t RabbitTime() { return rabbitTime; }
		Double_t Rabbittime() { return rabbittime; }

		//void MergeWFCTAInfo();
		void SetWFCTAEvent(int tel, 
				long long Rb_Time,
				double Rb_time,
				long long rb_Time, 
				double rb_time, 
				long long dt, 
				std::vector<int> &sipm, 
				std::vector<double> &sipmPe, 
				std::vector<double> &sipmT, 
				std::vector<int> &sipmBase,
				std::vector<int> &sipmBaserms);

		void SetTriggerTel(int tel, int trig);
		void SetSlcStatus(int tel,int slc_status);
		int goodWeather();


		ClassDef(LaserEvent,2);
};

//ClassImp(LaserEvent);

#endif // LASEREVENT_H
