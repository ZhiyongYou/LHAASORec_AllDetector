#ifndef LHAASORECEVENT_H
#define LHAASORECEVENT_H

#include <vector>
#include <string>
#include <map>
#include "TTree.h"
#include "TBranch.h"
#include "TObject.h"
#include "LHAASOEventRec.h"

class LHAASORecEvent : public TObject
{
	protected:
		static LHAASORecEvent* _Head;
		static TTree* _Tree;
		static const char * _Name;
		static TBranch* bAll;

	public:
		Double_t mjd;
		Long64_t rabbitTime; //!
		Double_t rabbittime; //!
		Int_t MaxPeTel; //!
		Int_t MaxSipm; //!
		Double_t MaxSipmPe; //!
		Int_t MainTel;
		Double_t Size;
		Double_t npec; //!
		Int_t Npix;
		Double_t Tail; //!
		Double_t Tail_pix; //!
		Double_t MeanZen; //!
		Double_t MeanAzi; //!
		Double_t MeanX; //!
		Double_t MeanY; //!
		Double_t Length; //!
		Double_t Width; //!

		Double_t deltaT_w; //!
		Double_t deltaT_k; //!
		Double_t D2Xmax_w; //!
		Double_t D2Xmax_k; //!
		Double_t Rp_w; //!
		Double_t Rp_k; //!
		Double_t SourceZen_w; //!
		Double_t SourceAzi_w; //!
		Double_t SourceZen_k; //!
		Double_t SourceAzi_k; //!
		Double_t DistW; //!
		Double_t DeltaW; //!
		Double_t DeltaK; //!
		Double_t SDP_GLine_Angle_W; //!
		Double_t GroundXW; //!
		Double_t GroundYW; //!
		Double_t CoreAtFocusX_W; //!
		Double_t CoreAtFocusY_W; //!
		Double_t CoreAtFocusX_K; //!
		Double_t CoreAtFocusY_K; //!
		Double_t Core_wx; //!
		Double_t Core_wy; //!
		Double_t Core_kx; //!
		Double_t Core_ky; //!
		Double_t core_wx; //!
		Double_t core_wy; //!
		Double_t top5; //!
		Double_t top9; //!
		Double_t top30; //!
		Double_t total_npe; //!
		Double_t pe_size[6]; //!
		Int_t npix_size[6]; //!
		Int_t inter_npix[6]; //!

	public:
		LHAASORecEvent();
		virtual ~LHAASORecEvent()	{	Init();};
		void Init();
		void EventInitial();
		void AddEvent(LHAASOEventRec& lhaasoeventrec);

		ClassDef(LHAASORecEvent,1);
};

//ClassImp(LHAASORecEvent);

#endif // LHAASORECEVENT_H
