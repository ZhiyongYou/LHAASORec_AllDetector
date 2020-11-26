#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include "TMath.h"
#include "WFCTAMap.h"

const double WFCTAMap::MAXDIST=0.7;////30.4;//0.6;
WFCTAMap* WFCTAMap::m_instance = 0;

WFCTAMap::WFCTAMap()
{
	std::cout << "====================================== wfcta map constructor ======================================" << std::endl;

	ntel=0;
	maxTelId = ntel;
	nsipm=0;
	ReadTelFile("./config/WFCTA.txt");

	SipmId.resize(nsipm,0);
	SipmStat.resize(nsipm,0);
	SipmA.resize(nsipm,0);
	SipmZ.resize(nsipm,0);
	SipmX.resize(nsipm,0);
	SipmY.resize(nsipm,0);
	SipmId_inArray.resize(nsipm,0);
	w_SipmA.resize(nsipm,0);
	w_SipmZ.resize(nsipm,0);
	SetSiPMMap();
	GetXYRange();
	SetSiPMStat("./config/Sipm_Stat.txt");
	SetwSiPMMap();

	std::cout << "====================================== wfcta map constructor ======================================" << std::endl;
}

WFCTAMap::~WFCTAMap()
{

}

void WFCTAMap::ReadTelFile(const char* filename)
{
	//  wcda1 parameter in lhaaso
	double wcda_ang=29.36*TMath::DegToRad();//rad
	double wcda1_cen_x=-47.50;//m
	double wcda1_cen_y=-80;//m

	int n=0;
	int telid;
	double telx, tely, tela, telz, telfocal;
	char sTemp[200];

	std::ifstream file1;
	file1.open(filename);
	std::cout<< "###### Open WFCTA file "<< filename<< std::endl;
	if(file1.good()) {
		file1.getline(sTemp,200);
		//sscanf(sTemp,"%*s %*s %*s %*s %*s %*s");
	}
	while(file1.good()) {
		file1.getline(sTemp,200);
		int i = sscanf(sTemp,"%d %lf %lf %lf %lf %lf", &telid, &telx, &tely, &tela, &telz, &telfocal);
		if(i<=0){continue;}
		//if(telid!=fixToTel && fixToTel!=-1){continue;}
		if(maxTelId<telid) maxTelId = telid;
		n++;
	}
	file1.close();
	ntel = n;
	nsipm = maxTelId*1024;

	Tel_Id.resize(maxTelId,0);
	TelX.resize(maxTelId,0);
	TelY.resize(maxTelId,0);
	TelXinWCDA1.resize(maxTelId,0);
	TelYinWCDA1.resize(maxTelId,0);
	TelA.resize(maxTelId,0);
	TelZ.resize(maxTelId,0);
	TelFocal.resize(maxTelId,0);

	file1.open(filename);
	if(file1.good()) {
		file1.getline(sTemp,200);
		//sscanf(sTemp,"%*s %*s %*s %*s %*s %*s");
	}
	while(file1.good()) {
		file1.getline(sTemp,200);
		int i = sscanf(sTemp,"%d %lf %lf %lf %lf %lf", &telid, &telx, &tely, &tela, &telz, &telfocal);
		if(i<=0){continue;}
		//if(telid!=fixToTel && fixToTel!=-1){continue;}
		Tel_Id[telid-1] = telid;
		TelX[telid-1] = telx;
		TelY[telid-1] = tely;
		TelA[telid-1] = tela;
		TelZ[telid-1] = telz;
		TelFocal[telid-1] = telfocal;

		//turn tel address from lhaaso to wcda1 coordinate
		double telxinwcda1 = (telx-wcda1_cen_x)*cos(wcda_ang) + (tely-wcda1_cen_y)*sin(wcda_ang);
		double telyinwcda1 = -(telx-wcda1_cen_x)*sin(wcda_ang) + (tely-wcda1_cen_y)*cos(wcda_ang);
		TelXinWCDA1[telid-1] = telxinwcda1;
		TelYinWCDA1[telid-1] = telyinwcda1;

		printf("tel%02d: focal:%7.2lf tel_addr:(%7.2lf,%7.2lf) tel_addr_inwcda1:(%7.2lf,%7.2lf) tel_pointing:(%7.2lf,%7.2lf)\n",
				Tel_Id[telid-1],TelFocal[telid-1],TelX[telid-1],TelY[telid-1],TelXinWCDA1[telid-1],TelYinWCDA1[telid-1],TelA[telid-1],TelZ[telid-1]);
	}
	file1.close();
	std::cout << "###### File read finished, all " << n << " Tels, last tel_id: " << maxTelId << std::endl;
}

