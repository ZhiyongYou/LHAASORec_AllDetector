#include <time.h>
#include "LHAASOEventRec.h"
#include "CollectIntensity.h"

using namespace std;

LHAASOEventRec::LHAASOEventRec()
{
	printf("lhaaso event rec ctor==================\n");

	deltaTwcda=-1000;
	deltaTkm2a=-1000;
}

LHAASOEventRec::~LHAASOEventRec()
{

}

////////////////////////////////
//// _block_: universal func////
////////////////////////////////
/*
int LHAASOEventRec::GetSipmIdInSimulation(int sipm_id)
{
	int itel = sipm_id/1024 + 1;
	int isipm_in_tel = sipm_id % 1024;
	int icolum = isipm_in_tel % 32;
	int iline = isipm_in_tel / 32;
	return (31-icolum) + 32*iline + (itel-1)*1024;

}
*/

void LHAASOEventRec::slaDs2tp ( double ra, double dec, double raz, double decz, double *xi, double *eta, int *j )
{
	double TINY=1e-6;
	double sdecz, sdec, cdecz, cdec, radif, sradif, cradif, denom;

	/* Trig functions */
	sdecz = sin ( decz );
	sdec = sin ( dec );
	cdecz = cos ( decz );
	cdec = cos ( dec );
	radif = ra - raz;
	sradif = sin ( radif );
	cradif = cos ( radif );
	/* Reciprocal of star vector length to tangent plane */
	denom = sdec * sdecz + cdec * cdecz * cradif;
	/* Handle vectors too far from axis */
	if ( denom > TINY )         {   *j = 0; }
	else if ( denom >= 0.0 )    {   *j = 1; denom = TINY;}
	else if ( denom > -TINY )   {   *j = 2; denom = -TINY;}
	else                        {   *j = 3; }
	/* Compute tangent plane coordinates (even in dubious cases) */
	*xi = cdec * sradif / denom;
	*eta = ( sdec * cdecz - cdec * sdecz * cradif ) / denom;
}

void LHAASOEventRec::slaDtp2s ( double xi, double eta, double raz, double decz, double *ra, double *dec )
{
	double d2pi = 2*TMath::Pi();
	double sdecz, cdecz, denom;
	double w;

	sdecz = sin ( decz );
	cdecz = cos ( decz );
	denom = cdecz - eta * sdecz;
	w = dmod ( atan2 ( xi, denom ) + raz, d2pi );
	*ra = ( w >= 0.0 ) ? w : w + d2pi;
	*dec = atan2 ( sdecz + eta * cdecz, sqrt ( xi * xi + denom * denom ) );
}

//private universal func
double LHAASOEventRec::GetPointtingDist(double azi0, double zen0, double azi1, double zen1)//input:rad    return:deg
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
	//return sqrt((azi0-azi1)*(azi0-azi1)+(zen0-zen1)*(zen0-zen1));
}

double LHAASOEventRec::DistInSphericalCoordinates(double azi0, double zen0, double azi1, double zen1)//input:rad    return:deg
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
	//return sqrt((azi0-azi1)*(azi0-azi1)+(zen0-zen1)*(zen0-zen1));
}

void LHAASOEventRec::GetPlaneNormal(double zenith1,double azimuth1,double zenith2,double azimuth2,double *x, double *y, double *z)
{
	double m, n,l,   m0,n0,l0;
	double x1, y1, z1,norm;

	m = sin(zenith1)*cos(azimuth1);
	n = sin(zenith1)*sin(azimuth1);
	l = cos(zenith1);

	m0 = sin(zenith2)*cos(azimuth2);
	n0 = sin(zenith2)*sin(azimuth2);
	l0 = cos(zenith2);

	x1 = n*l0 - n0*l;
	y1 = -(m*l0 - m0*l);
	z1 = m*n0 - m0*n;

	norm = sqrt(x1*x1+y1*y1+z1*z1);
	*x = x1/norm;
	*y = y1/norm;
	*z = z1/norm;
}

