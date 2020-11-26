#ifndef __WCDAEVENTREC_HH__
#define __WCDAEVENTREC_HH__
#include "TObject.h"
class WCDAEventRec : public TObject {
 public:
  Int_t nhit;
  Int_t ndetc;
  Int_t nfitc;
  Double_t mjd; 
  Double_t npea;
  Double_t npec;
  Double_t zen;
  Double_t azi;
  Double_t xc;
  Double_t yc;
  Double_t zenc;
  Double_t azic;
  Double_t xc1;
  Double_t yc1;
  Double_t rmd20;
  Double_t omega;
  Double_t chi2p;
  Double_t chi2c;
  Double_t compactness;
  Double_t pincness;
  Double_t CXPE[10];
  Double_t Top5s[5];
  Double_t Top5r[5];
  Double_t inters;
  Double_t intern;
  Double_t outers;
  Double_t outern;
  Double_t recflag;

  WCDAEventRec();
  ~WCDAEventRec();
  void Init();
  void SetCXPE(double cxpe[10]) { for(int i=0;i<10;i++) CXPE[i] = cxpe[i]; };
  void SetTop5s(double top5s[5]) { for(int i=0;i<5;i++) Top5s[i] = top5s[i]; };
  void SetTop5r(double top5r[5]) { for(int i=0;i<5;i++) Top5r[i] = top5r[i]; };

  ClassDef(WCDAEventRec,1)
};

#endif