///////////////////////
////_set_ WFCTA map////
///////////////////////
void WFCTAMap::SetSiPMMap()
{
	double R2D = TMath::RadToDeg();
	int PIX = 32;
	double D_ConeOut=25.8 ;// mm
	double interval = 1.0;// mm
	double centerx = 414.3;
	double centery = 414.3;

	for(int itel=0;itel<maxTelId;itel++)
	{
		if(0==Tel_Id[itel]){continue;}
		for(int k=0;k<1024;k++)
		{
			double imagex,imagey;
			int ISIPM = itel * 1024 + k;

			int i = k/32;
			int j = k%32;
			int Intery = i/4;
			int Interx = j/4;
			if(i%2==0)
				imagex = ((j+0.5)*D_ConeOut + interval*Interx-centerx);//in simulation
				//imagex = -((j+0.5)*D_ConeOut + interval*Interx-centerx);
			if(i%2==1)
				imagex = ((j+1)*D_ConeOut + interval*Interx-centerx);//in simulation
				//imagex = -((j+1)*D_ConeOut + interval*Interx-centerx);
			//imagey = ((PIX-i)*D_ConeOut + interval*(7-Intery)-centery);
			imagey = ((PIX-i)*D_ConeOut + interval*(Intery)-centery);//old wrong

			imagex /= TelFocal[itel];
			imagey /= TelFocal[itel];

			SipmX[ISIPM]=imagex;
			SipmY[ISIPM]=imagey;
			slaDtp2s(imagex,imagey,TelA[itel]*TMath::DegToRad(),(90-TelZ[itel])*TMath::DegToRad(),&SipmA[ISIPM],&SipmZ[ISIPM]);

			SipmA[ISIPM] *= TMath::RadToDeg();
			if(SipmA[ISIPM]>180) SipmA[ISIPM] -= 360;
			SipmA[ISIPM] = SipmA[ISIPM]*TMath::DegToRad();
			SipmZ[ISIPM] = 90*TMath::DegToRad() - SipmZ[ISIPM];
			SipmStat[ISIPM] = 1;
			//printf("sipm:%lf %5d %8.2lf %8.2lf %8.2lf %8.2lf\n",TelA[itel],ISIPM,SipmX[ISIPM]*R2D,SipmY[ISIPM]*R2D,SipmA[ISIPM]*R2D,SipmZ[ISIPM]*R2D);
		}
	}
}
void WFCTAMap::GetXYRange()
{
	y_min = 100000;
	y_max = -100000;
	for(int i=0;i<32;i++)
	{
		x_max[i] = -100000;
		x_min[i] = 100000;
	}
	for(int i=1024*2;i<1024+1024*2;i++)
	{
		int SIPM = i;
		int sipm = SIPM%1024;
		int iline = sipm/32;
		if(y_min > SipmY[SIPM])		y_min = SipmY[SIPM];
		if(y_max < SipmY[SIPM])		y_max = SipmY[SIPM];
		if(x_max[iline] < SipmX[SIPM])	x_max[iline] = SipmX[SIPM];
		if(x_min[iline] > SipmX[SIPM])	x_min[iline] = SipmX[SIPM];
	}
	/*
	for(int i=1024*2;i<1024+1024*2;i++)
	{
		int SIPM = i;
		int sipm = SIPM%1024;
		//if((sipm/32==0||sipm/32==31)||(sipm%32==0||sipm%32==31))
		if(sipm%32==0)
			printf("sipm:%4d(%4d) line:%d sipmx_y(%lf,%lf) dy:%lf each_DY:%lf\n",
					SIPM,SIPM%1024,sipm/32,
					SipmX[SIPM]*TMath::RadToDeg(),SipmY[SIPM]*TMath::RadToDeg(),
					(SipmY[SIPM]-y_min)*TMath::RadToDeg(),(SipmY[SIPM]-y_min)*TMath::RadToDeg()/(31-sipm/32));
	}
	printf("y_min:%lf y_max:%lf\n",y_min*TMath::RadToDeg(),y_max*TMath::RadToDeg());
	for(int i=0;i<32;i++)
		printf("x_min:%lf x_max:%lf\n",x_min[i]*TMath::RadToDeg(),x_max[i]*TMath::RadToDeg());
		*/
}
void WFCTAMap::SetSiPMStat(const char* filename)
{
	int n=0;
	int telid;
	int isipm;
	int sipmstat;
	char sTemp[200];

	std::ifstream file1;
	file1.open(filename);
	std::cout << "###### Open SiPM Status file " << filename << std::endl;
	if(file1.good()) {
		file1.getline(sTemp,200);
		//sscanf(sTemp,"%*s %*s %*s %*s %*s %*s");
	}
	while(file1.good()) {
		file1.getline(sTemp,200);
		int i = sscanf(sTemp,"%d %d %d", &telid, &isipm, &sipmstat);
		if(i<=0) {continue;}
		if(0==Tel_Id[telid-1]){continue;}
		int ISIPM = (telid-1) * 1024 + isipm;
		SipmStat[ISIPM] = sipmstat;
		n++;
	}
	std::cout<< "###### bad sipm number: " << n << std::endl;
	file1.close();
}