void LHAASOEventRec::DistPointToLine(double p_x, double p_y, double p_x0, double p_y0, double v_x, double v_y, double& dist)
{
	double k = v_y / v_x;
	double b = p_y0 - k*p_x0;
	dist = abs(k*p_x-p_y+b) / sqrt(1+pow(k,2));
}

double LHAASOEventRec::DistPointToLine(double corex, double corey, double telx, double tely, double zen, double azi)
{
	int i;
	double dx,dy,u[3],v[3];
	double L,rp,temp,psi;
	dx=corex-telx;
	dy=corey-tely;
	u[0]=sin(zen)*cos(azi);
	u[1]=sin(zen)*sin(azi);
	u[2]=cos(zen);
	L=sqrt(dx*dx+dy*dy);
	v[0]=dx/L; v[1]=dy/L; v[2]=0.;
	temp=0.;
	for(i=0;i<3;i++) temp +=-(u[i]*v[i]);
	psi=acos(temp);
	rp=L*sin(psi);
	return rp;
}


//////////////////////////////
//// _block_: rec by self ////
//////////////////////////////
/*
void LHAASOEventRec::rbtime2lt()
{
	double TAI2UTC = 37;
	time_t rawtime;
	time_t utc = rabbitTime-TAI2UTC;
	struct tm *info;
	info = localtime(&utc);
	eventime.T_year = 1900 + info->tm_year;
	eventime.T_mon = info->tm_mon+1;
	eventime.T_day = info->tm_mday;
	eventime.T_hour = info->tm_hour;
	eventime.T_minite = info->tm_min;
	eventime.T_second = info->tm_sec;
	eventime.subsec = rabbittime;

	printf("time: %d %d %d %d:%d:%d\n",eventime.T_year,eventime.T_mon,eventime.T_day,eventime.T_hour,eventime.T_minite,eventime.T_second);
}
*/
/*
double LHAASOEventRec::GetDeltaT(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	int main_tel = wfctarec.GetMainTel();
	if(!strcmp(det_type,"wcda"))
		return deltaTwcda + (rabbitTime-rbTime[main_tel-1])*1000000000 + (rabbittime-rbtime[main_tel-1]);
	else if(!strcmp(det_type,"km2a"))
		return deltaTkm2a + (rabbitTime-rbTime[main_tel-1])*1000000000 + (rabbittime-rbtime[main_tel-1]);
	else 
		return -1000;
}
*/
/*
double LHAASOEventRec::GetDistToXmax(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	int main_tel = wfctarec.GetMainTel();
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(main_tel, tel_x, tel_y);
	double core_x = GetCoreX(det_type);
	double core_y = GetCoreY(det_type);
	double source_zen = GetSourceZen(det_type);
	double mean_zen = GetMeanZen();

	double rp = sqrt(pow(tel_x-core_x,2)+pow(tel_y-core_y,2));

	double ang1;
	double ang2;
	double ang3;
	if(source_zen<mean_zen)
	{
		ang1 = 90*TMath::DegToRad() + source_zen;
		ang2 = 90*TMath::DegToRad() - mean_zen;
	}
	else
	{
		ang1 = 90*TMath::DegToRad() + mean_zen;
		ang2 = 90*TMath::DegToRad() - source_zen;
	}
	ang3 = 180*TMath::DegToRad() - ang1 - ang2;

	double distToXmax = rp * sin(ang1) / sin(ang3);
	printf("distToXmax:%lf\n",distToXmax);
	return distToXmax;
}
*/


