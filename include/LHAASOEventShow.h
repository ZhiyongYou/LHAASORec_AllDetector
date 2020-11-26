#ifndef LHAASOEVENTSHOW_H
#define LHAASOEVENTSHOW_H

#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TH2Poly.h"
#include "TH1D.h"
#include "TPaveText.h"
#include "TBox.h"
#include "TGaxis.h"
#include "TPaletteAxis.h"
#include "TLegend.h"
#include "WFCTAMap.h"
#include "LHEvent.h"
#include "G4KM2A_Geometry.h"

#define dmod(A,B) ((B)!=0.0?((A)*(B)>0.0?(A)-(B)*floor((A)/(B)):(A)+(B)*floor(-(A)/(B))):(A))
class LHAASOEventShow
{
	private:
		//wfcta map relevant parameters
		static const int n_zen_grid;
		static const int n_azi_grid;
		int draw_type;
		//wcda map relevant parameters
		double cell_x[900];
		double cell_y[900];
		double cell_z[900];
		//km2a map relevant parameters
		double ed_x[3600];
		double ed_y[3600];
		double ed_z[3600];
		double md_x[1800];
		double md_y[1800];
		double md_z[1800];

		//WFCTA Page INFO
		TPaveText *pave_info_event;
		TPaveText *pave_info_wfcta;
		//objects of drawing wfcta events
		TH2Poly *h2p_wfcta;
		TText *wfcta_scale_title;// = new TText(59,12,"log10(Npe)");
		TGraph *arr_dir_wcda;
		TGraph *arr_dir_km2a;
		TGraph *gr_centroid;
		TGraph *gcore_det_line_wcda;
		TGraph *gcore_det_line_km2a;
		TGraph *g_sdp;
		TGraph *g_sdp2;
		TGraph *gfram;
		TGraph *gr[36];
		TGraph *g_azi[36];
		
		//WCDA Page INFO
		TPaveText *pave_info_wcda;
		//WCDA objects of drawing wcda events
		TH2F *h2_wcda;
		int wcda_scale_drawed;
		TText *wcda_scale_title;// = new TText(59,12,"log10(Npe)");
		TGraph *g_sdp_ground_line_wcda;
		TGraph *g_core_inwcda1;
		TGraph *g_tel_inwcda1;
		
		//KM2A Page INFO
		TPaveText *pave_info_km2a1;
		TPaveText *pave_info_km2a;
		//KM2A objects of drawing km2a events
		TH2Poly *ed_h2p;
		TH2Poly *md_h2p;
		TText *ed_scale_title;// = new TText(59,12,"log10(Npe)");
		TText *md_scale_title;// = new TText(59,12,"log10(Npe)");
		TGraph *g_ed;
		TGraph *g_md;
		TGraph *g_sdp_ground_line_km2a;
		TGraph *g_core_inkm2a;
		TGraph *g_tel_inkm2a;

		//WFCTA FOCUS Page INFO
		TPaveText *pave_info_wfcta_focus;
		//WFCTA ON FOCUS objects of drawing wfcta events on focus
		TGraph *wfcta_focut_fram;
		TH2Poly *h2p_wfcta_focus;
		TText *wfcta_focus_scale_title;// = new TText(59,12,"log10(Npe)");
		TGraph *g_sdp_focus;
		TGraph *g_sdp_focus2;
		TGraph *gr_centroid_focus;
		TGraph *coredetectorline_focus;
		TGraph *arr_dir_wcda_f;
		TGraph *arr_dir_km2a_f;
		TLegend *leg_focus;
		//objects of drawing iamge alone sdp
		TGraph *g_evt_along_sdp;
		TGraph *g_time_along_sdp;
		TGraph *h_evt_along_sdp;
		TGaxis *slice_pix_axis;



		//COSMIC INFO objects of drawing cosmic event info
		TPaveText *pave_info_laser;
		//WFCTA objects of drawing laser event
		TGraph *g_laserline[6];
		//objects of drawing wfcta corsika events
		TGraph *g_wfcta_corsika;


