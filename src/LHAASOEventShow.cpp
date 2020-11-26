#include <time.h>
#include "TMath.h"
#include "TF1.h"
#include "LHAASOEventShow.h"
//using std::vector;
using namespace std;

const int LHAASOEventShow::n_zen_grid=4;
const int LHAASOEventShow::n_azi_grid=5;

LHAASOEventShow::LHAASOEventShow()
{
	printf("lhaaso event show ctor==================\n");

	draw_type=0;
	gStyle->SetOptStat(0);
	gStyle->SetPalette(kBird);

	//WFCTA Page Settings	
	pave_info_event = new TPaveText(0.1,0.1,0.9,0.9,"NDC");
	pave_info_event->SetBorderSize(1);

	h2p_wfcta = new TH2Poly();
	wfcta_scale_title = new TText(65,2,"log10(Npe)");
	wfcta_scale_title->SetTextAngle(90);
	arr_dir_wcda = new TGraph();
	arr_dir_km2a = new TGraph();
	arr_dir_wcda_f = new TGraph();
	arr_dir_km2a_f = new TGraph();
	gr_centroid = new TGraph();
	gcore_det_line_wcda = new TGraph();
	gcore_det_line_km2a = new TGraph();
	g_sdp = new TGraph();
	g_sdp2 = new TGraph();
	gfram = new TGraph();
	for(int i=0;i<36;i++)
	{
		gr[i] = new TGraph();
		g_azi[i] = new TGraph();
	}

	//wfcta corsika drawing objects
	g_wfcta_corsika = new TGraph(1);

	//wfcta focus drawing objects
	wfcta_focut_fram = new TGraph();
	h2p_wfcta_focus = new TH2Poly();
	wfcta_focus_scale_title = new TText(22,-5,"log10(Npe)");
	wfcta_focus_scale_title->SetTextAngle(90);
	g_sdp_focus = new TGraph();
	g_sdp_focus2 = new TGraph();
	gr_centroid_focus = new TGraph();
	coredetectorline_focus = new TGraph();

	//wfcta along sdp drawing objects
	g_evt_along_sdp = new TGraph(1);
	g_time_along_sdp = new TGraph(1);
	h_evt_along_sdp = new TGraph();
	slice_pix_axis = new TGaxis(0, 1, 1, 1, 0, 10, 510, "+L");
	slice_pix_axis->SetTitle("Npix_per_slice");
	slice_pix_axis->SetTitleSize(0.03);
	slice_pix_axis->SetTitleOffset(1.5);
	slice_pix_axis->SetTitleColor(2);
	slice_pix_axis->CenterTitle();

	//wcda drawing objects
	h2_wcda = new TH2F("position_absolute","",30,-75,75,30,-75,75);
	wcda_scale_drawed = 0;
	wcda_scale_title = new TText(115,-25,"log10(Npe)");
	wcda_scale_title->SetTextAngle(90);
	g_sdp_ground_line_wcda = new TGraph();
	g_core_inwcda1 = new TGraph();
	g_tel_inwcda1 = new TGraph();

	//km2a drawing objects
	g_ed = new TGraph();
	g_md = new TGraph();
	ed_h2p = new TH2Poly();
	md_h2p = new TH2Poly();
	ed_scale_title = new TText(950,-400,"log10(Nhit)");
	ed_scale_title->SetTextAngle(90);
	md_scale_title = new TText(950,-400,"log10(Nhit)");
	md_scale_title->SetTextAngle(90);
	g_sdp_ground_line_km2a = new TGraph();
	g_core_inkm2a = new TGraph();
	g_tel_inkm2a = new TGraph();

	//draw wfcta focus canvas
	pave_info_wfcta = new TPaveText(0.02,0.2,0.25,0.8,"NDC");
	pave_info_wfcta->SetBorderSize(1);
	wfctacanvas = new TCanvas("wfctacanvas","",1200,600);
	wfctacanvas->cd();
	gPad->SetMargin(0.25,0.25,0.25,0.25);
	gPad->SetTickx();
	gPad->SetTicky();

	pave_info_wcda = new TPaveText(0.1,0.2,0.4,0.8,"NDC");
	pave_info_wcda->SetBorderSize(1);
	wcdacanvas = new TCanvas("wcdacanvas","",1600,800);
	wcdacanvas->cd();
	gPad->SetMargin(0.5,0.1,0.1,0.1);
	gPad->SetTickx();
	gPad->SetTicky();
	//draw wcda and wfcta in one canvas
	lhaasocanvas = new TCanvas("lhaasocanvas","",1200,1200);//divide to (1,2)
//	lhaasocanvas = new TCanvas("lhaasocanvas","",1200,812.5);//divide to (1,2)  //new teteteteteteteetete
	lhaasocanvas->Divide(1,2);
	lhaasocanvas->cd(1);
	gPad->SetMargin(0.1,0.1,0.1,0.1);
	lhaasocanvas->cd(2);
//	lhaasocanvas->cd();    //new tettetettetetetet
	gPad->SetMargin(0.25,0.25,0.25,0.25);
	gPad->SetTickx();
	gPad->SetTicky();
	//gPad->SetMargin(0.1,0.1,0.1,0.1);
	//gPad->SetMargin(0.3,0.3,0.1,0.1);
	
	pave_info_km2a1 = new TPaveText(0.2,0.85,0.8,0.95,"NDC");
	pave_info_km2a1->SetBorderSize(1);
	pave_info_km2a = new TPaveText(0.2,0.85,0.8,0.95,"NDC");
	pave_info_km2a->SetBorderSize(1);
	km2acanvas = new TCanvas("km2acanvas","",1600,800);
	km2acanvas->Divide(2,1);
	km2acanvas->cd(1);
	gPad->SetMargin(0.2,0.2,0.2,0.2);
	gPad->SetTickx();
	gPad->SetTicky();
	km2acanvas->cd(2);
	gPad->SetMargin(0.2,0.2,0.2,0.2);
	gPad->SetTickx();
	gPad->SetTicky();
	//draw wfcta focus canvas
	leg_focus = new TLegend(0.2,0.72,0.8,0.86);
	pave_info_wfcta_focus = new TPaveText(0.2,0.88,0.8,0.98,"NDC");
	pave_info_wfcta_focus->SetBorderSize(1);
	wfctacanvas_focus = new TCanvas("wfctacanvas_focus","",1600,800);
	wfctacanvas_focus->Divide(2,1);
	wfctacanvas_focus->cd(1);
	gPad->SetMargin(0.2,0.2,0.1,0.3);
	gPad->SetTickx();
	gPad->SetTicky();
	wfctacanvas_focus->cd(2);
	gPad->SetMargin(0.1,0.1,0.2,0.2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetTickx();
	gPad->SetTicky();

	sdpslicecanvas = new TCanvas("sdpslicecanvas","",1200,800);
	sdpslicecanvas->cd();
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetTickx();
	gPad->SetTicky();

	//draw laser
	pave_info_laser = new TPaveText(0.2,0.72,0.8,0.8,"NDC");
	lasercanvas = new TCanvas("lasercanvas","",1600,800);//divide to (1,2)
	lasercanvas->cd();
	gPad->SetMargin(0.25,0.25,0.2,0.3);
	for(int i=0;i<6;i++)
	{
		g_laserline[i] = new TGraph();
	}


	for(int i=0;i<3600;i++)
	{
		ed_x[i] = 0; ed_y[i] = 0; ed_z[i] = 0;
	}
	for(int i=0;i<1800;i++)
	{
		md_x[i] = 0; md_y[i] = 0; md_z[i] = 0;
	}

}

LHAASOEventShow::~LHAASOEventShow()
{
	delete pave_info_event;
	delete pave_info_wfcta;
	delete pave_info_wfcta_focus;
	delete pave_info_wcda;
	delete pave_info_km2a;
	delete pave_info_km2a1;
	delete h2p_wfcta;
	delete wfcta_scale_title;
	delete arr_dir_wcda;
	delete arr_dir_km2a;
	delete arr_dir_wcda_f;
	delete arr_dir_km2a_f;
	delete gr_centroid;
	delete gcore_det_line_wcda;
	delete gcore_det_line_km2a;
	delete g_sdp;
	delete g_sdp2;
	delete gfram;
	for(int i=0;i<36;i++){
		delete gr[i];
		delete g_azi[i];
	}

	for(int i=0;i<6;i++)
	{
		delete g_laserline[i];
	}

	delete g_wfcta_corsika;

	delete sdpslicecanvas;
	delete g_evt_along_sdp;
	delete g_time_along_sdp;
	delete h_evt_along_sdp;
	delete slice_pix_axis;

	delete wfcta_focut_fram;
	delete g_sdp_focus;
	delete g_sdp_focus2;
	delete wfcta_focus_scale_title;
	delete h2p_wfcta_focus;
	delete gr_centroid_focus;
	delete coredetectorline_focus;
	delete leg_focus;

	delete h2_wcda;
	delete wcda_scale_title;
	delete wcdacanvas;
	delete g_sdp_ground_line_wcda;
	delete g_core_inwcda1;
	delete g_tel_inwcda1;

	delete g_ed;
	delete g_md;
	delete ed_h2p;
	delete md_h2p;
	delete ed_scale_title;
	delete md_scale_title;
	delete g_sdp_ground_line_km2a;
	delete g_core_inkm2a;
	delete g_tel_inkm2a;

	delete wfctacanvas;
	delete wfctacanvas_focus;
	delete lhaasocanvas;
	delete km2acanvas;
	delete lasercanvas;
	delete pave_info_laser;

}

//////////////////////
////_set_ WCDA map////
//////////////////////
void LHAASOEventShow::SetWCDAMap(double *x_igcell, double *y_igcell, double *z_igcell)
{   
	memcpy(cell_x, x_igcell, sizeof(double)*900);
	memcpy(cell_y, y_igcell, sizeof(double)*900);
	memcpy(cell_z, z_igcell, sizeof(double)*900);
}

//////////////////////
////_set_ KM2A map////
//////////////////////
void LHAASOEventShow::SetKM2AMap(double *x_ed, double *y_ed, double *z_ed, double *x_md, double *y_md, double *z_md)
{
	memcpy(ed_x, x_ed, sizeof(double)*3600);
	memcpy(ed_y, y_ed, sizeof(double)*3600);
	memcpy(ed_z, z_ed, sizeof(double)*3600);
	memcpy(md_x, x_md, sizeof(double)*1800);
	memcpy(md_y, y_md, sizeof(double)*1800);
	memcpy(md_z, z_md, sizeof(double)*1800);
}


////////////////////////
////_draw_ WFCTA map////
////////////////////////
void LHAASOEventShow::DrawWFCTAMap()
{
	printf("draw_type:%d\n", draw_type);
	if(1==draw_type)
	{
		lasercanvas->cd();
	}
	else
	{
		//wfctacanvas->cd();
//		lhaasocanvas->cd();  //new ttetetete
		lhaasocanvas->cd(2);
		if(1==WFCTAMap::Instance()->NTel())
			gPad->SetMargin(0.4,0.25,0.1,0.1); //tel10
			//gPad->SetMargin(0.26,0.26,0.1,0.1); //tel07
		else
//			gPad->SetMargin(0.15,0.15,0.15,0.15); // new tteteteteete
			gPad->SetMargin(0.33,0.12,0.15,0.15);
	}

	int ipot=0;
	for(int i=0;i<360;i++)
	{
		double zen = 10*n_zen_grid;
		if(1==WFCTAMap::Instance()->NTel())
		{
			if(i<135||i>225){continue;}
//			if(i>200){continue;}
		}
		else
		{
			if(i>200){continue;}
		}
		double azi = i+1;
		double xx = GetPointX(zen*TMath::DegToRad(),azi*TMath::DegToRad());//zen*cos(zen*TMath::DegToRad())*cos(azi*TMath::DegToRad());
		double yy = GetPointY(zen*TMath::DegToRad(),azi*TMath::DegToRad());//zen*cos(zen*TMath::DegToRad())*sin(azi*TMath::DegToRad());
		gr[n_zen_grid]->SetPoint(ipot,xx,yy);
		ipot++;
	}
//		gr[n_zen_grid]->SetPoint(ipot,0,0);
	gr[n_zen_grid]->SetLineStyle(2);
	gr[n_zen_grid]->Draw("al");
	gr[n_zen_grid]->GetXaxis()->SetTitle("West<-->East (^{o})");
	gr[n_zen_grid]->GetXaxis()->CenterTitle();
	gr[n_zen_grid]->GetYaxis()->SetTitle("South<-->North (^{o})");
	gr[n_zen_grid]->GetYaxis()->CenterTitle();
//	gr[n_zen_grid]->GetYaxis()->SetRangeUser(-14,31);
	wfcta_scale_title->Draw("same");
	//gr[n_zen_grid]->GetXaxis()->ChangeLabel(1,-1,-1,-1,kBlack,-1,Form("%.2lf",-TMath::RadToDeg()*asin(60/90.)));

	//DrawwfctaMap();
	Drawwfctafram();

	//add counter line
	for(int iz=0;iz<n_zen_grid;iz++) {
		DrawZenGrid(iz,iz*10*TMath::DegToRad());
	}
	for(int ia=0;ia<n_azi_grid;ia++) {
		DrawAziGrid(ia,ia*45*TMath::DegToRad());
	}

}
void LHAASOEventShow::DrawWFCTAFocusMap()
{
	wfctacanvas_focus->cd(1);
	double sipm_x, sipm_y;
	int ipot=0;
	for(int ii=0;ii<1024;ii++)
	{
		if(ii/32==0 || ii/32==31 || ii%32==0 ||ii%32==31){
			WFCTAMap::Instance()->GetSipmXY(ii, sipm_x, sipm_y);
			sipm_x *= TMath::RadToDeg();
			sipm_y *= TMath::RadToDeg();
			wfcta_focut_fram->SetPoint(ipot,sipm_x,sipm_y);
			ipot++;
		}
	}
	double edge = 12;
	wfcta_focut_fram->SetPoint(ipot,-edge,-edge);
	ipot++;
	wfcta_focut_fram->SetPoint(ipot,-edge,edge);
	ipot++;
	wfcta_focut_fram->SetPoint(ipot,edge,edge);
	ipot++;
	wfcta_focut_fram->SetPoint(ipot,edge,-edge);
	ipot++;
	wfcta_focut_fram->GetXaxis()->SetTitle("X (^{o})");
	wfcta_focut_fram->GetXaxis()->CenterTitle();
	wfcta_focut_fram->GetYaxis()->SetTitle("Y (^{o})");
	wfcta_focut_fram->GetYaxis()->CenterTitle();
	//wfcta_focut_fram->GetYaxis()->SetRangeUser(-10,10);
	//wfcta_focut_fram->GetXaxis()->SetRangeUser(-10,10);
	wfcta_focut_fram->Draw("ap");
	wfcta_focus_scale_title->Draw("same");
}
void LHAASOEventShow::DrawwfctaMap()
{
	double sipm_azi, sipm_zen;
	//add sipm map
	for(int ii=0;ii<WFCTAMap::Instance()->NSipm();ii++)
	{
		double x[5]={0};
		double y[5]={0};
		for(int ipot=0;ipot<4;ipot++){
			double imagex,imagey;
			if(ipot==0)		{	imagex=-0.25;	imagey=-0.25;}
			else if(ipot==1)	{	imagex=-0.25;	imagey=0.25;}
			else if(ipot==2)	{	imagex=0.25;	imagey=0.25;}
			else if(ipot==3)	{	imagex=0.25;	imagey=-0.25;}
			double imageazi,imagezen;
			WFCTAMap::Instance()->GetSipmAZ(ii, sipm_azi, sipm_zen);
			slaDtp2s(imagex*TMath::DegToRad(),imagey*TMath::DegToRad(),sipm_azi,90*TMath::DegToRad()-sipm_zen,&imageazi,&imagezen);
			imagezen = 90*TMath::DegToRad() - imagezen;
			x[ipot] = GetPointX(imagezen,imageazi);
			y[ipot] = GetPointY(imagezen,imageazi);
		}
		x[4] = x[0];
		y[4] = y[0];
		h2p_wfcta->AddBin(5,x,y);
	}
	h2p_wfcta->Draw("colz same");
	//h2p_wfcta->Draw("colz");
	//h2p_wfcta->GetYaxis()->SetRangeUser(18,54);

}
void LHAASOEventShow::Drawwfctafram()
{
	double sipm_azi, sipm_zen;
	int ipot=0;
	for(int ii=0;ii<WFCTAMap::Instance()->NSipm();ii++)
	{
		int is = ii%1024;
		if(is/32==0 || is/32==31 || is%32==0 ||is%32==31){
			double azi, zen;
			WFCTAMap::Instance()->GetSipmAZ(ii, sipm_azi, sipm_zen);
			double xx = GetPointX(sipm_zen,sipm_azi);
			double yy = GetPointY(sipm_zen,sipm_azi);
			gfram->SetPoint(ipot,xx,yy);
			ipot++;
		}
	}
	gfram->Draw("psame");
}
void LHAASOEventShow::DrawZenGrid(int iz, double zen) //rad
{
	//add counter line
	//set axis label
	int ipot=0;
	for(int i=0;i<360;i++)
	{
		double azi = (i+1);
		double xx = GetPointX(zen,azi*TMath::DegToRad());//zen*cos(zen*TMath::DegToRad())*cos(azi*TMath::DegToRad());
		double yy = GetPointY(zen,azi*TMath::DegToRad());//zen*cos(zen*TMath::DegToRad())*sin(azi*TMath::DegToRad());
		gr[iz]->SetPoint(ipot,xx,yy);
		ipot++;
	}
	gr[iz]->SetLineStyle(2);
	gr[iz]->Draw("lsame");
}
void LHAASOEventShow::DrawAziGrid(int ia, double azi) //input: rad
{
	int ipot=0;
	for(int i=0;i<10*n_zen_grid;i++)
	{
		double zen = (i+1);
		double xx = GetPointX(zen*TMath::DegToRad(),azi);//zen*cos(zen*TMath::DegToRad())*cos(azi*TMath::DegToRad());
		double yy = GetPointY(zen*TMath::DegToRad(),azi);//zen*cos(zen*TMath::DegToRad())*sin(azi*TMath::DegToRad());
		g_azi[ia]->SetPoint(ipot,xx,yy);
		ipot++;
	}
	g_azi[ia]->SetLineStyle(2);
	g_azi[ia]->Draw("lsame");
}


///////////////////////
////_draw_ KM2A map////
///////////////////////
void LHAASOEventShow::DrawKM2AMap()
{
	//lhaasocanvas->cd(4);
	km2acanvas->cd(1);
	int ipot=0;
	for(int ii=0;ii<3600;ii++)
	{
		if(0==ed_z[ii]){continue;}
		g_ed->SetPoint(ipot,ed_x[ii],ed_y[ii]);
		ipot++;
	}
	g_ed->SetMarkerStyle(97);
	g_ed->SetMarkerColor(18);
	g_ed->Draw("ap");
	g_ed->GetXaxis()->SetRangeUser(-650,650);
	g_ed->GetYaxis()->SetRangeUser(-750,550);
	ipot=0;
	for(int ii=0;ii<1800;ii++)
	{
		if(0==md_z[ii]){continue;}
		g_md->SetPoint(ipot,md_x[ii],md_y[ii]);
		ipot++;
	}
	g_md->SetMarkerStyle(4);
	g_md->SetMarkerColor(16);
	g_md->Draw("psame");
	md_scale_title->Draw("same");

	km2acanvas->cd(2);
	g_ed->Draw("ap");
	g_md->Draw("psame");
	g_ed->GetXaxis()->SetTitle("X (m)");
	g_ed->GetXaxis()->CenterTitle();
	g_ed->GetYaxis()->SetTitle("Y (m)");
	g_ed->GetYaxis()->CenterTitle();
	ed_scale_title->Draw("same");
}

/////////////////////////////
////_draw_ Set Event info////
/////////////////////////////
void LHAASOEventShow::SetCosmicInfo(long rb_T, double rb_t, double event_energy, const char* match_det_type, std::vector<int>& v_triggerTel)
{
	cosmic_event.rbT = rb_T;
	cosmic_event.rbt = rb_t;
	rbtime2lt(rb_T, rb_t);
	cosmic_event.event_energy = event_energy;
	strcpy(cosmic_event.detector_type, match_det_type);
	cosmic_event.v_triggerTel.clear();
	for(int ii=0; ii<v_triggerTel.size(); ii++)
	{
		cosmic_event.v_triggerTel.push_back(v_triggerTel.at(ii));
	}
}
void LHAASOEventShow::SetWFCTAInfo(int maintel, double size, int npix, double meanx, double meany, double meanazi, double meanzen, double length, double width, double ddelta, 
		double groundx, double groundy, double groundangle, double groundx_w, double groundy_w, double groundangle_w, double groundx_k, double groundy_k, double groundangle_k)
{
	wfcta_event.maintel = maintel;
	wfcta_event.size = size;
	wfcta_event.npix = npix;
	wfcta_event.meanx = meanx;
	wfcta_event.meany = meany;
	wfcta_event.meanazi = meanazi;
	wfcta_event.meanzen = meanzen;
	wfcta_event.length = length;
	wfcta_event.width = width;
	wfcta_event.ddelta = ddelta;
	wfcta_event.groundx = groundx;
	wfcta_event.groundy = groundy;
	wfcta_event.groundangle = groundangle;
	wfcta_event.groundx_w = groundx_w;
	wfcta_event.groundy_w = groundy_w;
	wfcta_event.groundangle_w = groundangle_w;
	wfcta_event.groundx_k = groundx_k;
	wfcta_event.groundy_k = groundy_k;
	wfcta_event.groundangle_k = groundangle_k;
}
void LHAASOEventShow::SetWCDAInfo(double size, int nhit, double core_x, double core_y, double Rp, double source_azi, double source_zen, double delta, double source_miss, double D_Core2Line)
{
	wcda_event.size = size;
	wcda_event.nhit = nhit;
	wcda_event.core_x = core_x;
	wcda_event.core_y = core_y;
	wcda_event.Rp = Rp;
	wcda_event.source_azi = source_azi;
	wcda_event.source_zen = source_zen;
	wcda_event.delta = delta;
	wcda_event.source_miss = source_miss;
	wcda_event.D_Core2Line = D_Core2Line;
	//printf("wcda_event.size:%lf wcda_event.nhit:%d wcda_event.core_x:%lf wcda_event.core_y:%lf wcda_event.Rp:%lf\n", wcda_event.size, wcda_event.nhit, wcda_event.core_x, wcda_event.core_y, wcda_event.Rp);
}
void LHAASOEventShow::SetKM2AInfo(double ED_hit, double ED_part, double MD_hit, double MD_part, double core_x, double core_y, double Rp, double source_azi, double source_zen, double delta, double source_miss, double D_Core2Line)
{
	km2a_event.ED_hit = ED_hit;
	km2a_event.ED_part = ED_part;
	km2a_event.MD_hit = MD_hit;
	km2a_event.MD_part = MD_part;
	km2a_event.core_x = core_x;
	km2a_event.core_y = core_y;
	km2a_event.Rp = Rp;
	km2a_event.source_azi = source_azi;
	km2a_event.source_zen = source_zen;
	km2a_event.delta = delta;
	km2a_event.source_miss = source_miss;
	km2a_event.D_Core2Line = D_Core2Line;
}


/////////////////////////
////_draw_ Event info////
/////////////////////////
void LHAASOEventShow::DrawEventInfoLaser(long rb_Time, double rb_time, double laser_size, int laser_npix)
{
	lasercanvas->cd();
	pave_info_laser->Clear();
	//pave_info_laser->AddText("#diamond Laser Info:");
	pave_info_laser->AddText(Form("rb_Time: %ld+%.9lf (s)",rb_Time, rb_time/1000000000));
	pave_info_laser->AddText(Form("Npix: %d, log_{10}(Size): %.2lf",laser_npix, log10(laser_size)));
	pave_info_laser->SetBorderSize(1);
	pave_info_laser->Draw();
}
void LHAASOEventShow::DrawEventInfo(double rp_rec)
{
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(wfcta_event.maintel, tel_x, tel_y);
	lhaasocanvas->cd(1);
	std::cout<< "cd to lhaasocanvas 1, draw event info"<<std::endl;

	char tri_tels[200];
	char tri_tel[100];
	strcpy(tri_tels,"WFCTA(");
	int v_triggerTellen = cosmic_event.v_triggerTel.size();
	printf("v_triggerTellen:%d \n", v_triggerTellen);
	if(v_triggerTellen>0)
	{
		for(int ii=0;ii<v_triggerTellen-1;ii++)
		{
			snprintf(tri_tel, 6, "T%02d, \n", cosmic_event.v_triggerTel.at(ii));
			strcat(tri_tels,tri_tel);
		}
		snprintf(tri_tel, 6, "T%02d", cosmic_event.v_triggerTel.at(v_triggerTellen-1));
		strcat(tri_tels,tri_tel);
	}
	strcat(tri_tels,")");

	pave_info_event->Clear();
	pave_info_event->AddText("#diamond Event Info:");
	pave_info_event->AddText(Form("EventType: %s + %s",tri_tels, cosmic_event.detector_type));
	pave_info_event->AddText(Form("Time: %4d-%02d%02d %02d:%02d:%02d",cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));
	pave_info_event->AddText(Form("Time(Mjd): %lf",cosmic_event.mjd));
	pave_info_event->AddText(Form("rb_Time: %ld (s), rb_time: %.0lf (ns)",cosmic_event.rbT, cosmic_event.rbt));
	
	if(cosmic_event.event_energy<6)
		pave_info_event->AddText(Form("recE: %.2lf TeV | Rp: %.2lf(m)",pow(10,cosmic_event.event_energy)/1000, rp_rec));
	if(cosmic_event.event_energy>=6)
		pave_info_event->AddText(Form("recE: %.2lf PeV | Rp: %.2lf(m)",pow(10,cosmic_event.event_energy)/1000000, rp_rec));
	pave_info_event->Draw();  ///new ttttt  afdssfd

	//wfctacanvas->cd();
	lhaasocanvas->cd(2);
	pave_info_wfcta->Clear();
	pave_info_wfcta->AddText(Form("log_{10}(Size): %.2lf", log10(wfcta_event.size)));
	pave_info_wfcta->AddText(Form("Npix: %d", wfcta_event.npix));
	pave_info_wfcta->AddText(Form("Centroid: (Zen:%.2lf^{o},Azi:%.2lf^{o})",wfcta_event.meanzen*TMath::RadToDeg(), wfcta_event.meanazi*TMath::RadToDeg()));
	pave_info_wfcta->AddText(Form("Length&Width: (%.2lf^{o},%.2lf^{o})",wfcta_event.length*TMath::RadToDeg(), wfcta_event.width*TMath::RadToDeg()));
	pave_info_wfcta->AddText(Form("Length/Width: %.2lf",wfcta_event.length/wfcta_event.width));
	pave_info_wfcta->AddText(Form("GroundXY: (%.2lf,%.2lf)",wfcta_event.groundx, wfcta_event.groundy));
	pave_info_wfcta->AddText(Form("Angle: %.2lf^{o}",TMath::ATan2(wfcta_event.groundy,wfcta_event.groundx)*TMath::RadToDeg()));
	pave_info_wfcta->Draw();  ///new tttttt adafd

	wcdacanvas->cd();
	pave_info_wcda->Clear();
	pave_info_wcda->AddText(Form("log10(Total Size): %.2lf",log10(wcda_event.size)));
	pave_info_wcda->AddText(Form("Total Hit: %d",wcda_event.nhit));
	pave_info_wcda->AddText(Form("Core_inWCDA1(m): (%.2lf,%.2lf)",wcda_event.core_x, wcda_event.core_y));
	pave_info_wcda->AddText(Form("Rp_wcda(m): %.2lf",wcda_event.Rp));
	pave_info_wcda->AddText(Form("Source_wcda: (%.2lf^{o},%.2lf^{o})",wcda_event.source_zen*TMath::RadToDeg(),wcda_event.source_azi*TMath::RadToDeg()));
	pave_info_wcda->AddText(Form("Delta: %.2lf^{o}, D_CoreToLine: %.2lf(m)",wcda_event.delta*TMath::RadToDeg(),wcda_event.D_Core2Line));
	pave_info_wcda->AddText(Form("Source_Miss: %.2lf^{o}",wcda_event.source_miss*TMath::RadToDeg()));
	pave_info_wcda->Draw();

	km2acanvas->cd(1);
	pave_info_km2a1->Clear();
	pave_info_km2a1->AddText(Form("ED_hit: %.0lf, MD_hit: %.0lf",km2a_event.ED_hit, km2a_event.MD_hit));
	pave_info_km2a1->AddText(Form("ED_partical: %.0lf, MD_partical: %.0lf",km2a_event.ED_part, km2a_event.MD_part));
	pave_info_km2a1->Draw();
	km2acanvas->cd(2);
	pave_info_km2a->Clear();
	pave_info_km2a->AddText(Form("Core_km2a(m): (%.2lf,%.2lf)",km2a_event.core_x, km2a_event.core_y));
	pave_info_km2a->AddText(Form("Rp_km2a(m): %.2lf  |  Source_km2a: (%.2lf^{o},%.2lf^{o})",km2a_event.Rp, km2a_event.source_zen*TMath::RadToDeg(), km2a_event.source_azi*TMath::RadToDeg()));
	pave_info_km2a->AddText(Form("Delta: %.2lf^{o}, D_CoreToLine: %.2lf(m)",km2a_event.delta*TMath::RadToDeg(),km2a_event.D_Core2Line));
	pave_info_km2a->Draw();

	wfctacanvas_focus->cd(1);
	pave_info_wfcta_focus->Clear();
	pave_info_wfcta_focus->AddText(Form("log_{10}(Size): %.2lf | Npix: %d", log10(wfcta_event.size), wfcta_event.npix));
	pave_info_wfcta_focus->Draw();

}


//////////////////////////////////
////_draw_ WFCTA Event////
//////////////////////////////////
void LHAASOEventShow::DrawWFCTA(const std::vector<int>& clean_sipm, const std::vector<double>& clean_pe, const std::vector<double>& clean_t)
{
	DrawWFCTAEvent(clean_sipm, clean_pe, clean_t);
	DrawArrivalDirWcda(wcda_event.source_zen, wcda_event.source_azi);
	DrawArrivalDirKm2a(km2a_event.source_zen, km2a_event.source_azi);
	DrawCentroid(wfcta_event.meanzen, wfcta_event.meanzen);
	DrawSDP(wfcta_event.maintel, wfcta_event.meanzen, wfcta_event.meanzen, wfcta_event.meanx, wfcta_event.meany, wfcta_event.ddelta, wfcta_event.length);
	//DrawSDP(wfcta_event.maintel, km2a_event.core_x, km2a_event.core_y, km2a_event.source_zen, km2a_event.source_azi);
	DrawSDP(1, km2a_event.core_x, km2a_event.core_y, km2a_event.source_zen, km2a_event.source_azi);
}

void LHAASOEventShow::DrawWCDA(const std::vector<double>& cell_x, const std::vector<double>& cell_y, const std::vector<double>& cell_pe)
{
	DrawWCDAEvent(cell_x,cell_y,cell_pe);
	DrawCoreWcda(wcda_event.core_x, wcda_event.core_y);
	DrawSG_Line_Wcda(wfcta_event.maintel, wfcta_event.groundx_w, wfcta_event.groundy_w);
}

void LHAASOEventShow::DrawWFCTA_F(const std::vector<int>& clean_focus_sipm, const std::vector<double>& clean_focus_pe, const std::vector<double>& clean_focus_x, const std::vector<double>& clean_focus_y)
{
	DrawWFCTAEventFocus(clean_focus_sipm, clean_focus_pe, clean_focus_x, clean_focus_y);
	DrawSDPFocus(wfcta_event.meanx, wfcta_event.meany, wfcta_event.ddelta, wfcta_event.length);
	//DrawSDPFocus(wfcta_event.maintel, km2a_event.core_x, km2a_event.core_y, km2a_event.source_zen, km2a_event.source_azi);
	DrawSDPFocus(1, km2a_event.core_x, km2a_event.core_y, km2a_event.source_zen, km2a_event.source_azi);
	DrawCentroidFocus(wfcta_event.meanx, wfcta_event.meany);
	DrawArrivalDirWcda_F(wfcta_event.maintel, wcda_event.source_zen, wcda_event.source_azi);
	DrawArrivalDirKm2a_F(wfcta_event.maintel, km2a_event.source_zen, km2a_event.source_azi);
}


//////////////////////////////////
////_draw_ WFCTA Corsika Event////
//////////////////////////////////
void LHAASOEventShow::DrawCorsikaEvent(const std::vector<float>& p_zen, const std::vector<float>& p_azi)
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	int npoints = g_wfcta_corsika->GetN();
	printf("npoints_grap:%d\n",npoints);
	for(int ip=npoints-1;ip>0;ip--)
	{
		g_wfcta_corsika->RemovePoint(ip);
	}
	int ipot=0;
	for(int i=0;i<p_zen.size();i++)
	{
		double x = GetPointX(p_zen.at(i), p_azi.at(i));
		double y = GetPointY(p_zen.at(i), p_azi.at(i));
		g_wfcta_corsika->SetPoint(ipot,x,y);
		ipot++;
	}

	g_wfcta_corsika->Draw("psame");
}

