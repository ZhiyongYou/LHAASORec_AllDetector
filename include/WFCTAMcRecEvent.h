#ifndef __WFCTAMCRECEVENT_HH__
#define __WFCTAMCRECEVENT_HH__
#include "TObject.h"
#include <vector>
#include <map>
#include "WFCTARec.h"

class WFCTAMcRecEvent : public TObject {
public:
  int iEvent;
  int iUse;
  double id;
  double energy;
  double zenith, azimuth;
  double corex, corey;
  double Xmax, Nmax;

  //**Hillas parameters **//
  double DMeanX, DMeanY, DLength, DWidth, DDeltaHillas, DAlpha ,DD2Center;
  double DSize;
  int Npix;
 
  //**geometry parameters **//
  int MainTel;
  double DSourceX, DSourceY,  DAngle, DDist;
  double DDeltaSDP,DCore2SDP,DTheta;  
  double CoreAtFocusX;
  double CoreAtFocusY;
  double TelX,TelY;
  double Rp;

  //**ronstruction geometry parameters**//
  double DRecSourceX, DRecSourceY, DRecAngle,DRecDist;
  double DRecCore2SDP,DRecTheta;
  double RecCoreAtFocusX,RecCoreAtFocusY;
  double RecRp; 
  double RecEnergyProton,RecEnergyHelium,RecEnergyMix;

  //** Xmax related **//
  double DPemax;
  double DXmax, DYmax;
  double DDistmax;
  

  //**image information **//
  std::vector<double> CleanImagePe; //!
  std::vector<double> CleanImageX;  //!
  std::vector<double> CleanImageY;  //!



  WFCTAMcRecEvent();
  ~WFCTAMcRecEvent();
  void Init();
  void SetEvent(WFCTARec* wfctarec);
  ClassDef(WFCTAMcRecEvent,1)
};

#endif

