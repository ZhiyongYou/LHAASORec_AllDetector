#include <stdlib.h>
#include "astro.h"
#include "TMath.h"
#include "LHAASORecEvent.h"

using namespace std;

ClassImp(LHAASORecEvent);
LHAASORecEvent* LHAASORecEvent::_Head=0;
TTree* LHAASORecEvent::_Tree=0;
const char* LHAASORecEvent::_Name="LHAASORecEvent";
TBranch* LHAASORecEvent::bAll=0;

LHAASORecEvent::LHAASORecEvent():TObject()
{
	Init();
}

void LHAASORecEvent::Init()
{
	mjd = 0;
	rabbitTime = 0;
	rabbittime = 0;
	MaxPeTel = 0;
	MaxSipm = 0;
	MaxSipmPe = 0;
	MainTel = 0;
	Size = 0;
	npec = 0;
	Npix = 0;
	MeanZen = -1000;
	MeanAzi = -1000;
	MeanX = -1000;
	MeanY = -1000;
	Length = 0;
	Width = 0;

	deltaT_w = -1000;
	deltaT_k = -1000;
	D2Xmax_w = -1000;
	D2Xmax_k = -1000;
	Rp_w = -1000;
	Rp_k = -1000;
	SourceZen_w = -1000;
	SourceAzi_w = -1000;
	SourceZen_k = -1000;
	SourceAzi_k = -1000;
	DistW = -1000;
	DeltaW = -1000;
	DeltaK = -1000;
	SDP_GLine_Angle_W = -1000;
	GroundXW = -1000;
	GroundYW = -1000;
	CoreAtFocusX_W = -1000;
	CoreAtFocusY_W = -1000;
	CoreAtFocusX_K = -1000;
	CoreAtFocusY_K = -1000;
	Core_wx = -1000;
	Core_wy = -1000;
	Core_kx = -1000;
	Core_ky = -1000;
	core_wx = -1000;
	core_wy = -1000;
	top5 = 0;
	top9 = 0;
	top30 = 0;
	total_npe = 0;
	for(int i=0;i<6;i++)
	{
		pe_size[i] = 0;
		npix_size[i] = 0;
		inter_npix[i] = 0;
	}
}

void LHAASORecEvent::EventInitial()
{
	mjd = 0;
	rabbitTime = 0;
	rabbittime = 0;
	MaxPeTel = 0;
	MaxSipm = 0;
	MaxSipmPe = 0;
	MainTel = 0;
	Size = 0;
	npec = 0;
	Npix = 0;
	MeanZen = -1000;
	MeanAzi = -1000;
	MeanX = -1000;
	MeanY = -1000;
	Length = 0;
	Width = 0;

	deltaT_w = -1000;
	deltaT_k = -1000;
	D2Xmax_w = -1000;
	D2Xmax_k = -1000;
	Rp_w = -1000;
	Rp_k = -1000;
	SourceZen_w = -1000;
	SourceAzi_w = -1000;
	SourceZen_k = -1000;
	SourceAzi_k = -1000;
	DistW = -1000;
	DeltaW = -1000;
	DeltaK = -1000;
	SDP_GLine_Angle_W = -1000;
	GroundXW = -1000;
	GroundYW = -1000;
	CoreAtFocusX_W = -1000;
	CoreAtFocusY_W = -1000;
	CoreAtFocusX_K = -1000;
	CoreAtFocusY_K = -1000;
	Core_wx = -1000;
	Core_wy = -1000;
	Core_kx = -1000;
	Core_ky = -1000;
	core_wx = -1000;
	core_wy = -1000;
	top5 = 0;
	top9 = 0;
	top30 = 0;
	total_npe = 0;
	for(int i=0;i<6;i++)
	{
		pe_size[i] = 0;
		npix_size[i] = 0;
		inter_npix[i] = 0;
	}
}