//////////////////////////
////_draw_ WFCTA Event////
//////////////////////////
void LHAASOEventShow::DrawWFCTAEventFocus(const std::vector<int>& clean_focus_sipm, const vector<double>& clean_focus_pe, 
		const vector<double>& clean_focus_x, const vector<double>& clean_focus_y)
{
	wfctacanvas_focus->cd(1);
	//wfcta_focut_fram->SetTitle(Form("Time:%lld+%.9lf (%4d/%02d/%02d %02d:%02d:%02d)",cosmic_event.rbT,cosmic_event.rbt/1000000000,cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));

	if(h2p_wfcta_focus) {
		printf("delete h2p_wfcta_focus\n");
		delete h2p_wfcta_focus;
	}
	h2p_wfcta_focus = new TH2Poly();
	int ibin=0;
	for(int ii=0;ii<clean_focus_pe.size();ii++)
	{
		if(clean_focus_pe.at(ii)<=0){continue;}
		//printf("clean_focus_pe:%lf %lf %lf \n",clean_focus_pe.at(ii), clean_focus_x.at(ii)*57.3, clean_focus_y.at(ii)*57.3);

		double x[25]={0};
		double y[25]={0};
		int npots=4;
		double imagex = clean_focus_x.at(ii)*TMath::RadToDeg();
		double imagey = clean_focus_y.at(ii)*TMath::RadToDeg();
		if(clean_focus_sipm.at(ii)<1024*1)
			npots=4;
		else
			npots=24;
		for(int ipot=0;ipot<npots;ipot++){
			double itheta = (45+ipot*(360/npots))*TMath::DegToRad();
			if(4==npots)
			{
				x[ipot] = imagex+0.25*sqrt(2)*cos(itheta);
				y[ipot] = imagey+0.25*sqrt(2)*sin(itheta);
			}
			else
			{
				x[ipot] = imagex+0.25*cos(itheta);
				y[ipot] = imagey+0.25*sin(itheta);
			}
		}
		x[npots] = x[0];
		y[npots] = y[0];
		h2p_wfcta_focus->AddBin(npots,x,y);
		ibin++;
		double content = log10(clean_focus_pe.at(ii));
		h2p_wfcta_focus->SetBinContent(ibin,content);
	}

	h2p_wfcta_focus->SetMaximum(5);
	h2p_wfcta_focus->SetMinimum(1);
	h2p_wfcta_focus->Draw("colz same");
}

