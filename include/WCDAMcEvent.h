#ifndef __WCDAMCEVENT_HH__
#define __WCDAMCEVENT_HH__
#include "TObject.h"
#include <vector>
#include <map>
using namespace std;

class WCDAMcEvent : public TObject {
public:
  double e0;
  int recnpea,recnpec;
  double mthx;
  double mthy;
  vector<double>* mcq = new vector<double>();//！
  vector<double>* mct = new vector<double>();//！
  vector<int>* mcig = new vector<int>();     //！
  vector<double>* mcx = new vector<double>();//!
  vector<double>* mcy = new vector<double>();//!
  vector<double>* mcz = new vector<double>();//!
  double mcxc;
  double mcyc;
  double mczen;
  double mcazi;
  double mczen_inwcda;
  double mcazi_inwcda;
  double recxc;
  double recyc;
  double reczenp;
  double recazip;
  double reczenc;
  double recazic;
  double reczenc_inwcda;
  double recazic_inwcda;
  double recdcore;
  double recomega;
  double recomega_inwcda;
  int recnhit0, recnhitt,recnhitf,recnhits;
  int recnhitc,recnfitc;
  int recnhitfix;
  int fileid;
  int coreset;
  int runid;
  int eventid;
  int recflag;
  double reccompacness;

  WCDAMcEvent();
  ~WCDAMcEvent();
  void SetEvent();
  ClassDef(WCDAMcEvent,1)
};

#endif