//////////////////////////////////////////
//// _block_: rec commission to WFCTA ////
//////////////////////////////////////////
/*
void LHAASOEventRec::CalcSDP(const char* det_type)
{
	//if(!IsWcdaEvt)
	if(1)
	{
		wfctarec.CalcSDP();
		SDP_G_X_W = GetSDP_GLine_X_wcda();
		SDP_G_Y_W = GetSDP_GLine_Y_wcda();
		SDP_G_X_K = GetSDP_GLine_X_km2a();
		SDP_G_Y_K = GetSDP_GLine_Y_km2a();
		SDP_G_Angle_W = TMath::ATan2(SDP_G_Y_W,SDP_G_X_W);
		SDP_G_Angle_K = TMath::ATan2(SDP_G_Y_K,SDP_G_X_K);
	}
	else
	{
		CalcSDP_GLine_Parameters(det_type);
	}
}
*/
///////////////////////////////////////////////////////
//// _block_: return info (calc by lhaasoeventrec) ////
///////////////////////////////////////////////////////
/*
double LHAASOEventRec::GetRp(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	int main_tel = wfctarec.GetMainTel();
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(main_tel, tel_x, tel_y);
	double sourceazi = GetSourceAzi(det_type);
	double sourcezen = GetSourceZen(det_type);
	double core_x = GetCoreX(det_type);
	double core_y = GetCoreY(det_type);
	//printf("main_tel:%d telx:%lf tely:%lf\n",main_tel,tel_x,tel_y);

	return DistPointToLine(core_x,core_y,tel_x,tel_y,sourcezen,sourceazi);;
}
*/
/*
double LHAASOEventRec::GetDist(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	double mean_azi = wfctarec.GetMeanAzi();
	double mean_zen = wfctarec.GetMeanZen();
	double source_azi = GetSourceAzi(det_type);
	double source_zen = GetSourceZen(det_type);

	return TMath::DegToRad()*DistInSphericalCoordinates(mean_azi, mean_zen, source_azi, source_zen);
}
*/
/*
double LHAASOEventRec::GetDTheta(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	if(!strcmp(det_type,"wcda"))
	{
		double dist_core2line;
		int main_tel = wfctarec.GetMainTel();
		double tel_x, tel_y;
		WFCTAMap::Instance()->GetTelXYinWCDA1(main_tel, tel_x, tel_y);
		double ground_x = GetSDP_GLine_X_W();
		double ground_y = GetSDP_GLine_Y_W();
		//double ground_x = wfctarec.GetSDP_GLine_X_wcda();
		//double ground_y = wfctarec.GetSDP_GLine_Y_wcda();
		double core_x = wcdarec.GetCoreXinWCDA1();
		double core_y = wcdarec.GetCoreYinWCDA1();
		DistPointToLine(core_x, core_y, tel_x, tel_y, ground_x, ground_y, dist_core2line);

		return asin( dist_core2line / sqrt(pow(tel_x-core_x,2)+pow(tel_y-core_y,2)) );
	}
	if(!strcmp(det_type,"km2a"))
	{
		double dist_core2line;
		int main_tel = wfctarec.GetMainTel();
		double tel_x, tel_y;
		WFCTAMap::Instance()->GetTelXY(main_tel, tel_x, tel_y);
		double ground_x = GetSDP_GLine_X_K();
		double ground_y = GetSDP_GLine_Y_K();
		//double ground_x = wfctarec.GetSDP_GLine_X_km2a();
		//double ground_y = wfctarec.GetSDP_GLine_Y_km2a();
		double core_x = GetCoreX("km2a");
		double core_y = GetCoreY("km2a");
		DistPointToLine(core_x, core_y, tel_x, tel_y, ground_x, ground_y, dist_core2line);

		return asin( dist_core2line / sqrt(pow(tel_x-core_x,2)+pow(tel_y-core_y,2)) );
	}

}
*/
/*
double LHAASOEventRec::GetD_CoreToLine(const char* det_type)
{
	if(!DetctorTrigger(det_type)) return -1000;
	if(!strcmp(det_type,"wcda"))
	{
		double dist_core2line;
		int main_tel = wfctarec.GetMainTel();
		double tel_x, tel_y;
		WFCTAMap::Instance()->GetTelXYinWCDA1(main_tel, tel_x, tel_y);
		double ground_x = GetSDP_GLine_X_W();
		double ground_y = GetSDP_GLine_Y_W();
		//double ground_x = wfctarec.GetSDP_GLine_X_wcda();
		//double ground_y = wfctarec.GetSDP_GLine_Y_wcda();
		double core_x = wcdarec.GetCoreXinWCDA1();
		double core_y = wcdarec.GetCoreYinWCDA1();

		DistPointToLine(core_x, core_y, tel_x, tel_y, ground_x, ground_y, dist_core2line);
		printf("wcda: tel_x:%lf tel_y:%lf ground_x:%lf ground_y:%lf core_x:%lf core_y:%lf dist_core2line:%lf\n",
				tel_x,tel_y, ground_x,ground_y, core_x,core_y, dist_core2line);
		return dist_core2line;
	}
	if(!strcmp(det_type,"km2a"))
	{
		double dist_core2line;
		int main_tel = wfctarec.GetMainTel();
		double tel_x, tel_y;
		WFCTAMap::Instance()->GetTelXY(main_tel, tel_x, tel_y);
		double ground_x = GetSDP_GLine_X_K();
		double ground_y = GetSDP_GLine_Y_K();
		//double ground_x = wfctarec.GetSDP_GLine_X_km2a();
		//double ground_y = wfctarec.GetSDP_GLine_Y_km2a();
		double core_x = GetCoreX("km2a");
		double core_y = GetCoreY("km2a");

		DistPointToLine(core_x, core_y, tel_x, tel_y, ground_x, ground_y, dist_core2line);
		printf("km2a: tel_x:%lf tel_y:%lf ground_x:%lf ground_y:%lf core_x:%lf core_y:%lf dist_core2line:%lf\n",
				tel_x,tel_y, ground_x,ground_y, core_x,core_y, dist_core2line);
		return dist_core2line;
	}
}
*/
/*
void LHAASOEventRec::CalcSDP_GLine_Parameters(const char* det_type)
{
	double sdp_azi1, sdp_azi2;
	double sdp_zen1, sdp_zen2;
	double km2a_sdp_azi1, km2a_sdp_azi2;
	double km2a_sdp_zen1, km2a_sdp_zen2;
	double wcda_sdp_azi1, wcda_sdp_azi2;
	double wcda_sdp_zen1, wcda_sdp_zen2;

	double DMeanX = GetMeanX();
	double DMeanY = GetMeanY();
	double DDelta = GetDelta();
	double DLength = GetLength();
	double sourceazi = GetSourceAzi(det_type);
	double sourcezen = GetSourceZen(det_type);
	int main_tel = wfctarec.GetMainTel();

	int jj;
	double DSourcX=0;
	double DSourcY=0;
	double tel_azi, tel_zen; 
	WFCTAMap::Instance()->GetTelAZ(main_tel, tel_azi, tel_zen);

	wfctarec.slaDs2tp(sourceazi, 90*TMath::DegToRad()-sourcezen, 
			tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), 
			&DSourcX, &DSourcY, &jj);

	double orientation = 1;
	double S_M_X = DSourcX-DMeanX;
	double S_M_Y = DSourcY-DMeanY;
	double Dalpha = TMath::ATan2(S_M_Y,S_M_X);
	if((Dalpha-DDelta)<90*TMath::DegToRad() && (Dalpha-DDelta)>-90*TMath::DegToRad())
		orientation = -1;
	else
		orientation = 1;
	//if(0!=DSourcX-DMeanX)
	//	orientation = (DSourcX-DMeanX)*cos(DDelta)/abs((DSourcX-DMeanX)*cos(DDelta));
	printf("IsWcdaEvt:%d orientation:%lf DSource:(%lf,%lf) DMean:%lf,%lf DSourceX-DMeanX:%lf cos(DDelta):%lf DDelta:%lf Dalpha:%lf\n",
			IsWcdaEvt,orientation, DSourcX,DSourcY, DMeanX,DMeanY, DSourcX-DMeanX, cos(DDelta), DDelta,Dalpha);
	//get two directions in this plane
	wfctarec.slaDtp2s( DMeanX-orientation*DLength*cos(DDelta)/2, DMeanY-orientation*DLength*sin(DDelta)/2,
			tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(),
			&sdp_azi1, &sdp_zen1);
	wfctarec.slaDtp2s( DMeanX+orientation*DLength*cos(DDelta)/2, DMeanY+orientation*DLength*sin(DDelta)/2,
			tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(),
			&sdp_azi2, &sdp_zen2);

	wcda_sdp_azi1 = sdp_azi1 - 29.36*TMath::DegToRad();
	wcda_sdp_zen1 = 90*TMath::DegToRad()-sdp_zen1;
	wcda_sdp_azi2 = sdp_azi2 - 29.36*TMath::DegToRad();
	wcda_sdp_zen2 = 90*TMath::DegToRad()-sdp_zen2;

	km2a_sdp_azi1 = sdp_azi1;
	km2a_sdp_zen1 = 90*TMath::DegToRad()-sdp_zen1;
	km2a_sdp_azi2 = sdp_azi2;
	km2a_sdp_zen2 = 90*TMath::DegToRad()-sdp_zen2;

	double wcda_sdp_x, wcda_sdp_y, wcda_sdp_z;
	double km2a_sdp_x, km2a_sdp_y, km2a_sdp_z;
	//calc plane normal vector
	wfctarec.GetPlaneNormal(wcda_sdp_zen1, wcda_sdp_azi1, wcda_sdp_zen2, wcda_sdp_azi2, &wcda_sdp_x, &wcda_sdp_y, &wcda_sdp_z);
	wfctarec.GetPlaneNormal(km2a_sdp_zen1, km2a_sdp_azi1, km2a_sdp_zen2, km2a_sdp_azi2, &km2a_sdp_x, &km2a_sdp_y, &km2a_sdp_z);

	SDP_G_X_W = wcda_sdp_y;
	SDP_G_Y_W = -wcda_sdp_x;
	SDP_G_X_K = km2a_sdp_y;
	SDP_G_Y_K = -km2a_sdp_x;
	SDP_G_Angle_W = TMath::ATan2(SDP_G_Y_W, SDP_G_X_W);
	SDP_G_Angle_K = TMath::ATan2(SDP_G_Y_W, SDP_G_X_K);
	//SDP_GLine_X_wcda = wcda_sdp_y;
	//SDP_GLine_Y_wcda = -wcda_sdp_x;
}
*/