void LHAASOEventShow::DrawArrivalDirWcda_F(int maintel, double source_zen, double source_azi) //rad
{
	wfctacanvas_focus->cd(1);
	int jj;
	double source_x, source_y;
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(maintel, tel_azi, tel_zen);
	slaDs2tp(source_azi, 90*TMath::DegToRad()-source_zen, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &source_x, &source_y, &jj);
	arr_dir_wcda_f->SetPoint(0,source_x*TMath::RadToDeg(),source_y*TMath::RadToDeg());
	arr_dir_wcda_f->SetMarkerStyle(2);
	arr_dir_wcda_f->SetMarkerSize(1);
	arr_dir_wcda_f->SetMarkerColor(1);
	arr_dir_wcda_f->Draw("psame");
	leg_focus->AddEntry(arr_dir_wcda_f,"Source Reconstructed by WCDA","p");
}
void LHAASOEventShow::DrawArrivalDirKm2a_F(int maintel, double source_zen, double source_azi) //rad
{
	wfctacanvas_focus->cd(1);
	int jj;
	double source_x, source_y;
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(maintel, tel_azi, tel_zen);
	slaDs2tp(source_azi, 90*TMath::DegToRad()-source_zen, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &source_x, &source_y, &jj);
	arr_dir_km2a_f->SetPoint(0,source_x*TMath::RadToDeg(),source_y*TMath::RadToDeg());
	arr_dir_km2a_f->SetMarkerStyle(2);
	arr_dir_km2a_f->SetMarkerSize(1);
	arr_dir_km2a_f->SetMarkerColor(2);
	arr_dir_km2a_f->Draw("psame");
	leg_focus->AddEntry(arr_dir_km2a_f,"Source Reconstructed by KM2A","p");
	leg_focus->Draw("same");
}
void LHAASOEventShow::DrawCoreDetectorLine_F(int maintel, double source_zen, double source_azi, double corex, double corey) //m
{
	wfctacanvas_focus->cd(1);
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(maintel, tel_x, tel_y);
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(maintel, tel_azi, tel_zen);

	double m0 = sin(source_zen)*cos(source_azi);
	double n0 = sin(source_zen)*sin(source_azi);
	double l0 = cos(source_zen);

	int jj;
	for(int i=0;i<50;i++)
	{
		double zz = i*100;
		double xx = m0*zz/l0 + corex;
		double yy = n0*zz/l0 + corey;
		double v_x = xx - tel_x;
		double v_y = yy - tel_y;
		double v_z = zz;
		double norm = sqrt(v_x*v_x + v_y*v_y + v_z*v_z);
		v_x /= norm;
		v_y /= norm;
		v_z /= norm;
		double phi = TMath::ATan2(v_y,v_x);
		double theta = acos(v_z);
		double CoreAtFocusX, CoreAtFocusY;
		slaDs2tp ( phi, 90*TMath::DegToRad() - theta, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &CoreAtFocusX, &CoreAtFocusY, &jj );
//		printf("core_jj:%d\n",jj);
		if(0!=jj){continue;}
		CoreAtFocusX *= TMath::RadToDeg();
		CoreAtFocusY *= TMath::RadToDeg();
		coredetectorline_focus->SetPoint(0, CoreAtFocusX, CoreAtFocusY);
		break;
	}
	double source_x, source_y;
	slaDs2tp(source_azi, 90*TMath::DegToRad()-source_zen, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &source_x, &source_y, &jj);
//	printf("source_jj:%d\n",jj);
	coredetectorline_focus->SetPoint(1, source_x*TMath::RadToDeg(), source_y*TMath::RadToDeg());
	coredetectorline_focus->Draw("lsame");

}