void WFCTAMap::SetwSiPMMap()
{
	printf("set w_sipm map:...\n");

	double distance;
	double w_imageazi, w_imagezen;
	std::vector<int> usedsipm;
	std::vector<int> mapedsipm;

	merged_pix.clear();
	usedsipm.clear();
	for(int itel=0;itel<maxTelId;itel++)
	{
		for(int iisipm=0+1024*itel;iisipm<1024+1024*itel;iisipm++)
		{
			if(0==SipmStat[iisipm]){continue;}

			int jump=0;
			mapedsipm.clear();
			for(int ii=0;ii<usedsipm.size();ii++){  if(usedsipm.at(ii)==iisipm){jump=1;break;}}
			if(jump==1){continue;}//jump==1 means this sipm is matched with previous sipm
			mapedsipm.push_back(iisipm);
			//find sipms in other telescope that matched with "iisipm"
			for(int jjsipm=1024+1024*itel;jjsipm<nsipm;jjsipm++)
			{
				if(0==SipmStat[jjsipm]){continue;}
				distance = GetSiPMDist(SipmA[iisipm],SipmZ[iisipm],SipmA[jjsipm],SipmZ[jjsipm]);
				if(distance<0.25)
				{
					mapedsipm.push_back(jjsipm);
					//if(4==iisipm/1024&&5==jjsipm/1024)
				//printf("%d %d %lf %lf %lf %lf %lf\n",iisipm,jjsipm,SipmA[iisipm]*57.3,SipmZ[iisipm]*57.3,SipmA[jjsipm]*57.3,SipmZ[jjsipm]*57.3,distance);
					merged_pix.push_back(std::make_pair(iisipm,jjsipm));
					usedsipm.push_back(jjsipm);
				}
			}
			//merge "iisipm" with mapedsipms(sipms that overlap with iisipm)
			w_imageazi = 0;
			w_imagezen = 0;
			for(int ii=0;ii<mapedsipm.size();ii++)
			{
				SipmId_inArray[mapedsipm.at(ii)] = iisipm;
				w_imageazi += SipmA[mapedsipm.at(ii)];
				w_imagezen += SipmZ[mapedsipm.at(ii)];
			}
			w_imageazi /= mapedsipm.size();
			w_imagezen /= mapedsipm.size();
			for(int ii=0;ii<mapedsipm.size();ii++)
			{
				w_SipmA[mapedsipm.at(ii)] = w_imageazi;
				w_SipmZ[mapedsipm.at(ii)] = w_imagezen;
			}
		}
	}
	printf("map set finished\n");
}

void WFCTAMap::SetEventOnFocus(int main_tel, std::vector<int> iSipm)
{
	w_SipmX.resize(nsipm,0);
	w_SipmY.resize(nsipm,0);
	int SIPM, jj;
	double w_imagex, w_imagey;
	for(int ii=0;ii<iSipm.size();ii++)
	{
		SIPM = iSipm.at(ii);
		//<=============>
		//befor change
		double azi = SipmA[SIPM];
		double zen = SipmZ[SIPM];
		slaDs2tp(azi, 90*TMath::DegToRad()-zen, TelA[main_tel-1]*TMath::DegToRad(), (90-TelZ[main_tel-1])*TMath::DegToRad(), &w_imagex, &w_imagey, &jj);        
		//>=============<
		
		/*
		//<=============>
		//after change
		double azi = SipmA[SIPM];
		double zen = SipmZ[SIPM]; 
		int tel_id = SIPM/1024 + 1;
		double azi_trans, zen_trans;
		PointTransform(tel_id, azi, zen, main_tel, azi_trans, zen_trans, km2a_event.core_x, km2a_event.core_y, km2a_event.source_azi, km2a_event.source_zen);
		slaDs2tp(azi_trans, 90*TMath::DegToRad()-zen_trans, TelA[main_tel-1]*TMath::DegToRad(), (90-TelZ[main_tel-1])*TMath::DegToRad(), &w_imagex, &w_imagey, &jj);        
		//>=============<
		*/
		w_SipmX[SIPM] = w_imagex;
		w_SipmY[SIPM] = w_imagey;
	}
}

