// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIsrcdIEventDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "KM2AEvent.h"
#include "LHEvent.h"
#include "LHRecEvent.h"
#include "LHAASOEvent.h"
#include "LaserEvent.h"
#include "WFCTAMcEvent.h"
#include "WCDAMcEvent.h"
#include "WCDAEventRec.h"
#include "WFCTAMcRecEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KM2AEvent(void *p = 0);
   static void *newArray_KM2AEvent(Long_t size, void *p);
   static void delete_KM2AEvent(void *p);
   static void deleteArray_KM2AEvent(void *p);
   static void destruct_KM2AEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KM2AEvent*)
   {
      ::KM2AEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KM2AEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KM2AEvent", ::KM2AEvent::Class_Version(), "KM2AEvent.h", 24,
                  typeid(::KM2AEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KM2AEvent::Dictionary, isa_proxy, 4,
                  sizeof(::KM2AEvent) );
      instance.SetNew(&new_KM2AEvent);
      instance.SetNewArray(&newArray_KM2AEvent);
      instance.SetDelete(&delete_KM2AEvent);
      instance.SetDeleteArray(&deleteArray_KM2AEvent);
      instance.SetDestructor(&destruct_KM2AEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KM2AEvent*)
   {
      return GenerateInitInstanceLocal((::KM2AEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KM2AEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KM2AHit(void *p = 0);
   static void *newArray_KM2AHit(Long_t size, void *p);
   static void delete_KM2AHit(void *p);
   static void deleteArray_KM2AHit(void *p);
   static void destruct_KM2AHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KM2AHit*)
   {
      ::KM2AHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KM2AHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KM2AHit", ::KM2AHit::Class_Version(), "KM2AEvent.h", 102,
                  typeid(::KM2AHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KM2AHit::Dictionary, isa_proxy, 4,
                  sizeof(::KM2AHit) );
      instance.SetNew(&new_KM2AHit);
      instance.SetNewArray(&newArray_KM2AHit);
      instance.SetDelete(&delete_KM2AHit);
      instance.SetDeleteArray(&deleteArray_KM2AHit);
      instance.SetDestructor(&destruct_KM2AHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KM2AHit*)
   {
      return GenerateInitInstanceLocal((::KM2AHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KM2AHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHEvent(void *p = 0);
   static void *newArray_LHEvent(Long_t size, void *p);
   static void delete_LHEvent(void *p);
   static void deleteArray_LHEvent(void *p);
   static void destruct_LHEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHEvent*)
   {
      ::LHEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHEvent", ::LHEvent::Class_Version(), "LHEvent.h", 12,
                  typeid(::LHEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHEvent::Dictionary, isa_proxy, 4,
                  sizeof(::LHEvent) );
      instance.SetNew(&new_LHEvent);
      instance.SetNewArray(&newArray_LHEvent);
      instance.SetDelete(&delete_LHEvent);
      instance.SetDeleteArray(&deleteArray_LHEvent);
      instance.SetDestructor(&destruct_LHEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHEvent*)
   {
      return GenerateInitInstanceLocal((::LHEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHHit(void *p = 0);
   static void *newArray_LHHit(Long_t size, void *p);
   static void delete_LHHit(void *p);
   static void deleteArray_LHHit(void *p);
   static void destruct_LHHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHHit*)
   {
      ::LHHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHHit", ::LHHit::Class_Version(), "LHEvent.h", 153,
                  typeid(::LHHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHHit::Dictionary, isa_proxy, 4,
                  sizeof(::LHHit) );
      instance.SetNew(&new_LHHit);
      instance.SetNewArray(&newArray_LHHit);
      instance.SetDelete(&delete_LHHit);
      instance.SetDeleteArray(&deleteArray_LHHit);
      instance.SetDestructor(&destruct_LHHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHHit*)
   {
      return GenerateInitInstanceLocal((::LHHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHWave(void *p = 0);
   static void *newArray_LHWave(Long_t size, void *p);
   static void delete_LHWave(void *p);
   static void deleteArray_LHWave(void *p);
   static void destruct_LHWave(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHWave*)
   {
      ::LHWave *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHWave >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHWave", ::LHWave::Class_Version(), "LHEvent.h", 221,
                  typeid(::LHWave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHWave::Dictionary, isa_proxy, 4,
                  sizeof(::LHWave) );
      instance.SetNew(&new_LHWave);
      instance.SetNewArray(&newArray_LHWave);
      instance.SetDelete(&delete_LHWave);
      instance.SetDeleteArray(&deleteArray_LHWave);
      instance.SetDestructor(&destruct_LHWave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHWave*)
   {
      return GenerateInitInstanceLocal((::LHWave*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHWave*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHRecEvent(void *p = 0);
   static void *newArray_LHRecEvent(Long_t size, void *p);
   static void delete_LHRecEvent(void *p);
   static void deleteArray_LHRecEvent(void *p);
   static void destruct_LHRecEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHRecEvent*)
   {
      ::LHRecEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHRecEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHRecEvent", ::LHRecEvent::Class_Version(), "LHRecEvent.h", 7,
                  typeid(::LHRecEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHRecEvent::Dictionary, isa_proxy, 4,
                  sizeof(::LHRecEvent) );
      instance.SetNew(&new_LHRecEvent);
      instance.SetNewArray(&newArray_LHRecEvent);
      instance.SetDelete(&delete_LHRecEvent);
      instance.SetDeleteArray(&deleteArray_LHRecEvent);
      instance.SetDestructor(&destruct_LHRecEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHRecEvent*)
   {
      return GenerateInitInstanceLocal((::LHRecEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHRecEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHAASOEvent(void *p = 0);
   static void *newArray_LHAASOEvent(Long_t size, void *p);
   static void delete_LHAASOEvent(void *p);
   static void deleteArray_LHAASOEvent(void *p);
   static void destruct_LHAASOEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHAASOEvent*)
   {
      ::LHAASOEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHAASOEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHAASOEvent", ::LHAASOEvent::Class_Version(), "LHAASOEvent.h", 17,
                  typeid(::LHAASOEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHAASOEvent::Dictionary, isa_proxy, 4,
                  sizeof(::LHAASOEvent) );
      instance.SetNew(&new_LHAASOEvent);
      instance.SetNewArray(&newArray_LHAASOEvent);
      instance.SetDelete(&delete_LHAASOEvent);
      instance.SetDeleteArray(&deleteArray_LHAASOEvent);
      instance.SetDestructor(&destruct_LHAASOEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHAASOEvent*)
   {
      return GenerateInitInstanceLocal((::LHAASOEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHAASOEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LaserEvent(void *p = 0);
   static void *newArray_LaserEvent(Long_t size, void *p);
   static void delete_LaserEvent(void *p);
   static void deleteArray_LaserEvent(void *p);
   static void destruct_LaserEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LaserEvent*)
   {
      ::LaserEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LaserEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LaserEvent", ::LaserEvent::Class_Version(), "LaserEvent.h", 13,
                  typeid(::LaserEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LaserEvent::Dictionary, isa_proxy, 4,
                  sizeof(::LaserEvent) );
      instance.SetNew(&new_LaserEvent);
      instance.SetNewArray(&newArray_LaserEvent);
      instance.SetDelete(&delete_LaserEvent);
      instance.SetDeleteArray(&deleteArray_LaserEvent);
      instance.SetDestructor(&destruct_LaserEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LaserEvent*)
   {
      return GenerateInitInstanceLocal((::LaserEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LaserEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WFCTAMcEvent(void *p = 0);
   static void *newArray_WFCTAMcEvent(Long_t size, void *p);
   static void delete_WFCTAMcEvent(void *p);
   static void deleteArray_WFCTAMcEvent(void *p);
   static void destruct_WFCTAMcEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WFCTAMcEvent*)
   {
      ::WFCTAMcEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WFCTAMcEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WFCTAMcEvent", ::WFCTAMcEvent::Class_Version(), "WFCTAMcEvent.h", 8,
                  typeid(::WFCTAMcEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WFCTAMcEvent::Dictionary, isa_proxy, 4,
                  sizeof(::WFCTAMcEvent) );
      instance.SetNew(&new_WFCTAMcEvent);
      instance.SetNewArray(&newArray_WFCTAMcEvent);
      instance.SetDelete(&delete_WFCTAMcEvent);
      instance.SetDeleteArray(&deleteArray_WFCTAMcEvent);
      instance.SetDestructor(&destruct_WFCTAMcEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WFCTAMcEvent*)
   {
      return GenerateInitInstanceLocal((::WFCTAMcEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WFCTAMcEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WCDAMcEvent(void *p = 0);
   static void *newArray_WCDAMcEvent(Long_t size, void *p);
   static void delete_WCDAMcEvent(void *p);
   static void deleteArray_WCDAMcEvent(void *p);
   static void destruct_WCDAMcEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WCDAMcEvent*)
   {
      ::WCDAMcEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WCDAMcEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WCDAMcEvent", ::WCDAMcEvent::Class_Version(), "WCDAMcEvent.h", 8,
                  typeid(::WCDAMcEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WCDAMcEvent::Dictionary, isa_proxy, 4,
                  sizeof(::WCDAMcEvent) );
      instance.SetNew(&new_WCDAMcEvent);
      instance.SetNewArray(&newArray_WCDAMcEvent);
      instance.SetDelete(&delete_WCDAMcEvent);
      instance.SetDeleteArray(&deleteArray_WCDAMcEvent);
      instance.SetDestructor(&destruct_WCDAMcEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WCDAMcEvent*)
   {
      return GenerateInitInstanceLocal((::WCDAMcEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WCDAMcEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WCDAEventRec(void *p = 0);
   static void *newArray_WCDAEventRec(Long_t size, void *p);
   static void delete_WCDAEventRec(void *p);
   static void deleteArray_WCDAEventRec(void *p);
   static void destruct_WCDAEventRec(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WCDAEventRec*)
   {
      ::WCDAEventRec *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WCDAEventRec >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WCDAEventRec", ::WCDAEventRec::Class_Version(), "WCDAEventRec.h", 4,
                  typeid(::WCDAEventRec), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WCDAEventRec::Dictionary, isa_proxy, 4,
                  sizeof(::WCDAEventRec) );
      instance.SetNew(&new_WCDAEventRec);
      instance.SetNewArray(&newArray_WCDAEventRec);
      instance.SetDelete(&delete_WCDAEventRec);
      instance.SetDeleteArray(&deleteArray_WCDAEventRec);
      instance.SetDestructor(&destruct_WCDAEventRec);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WCDAEventRec*)
   {
      return GenerateInitInstanceLocal((::WCDAEventRec*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WCDAEventRec*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WFCTAMcRecEvent(void *p = 0);
   static void *newArray_WFCTAMcRecEvent(Long_t size, void *p);
   static void delete_WFCTAMcRecEvent(void *p);
   static void deleteArray_WFCTAMcRecEvent(void *p);
   static void destruct_WFCTAMcRecEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WFCTAMcRecEvent*)
   {
      ::WFCTAMcRecEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WFCTAMcRecEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WFCTAMcRecEvent", ::WFCTAMcRecEvent::Class_Version(), "WFCTAMcRecEvent.h", 8,
                  typeid(::WFCTAMcRecEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WFCTAMcRecEvent::Dictionary, isa_proxy, 4,
                  sizeof(::WFCTAMcRecEvent) );
      instance.SetNew(&new_WFCTAMcRecEvent);
      instance.SetNewArray(&newArray_WFCTAMcRecEvent);
      instance.SetDelete(&delete_WFCTAMcRecEvent);
      instance.SetDeleteArray(&deleteArray_WFCTAMcRecEvent);
      instance.SetDestructor(&destruct_WFCTAMcRecEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WFCTAMcRecEvent*)
   {
      return GenerateInitInstanceLocal((::WFCTAMcRecEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WFCTAMcRecEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KM2AEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KM2AEvent::Class_Name()
{
   return "KM2AEvent";
}

//______________________________________________________________________________
const char *KM2AEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KM2AEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KM2AEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KM2AEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KM2AEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KM2AEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KM2AEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KM2AEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KM2AHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KM2AHit::Class_Name()
{
   return "KM2AHit";
}

//______________________________________________________________________________
const char *KM2AHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KM2AHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KM2AHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KM2AHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KM2AHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KM2AHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KM2AHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KM2AHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHEvent::Class_Name()
{
   return "LHEvent";
}

//______________________________________________________________________________
const char *LHEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHHit::Class_Name()
{
   return "LHHit";
}

//______________________________________________________________________________
const char *LHHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHWave::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHWave::Class_Name()
{
   return "LHWave";
}

//______________________________________________________________________________
const char *LHWave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHWave*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHWave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHWave*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHWave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHWave*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHWave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHWave*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHRecEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHRecEvent::Class_Name()
{
   return "LHRecEvent";
}

//______________________________________________________________________________
const char *LHRecEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHRecEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHRecEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHRecEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHRecEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHRecEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHRecEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHRecEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHAASOEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHAASOEvent::Class_Name()
{
   return "LHAASOEvent";
}

//______________________________________________________________________________
const char *LHAASOEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHAASOEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHAASOEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHAASOEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHAASOEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHAASOEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHAASOEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHAASOEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LaserEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LaserEvent::Class_Name()
{
   return "LaserEvent";
}

//______________________________________________________________________________
const char *LaserEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LaserEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LaserEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LaserEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LaserEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LaserEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LaserEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LaserEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WFCTAMcEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WFCTAMcEvent::Class_Name()
{
   return "WFCTAMcEvent";
}

//______________________________________________________________________________
const char *WFCTAMcEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WFCTAMcEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WFCTAMcEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WFCTAMcEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WCDAMcEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WCDAMcEvent::Class_Name()
{
   return "WCDAMcEvent";
}

//______________________________________________________________________________
const char *WCDAMcEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WCDAMcEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WCDAMcEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WCDAMcEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WCDAMcEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WCDAMcEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WCDAMcEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WCDAMcEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WCDAEventRec::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WCDAEventRec::Class_Name()
{
   return "WCDAEventRec";
}

//______________________________________________________________________________
const char *WCDAEventRec::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WCDAEventRec*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WCDAEventRec::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WCDAEventRec*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WCDAEventRec::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WCDAEventRec*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WCDAEventRec::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WCDAEventRec*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WFCTAMcRecEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WFCTAMcRecEvent::Class_Name()
{
   return "WFCTAMcRecEvent";
}

//______________________________________________________________________________
const char *WFCTAMcRecEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcRecEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WFCTAMcRecEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcRecEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WFCTAMcRecEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcRecEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WFCTAMcRecEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFCTAMcRecEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KM2AEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class KM2AEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KM2AEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(KM2AEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KM2AEvent(void *p) {
      return  p ? new(p) ::KM2AEvent : new ::KM2AEvent;
   }
   static void *newArray_KM2AEvent(Long_t nElements, void *p) {
      return p ? new(p) ::KM2AEvent[nElements] : new ::KM2AEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_KM2AEvent(void *p) {
      delete ((::KM2AEvent*)p);
   }
   static void deleteArray_KM2AEvent(void *p) {
      delete [] ((::KM2AEvent*)p);
   }
   static void destruct_KM2AEvent(void *p) {
      typedef ::KM2AEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KM2AEvent

//______________________________________________________________________________
void KM2AHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class KM2AHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KM2AHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(KM2AHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KM2AHit(void *p) {
      return  p ? new(p) ::KM2AHit : new ::KM2AHit;
   }
   static void *newArray_KM2AHit(Long_t nElements, void *p) {
      return p ? new(p) ::KM2AHit[nElements] : new ::KM2AHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_KM2AHit(void *p) {
      delete ((::KM2AHit*)p);
   }
   static void deleteArray_KM2AHit(void *p) {
      delete [] ((::KM2AHit*)p);
   }
   static void destruct_KM2AHit(void *p) {
      typedef ::KM2AHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KM2AHit

//______________________________________________________________________________
void LHEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHEvent(void *p) {
      return  p ? new(p) ::LHEvent : new ::LHEvent;
   }
   static void *newArray_LHEvent(Long_t nElements, void *p) {
      return p ? new(p) ::LHEvent[nElements] : new ::LHEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHEvent(void *p) {
      delete ((::LHEvent*)p);
   }
   static void deleteArray_LHEvent(void *p) {
      delete [] ((::LHEvent*)p);
   }
   static void destruct_LHEvent(void *p) {
      typedef ::LHEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHEvent

//______________________________________________________________________________
void LHHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHHit(void *p) {
      return  p ? new(p) ::LHHit : new ::LHHit;
   }
   static void *newArray_LHHit(Long_t nElements, void *p) {
      return p ? new(p) ::LHHit[nElements] : new ::LHHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHHit(void *p) {
      delete ((::LHHit*)p);
   }
   static void deleteArray_LHHit(void *p) {
      delete [] ((::LHHit*)p);
   }
   static void destruct_LHHit(void *p) {
      typedef ::LHHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHHit

//______________________________________________________________________________
void LHWave::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHWave.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHWave::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHWave::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHWave(void *p) {
      return  p ? new(p) ::LHWave : new ::LHWave;
   }
   static void *newArray_LHWave(Long_t nElements, void *p) {
      return p ? new(p) ::LHWave[nElements] : new ::LHWave[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHWave(void *p) {
      delete ((::LHWave*)p);
   }
   static void deleteArray_LHWave(void *p) {
      delete [] ((::LHWave*)p);
   }
   static void destruct_LHWave(void *p) {
      typedef ::LHWave current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHWave

//______________________________________________________________________________
void LHRecEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHRecEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHRecEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHRecEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHRecEvent(void *p) {
      return  p ? new(p) ::LHRecEvent : new ::LHRecEvent;
   }
   static void *newArray_LHRecEvent(Long_t nElements, void *p) {
      return p ? new(p) ::LHRecEvent[nElements] : new ::LHRecEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHRecEvent(void *p) {
      delete ((::LHRecEvent*)p);
   }
   static void deleteArray_LHRecEvent(void *p) {
      delete [] ((::LHRecEvent*)p);
   }
   static void destruct_LHRecEvent(void *p) {
      typedef ::LHRecEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHRecEvent

//______________________________________________________________________________
void LHAASOEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHAASOEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHAASOEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHAASOEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHAASOEvent(void *p) {
      return  p ? new(p) ::LHAASOEvent : new ::LHAASOEvent;
   }
   static void *newArray_LHAASOEvent(Long_t nElements, void *p) {
      return p ? new(p) ::LHAASOEvent[nElements] : new ::LHAASOEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHAASOEvent(void *p) {
      delete ((::LHAASOEvent*)p);
   }
   static void deleteArray_LHAASOEvent(void *p) {
      delete [] ((::LHAASOEvent*)p);
   }
   static void destruct_LHAASOEvent(void *p) {
      typedef ::LHAASOEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHAASOEvent

//______________________________________________________________________________
void LaserEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class LaserEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LaserEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(LaserEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LaserEvent(void *p) {
      return  p ? new(p) ::LaserEvent : new ::LaserEvent;
   }
   static void *newArray_LaserEvent(Long_t nElements, void *p) {
      return p ? new(p) ::LaserEvent[nElements] : new ::LaserEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_LaserEvent(void *p) {
      delete ((::LaserEvent*)p);
   }
   static void deleteArray_LaserEvent(void *p) {
      delete [] ((::LaserEvent*)p);
   }
   static void destruct_LaserEvent(void *p) {
      typedef ::LaserEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LaserEvent

//______________________________________________________________________________
void WFCTAMcEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class WFCTAMcEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WFCTAMcEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(WFCTAMcEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WFCTAMcEvent(void *p) {
      return  p ? new(p) ::WFCTAMcEvent : new ::WFCTAMcEvent;
   }
   static void *newArray_WFCTAMcEvent(Long_t nElements, void *p) {
      return p ? new(p) ::WFCTAMcEvent[nElements] : new ::WFCTAMcEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_WFCTAMcEvent(void *p) {
      delete ((::WFCTAMcEvent*)p);
   }
   static void deleteArray_WFCTAMcEvent(void *p) {
      delete [] ((::WFCTAMcEvent*)p);
   }
   static void destruct_WFCTAMcEvent(void *p) {
      typedef ::WFCTAMcEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WFCTAMcEvent

//______________________________________________________________________________
void WCDAMcEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class WCDAMcEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WCDAMcEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(WCDAMcEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WCDAMcEvent(void *p) {
      return  p ? new(p) ::WCDAMcEvent : new ::WCDAMcEvent;
   }
   static void *newArray_WCDAMcEvent(Long_t nElements, void *p) {
      return p ? new(p) ::WCDAMcEvent[nElements] : new ::WCDAMcEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_WCDAMcEvent(void *p) {
      delete ((::WCDAMcEvent*)p);
   }
   static void deleteArray_WCDAMcEvent(void *p) {
      delete [] ((::WCDAMcEvent*)p);
   }
   static void destruct_WCDAMcEvent(void *p) {
      typedef ::WCDAMcEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WCDAMcEvent

//______________________________________________________________________________
void WCDAEventRec::Streamer(TBuffer &R__b)
{
   // Stream an object of class WCDAEventRec.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WCDAEventRec::Class(),this);
   } else {
      R__b.WriteClassBuffer(WCDAEventRec::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WCDAEventRec(void *p) {
      return  p ? new(p) ::WCDAEventRec : new ::WCDAEventRec;
   }
   static void *newArray_WCDAEventRec(Long_t nElements, void *p) {
      return p ? new(p) ::WCDAEventRec[nElements] : new ::WCDAEventRec[nElements];
   }
   // Wrapper around operator delete
   static void delete_WCDAEventRec(void *p) {
      delete ((::WCDAEventRec*)p);
   }
   static void deleteArray_WCDAEventRec(void *p) {
      delete [] ((::WCDAEventRec*)p);
   }
   static void destruct_WCDAEventRec(void *p) {
      typedef ::WCDAEventRec current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WCDAEventRec

//______________________________________________________________________________
void WFCTAMcRecEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class WFCTAMcRecEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WFCTAMcRecEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(WFCTAMcRecEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WFCTAMcRecEvent(void *p) {
      return  p ? new(p) ::WFCTAMcRecEvent : new ::WFCTAMcRecEvent;
   }
   static void *newArray_WFCTAMcRecEvent(Long_t nElements, void *p) {
      return p ? new(p) ::WFCTAMcRecEvent[nElements] : new ::WFCTAMcRecEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_WFCTAMcRecEvent(void *p) {
      delete ((::WFCTAMcRecEvent*)p);
   }
   static void deleteArray_WFCTAMcRecEvent(void *p) {
      delete [] ((::WFCTAMcRecEvent*)p);
   }
   static void destruct_WFCTAMcRecEvent(void *p) {
      typedef ::WFCTAMcRecEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WFCTAMcRecEvent

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 216,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 216,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_EventDict_Impl() {
    static const char* headers[] = {
"KM2AEvent.h",
"LHEvent.h",
"LHRecEvent.h",
"LHAASOEvent.h",
"LaserEvent.h",
"WFCTAMcEvent.h",
"WCDAMcEvent.h",
"WCDAEventRec.h",
"WFCTAMcRecEvent.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/lhaaso.ihep.ac.cn/anysw/slc5_ia64_gcc73/external/root/6.14.00/include",
"/workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector/include/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "EventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$KM2AEvent.h")))  KM2AEvent;
class __attribute__((annotate("$clingAutoload$KM2AEvent.h")))  KM2AHit;
class __attribute__((annotate("$clingAutoload$LHEvent.h")))  LHEvent;
class __attribute__((annotate("$clingAutoload$LHEvent.h")))  LHHit;
class __attribute__((annotate("$clingAutoload$LHEvent.h")))  LHWave;
class __attribute__((annotate("$clingAutoload$LHRecEvent.h")))  LHRecEvent;
class __attribute__((annotate("$clingAutoload$LHAASOEvent.h")))  LHAASOEvent;
class __attribute__((annotate("$clingAutoload$LaserEvent.h")))  LaserEvent;
class __attribute__((annotate("$clingAutoload$WFCTAMcEvent.h")))  WFCTAMcEvent;
class __attribute__((annotate("$clingAutoload$WCDAMcEvent.h")))  WCDAMcEvent;
class __attribute__((annotate("$clingAutoload$WCDAEventRec.h")))  WCDAEventRec;
class __attribute__((annotate("$clingAutoload$WFCTAMcRecEvent.h")))  WFCTAMcRecEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "EventDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "KM2AEvent.h"
#include "LHEvent.h"
#include "LHRecEvent.h"
#include "LHAASOEvent.h"
#include "LaserEvent.h"
#include "WFCTAMcEvent.h"
#include "WCDAMcEvent.h"
#include "WCDAEventRec.h"
#include "WFCTAMcRecEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KM2AEvent", payloadCode, "@",
"KM2AHit", payloadCode, "@",
"LHAASOEvent", payloadCode, "@",
"LHEvent", payloadCode, "@",
"LHHit", payloadCode, "@",
"LHRecEvent", payloadCode, "@",
"LHWave", payloadCode, "@",
"LaserEvent", payloadCode, "@",
"StrDup", payloadCode, "@",
"WCDAEventRec", payloadCode, "@",
"WCDAMcEvent", payloadCode, "@",
"WFCTAMcEvent", payloadCode, "@",
"WFCTAMcRecEvent", payloadCode, "@",
"operator+", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("EventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_EventDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_EventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_EventDict() {
  TriggerDictionaryInitialization_EventDict_Impl();
}