void LHAASOEventShow::DrawWFCTAEvent(const vector<int>& clean_sipm, const vector<double>& clean_pe, const vector<double>& clean_t)
{
	double slice[32]={0};
	double slice0[32]={0};
	//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	//gr[n_zen_grid]->SetTitle(Form("Time:%lld+%.9lf (%4d/%02d/%02d %02d:%02d:%02d)",cosmic_event.rbT,cosmic_event.rbt/1000000000,cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));

	if(h2p_wfcta) {
		printf("delete h2p_wfcta\n");
		delete h2p_wfcta;
	}
	h2p_wfcta = new TH2Poly();
	int ibin=0;
	for(int ii=0;ii<clean_sipm.size();ii++)
	{
		int iisipm = clean_sipm.at(ii);

		double x[25]={0};
		double y[25]={0};
		double sipm_azi, sipm_zen;
		int npots=4;
		if(iisipm<1024*1)
			npots=4;
		else
			npots=24;

		for(int ipot=0;ipot<npots;ipot++){
			double itheta = (45+ipot*(360/npots))*TMath::DegToRad();
			double imagex,imagey;
			if(4==npots) {
				imagex=0.25*sqrt(2)*cos(itheta);
				imagey=0.25*sqrt(2)*sin(itheta);
			}
			else {
				imagex=0.25*cos(itheta);
				imagey=0.25*sin(itheta);
			}
			double imageazi,imagezen;
			WFCTAMap::Instance()->GetSipmAZ(iisipm, sipm_azi, sipm_zen);
			slaDtp2s(imagex*TMath::DegToRad(), imagey*TMath::DegToRad(), sipm_azi, 90*TMath::DegToRad()-sipm_zen, &imageazi,&imagezen);
			imagezen = 90*TMath::DegToRad() - imagezen;
			x[ipot] = GetPointX(imagezen,imageazi);
			y[ipot] = GetPointY(imagezen,imageazi);
		}
		x[npots] = x[0];
		y[npots] = y[0];
		h2p_wfcta->AddBin(npots,x,y);

		ibin++;
		double content;
		//		double pe = clean_pe.at(ii)/efficiency[iisipm];
		content = log10(clean_pe.at(ii));	//scale by npe
		//content = (clean_t.at(ii));	//scale by t
		//printf("wfcta event: %d %lf\n",iisipm,clean_pe.at(ii));
		h2p_wfcta->SetBinContent(ibin,content);

		//slice[iisipm/32] += pe;
		//slice0[iisipm/32] += clean_pe.at(ii);
	}

	h2p_wfcta->SetMaximum(5);
	h2p_wfcta->SetMinimum(1);
	h2p_wfcta->Draw("colz same");
}

void LHAASOEventShow::DrawLaserEvent(const vector<int>& clean_sipm, const vector<double>& clean_pe, const vector<double>& clean_t)
{
	lasercanvas->cd();
	if(h2p_wfcta) {
		printf("delete h2p_wfcta\n");
		delete h2p_wfcta;
	}
	h2p_wfcta = new TH2Poly();
	int ibin=0;
	for(int ii=0;ii<clean_sipm.size();ii++)
	{
		int iisipm = clean_sipm.at(ii);
		double x[5]={0};
		double y[5]={0};
		double sipm_azi, sipm_zen;
		for(int ipot=0;ipot<4;ipot++){
			double imagex,imagey;
			if(ipot==0)		{	imagex=-0.25;	imagey=-0.25;}
			else if(ipot==1)	{	imagex=-0.25;	imagey=0.25;}
			else if(ipot==2)	{	imagex=0.25;	imagey=0.25;}
			else if(ipot==3)	{	imagex=0.25;	imagey=-0.25;}
			double imageazi,imagezen;
			WFCTAMap::Instance()->GetSipmAZ(iisipm, sipm_azi, sipm_zen);
			slaDtp2s(imagex*TMath::DegToRad(),imagey*TMath::DegToRad(),sipm_azi,90*TMath::DegToRad()-sipm_zen,&imageazi,&imagezen);
			imagezen = 90*TMath::DegToRad() - imagezen;
			x[ipot] = GetPointX(imagezen,imageazi);
			y[ipot] = GetPointY(imagezen,imageazi);
		}
		x[4] = x[0];
		y[4] = y[0];
		h2p_wfcta->AddBin(5,x,y);
		ibin++;
		double content;
		content = log10(clean_pe.at(ii));	//scale by npe
		//content = (clean_t.at(ii));	//scale by npe
		//printf("wfcta event: %d %lf\n",iisipm,clean_pe.at(ii));
		h2p_wfcta->SetBinContent(ibin,content);

	}
	h2p_wfcta->Draw("colz same");
}

