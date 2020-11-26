#ifndef LHAASOEVENTREC_H
#define LHAASOEVENTREC_H
#include <vector>
#include "TMath.h"
#include "WFCTAMap.h"

class LHAASOEventRec
{
	private:
		struct TM{
			int T_year;
			int T_mon;
			int T_day;
			int T_hour;
			int T_minite;
			int T_second;
			double subsec;
		};
		double SDP_G_X_W;
		double SDP_G_Y_W;
		double SDP_G_X_K;
		double SDP_G_Y_K;
		double SDP_G_Angle_W;
		double SDP_G_Angle_K;

		//universal func
		double GetPointtingDist(double azi0, double zen0, double azi1, double zen1);//input:rad    return:deg
		double DistInSphericalCoordinates(double azi0, double zen0, double azi1, double zen1);
		void GetPlaneNormal(double zenith1,double azimuth1,double zenith2,double azimuth2,double *x, double *y, double *z);
		void DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist);
		double DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi);
		void slaDs2tp ( double ra, double dec, double raz, double decz, double *xi, double *eta, int *j );
		void slaDtp2s ( double xi, double eta, double raz, double decz, double *ra, double *dec );

	public:
		LHAASOEventRec();
		~LHAASOEventRec();

		double deltaTwcda;
		double deltaTkm2a;
		TM eventime;

		/*
		//do rec by self
		void rbtime2lt();
		void GetKm2aSDP();

		//return
		double GetRp(const char* det_type);
		double GetDeltaT(const char* det_type);
		double GetDist(const char* det_type);
		double GetDTheta(const char* det_type);
		double GetD_CoreToLine(const char* det_type);
		void CalcSDP_GLine_Parameters(const char* det_type);
		double GetSDP_GLine_Angle_W()	{	return SDP_G_Angle_W;	};
		double GetSDP_GLine_X_W()		{	return SDP_G_X_W;	};
		double GetSDP_GLine_Y_W()		{	return SDP_G_Y_W;	};
		double GetSDP_GLine_Angle_K()	{	return SDP_G_Angle_K;	};
		double GetSDP_GLine_X_K()		{	return SDP_G_X_K;	};
		double GetSDP_GLine_Y_K()		{	return SDP_G_Y_K;	};
		*/
		double GetSourceMiss(int maintel, double MeanX, double MeanY, double Delta, double source_zen, double source_azi);
		double GetDistanceToXmax(int maintel, double mean_zen, double source_zen, double corex, double corey);
		double GetDistSourceToMean(double mean_zen, double mean_azi, double source_zen, double source_azi);

};

#endif // LHAASOEVENTREC_H
