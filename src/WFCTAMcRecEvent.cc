#include "WFCTAMcRecEvent.h"

ClassImp(WFCTAMcRecEvent)

WFCTAMcRecEvent::WFCTAMcRecEvent()
{
}

WFCTAMcRecEvent::~WFCTAMcRecEvent()  {
}

void WFCTAMcRecEvent::Init()
{
	iEvent = 0;
	iUse = 0;
	id = 0;
	energy = 0;
	zenith = -1000;
	azimuth = -1000;
	corex = -1000;
	corey = -1000;
	Xmax = 0;
	Nmax = 0;

	//**Hillas parameters **//
	DMeanX = -1000;
	DMeanY = -1000;
	DLength = 0;
	DWidth = 0;
	DDeltaHillas = 0;
	DAlpha = 0;
	DD2Center = -1000;
	DSize = 0;
	Npix = 0;
	//**geometry parameters **//
	MainTel = 0;
	DSourceX = -1000;
	DSourceY = -1000;
	DAngle = -1000;
	DDist = -1000;
	DDeltaSDP = 0;
	DCore2SDP = 0;
	DTheta = -1000;
	CoreAtFocusX = -1000;
	CoreAtFocusY = -1000;
	TelX = 0;
	TelY = 0;
	Rp = 0;
	//**ronstruction geometry parameters**//
	DRecSourceX = -1000;
	DRecSourceY = -1000;
	DRecAngle = 0;
	DRecDist = 0;
	DRecCore2SDP = 0;
	DRecTheta = 0;
	RecCoreAtFocusX = -1000;
	RecCoreAtFocusY = -1000;
	RecRp = 0;
	RecEnergyProton = 0;
	RecEnergyHelium = 0;
	RecEnergyMix = 0;
	//** Xmax related **//
	DPemax = 0;
	DXmax = 0;
	DYmax = 0;
	DDistmax = 0;
	//**image information **//
	CleanImagePe.clear();
	CleanImageX.clear();
	CleanImageY.clear();

}
void WFCTAMcRecEvent::SetEvent(WFCTARec* wfctarec)
{
}