void WFCTAMap::SetEventOnFocus_New(int main_tel, std::vector<int> iSipm, double core_x, double core_y, double source_azi, double source_zen)
{
	w_SipmX.resize(nsipm,0);
	w_SipmY.resize(nsipm,0);
	int SIPM, jj;
	double w_imagex, w_imagey;
	for(int ii=0;ii<iSipm.size();ii++)
	{
		SIPM = iSipm.at(ii);
		//<=============>
		//befor change
		double azi = SipmA[SIPM];
		double zen = SipmZ[SIPM];
		slaDs2tp(azi, 90*TMath::DegToRad()-zen, TelA[main_tel-1]*TMath::DegToRad(), (90-TelZ[main_tel-1])*TMath::DegToRad(), &w_imagex, &w_imagey, &jj);        
		//>=============<
		
		/*
		//<=============>
		//after change
		double azi = SipmA[SIPM];
		double zen = SipmZ[SIPM]; 
		int tel_id = SIPM/1024 + 1;
		double azi_trans, zen_trans;
		if(tel_id != main_tel)
		{
			PointTransform(tel_id, azi, zen, main_tel, azi_trans, zen_trans, core_x, core_y, source_azi, source_zen);
		}
		else
		{
			azi_trans = azi;
			zen_trans = zen;
		}
		slaDs2tp(azi_trans, 90*TMath::DegToRad()-zen_trans, TelA[main_tel-1]*TMath::DegToRad(), (90-TelZ[main_tel-1])*TMath::DegToRad(), &w_imagex, &w_imagey, &jj);        
		//>=============<
		*/
		w_SipmX[SIPM] = w_imagex;
		w_SipmY[SIPM] = w_imagey;
	}
}





////////////////////////
////private function////
////////////////////////
double WFCTAMap::GetSiPMDist(double azi0, double zen0, double azi1, double zen1)//input:rad    return:deg
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

void WFCTAMap::slaDs2tp ( double ra, double dec, double raz, double decz, double *xi, double *eta, int *j )
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

void WFCTAMap::slaDtp2s ( double xi, double eta, double raz, double decz, double *ra, double *dec )
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