		//draw wfcta map
		void DrawwfctaMap();
		void Drawwfctafram();
		void DrawZenGrid(int iz, double zen); //input: rad
		void DrawAziGrid(int ia, double azi); //input: rad
		//universal function
		double GetPointX(double p_zen, double p_azi); // input: rad
		double GetPointY(double p_zen, double p_azi); // input: rad
		void GetKm2aSDP();
		void GetPlaneNormal(double zenith1,double azimuth1,double zenith2,double azimuth2,double *x, double *y, double *z);
		void slaDs2tp ( double ra, double dec, double raz, double decz, double *xi, double *eta, int *j );
		void slaDtp2s ( double xi, double eta, double raz, double decz, double *ra, double *dec );
		// tansform pointing from tel1 to tel2
		//void PointTransform_firstversion(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen);
		//void PointTransform_backup(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen);
		//void PointTransform(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen);

	public:
		LHAASOEventShow();
		~LHAASOEventShow();
		TCanvas* lhaasocanvas;
		TCanvas* wcdacanvas;
		TCanvas* km2acanvas;
		TCanvas* lasercanvas;
		TCanvas* wfctacanvas;
		TCanvas* wfctacanvas_focus;
		TCanvas* sdpslicecanvas;

		//events information
		struct COSMIC_Event{
			long rbT;
			double rbt;
			int year;
			int month;
			int day;
			int hour;
			int minite;
			int second;
			double mjd;
			double event_energy;
			char detector_type[20];
			std::vector<int> v_triggerTel;
		};
		COSMIC_Event cosmic_event;
		struct WFCTA_Event{
			int maintel;
			double size;
			int npix;
			double meanx;
			double meany;
			double meanazi;
			double meanzen;
			double length, width;
			double ddelta;
			double groundx, groundy;
			double groundangle;
			double groundx_w, groundy_w;
			double groundangle_w;
			double groundx_k, groundy_k;
			double groundangle_k;
		};
		WFCTA_Event wfcta_event;
		struct WCDA_Event{
			double size;
			int nhit;
			double core_x, core_y;
			double Rp;
			double source_azi, source_zen; //rad
			double delta;  //angle between core-telescope line and cherenkov image length axis
			double source_miss;  //angle between source and cherenkov image length axis
			double D_Core2Line;
		};
		WCDA_Event wcda_event;
		struct KM2A_Event{
			double ED_hit, ED_part;
			double MD_hit, MD_part;
			double core_x, core_y;
			double Rp;
			double source_azi, source_zen; //rad
			double delta;  //angle between core-telescope line and cherenkov image length axis
			double source_miss;  //angle between source and cherenkov image length axis
			double D_Core2Line;
		};
		KM2A_Event km2a_event;

		//set infomation of wfcta wcda and km2a
		void SetCosmicInfo(long rb_T, double rb_t, double event_energy, const char* match_det_type, std::vector<int>& v_triggerTel);
		void SetWFCTAInfo(int maintel, double size, int npix, double meanx, double meany, double meanazi, double meanzen, double length, double width, double ddelta, 
				double groundx, double groundy, double groundangle, double groundx_w, double groundy_w, double groundangle_w, double groundx_k, double groundy_k, double groundangle_k);
		void SetWCDAInfo(double size, int nhit,	double core_x, double core_y, double Rp, double source_azi, double source_zen, double delta, double source_miss, double D_Core2Line);
		void SetKM2AInfo(double ED_hit, double ED_part, double MD_hit, double MD_part, double core_x, double core_y, double Rp, double source_azi, double source_zen, double delta, double source_miss, double D_Core2Line);
		void rbtime2lt(long rb_Time, double rb_time);
		void SetDrawType(int drawtype) {	draw_type = drawtype;}