void LHAASOEventShow::DrawArrivalDirWcda(double source_zen, double source_azi) //rad
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	double source_xx = GetPointX(source_zen, source_azi);
	double source_yy = GetPointY(source_zen, source_azi);
	arr_dir_wcda->SetPoint(0,source_xx,source_yy);
	arr_dir_wcda->SetMarkerStyle(2);
	arr_dir_wcda->SetMarkerSize(0.5);
	arr_dir_wcda->SetMarkerColor(1);
	arr_dir_wcda->Draw("psame");
}
void LHAASOEventShow::DrawArrivalDirKm2a(double source_zen, double source_azi) //rad
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	double source_xx_km2a = GetPointX(source_zen, source_azi);
	double source_yy_km2a = GetPointY(source_zen, source_azi);
	arr_dir_km2a->SetPoint(0,source_xx_km2a,source_yy_km2a);
	arr_dir_km2a->SetMarkerStyle(2);
	arr_dir_km2a->SetMarkerSize(0.5);
	arr_dir_km2a->SetMarkerColor(2);
	arr_dir_km2a->Draw("psame");
}



void LHAASOEventShow::DrawCentroidFocus(double mean_x, double mean_y)
{
	wfctacanvas_focus->cd(1);
	gr_centroid_focus->SetPoint(0,mean_x*TMath::RadToDeg(),mean_y*TMath::RadToDeg());
	gr_centroid_focus->SetMarkerStyle(2);
	gr_centroid_focus->SetMarkerSize(1.5);
	gr_centroid_focus->SetMarkerColor(3);
	gr_centroid_focus->Draw("psame");
	leg_focus->Clear();
	leg_focus->AddEntry(gr_centroid_focus,"Centroid of Cherenkov Image","p");
}
void LHAASOEventShow::DrawCentroid(double mean_zen, double mean_azi)
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	double xx = GetPointX(mean_zen, mean_azi);
	double yy = GetPointY(mean_zen, mean_azi);
	gr_centroid->SetPoint(0,xx,yy);
	gr_centroid->SetMarkerStyle(2);
	gr_centroid->SetMarkerSize(0.5);
	gr_centroid->SetMarkerColor(3);
	gr_centroid->Draw("psame");
}

void LHAASOEventShow::DrawSDPFocus(double mean_x, double mean_y, double delta, double length)
{
	wfctacanvas_focus->cd(1);

	int ipot = 0;
	double tel_azi, tel_zen;
	for(int i=-10;i<10;i++)
	{
		double shift = i*length;

		/*
		//change from tel2 to tel1
		double sdp_azi,sdp_zen;
		double sdp_azi_trans,sdp_zen_trans;
		WFCTAMap::Instance()->GetTelAZ(wfcta_event.maintel, tel_azi, tel_zen);
		slaDtp2s( mean_x+shift*cos(delta), mean_y+shift*sin(delta), tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &sdp_azi, &sdp_zen);
		sdp_zen = 90*TMath::DegToRad()-sdp_zen;
		//trans point from address tel2 to address tel1
		WFCTAMap::Instance()->PointTransform(2, sdp_azi, sdp_zen, 1, sdp_azi_trans, sdp_zen_trans, km2a_event.core_x, km2a_event.core_y, km2a_event.source_azi, km2a_event.source_zen);
		//coordinate from s_plan to tan_plan
		int jj;
		double xx,yy;
		WFCTAMap::Instance()->GetTelAZ(1, tel_azi, tel_zen);
		slaDs2tp ( sdp_azi_trans, 90*TMath::DegToRad() - sdp_zen_trans, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &xx, &yy, &jj );
		xx *= TMath::RadToDeg();
		yy *= TMath::RadToDeg();
		*/

		//not change from tel2 to tel1
		double xx = (mean_x+shift*cos(delta))*TMath::RadToDeg();
		double yy = (mean_y+shift*sin(delta))*TMath::RadToDeg();
		g_sdp_focus->SetPoint(ipot,xx,yy);
		ipot++;
	}

	g_sdp_focus->SetMarkerStyle(7);
	g_sdp_focus->SetLineColor(3);
	g_sdp_focus->SetLineWidth(1.5);
	g_sdp_focus->Draw("lsame");
}
void LHAASOEventShow::DrawSDPFocus(int tel_id, double core_x, double core_y, double source_zen, double source_azi) //draw shower detector plan by using info from ground based array
{
	wfctacanvas_focus->cd(1);
	double source_x = sin(source_zen)*cos(source_azi);
	double source_y = sin(source_zen)*sin(source_azi);
	double source_z = cos(source_zen);

	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(tel_id, tel_x, tel_y);
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(tel_id, tel_azi, tel_zen);

	int ipot=0;
	for(int istep=1;istep<21;istep++)
	{
		double ilength = istep*500;
		double point_x = core_x + ilength*source_x;
		double point_y = core_y + ilength*source_y;
		double point_z = 0 + ilength*source_z;

		double v_x = point_x - tel_x;
		double v_y = point_y - tel_y;
		double v_z = point_z - 0;

		double length_new = sqrt(pow(v_x,2)+pow(v_y,2)+pow(v_z,2));

		double point_zen = acos(v_z/length_new);
		double point_azi = TMath::ATan2(v_y, v_x);

		int jj;
		double xx,yy;
		slaDs2tp ( point_azi, 90*TMath::DegToRad() - point_zen, tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &xx, &yy, &jj );
		g_sdp_focus2->SetPoint(ipot,xx*TMath::RadToDeg(),yy*TMath::RadToDeg());
		ipot++;
	}
	g_sdp_focus2->SetMarkerStyle(7);
	g_sdp_focus2->SetLineColor(1);
	g_sdp_focus2->SetLineWidth(1);
	g_sdp_focus2->Draw("lsame");

}
void LHAASOEventShow::DrawSDP(int main_tel, double mean_zen, double mean_azi, double mean_x, double mean_y, double delta, double length)
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();

	int ipot = 0;
	double tel_azi, tel_zen;
	WFCTAMap::Instance()->GetTelAZ(main_tel, tel_azi, tel_zen);
	for(int i=-10;i<10;i++)
	{
		double shift = i*length;

		double sdp_azi,sdp_zen;
		double sdp_azi_trans,sdp_zen_trans;
	
		slaDtp2s( mean_x+shift*cos(delta), mean_y+shift*sin(delta), tel_azi*TMath::DegToRad(), (90-tel_zen)*TMath::DegToRad(), &sdp_azi, &sdp_zen);
		sdp_zen = 90*TMath::DegToRad()-sdp_zen;

		WFCTAMap::Instance()->PointTransform(2, sdp_azi, sdp_zen, 1, sdp_azi_trans, sdp_zen_trans, km2a_event.core_x, km2a_event.core_y, km2a_event.source_azi, km2a_event.source_zen);

		/*
		//change from tel2 to tel1
		double xx = GetPointX(sdp_zen_trans,sdp_azi_trans);
		double yy = GetPointY(sdp_zen_trans,sdp_azi_trans);
		*/
		//not change from tel2 to tel1
		double xx = GetPointX(sdp_zen,sdp_azi);
		double yy = GetPointY(sdp_zen,sdp_azi);

		g_sdp->SetPoint(ipot,xx,yy);
		ipot++;
	}

	g_sdp->SetMarkerStyle(7);
	g_sdp->SetLineColor(3);
	g_sdp->SetLineWidth(1);
	g_sdp->Draw("lsame");
}

void LHAASOEventShow::DrawSDP(int tel_id, double core_x, double core_y, double source_zen, double source_azi) //draw shower detector plan by using info from ground based array
{
	lhaasocanvas->cd(2);
	double source_x = sin(source_zen)*cos(source_azi);
	double source_y = sin(source_zen)*sin(source_azi);
	double source_z = cos(source_zen);
	//printf("source_xyz:(%lf, %lf, %lf)\n", source_x,source_y,source_z);

	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(tel_id, tel_x, tel_y);

	int ipot=0;
	for(int istep=1;istep<21;istep++)
	{
		double ilength = istep*500;
		double point_x = core_x + ilength*source_x;
		double point_y = core_y + ilength*source_y;
		double point_z = 0 + ilength*source_z;

		double v_x = point_x - tel_x;
		double v_y = point_y - tel_y;
		double v_z = point_z - 0;

		double length_new = sqrt(pow(v_x,2)+pow(v_y,2)+pow(v_z,2));

		double point_zen = acos(v_z/length_new);
		double point_azi = TMath::ATan2(v_y, v_x);

		double xx = GetPointX(point_zen,point_azi);
		double yy = GetPointY(point_zen,point_azi);
		g_sdp2->SetPoint(ipot,xx,yy);
		//printf("point_xyz:(%lf, %lf, %lf)   point_az(%lf, %lf)  xxyy(%lf, %lf)\n", point_x,point_y,point_z, point_zen, point_azi, xx,yy);
		ipot++;
	}
	g_sdp2->SetMarkerStyle(7);
	g_sdp2->SetLineColor(1);
	g_sdp2->SetLineWidth(1);
	g_sdp2->Draw("lsame");

}