void LHAASORecEvent::AddEvent(LHAASOEventRec& lhaasoeventrec)
{
	mjd = rbtime2mjd(lhaasoeventrec.rabbitTime,lhaasoeventrec.rabbittime);
	rabbitTime = lhaasoeventrec.rabbitTime;
	rabbittime = lhaasoeventrec.rabbittime;
	MaxPeTel = lhaasoeventrec.GetMaxPeTel();
	MaxSipm = lhaasoeventrec.GetMaxSipm();
	MaxSipmPe = lhaasoeventrec.GetMaxSipmPe();
	MainTel = lhaasoeventrec.GetMainTel();
	Size = lhaasoeventrec.GetSize();
	//npec = wcdarec->npec;
	Npix = lhaasoeventrec.GetNpix();
	Tail = lhaasoeventrec.GetTail();
	Tail_pix = lhaasoeventrec.GetTail_pix();
	MeanZen = lhaasoeventrec.GetMeanZen();
	MeanAzi = lhaasoeventrec.GetMeanAzi();
	MeanX = lhaasoeventrec.GetMeanX();
	MeanY = lhaasoeventrec.GetMeanY();
	Length = lhaasoeventrec.GetLength();
	Width = lhaasoeventrec.GetWidth();

	deltaT_w = lhaasoeventrec.GetDeltaT("wcda");;
	deltaT_k = lhaasoeventrec.GetDeltaT("km2a");;
	D2Xmax_w = lhaasoeventrec.GetDistToXmax("wcda");
	D2Xmax_k = lhaasoeventrec.GetDistToXmax("km2a");
	Rp_w = lhaasoeventrec.GetRp("wcda");
	Rp_k = lhaasoeventrec.GetRp("km2a");
	SourceZen_w = lhaasoeventrec.GetSourceZen("wcda");
	SourceAzi_w = lhaasoeventrec.GetSourceAzi("wcda");
	SourceZen_k = lhaasoeventrec.GetSourceZen("km2a");
	SourceAzi_k = lhaasoeventrec.GetSourceAzi("km2a");
	DistW = lhaasoeventrec.GetDist("wcda");
	DeltaW = lhaasoeventrec.GetDTheta("wcda");
	DeltaK = lhaasoeventrec.GetDTheta("km2a");
	//printf("DeltaW:%lf DeltaK%lf\n",DeltaW,DeltaK);
	SDP_GLine_Angle_W = lhaasoeventrec.GetSDP_GLine_Angle_W();
	GroundXW = lhaasoeventrec.GetSDP_GLine_X_W();
	GroundYW = lhaasoeventrec.GetSDP_GLine_Y_W();
	//SDP_GLine_Angle = lhaasoeventrec.GetSDP_GLine_Angle();
	//GroundXW = lhaasoeventrec.GetSDP_GLine_X_wcda();
	//GroundYW = lhaasoeventrec.GetSDP_GLine_Y_wcda();
	Core_wx = lhaasoeventrec.GetCoreX("wcda");
	Core_wy = lhaasoeventrec.GetCoreY("wcda");
	//core_wx = wcdarec->xc1;
	//core_wy = wcdarec->yc1;
	Core_kx = lhaasoeventrec.GetCoreX("km2a");
	Core_ky = lhaasoeventrec.GetCoreY("km2a");
	double cx,cy;
	lhaasoeventrec.GetCoreToFocus("wcda",cx, cy);
	CoreAtFocusX_W = cx;
	CoreAtFocusY_W = cy;
	lhaasoeventrec.GetCoreToFocus("km2a",cx, cy);
	CoreAtFocusX_K = cx;
	CoreAtFocusY_K = cy;
	printf("CoreAtFocusX:(%lf, %lf)\n",CoreAtFocusX_K, CoreAtFocusY_K);
//	lhaasoeventrec.GetCoreToFocus("km2a",CoreAtFocusX_K, CoreAtFocusY_K);
	top5 = lhaasoeventrec.GetTop5();
	top9 = lhaasoeventrec.GetTop9();
	top30 = lhaasoeventrec.GetTop30();
	total_npe = lhaasoeventrec.GetTotalNpe();//wcda total npe
	lhaasoeventrec.GetPe_Size(pe_size);
	lhaasoeventrec.GetNpix_Size(npix_size);
	lhaasoeventrec.GetInter_Npix(inter_npix);




}