		//draw cosmic event
		void DrawEventInfo(double rp_rec);
		void DrawWFCTA(const std::vector<int>& clean_sipm, const std::vector<double>& clean_pe, const std::vector<double>& clean_t);
		void DrawWCDA(const std::vector<double>& cell_x, const std::vector<double>& cell_y, const std::vector<double>& cell_pe);
		void DrawWFCTA_F(const std::vector<int>& clean_focus_sipm, const std::vector<double>& clean_focus_pe, const std::vector<double>& clean_focus_x, const std::vector<double>& clean_focus_y);
		void DrawEventAlongSDP(const std::vector<double>& sipm_coords, const std::vector<double>& sipm_pe, const std::vector<int>& sipm_pix);
		void DrawTimeAlongSDP(const std::vector<double>& slice_coords, const std::vector<double>& slice_t);

		//draw wfcta map
		void DrawWFCTAMap();
		void DrawWFCTAFocusMap();

		//laser
		void DrawLaserEvent(const std::vector<int>& clean_sipm, const std::vector<double>& clean_pe, const std::vector<double>& clean_t);
		void DrawEventInfoLaser(long rb_Time, double rb_time, double laser_size, int laser_npix);
		void DrawLaserLine(double l3_zen, double l3_azi);

		//draw wfcta corsika events
		void DrawCorsikaEvent(const std::vector<float>& p_zen, const std::vector<float>& p_azi);
		//void DrawWFCTAEvent(const std::vector<int>& clean_sipm, const std::vector<double>& clean_pe, const std::vector<double>& clean_t,
		//		double *efficiency);
		//draw wfcta events
		void DrawWFCTAEvent(const std::vector<int>& clean_sipm, const std::vector<double>& clean_pe, const std::vector<double>& clean_t);
		void DrawArrivalDirWcda(double source_zen, double source_azi); //rad
		void DrawArrivalDirKm2a(double source_zen, double source_azi); //rad
		void DrawCentroid(double mean_zen, double mean_azi); //rad
		void DrawSDP(int main_tel, double mean_zen, double mean_azi, double mean_x, double mean_y, double delta, double length); //rad
		void DrawSDP(int tel_id, double core_x, double core_y, double source_zen, double source_azi); //draw shower detector plan by using info from ground based array
		void DrawCoreDetLine();
		//draw wcda events
		void DrawWCDAEvent(const std::vector<double>& cell_x, const std::vector<double>& cell_y, const std::vector<double>& cell_pe);
		void DrawWCDAEvent(const std::vector<int>& cell_ig, const std::vector<double>& cell_pe, const std::vector<double>& cell_t);
		void DrawCoreWcda(double xc, double yc);
		void DrawSG_Line_Wcda(int main_tel, double ground_x, double ground_y);
		//draw km2a events
		void outputKm2aLat(double cor_x, double cor_y, const LHEvent& km2aevent, const char* clean="clean");
		void DrawKM2AMap();
		void DrawKM2AEvent(const LHEvent& km2aevent, const char* clean="clean");
		void DrawCoreKm2a(double xc, double yc);
		void DrawSG_Line_Km2a(int main_tel, double ground_x, double ground_y);
		//draw wfcta events on focus
		void DrawWFCTAEventFocus(const std::vector<int>& clean_focus_sipm, const std::vector<double>& clean_focus_pe, 
				const std::vector<double>& clean_focus_x, const std::vector<double>& clean_focus_y);
		void DrawArrivalDirWcda_F(int maintel, double source_zen, double source_azi); //rad
		void DrawArrivalDirKm2a_F(int maintel, double source_zen, double source_azi); //rad
		void DrawCoreDetectorLine_F(int maintel, double source_zen, double source_azi, double corex, double corey); //rad
		void DrawSDPFocus(double mean_x, double mean_y, double delta, double length); //rad
		void DrawSDPFocus(int tel_id, double core_x, double core_y, double source_zen, double source_azi); //draw shower detector plan by using info from ground based array
		void DrawCentroidFocus(double mean_x, double mean_y);

		//set wcda map
		void SetWCDAMap(double *x_igcell, double *y_igcell, double *z_igcell);
		//set km2a map
		void SetKM2AMap(double *x_ed, double *y_ed, double *z_ed, double *x_md, double *y_md, double *z_md);

};

#endif // LHAASOEVENTSHOW_H