void LHAASOEventShow::DrawEventAlongSDP(const std::vector<double>& sipm_coords, const std::vector<double>& sipm_pe, const std::vector<int>& sipm_pix)
{
	//sdpslicecanvas->cd();
	wfctacanvas_focus->cd(2);
	int npoints = g_evt_along_sdp->GetN();
	printf("npoints_grap:%d\n",npoints);
	for(int ip=npoints-1;ip>0;ip--)
	{
		g_evt_along_sdp->RemovePoint(ip);
	}
	g_evt_along_sdp->SetTitle(Form(";X_Along_SDP (^{o});log_{10}Npe"));

	int ipot=0;
	for(int i=0;i<sipm_coords.size();i++)
	{
		if(sipm_pe.at(i)<=0){continue;}
		double x = sipm_coords.at(i);
		double y = log10(sipm_pe.at(i));
		g_evt_along_sdp->SetPoint(ipot,x,y);
//		if(xmax<x) xmax = x;
//		if(slice_pe_max<y) slice_pe_max = y;
//		if(slice_pe_min>y) slice_pe_min = y;
		//printf("slice_point:%d %d (%d %lf %lf)\n",sipm_coords.size(),sipm_pe.size(),ipot,x,y);
		ipot++;
	}
	double xmax = g_evt_along_sdp->GetXaxis()->GetXmax();
	double slice_pe_min = g_evt_along_sdp->GetYaxis()->GetXmin();
	double slice_pe_max = g_evt_along_sdp->GetYaxis()->GetXmax();

	g_evt_along_sdp->SetMarkerStyle(22);
	g_evt_along_sdp->SetMarkerSize(2);
	g_evt_along_sdp->SetMarkerColor(3);
	g_evt_along_sdp->GetXaxis()->CenterTitle();
	g_evt_along_sdp->GetYaxis()->CenterTitle();
	g_evt_along_sdp->Draw("ap");

	if(h_evt_along_sdp)
		delete h_evt_along_sdp;
	h_evt_along_sdp = new TGraph();
	double max_silce_pix=-1000;
	for(int i=0;i<sipm_coords.size();i++)
	{
		if(sipm_pix.at(i)<=0){continue;}
		double y = double(sipm_pix.at(i));
		if(max_silce_pix<y) max_silce_pix=y;
	}
	double dy = (slice_pe_max-slice_pe_min)/(max_silce_pix*1.1);
	ipot=0;
	for(int i=0;i<sipm_coords.size();i++)
	{
		if(sipm_pix.at(i)<=0){continue;}
		double x = sipm_coords.at(i);
		double y = slice_pe_min + dy*sipm_pix.at(i);
//		printf("tttt: %lf %lf\n",x,y);
		h_evt_along_sdp->SetPoint(ipot,x,y);
		ipot++;
		//double x = sipm_coords.at(i);
	}
	h_evt_along_sdp->SetMarkerStyle(4);
	h_evt_along_sdp->SetMarkerSize(2);
	h_evt_along_sdp->SetMarkerColor(2);
	h_evt_along_sdp->Draw("psame");
//	printf("%lf %lf %lf\n",xmax,slice_pe_min,slice_pe_max);
	slice_pix_axis->SetX1(xmax);
	slice_pix_axis->SetX2(xmax);
	slice_pix_axis->SetY1(slice_pe_min);
	slice_pix_axis->SetY2(slice_pe_max);
	slice_pix_axis->SetWmax(max_silce_pix*1.1);
	slice_pix_axis->SetLineColor(kRed);
	slice_pix_axis->SetLabelColor(kRed);
	slice_pix_axis->Draw("same");
}

void LHAASOEventShow::DrawTimeAlongSDP(const std::vector<double>& slice_coords, const std::vector<double>& slice_t)
{
	sdpslicecanvas->cd();
	g_time_along_sdp->SetTitle(Form(";X_Along_SDP (^{o});Trigger Time"));

	int ipot=0;
	for(int i=0;i<slice_coords.size();i++)
	{
		if(slice_t.at(i)<=0){continue;}
		double x = slice_coords.at(i);
		double y = slice_t.at(i);
		g_time_along_sdp->SetPoint(ipot,x,y);
//		if(xmax<x) xmax = x;
//		if(slice_pe_max<y) slice_pe_max = y;
//		if(slice_pe_min>y) slice_pe_min = y;
		//printf("slice_point:%d %d (%d %lf %lf)\n",slice_coords.size(),slice_t.size(),ipot,x,y);
		ipot++;
	}

	g_time_along_sdp->SetMarkerStyle(21);
	g_time_along_sdp->SetMarkerSize(1);
	g_time_along_sdp->SetMarkerColor(1);
	g_time_along_sdp->GetXaxis()->CenterTitle();
	g_time_along_sdp->GetYaxis()->CenterTitle();
	g_time_along_sdp->Draw("ap");
}


void LHAASOEventShow::DrawCoreWcda(double xc, double yc)
{
	wcdacanvas->cd();
	g_core_inwcda1->SetPoint(0,xc,yc);
	g_core_inwcda1->SetMarkerStyle(29);
	g_core_inwcda1->SetMarkerColor(2);
	g_core_inwcda1->SetMarkerSize(2);
	g_core_inwcda1->Draw("psame");
}
void LHAASOEventShow::DrawCoreKm2a(double xc, double yc)
{
	g_core_inkm2a->SetPoint(0,xc,yc);
	g_core_inkm2a->SetMarkerStyle(29);
	g_core_inkm2a->SetMarkerColor(2);
	//g_core_inkm2a->SetMarkerSize(2);
	g_core_inkm2a->SetMarkerSize(0.5);
	km2acanvas->cd(1);
	g_core_inkm2a->Draw("psame");
	km2acanvas->cd(2);
	g_core_inkm2a->Draw("psame");
}
void LHAASOEventShow::DrawSG_Line_Wcda(int main_tel, double ground_x, double ground_y)
{
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXYinWCDA1(main_tel, tel_x, tel_y);
	g_tel_inwcda1->SetPoint(0, tel_x, tel_y);
	g_tel_inwcda1->SetMarkerStyle(21);
	g_tel_inwcda1->SetMarkerColor(2);
	int ipot=0;
	for(int i=-300;i<300;)
	{
		double w_xx = tel_x + i*ground_x;
		double w_yy = tel_y + i*ground_y;
		g_sdp_ground_line_wcda->SetPoint(ipot,w_xx,w_yy);
		i += 10;
		ipot++;
	}
	wcdacanvas->cd();
	g_sdp_ground_line_wcda->SetLineColor(3);
	g_sdp_ground_line_wcda->SetLineWidth(2);
	g_tel_inwcda1->Draw("psame");
	g_sdp_ground_line_wcda->Draw("lsame");
}
void LHAASOEventShow::DrawSG_Line_Km2a(int main_tel, double ground_x, double ground_y)
{
	double tel_x, tel_y;
	WFCTAMap::Instance()->GetTelXY(main_tel, tel_x, tel_y);
	g_tel_inkm2a->SetPoint(0,tel_x, tel_y);
	g_tel_inkm2a->SetMarkerStyle(21);
	g_tel_inkm2a->SetMarkerColor(2);
	int ipot=0;
	for(int i=-600;i<600;)
	{
		double k_xx = tel_x + i*ground_x;
		double k_yy = tel_y + i*ground_y;
		g_sdp_ground_line_km2a->SetPoint(ipot,k_xx,k_yy);
		i += 20;
		ipot++;
	}
	g_sdp_ground_line_km2a->SetLineColor(3);
	g_sdp_ground_line_km2a->SetLineWidth(1);
	km2acanvas->cd(1);
	g_tel_inkm2a->Draw("psame");
	g_sdp_ground_line_km2a->Draw("lsame");
	km2acanvas->cd(2);
	g_tel_inkm2a->Draw("psame");
	g_sdp_ground_line_km2a->Draw("lsame");
}

//this line is drawed on wfcta map
void LHAASOEventShow::DrawCoreDetLine()
{
	/*
	   lhaasocanvas->cd(2);
	   GetKm2aSDP();

	   int ipot=0;
	   for(int iphi=0;iphi<360;iphi++)
	{
		if(!(abs(iphi-wfctamap.TelA[MainTel-1])<16||abs(iphi-wfctamap.TelA[MainTel-1]-360)<16)){continue;}
		double rhs = -km2a_sdp_z0/(km2a_sdp_x0*cos(iphi*TMath::DegToRad())+km2a_sdp_y0*sin(iphi*TMath::DegToRad()));
		double azi = iphi*TMath::DegToRad();
		double zen = TMath::ATan(rhs);
		if(zen<20*TMath::DegToRad()||zen>40*TMath::DegToRad()) continue;
		double xx = GetPointX(zen,azi);
		double yy = GetPointY(zen,azi);
		printf("ipot:%d xx:%lf yy:%lf azi:%lf zen:%lf rhs:%lf iphi:%d\n",ipot,xx,yy,azi*57.3,zen*57.3,rhs,iphi);
		//g_laserline[itel]->SetPoint(ipot,xx,yy);
		gcore_det_line_km2a->SetPoint(ipot,xx,yy);
		ipot++;
	}
	*/
	/*
	for(int itheta=20;itheta<50;itheta++)
	{
		double rhs = -1/(tan(km2a_sdp_theta0)*tan(itheta*TMath::DegToRad()));
		double azi = km2a_sdp_phi0-acos(rhs);
		double zen = itheta*TMath::DegToRad();
		double xx = GetPointX(zen,azi);
		double yy = GetPointY(zen,azi);
		//printf("xx:%lf yy:%lf\n",xx,yy);
		gcore_det_line_km2a->SetPoint(ipot,xx,yy);
		ipot++;
	}
	*/
	/*
	double source_xx = GetPointX(DSourceZen_w,DSourceAzi_w);
	double source_yy = GetPointY(DSourceZen_w,DSourceAzi_w);

	double source_xx_km2a = GetPointX(DSourceZen_k,DSourceAzi_k);
	double source_yy_km2a = GetPointY(DSourceZen_k,DSourceAzi_k);

	double telx=wfctamap.TelX[MainTel-1]; 
	double tely=wfctamap.TelY[MainTel-1]; 
	double core_det_phi = atan2((Core_wy-tely),(Core_wx-telx))*TMath::RadToDeg();
	double core_det_phi_km2a = atan2((Core_ky-tely),(Core_kx-telx))*TMath::RadToDeg();
	printf("core_det_phi_km2a:%lf\n",core_det_phi_km2a);
	//double core_det_phi = atan((Core_wy-tely)/(Core_wx-telx))*TMath::RadToDeg();
	for(int i=0;i<90;i++)
	{
		double xx = GetPointX(i*TMath::DegToRad(),core_det_phi*TMath::DegToRad()) + source_xx;
		double yy = GetPointY(i*TMath::DegToRad(),core_det_phi*TMath::DegToRad()) + source_yy;
		gcore_det_line_wcda->SetPoint(i,xx,yy);
		double xx_km2a = GetPointX(i*TMath::DegToRad(),core_det_phi_km2a*TMath::DegToRad()) + source_xx_km2a;
		double yy_km2a = GetPointY(i*TMath::DegToRad(),core_det_phi_km2a*TMath::DegToRad()) + source_yy_km2a;
		gcore_det_line_km2a->SetPoint(i,xx_km2a,yy_km2a);
	}
	*/
//	gcore_det_line_wcda->SetLineStyle(1);
//	gcore_det_line_wcda->Draw("lsame");
	gcore_det_line_km2a->SetLineStyle(1);
	gcore_det_line_km2a->Draw("lsame");

}