double LHAASOEventRec::GetSourceMiss(int maintel, double MeanX, double MeanY, double Delta, double source_zen, double source_azi)
{
	int jj;
	double source_x, source_y;
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(maintel, tel_azi, tel_zen);
	slaDs2tp(source_azi, 90*TMath::DegToRad()-source_zen, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &source_x, &source_y, &jj);

	double source_miss=-1000;
	DistPointToLine(source_x, source_y, MeanX, MeanY, cos(Delta), sin(Delta), source_miss);
	return source_miss;
}

double LHAASOEventRec::GetDistanceToXmax(int maintel, double mean_zen, double source_zen, double corex, double corey)
{
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(maintel, tel_x, tel_y);

	double rp = sqrt(pow(tel_x-corex,2)+pow(tel_y-corey,2));

	double ang1;
	double ang2;
	double ang3;
	if(source_zen<mean_zen)
	{
		ang1 = 90*TMath::DegToRad() + source_zen;
		ang2 = 90*TMath::DegToRad() - mean_zen;
	}
	else
	{
		ang1 = 90*TMath::DegToRad() + mean_zen;
		ang2 = 90*TMath::DegToRad() - source_zen;
	}
	ang3 = 180*TMath::DegToRad() - ang1 - ang2;

	double distToXmax = rp * sin(ang1) / sin(ang3);
	//  printf("distToXmax:%lf\n",distToXmax);
	return distToXmax;
}

double LHAASOEventRec::GetDistSourceToMean(double mean_zen, double mean_azi, double source_zen, double source_azi)
{
	return GetPointtingDist(mean_azi, mean_zen, source_azi, source_zen);//input:rad    return:deg
}