void WFCTAMap::PointTransform(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen)// tansform pointing from tel1 to tel2
{
	bool trans_debug=0;
	if(trans_debug) printf("================================================OOOOOOOOOOO  TANSFORM  OOOOOOOOOOO================================================\n");
	// set corez to 0
	double core_z = 0;

	// get component of source in (x,y,z)
	double source_x = sin(source_zen)*cos(source_azi);
	double source_y = sin(source_zen)*sin(source_azi);
	double source_z = cos(source_zen);
	if(trans_debug) printf("source_xyz:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", source_x,source_y,source_z, source_zen*57.3,source_azi*57.3);

	// get tel address and tel pointing
	double tel_x1, tel_y1, tel_z1 = 0, tel_azi1, tel_zen1;
	WFCTAMap::Instance()->GetTelXY(tel_id1, tel_x1, tel_y1);
	WFCTAMap::Instance()->GetTelAZ(tel_id1, tel_azi1, tel_zen1);
	double tel_x2, tel_y2, tel_z2 = 0, tel_azi2, tel_zen2;
	WFCTAMap::Instance()->GetTelXY(tel_id2, tel_x2, tel_y2);
	WFCTAMap::Instance()->GetTelAZ(tel_id2, tel_azi2, tel_zen2);
	// get component of core_tel1 in (x,y,z)
	double v_core_tel_x1 = core_x - tel_x1;
	double v_core_tel_y1 = core_y - tel_y1;
	double v_core_tel_z1 = core_z - tel_z1;
	double mode_core_tel1 = sqrt( pow(v_core_tel_x1,2)+pow(v_core_tel_y1,2)+pow(v_core_tel_z1,2) );
	// get component of core_tel2 in (x,y,z)
	double v_core_tel_x2 = core_x - tel_x2;
	double v_core_tel_y2 = core_y - tel_y2;
	double v_core_tel_z2 = core_z - tel_z2;
	double mode_core_tel2 = sqrt( pow(v_core_tel_x2,2)+pow(v_core_tel_y2,2)+pow(v_core_tel_z2,2) );
	if(trans_debug) printf("core_tel(%lf, %lf, %lf) mode:[ %lf ]   |   core_tel(%lf, %lf, %lf) mode:[ %lf ]\n\n",v_core_tel_x1,v_core_tel_y1,v_core_tel_z1,mode_core_tel1, v_core_tel_x2,v_core_tel_y2,v_core_tel_z2,mode_core_tel2);

	// get the component of point that need to trans in (x,y,z)
	double v_point_x1 = sin(point_zen1)*cos(point_azi1);
	double v_point_y1 = sin(point_zen1)*sin(point_azi1);
	double v_point_z1 = cos(point_zen1);
	double mode_point1 = sqrt( pow(v_point_x1,2)+pow(v_point_y1,2)+pow(v_point_z1,2) );
	if(trans_debug) printf("point_xyz1:(%lf, %lf, %lf) az:[%lf,%lf] | mode_point1:%lf\n\n", v_point_x1,v_point_y1,v_point_z1, point_zen1*57.3,point_azi1*57.3, mode_point1);

	//NEXT CHECK..................
	// get the coordinate of point in (x,y,z) that need to trans
	double cos_theta1 = (v_point_x1*v_core_tel_x1 + v_point_y1*v_core_tel_y1 + v_point_z1*v_core_tel_z1)/(mode_point1*mode_core_tel1);
	double cos_theta_source = -(source_x*v_core_tel_x1 + source_y*v_core_tel_y1 + source_z*v_core_tel_z1)/(mode_core_tel1);
	double angle_third = 180*TMath::DegToRad()-(acos(cos_theta1)+acos(cos_theta_source));
	//double length = mode_core_tel1 / cos_theta1;
	double length = sin(acos(cos_theta_source)) * mode_core_tel1 / sin(angle_third);
	double point_x1 = tel_x1 + length*v_point_x1;
	double point_y1 = tel_y1 + length*v_point_y1;
	double point_z1 = tel_z1 + length*v_point_z1;
	double c_length = sin(acos(cos_theta1)) * mode_core_tel1 / sin(angle_third);
	double c_point_x1 = core_x + c_length*source_x;
	double c_point_y1 = core_y + c_length*source_y;
	double c_point_z1 = core_z + c_length*source_z;
	if(trans_debug) printf("theta1:%lf theta_source:%lf  theta_third_angle:%lf\n",acos(cos_theta1)*57.3,acos(cos_theta_source)*57.3, angle_third*TMath::RadToDeg());
	if(trans_debug) printf("length:%lf c_length:%lf cos_theta1:%lf(%lf{^o})\n\n", length, c_length, cos_theta1, acos(cos_theta1)*57.3);
	if(trans_debug) printf("  point_xyz1:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", v_point_x1*length,v_point_y1*length,v_point_z1*length, point_zen1*57.3,point_azi1*57.3);
	if(trans_debug) printf("c_point_xyz1:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", source_x*c_length,source_y*c_length,source_z*c_length, source_zen*57.3,source_azi*57.3);

	//assume same image around main axis, get the coordinate of point that transform from tel1 to tel2
	double point_x2 = point_x1;
	double point_y2 = point_y1;
	double point_z2 = point_z1;

	double v_point_x2 = point_x2 - tel_x2;
	double v_point_y2 = point_y2 - tel_y2;
	double v_point_z2 = point_z2 - tel_z2;
	v_point_x2 *= length/abs(length);
	v_point_y2 *= length/abs(length);
	v_point_z2 *= length/abs(length);

	double mode_point2 = sqrt( pow(v_point_x2,2)+pow(v_point_y2,2)+pow(v_point_z2,2) );
	//get component of point that transform from tel1 to tel2 in (azi,zen)
	point_zen2 = acos(v_point_z2/mode_point2);
	point_azi2 = TMath::ATan2(v_point_y2, v_point_x2);
	if(trans_debug) printf("point_xyz2:(%lf, %lf, %lf) az:[%lf,%lf] | mode_point2:%lf\n", v_point_x2,v_point_y2,v_point_z2, point_zen2*57.3, point_azi2*57.3, mode_point2);


	if(trans_debug) printf("================================================OOOOOOOOOOO  TANSFORM  OOOOOOOOOOO================================================\n");
}