void LHAASOEventShow::DrawLaserLine(double l3_zen, double l3_azi)
{
//	lhaasocanvas->cd(); //new tetetetet
	lhaasocanvas->cd(2);
	//wfctacanvas->cd();
	double L3_x = -992.35300;
	double L3_y = -451.57000;
	double L3_z = 4376.775;
	double L3_Zen = l3_zen*TMath::DegToRad();
	//double L3_Azi = 16.03*TMath::DegToRad();
	double L3_Azi = l3_azi*TMath::DegToRad();
	double tel_laser_x0[6];
	double tel_laser_y0[6];
	double tel_laser_z0[6];
	double tel_laser_theta0[6];
	double tel_laser_phi0[6];
	double tel_laser_phi[6];
	double tel_laser_theta[6];

	double telz = 4394.567;
	double tel_x, tel_y;
	for(int i=0;i<6;i++)
	{
		WFCTAMap::Instance()->GetTelXY(i+1, tel_x, tel_y);
		double distence = sqrt(pow(L3_x-tel_x,2)+pow(L3_y-tel_y,2)+pow(L3_z-telz,2));
		tel_laser_theta[i] = asin((telz-L3_z)/distence);
		tel_laser_phi[i] = atan2(L3_y-tel_y, L3_x-tel_x);
		//GetPlaneNormal(L3_Zen, L3_Azi, 90*TMath::DegToRad(), tel_laser_phi[i], &tel_laser_x0[i], &tel_laser_y0[i], &tel_laser_z0[i]);
		GetPlaneNormal(90*TMath::DegToRad(), tel_laser_phi[i], L3_Zen, L3_Azi, &tel_laser_x0[i], &tel_laser_y0[i], &tel_laser_z0[i]);
		//GetPlaneNormal(tel_laser_theta[i], tel_laser_phi[i], L3_Zen, L3_Azi, &tel_laser_x0[i], &tel_laser_y0[i], &tel_laser_z0[i]);
		tel_laser_theta0[i] = acos(tel_laser_z0[i]);
		tel_laser_phi0[i] = atan2(tel_laser_y0[i],tel_laser_x0[i]);
		printf("tel_l3_x0:%lf tel_l3_y0:%lf tel_l3_z0:%lf\n",tel_laser_x0[i],tel_laser_y0[i],tel_laser_z0[i]);
		printf("tel_x:%lf tel_y:%lf dy:%lf dx:%lf tel_L3_phi;%lf tel_laser_theta0:%lf tel_laser_phi0:%lf\n",
				tel_x, tel_y, L3_y-tel_y, L3_x-tel_x, tel_laser_phi[i]*57.3,tel_laser_theta0[i]*57.3,tel_laser_phi0[i]*57.3);
	}

	double tel_azi, tel_zen;
	for(int itel=0;itel<6;itel++)
	{
	    WFCTAMap::Instance()->GetTelAZ(itel+1, tel_azi, tel_zen);
		int ipot=0;
		for(int iphi=0;iphi<360;iphi++)
		{
			if(!(abs(iphi-tel_azi)<16||abs(iphi-tel_azi-360)<16)){continue;}
			double rhs = -tel_laser_z0[itel]/(tel_laser_x0[itel]*cos(iphi*TMath::DegToRad())+tel_laser_y0[itel]*sin(iphi*TMath::DegToRad()));
			double azi = iphi*TMath::DegToRad();
			double zen = TMath::ATan(rhs);
			if(zen<20*TMath::DegToRad()||zen>40*TMath::DegToRad()) continue;
			double xx = GetPointX(zen,azi);
			double yy = GetPointY(zen,azi);
			printf("itel:%d ipot:%d xx:%lf yy:%lf azi:%lf zen:%lf rhs:%lf iphi:%d\n",itel+1,ipot,xx,yy,azi*57.3,zen*57.3,rhs,iphi);
			g_laserline[itel]->SetPoint(ipot,xx,yy);
			ipot++;
		}
		if(ipot==0){continue;}

		g_laserline[itel]->SetLineStyle(1);
		g_laserline[itel]->SetLineColor(itel+1);
		g_laserline[itel]->Draw("lsame");
	}
}

/////////////////////////
////_draw_ WCDA Event////
/////////////////////////
void LHAASOEventShow::DrawWCDAEvent(const std::vector<double>& cell_x, const std::vector<double>& cell_y, const std::vector<double>& cell_pe)
{
	wcdacanvas->cd();
	//lhaasocanvas->cd(1);
	gPad->SetLogz();
	h2_wcda->Reset();
	//h2_wcda->SetTitle(Form("Time:%lld+%.9lf (%4d/%02d/%02d %02d:%02d:%02d)",cosmic_event.rbT,cosmic_event.rbt/1000000000,cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));

	h2_wcda->GetXaxis()->SetTitle("X (m)");
	h2_wcda->GetXaxis()->CenterTitle();
	h2_wcda->GetYaxis()->SetTitle("Y (m)");
	h2_wcda->GetYaxis()->CenterTitle();
	for(int ii=0;ii<cell_x.size();ii++)
	{
		double content = cell_pe.at(ii);
		//double content = cell_pe.at(ii);//scal by t
		if(content<0.03){continue;}
		//if(content<500){continue;}//scale by t
		h2_wcda->Fill(cell_x.at(ii),cell_y.at(ii),content);
	}
	h2_wcda->Draw("colz");
	//if(!wcda_scale_drawed)
	//{
		wcda_scale_title->Draw("same");
	//	wcda_scale_drawed=1;
	//}
	//h2_wcda->GetZaxis()->SetRangeUser(800,2000);
	h2_wcda->GetXaxis()->SetRangeUser(-90,90);
	h2_wcda->GetYaxis()->SetRangeUser(-90,90);

}
void LHAASOEventShow::DrawWCDAEvent(const std::vector<int>& cell_ig, const std::vector<double>& cell_pe, const std::vector<double>& cell_t)
{
	wcdacanvas->cd();
	//lhaasocanvas->cd(1);
	gPad->SetLogz();
	h2_wcda->Reset();
	//h2_wcda->SetTitle(Form("Time:%lld+%.9lf (%4d/%02d/%02d %02d:%02d:%02d)",cosmic_event.rbT,cosmic_event.rbt/1000000000,cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));

	h2_wcda->GetXaxis()->SetTitle("X (m)");
	h2_wcda->GetXaxis()->CenterTitle();
	h2_wcda->GetYaxis()->SetTitle("Y (m)");
	h2_wcda->GetYaxis()->CenterTitle();
	Double_t kvx[3000]={0}, kvy[3000]={0},kvz[3000]={0},kvq[3000]={0},kvigcell[3000]={-1},kvtp[3000]={-999};
	int kigcell=-1;
	for(int i=0;i< cell_pe.size();i++){//get x y z q t igcell

		kvq[i] = cell_pe.at(i);//(*cell_pe)[i];
		kvtp[i] = cell_t.at(i);//(*cell_t)[i];
		kvigcell[i] = kigcell = cell_ig.at(i);//(*cell_ig)[i];

		//kvq[i] = kvq[i] * cell_water_eff[kigcell];//water_eff
		kvx[i] = cell_x[kigcell];
		kvy[i] = cell_y[kigcell];
		kvz[i] = cell_z[kigcell];

		kvtp[i]=kvtp[i]-(20*pow(kvq[i],-0.1)+10*pow(kvq[i],-0.08)-24.2);//Q-T  tp=tp-(20*pow(q,-0.1)+10*pow(q,-0.08)-24.2);  //by gaob


		//cout<<" igcell "<<kigcell<<" "<<kvx[i]<<" "<<kvy[i]<<" "<<kvq[i]<<" "<<kvtp[i]<<endl;//ok!
		//check by zengzk
		//if(kvq[i]<10){continue;}
		//h2_wcda->Fill(kvx[i],kvy[i],1.0*log10(1.0*kvq[i]));
		double content = kvq[i];
		//double content = kvq[i];
		if(content<0.03){continue;}
		h2_wcda->Fill(kvx[i],kvy[i],content);
	}
	h2_wcda->Draw("colz");
	if(!wcda_scale_drawed)
	{
		wcda_scale_title->Draw("same");
		wcda_scale_drawed=1;
	}
	h2_wcda->GetXaxis()->SetRangeUser(-90,90);
	h2_wcda->GetYaxis()->SetRangeUser(-90,90);

}

