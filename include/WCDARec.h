#ifndef WCDARECZ_H
#define WCDARECZ_H

#include <vector>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include "TMinuit.h"
#include <cmath>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <TGraph.h>
#include <TF2.h>
#include "TROOT.h"
#include "TRandom.h"
#include "TMinuit.h"
#include "TStyle.h"
#include "TPad.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"
#include <cmath>

struct event{
	Double_t kvx;
	Double_t kvy;
	Double_t kvz;
	Double_t kvq;
	Double_t kvigcell;
};
extern int comp(const event &s1,const event &s2);

struct tevent{
	Double_t kvx;
	Double_t kvy;
	Double_t kvz;
	Double_t kvq;
	Double_t kvtp;
	Double_t kvigcell;
};
extern int tcomp(const tevent &ts1,const tevent &ts2);

struct Sevent{
	Double_t skdcore;
	Double_t skvx;
	Double_t skvy;
	Double_t skvz;
	Double_t skvq;
	Double_t skvigcell;
};
extern int scomp(const Sevent &ss1,const Sevent &ss2);

class WCDARec
{
	private:
		static int Nn;

		std::vector<int> cell_ig;
		std::vector<double> cell_pe;
		std::vector<double> cell_t;

		Double_t big1_pmtx_igcell[900];
		Double_t big1_pmty_igcell[900];
		Double_t big1_pmtz_igcell[900];
		Double_t cell_water_eff[900];

		//raw cells
		Double_t kvx[3000];
		Double_t kvy[3000];
		Double_t kvz[3000];
		Double_t kvq[3000];
		Double_t kvigcell[3000];
		Double_t kvtp[3000];
		//afterpulse clean cells
		Double_t z_dx[3000];
		Double_t z_dy[3000];
		Double_t z_dz[3000];
		Double_t z_dq[3000];
		Double_t z_digcell[3000];
		Double_t z_dt[3000];
		//????? cells
		Double_t cf_x[3000];//in meter
		Double_t cf_y[3000];
		Double_t cf_z[3000];
		Double_t cf_q[3000];
		Double_t cf_igcell[3000];
		Double_t cf_t[3000];//in ns
		//????? cells
		Double_t skvx[3000];//in meter
		Double_t skvy[3000];
		Double_t skvz[3000];
		Double_t skvq[3000];
		Double_t skvtp[3000];
		Double_t skvigcell[3000];
		//????? cells
		Double_t sskvx[3000];//in meter
		Double_t sskvy[3000];
		Double_t sskvz[3000];
		Double_t sskvq[3000];
		Double_t sskvtp[3000];
		Double_t sskvigcell[3000];
		//dr and dq ????????
		Double_t dr[3000];
		Double_t dq[3000];

		//sort containers
		event s[4000];

		//fit parameters
		Double_t t_par[5];//filter1
		Double_t theta_first;
		Double_t phi_first;

		TMinuit *wcda_minuit;
		Double_t vcore_like[8];

		//rec parameters
		double l_z;
		double m_z;
		double n_z;

		double d_theta;
		double d_phi;
		double ch2_sigma;

		int raw_nhit;
		int nhit_no_ap;
		int nhit_pfilter;
		int nhit_pnoise;
		int nnhit;

		int npmt10;
		int npmt20;
		int npmt30;
		int npmt40out;
		int npmtall;
		long long int kN10;
		long long int kN20;
		long long int kN30;
		long long int kN40out;
		long long int kNall;

		int N_secCore2;
		int N_secCore4;
		int N_secCore6;
		int N_secCore8;
		int N_secCore10;
		int N_Top50rate;
		int N_Top10rate;

		Double_t MaxX;
		Double_t MaxY;
		Double_t MaxQ;
		Double_t direction_Resolution;
		Double_t sort_tp_trig;
		Double_t clustering_q;
		Double_t clustering_rq;
		Double_t clustering;

		int iter;
		int iter2;
		int iiter;
		int for_iiter;
		int recFlag;
		int wt;

		Double_t top50_x;
		Double_t core_x_check;
		Double_t core_y_check;
		Double_t top50_y;
		Double_t top50_z;
		Double_t even_x;
		Double_t even_y;
		Double_t odd_x;
		Double_t odd_y;
		Double_t xc;
		Double_t yc;
		Double_t zc;
		Double_t zxc;
		Double_t zyc;

		static Double_t dirl;
		static Double_t dirm;
		static Double_t dirn;
		static Double_t r[5000];
		static Double_t ElPosx[5000];
		static Double_t ElPosy[5000];
		static Double_t ElData[5000];
		static Double_t _size;
		static Double_t _age;
		static Double_t _cx;
		static Double_t _cy;
		static int NHIT;
		static Double_t zChi2;

	public:
		WCDARec();
		~WCDARec();

		void Init();
		void SetWaterEff(char* water_eff_filename);
		void SetWCDAEvent(const std::vector<int>& cellig, const std::vector<double>& cellpe, const std::vector<double>& cellt);
		void AfterPulseClean();
		void TimeResidualClean();
		void CoreReconstruction();
		void DirectionReconstruction();
		void OddAndEven();
		void RecEnergy();

		static double fme(double *x, double *p);
		static double NKGlike(double r, double s,double ne);
		static void NKG_FUNC(int &npar, double *gin, double &f,double *par, int iflag);
		static void NKG_FUNCL(int &npar, double *gin, double &f,double *par, int iflag);
		void core_likelihood();


		void GetRecResult(double* evrec);
		double GetMaxPe();
		void GetHits(std::vector<double>& wcda_clean_x, std::vector<double>& wcda_clean_y, std::vector<double>& wcda_clean_pe, std::vector<int>& wcda_clean_ig, std::vector<double>& wcda_clean_t);


};

#endif
