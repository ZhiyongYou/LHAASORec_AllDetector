#include "WCDAEventRec.h"

ClassImp(WCDAEventRec)

WCDAEventRec::WCDAEventRec()
{
}

WCDAEventRec::~WCDAEventRec()
{
}

void WCDAEventRec::Init()
{
  nhit        = -1000;
  ndetc       = -1000;
  nfitc       = -1000;
  mjd         = -1000;
  npea        = -1000;
  npec        = -1000;
  zen         = -1000;
  azi         = -1000;
  xc          = 0;
  yc          = 0;
  zenc        = -1000;
  azic        = -1000;
  xc1         = -10000;
  yc1         = -10000;
  rmd20       = -1000;
  omega       = -1000;
  chi2p       = -1000;
  chi2c       = -1000;
  compactness = -1000;
  pincness    = -1000;
  for(int i=0;i<10;i++) CXPE[i] = -1000;
  for(int i=0;i<10;i++) Top5s[i] = -1000;
  for(int i=0;i<10;i++) Top5r[i] = -1000;
  inters      = -1000;
  intern      = -1000;
  outers      = -1000;
  outern      = -1000;
  recflag     = -10000;
}