/////////////////////////
////_draw_ KM2A Event////
/////////////////////////
void LHAASOEventShow::outputKm2aLat(double cor_x, double cor_y, const LHEvent& km2aevent, const char* clean)
{
	TClonesArray *HitsE, *HitsM;
	LHHit* HitE;
	LHHit* HitM;
	//output ed event
	HitsE = km2aevent.GetHitsE();
	int nHitsE = km2aevent.GetNhitE();
	printf("ed_r_pe:\n");
	for(int j=0;j<nHitsE;j++)
	{
		HitE = (LHHit *)((*HitsE)[j]);
		if(HitE->GetPe()<=0){continue;}
		if(0==strcmp(clean,"clean"))
			if(HitE->GetStatus()<2){continue;}
		int ied = HitE->GetId();
		double imagex = ed_x[ied];
		double imagey = ed_y[ied];
		double r=sqrt(pow(cor_x-imagex,2)+pow(cor_y-imagey,2));
		double content;
		//content = log10(HitE->GetPe());	//scale by npe
		content = HitE->GetPe();	//scale by npe
		//content = HitE->GetTime();	//scale by t
		printf("%lf %lf\n",r,content);
	}
	printf("<==============\n");
}
void LHAASOEventShow::DrawKM2AEvent(const LHEvent& km2aevent, const char* clean)
{
	km2acanvas->cd(1);
	//g_ed->SetTitle(Form("Time:%lld+%.9lf (%4d/%02d/%02d %02d:%02d:%02d)",cosmic_event.rbT,cosmic_event.rbt/1000000000,cosmic_event.year,cosmic_event.month,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second));

	km2acanvas->cd(1);
	TClonesArray *HitsE, *HitsM;
	LHHit* HitE;
	LHHit* HitM;

	//draw ed event
	if(ed_h2p) {
		printf("delete ed_h2p\n");
		delete ed_h2p;
	}
	ed_h2p = new TH2Poly();
	HitsE = km2aevent.GetHitsE();
	int nHitsE = km2aevent.GetNhitE();
	printf("ed.size():%d\n",nHitsE);
	int ibin=0;
	for(int j=0;j<nHitsE;j++)
	{
		HitE = (LHHit *)((*HitsE)[j]);
		if(HitE->GetPe()<=0){continue;}
		if(0==strcmp(clean,"clean"))
			if(HitE->GetStatus()<2){continue;}
		int ied = HitE->GetId();
		double x[5]={0};
		double y[5]={0};
		for(int ipot=0;ipot<4;ipot++){
			double imagex = ed_x[ied];
			double imagey = ed_y[ied];
			if(ipot==0)		{	imagex-=5;	imagey-=5;}
			else if(ipot==1)	{	imagex-=5;	imagey+=5;}
			else if(ipot==2)	{	imagex+=5;	imagey+=5;}
			else if(ipot==3)	{	imagex+=5;	imagey-=5;}
			x[ipot] = imagex;
			y[ipot] = imagey;
		}
		x[4] = x[0];
		y[4] = y[0];
		ed_h2p->AddBin(5,x,y);

		ibin++;
		double content;
		content = log10(HitE->GetPe());	//scale by npe
		//content = HitE->GetTime();	//scale by t
		//ed_h2p->SetBinContent(ibin,content);
		//printf("%d ed content:%lf pe:%lf\n",ied,content,HitE->GetPe());
		ed_h2p->SetBinContent(ibin,content);
	}
	ed_h2p->Draw("colz same");

	//draw ed event
	km2acanvas->cd(2);
	if(md_h2p) {
		printf("delete md_h2p\n");
		delete md_h2p;
	}
	md_h2p = new TH2Poly();
	HitsM = km2aevent.GetHitsM();
	int nHitsM = km2aevent.GetNhitM();
	printf("md.size():%d\n",nHitsM);
	ibin=0;
	for(int ii=0;ii<nHitsM;ii++)
	{
		HitM = (LHHit *)((*HitsM)[ii]);
		if(HitM->GetPe()<=0){continue;}
		if(0==strcmp(clean,"clean"))
			if(HitM->GetStatus()<2){continue;}
		int imd = HitM->GetId();
		double x[5]={0};
		double y[5]={0};
		for(int ipot=0;ipot<4;ipot++){
			double imagex = md_x[imd];
			double imagey = md_y[imd];
			if(ipot==0)		{	imagex-=5;	imagey-=5;}
			else if(ipot==1)	{	imagex-=5;	imagey+=5;}
			else if(ipot==2)	{	imagex+=5;	imagey+=5;}
			else if(ipot==3)	{	imagex+=5;	imagey-=5;}
			x[ipot] = imagex;
			y[ipot] = imagey;
		}
		x[4] = x[0];
		y[4] = y[0];
		//printf("md pos: %d %lf %lf\n",imd,x[0],y[0]);
		md_h2p->AddBin(5,x,y);

		ibin++;
		double content;
		content = log10(HitM->GetPe());	//scale by npe
		//content = HitM->GetTime();	//scale by t
		//printf("%d md content:%lf pe:%lf\n",imd,content,HitM->GetPe());
		md_h2p->SetBinContent(ibin,content);
	}
	md_h2p->Draw("colz same");

	/*
	for(int ii=0;ii<hitid.size();ii++)
	{
		if(1==hitmode.at(ii)){continue;}
		int ied = hitid.at(ii);
		double x[5]={0};
		double y[5]={0};
		for(int ipot=0;ipot<4;ipot++){
			double imagex = ed_x[ied];
			double imagey = ed_y[ied];
			if(ipot==0)		{	imagex-=5;	imagey-=5;}
			else if(ipot==1)	{	imagex-=5;	imagey+=5;}
			else if(ipot==2)	{	imagex+=5;	imagey+=5;}
			else if(ipot==3)	{	imagex+=5;	imagey-=5;}
			x[ipot] = imagex;
			y[ipot] = imagey;
		}
		x[4] = x[0];
		y[4] = y[0];
		//printf("ed pos: %d %lf %lf\n",ied,x[0],y[0]);
		ed_h2p->AddBin(5,x,y);
	}
	int ibin=0;
	for(int ii=0;ii<hitid.size();ii++)
	{
		if(hitmode.at(ii)==1){continue;}
		ibin++;
		double content;
		content = log10(hitpart.at(ii));	//scale by npe
		ed_h2p->SetBinContent(ibin,content);
	}
	ed_h2p->Draw("colz same");

	km2acanvas->cd(2);
	if(md_h2p) {
		printf("delete md_h2p\n");
		delete md_h2p;
	}
	md_h2p = new TH2Poly();
	printf("hitid.size():%d\n",hitid.size());
	for(int ii=0;ii<hitid.size();ii++)
	{
		if(0==hitmode.at(ii)){continue;}
		int imd = hitid.at(ii);
		double x[5]={0};
		double y[5]={0};
		for(int ipot=0;ipot<4;ipot++){
			double imagex = md_x[imd];
			double imagey = md_y[imd];
			if(ipot==0)		{	imagex-=5;	imagey-=5;}
			else if(ipot==1)	{	imagex-=5;	imagey+=5;}
			else if(ipot==2)	{	imagex+=5;	imagey+=5;}
			else if(ipot==3)	{	imagex+=5;	imagey-=5;}
			x[ipot] = imagex;
			y[ipot] = imagey;
		}
		x[4] = x[0];
		y[4] = y[0];
		//printf("md pos: %d %lf %lf\n",imd,x[0],y[0]);
		md_h2p->AddBin(5,x,y);
	}
	ibin=0;
	for(int ii=0;ii<hitid.size();ii++)
	{
		if(hitmode.at(ii)==0){continue;}
		ibin++;
		double content;
		content = log10(hitpart.at(ii));	//scale by npe
		md_h2p->SetBinContent(ibin,content);
	}
	md_h2p->Draw("colz same");
	*/
}






double LHAASOEventShow::GetPointX(double p_zen, double p_azi) // input: rad
{
	return p_zen*TMath::RadToDeg()*cos(p_azi);
	//return p_azi*TMath::RadToDeg();
}
double LHAASOEventShow::GetPointY(double p_zen, double p_azi) //input: rad
{
	return p_zen*TMath::RadToDeg()*sin(p_azi);
	//return p_zen*TMath::RadToDeg();
}


void LHAASOEventShow::GetKm2aSDP()
{
	/*
	double telx=wfctamap.TelX[MainTel-1]; 
	double tely=wfctamap.TelY[MainTel-1]; 
	double core_det_phi_km2a = atan2((Core_ky-tely),(Core_kx-telx));
	printf("km2a_cx:%lf km2a_cy:%lf  telx:%lf tely:%lf  DSourceZen_k:%lf DSourceAzi_k:%lf  core_det_phi_km2a:%lf\n",Core_kx,Core_ky,telx,tely,DSourceZen_k,DSourceAzi_k,core_det_phi_km2a*57.3);
	double km2a_sdp_x0,km2a_sdp_y0,km2a_sdp_z0;
	GetPlaneNormal(DSourceZen_k, DSourceAzi_k, 90*TMath::DegToRad(), core_det_phi_km2a, &km2a_sdp_x0, &km2a_sdp_y0, &km2a_sdp_z0);
	km2a_sdp_theta0 = acos(km2a_sdp_z0);
	km2a_sdp_phi0 = atan2(km2a_sdp_y0,km2a_sdp_x0);
	printf("sdp_x:%lf sdp_y:%lf sdp_z:%lf km2a_sdp_theta:%lf km2a_sdp_phi:%lf\n",km2a_sdp_x0,km2a_sdp_y0,km2a_sdp_z0,km2a_sdp_theta0*57.3,km2a_sdp_phi0*57.3);
*/
}


void LHAASOEventShow::slaDs2tp ( double ra, double dec, double raz, double decz, double *xi, double *eta, int *j )
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

void LHAASOEventShow::slaDtp2s ( double xi, double eta, double raz, double decz, double *ra, double *dec )
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

void LHAASOEventShow::GetPlaneNormal(double zenith1,double azimuth1,double zenith2,double azimuth2,double *x, double *y, double *z)
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

void LHAASOEventShow::rbtime2lt(long rb_Time, double rb_time)
{   
	cosmic_event.rbT = rb_Time;
	cosmic_event.rbt = rb_time;
	double TAI2UTC = 37;
	time_t rawtime;
	time_t utc = rb_Time-TAI2UTC;
	struct tm *info;
	info = localtime(&utc);
	cosmic_event.year = 1900 + info->tm_year;
	cosmic_event.month = info->tm_mon+1;
	cosmic_event.day = info->tm_mday;
	cosmic_event.hour = info->tm_hour;
	cosmic_event.minite = info->tm_min;
	cosmic_event.second = info->tm_sec;

	cosmic_event.mjd = 40587 + (rb_Time + rb_time/1000000000. - TAI2UTC)/86400;

	//printf("time: %d %d %d %d:%d:%d\n",cosmic_event.year,mon,cosmic_event.day,cosmic_event.hour,cosmic_event.minite,cosmic_event.second);
}

/*
void LHAASOEventShow::PointTransform_firstversion(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen)// tansform pointing from tel1 to tel2
{
	bool trans_debug=0;
	if(trans_debug) printf("================================================OOOOOOOOOOO  TANSFORM  OOOOOOOOOOO================================================\n");
	// set corez , telz to 0
	double core_z = 0;
	double tel_z1 = 0, tel_z2 = 0;

	// get component of source in (x,y,z)
	double source_x = sin(source_zen)*cos(source_azi);
	double source_y = sin(source_zen)*sin(source_azi);
	double source_z = cos(source_zen);
	if(trans_debug) printf("source_xyz:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", source_x,source_y,source_z, source_zen*57.3,source_azi*57.3);

	// get tel address and tel pointing
	double tel_x1, tel_y1;
	WFCTAMap::Instance()->GetTelXY(tel_id1, tel_x1, tel_y1);
	double tel_azi1, tel_zen1;
	WFCTAMap::Instance()->GetTelAZ(tel_id1, tel_azi1, tel_zen1);
	double tel_x2, tel_y2;
	WFCTAMap::Instance()->GetTelXY(tel_id2, tel_x2, tel_y2);
	double tel_azi2, tel_zen2;
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
	// get the coordinate of point that need to trans
	double cos_theta1 = (v_point_x1*v_core_tel_x1 + v_point_y1*v_core_tel_y1 + v_point_z1*v_core_tel_z1)/(mode_point1*mode_core_tel1);
	double length = mode_core_tel1 / cos_theta1;
	if(trans_debug) printf("mode_core_tel1:%lf length:%lf cos_theta1:%lf(%lf{^o})\n\n", mode_core_tel1, length, cos_theta1, acos(cos_theta1)*57.3);
	if(trans_debug) printf("point_xyz1:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", v_point_x1*length,v_point_y1*length,v_point_z1*length, point_zen1*57.3,point_azi1*57.3);
	double point_x1 = tel_x1 + length*v_point_x1;
	double point_y1 = tel_y1 + length*v_point_y1;
	double point_z1 = tel_z1 + length*v_point_z1;

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
*/

/*
void LHAASOEventShow::PointTransform_backup(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen)// tansform pointing from tel1 to tel2
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
	if(trans_debug) printf("theta1:%lf theta_source:%lf  theta_third_angle:%lf\n",acos(cos_theta1),acos(cos_theta_source), angle_third*TMath::RadToDeg());
	if(trans_debug) printf("mode_core_tel1:%lf length:%lf cos_theta1:%lf(%lf{^o})\n\n", mode_core_tel1, length, cos_theta1, acos(cos_theta1)*57.3);
	if(trans_debug) printf("point_xyz1:(%lf, %lf, %lf) az:[%lf,%lf]\n\n", v_point_x1*length,v_point_y1*length,v_point_z1*length, point_zen1*57.3,point_azi1*57.3);

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
*/

/*
void LHAASOEventShow::PointTransform(int tel_id1, double point_azi1, double point_zen1, int tel_id2, double& point_azi2, double& point_zen2, double core_x, double core_y, double source_azi, double source_zen)// tansform pointing from tel1 to tel2
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
*/





