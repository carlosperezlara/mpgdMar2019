// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Dict_

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
#include "MappingTableCollection.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Cluster(void *p = 0);
   static void *newArray_Cluster(Long_t size, void *p);
   static void delete_Cluster(void *p);
   static void deleteArray_Cluster(void *p);
   static void destruct_Cluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Cluster*)
   {
      ::Cluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Cluster >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Cluster", ::Cluster::Class_Version(), "MappingTableCollection.h", 13,
                  typeid(::Cluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Cluster::Dictionary, isa_proxy, 4,
                  sizeof(::Cluster) );
      instance.SetNew(&new_Cluster);
      instance.SetNewArray(&newArray_Cluster);
      instance.SetDelete(&delete_Cluster);
      instance.SetDeleteArray(&deleteArray_Cluster);
      instance.SetDestructor(&destruct_Cluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Cluster*)
   {
      return GenerateInitInstanceLocal((::Cluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Cluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MappingPlane(void *p = 0);
   static void *newArray_MappingPlane(Long_t size, void *p);
   static void delete_MappingPlane(void *p);
   static void deleteArray_MappingPlane(void *p);
   static void destruct_MappingPlane(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MappingPlane*)
   {
      ::MappingPlane *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MappingPlane >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MappingPlane", ::MappingPlane::Class_Version(), "MappingTableCollection.h", 25,
                  typeid(::MappingPlane), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MappingPlane::Dictionary, isa_proxy, 4,
                  sizeof(::MappingPlane) );
      instance.SetNew(&new_MappingPlane);
      instance.SetNewArray(&newArray_MappingPlane);
      instance.SetDelete(&delete_MappingPlane);
      instance.SetDeleteArray(&deleteArray_MappingPlane);
      instance.SetDestructor(&destruct_MappingPlane);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MappingPlane*)
   {
      return GenerateInitInstanceLocal((::MappingPlane*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MappingPlane*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MappingSpot(void *p = 0);
   static void *newArray_MappingSpot(Long_t size, void *p);
   static void delete_MappingSpot(void *p);
   static void deleteArray_MappingSpot(void *p);
   static void destruct_MappingSpot(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MappingSpot*)
   {
      ::MappingSpot *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MappingSpot >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MappingSpot", ::MappingSpot::Class_Version(), "MappingTableCollection.h", 73,
                  typeid(::MappingSpot), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MappingSpot::Dictionary, isa_proxy, 4,
                  sizeof(::MappingSpot) );
      instance.SetNew(&new_MappingSpot);
      instance.SetNewArray(&newArray_MappingSpot);
      instance.SetDelete(&delete_MappingSpot);
      instance.SetDeleteArray(&deleteArray_MappingSpot);
      instance.SetDestructor(&destruct_MappingSpot);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MappingSpot*)
   {
      return GenerateInitInstanceLocal((::MappingSpot*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MappingSpot*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MappingTable(void *p = 0);
   static void *newArray_MappingTable(Long_t size, void *p);
   static void delete_MappingTable(void *p);
   static void deleteArray_MappingTable(void *p);
   static void destruct_MappingTable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MappingTable*)
   {
      ::MappingTable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MappingTable >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MappingTable", ::MappingTable::Class_Version(), "MappingTableCollection.h", 111,
                  typeid(::MappingTable), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MappingTable::Dictionary, isa_proxy, 4,
                  sizeof(::MappingTable) );
      instance.SetNew(&new_MappingTable);
      instance.SetNewArray(&newArray_MappingTable);
      instance.SetDelete(&delete_MappingTable);
      instance.SetDeleteArray(&deleteArray_MappingTable);
      instance.SetDestructor(&destruct_MappingTable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MappingTable*)
   {
      return GenerateInitInstanceLocal((::MappingTable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MappingTable*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MappingTableCollection(void *p = 0);
   static void *newArray_MappingTableCollection(Long_t size, void *p);
   static void delete_MappingTableCollection(void *p);
   static void deleteArray_MappingTableCollection(void *p);
   static void destruct_MappingTableCollection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MappingTableCollection*)
   {
      ::MappingTableCollection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MappingTableCollection >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MappingTableCollection", ::MappingTableCollection::Class_Version(), "MappingTableCollection.h", 144,
                  typeid(::MappingTableCollection), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MappingTableCollection::Dictionary, isa_proxy, 4,
                  sizeof(::MappingTableCollection) );
      instance.SetNew(&new_MappingTableCollection);
      instance.SetNewArray(&newArray_MappingTableCollection);
      instance.SetDelete(&delete_MappingTableCollection);
      instance.SetDeleteArray(&deleteArray_MappingTableCollection);
      instance.SetDestructor(&destruct_MappingTableCollection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MappingTableCollection*)
   {
      return GenerateInitInstanceLocal((::MappingTableCollection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MappingTableCollection*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Cluster::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Cluster::Class_Name()
{
   return "Cluster";
}

//______________________________________________________________________________
const char *Cluster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Cluster*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Cluster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Cluster*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Cluster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Cluster*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Cluster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Cluster*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MappingPlane::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MappingPlane::Class_Name()
{
   return "MappingPlane";
}

//______________________________________________________________________________
const char *MappingPlane::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingPlane*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MappingPlane::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingPlane*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MappingPlane::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingPlane*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MappingPlane::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingPlane*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MappingSpot::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MappingSpot::Class_Name()
{
   return "MappingSpot";
}

//______________________________________________________________________________
const char *MappingSpot::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingSpot*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MappingSpot::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingSpot*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MappingSpot::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingSpot*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MappingSpot::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingSpot*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MappingTable::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MappingTable::Class_Name()
{
   return "MappingTable";
}

//______________________________________________________________________________
const char *MappingTable::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingTable*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MappingTable::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingTable*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MappingTable::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingTable*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MappingTable::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingTable*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MappingTableCollection::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MappingTableCollection::Class_Name()
{
   return "MappingTableCollection";
}

//______________________________________________________________________________
const char *MappingTableCollection::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingTableCollection*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MappingTableCollection::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MappingTableCollection*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MappingTableCollection::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingTableCollection*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MappingTableCollection::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MappingTableCollection*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Cluster::Streamer(TBuffer &R__b)
{
   // Stream an object of class Cluster.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Cluster::Class(),this);
   } else {
      R__b.WriteClassBuffer(Cluster::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Cluster(void *p) {
      return  p ? new(p) ::Cluster : new ::Cluster;
   }
   static void *newArray_Cluster(Long_t nElements, void *p) {
      return p ? new(p) ::Cluster[nElements] : new ::Cluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_Cluster(void *p) {
      delete ((::Cluster*)p);
   }
   static void deleteArray_Cluster(void *p) {
      delete [] ((::Cluster*)p);
   }
   static void destruct_Cluster(void *p) {
      typedef ::Cluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Cluster

//______________________________________________________________________________
void MappingPlane::Streamer(TBuffer &R__b)
{
   // Stream an object of class MappingPlane.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MappingPlane::Class(),this);
   } else {
      R__b.WriteClassBuffer(MappingPlane::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MappingPlane(void *p) {
      return  p ? new(p) ::MappingPlane : new ::MappingPlane;
   }
   static void *newArray_MappingPlane(Long_t nElements, void *p) {
      return p ? new(p) ::MappingPlane[nElements] : new ::MappingPlane[nElements];
   }
   // Wrapper around operator delete
   static void delete_MappingPlane(void *p) {
      delete ((::MappingPlane*)p);
   }
   static void deleteArray_MappingPlane(void *p) {
      delete [] ((::MappingPlane*)p);
   }
   static void destruct_MappingPlane(void *p) {
      typedef ::MappingPlane current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MappingPlane

//______________________________________________________________________________
void MappingSpot::Streamer(TBuffer &R__b)
{
   // Stream an object of class MappingSpot.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MappingSpot::Class(),this);
   } else {
      R__b.WriteClassBuffer(MappingSpot::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MappingSpot(void *p) {
      return  p ? new(p) ::MappingSpot : new ::MappingSpot;
   }
   static void *newArray_MappingSpot(Long_t nElements, void *p) {
      return p ? new(p) ::MappingSpot[nElements] : new ::MappingSpot[nElements];
   }
   // Wrapper around operator delete
   static void delete_MappingSpot(void *p) {
      delete ((::MappingSpot*)p);
   }
   static void deleteArray_MappingSpot(void *p) {
      delete [] ((::MappingSpot*)p);
   }
   static void destruct_MappingSpot(void *p) {
      typedef ::MappingSpot current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MappingSpot

//______________________________________________________________________________
void MappingTable::Streamer(TBuffer &R__b)
{
   // Stream an object of class MappingTable.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MappingTable::Class(),this);
   } else {
      R__b.WriteClassBuffer(MappingTable::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MappingTable(void *p) {
      return  p ? new(p) ::MappingTable : new ::MappingTable;
   }
   static void *newArray_MappingTable(Long_t nElements, void *p) {
      return p ? new(p) ::MappingTable[nElements] : new ::MappingTable[nElements];
   }
   // Wrapper around operator delete
   static void delete_MappingTable(void *p) {
      delete ((::MappingTable*)p);
   }
   static void deleteArray_MappingTable(void *p) {
      delete [] ((::MappingTable*)p);
   }
   static void destruct_MappingTable(void *p) {
      typedef ::MappingTable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MappingTable

//______________________________________________________________________________
void MappingTableCollection::Streamer(TBuffer &R__b)
{
   // Stream an object of class MappingTableCollection.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MappingTableCollection::Class(),this);
   } else {
      R__b.WriteClassBuffer(MappingTableCollection::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MappingTableCollection(void *p) {
      return  p ? new(p) ::MappingTableCollection : new ::MappingTableCollection;
   }
   static void *newArray_MappingTableCollection(Long_t nElements, void *p) {
      return p ? new(p) ::MappingTableCollection[nElements] : new ::MappingTableCollection[nElements];
   }
   // Wrapper around operator delete
   static void delete_MappingTableCollection(void *p) {
      delete ((::MappingTableCollection*)p);
   }
   static void deleteArray_MappingTableCollection(void *p) {
      delete [] ((::MappingTableCollection*)p);
   }
   static void destruct_MappingTableCollection(void *p) {
      typedef ::MappingTableCollection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MappingTableCollection

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 210,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<unsigned int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned int>*)0x0)->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete ((vector<unsigned int>*)p);
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] ((vector<unsigned int>*)p);
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlEMappingPlanemUgR_Dictionary();
   static void vectorlEMappingPlanemUgR_TClassManip(TClass*);
   static void *new_vectorlEMappingPlanemUgR(void *p = 0);
   static void *newArray_vectorlEMappingPlanemUgR(Long_t size, void *p);
   static void delete_vectorlEMappingPlanemUgR(void *p);
   static void deleteArray_vectorlEMappingPlanemUgR(void *p);
   static void destruct_vectorlEMappingPlanemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MappingPlane*>*)
   {
      vector<MappingPlane*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MappingPlane*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MappingPlane*>", -2, "vector", 210,
                  typeid(vector<MappingPlane*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMappingPlanemUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<MappingPlane*>) );
      instance.SetNew(&new_vectorlEMappingPlanemUgR);
      instance.SetNewArray(&newArray_vectorlEMappingPlanemUgR);
      instance.SetDelete(&delete_vectorlEMappingPlanemUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMappingPlanemUgR);
      instance.SetDestructor(&destruct_vectorlEMappingPlanemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MappingPlane*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<MappingPlane*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMappingPlanemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MappingPlane*>*)0x0)->GetClass();
      vectorlEMappingPlanemUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMappingPlanemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMappingPlanemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MappingPlane*> : new vector<MappingPlane*>;
   }
   static void *newArray_vectorlEMappingPlanemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MappingPlane*>[nElements] : new vector<MappingPlane*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMappingPlanemUgR(void *p) {
      delete ((vector<MappingPlane*>*)p);
   }
   static void deleteArray_vectorlEMappingPlanemUgR(void *p) {
      delete [] ((vector<MappingPlane*>*)p);
   }
   static void destruct_vectorlEMappingPlanemUgR(void *p) {
      typedef vector<MappingPlane*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MappingPlane*>

namespace ROOT {
   static TClass *maplETStringcOMappingTablemUgR_Dictionary();
   static void maplETStringcOMappingTablemUgR_TClassManip(TClass*);
   static void *new_maplETStringcOMappingTablemUgR(void *p = 0);
   static void *newArray_maplETStringcOMappingTablemUgR(Long_t size, void *p);
   static void delete_maplETStringcOMappingTablemUgR(void *p);
   static void deleteArray_maplETStringcOMappingTablemUgR(void *p);
   static void destruct_maplETStringcOMappingTablemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,MappingTable*>*)
   {
      map<TString,MappingTable*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,MappingTable*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,MappingTable*>", -2, "map", 96,
                  typeid(map<TString,MappingTable*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOMappingTablemUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,MappingTable*>) );
      instance.SetNew(&new_maplETStringcOMappingTablemUgR);
      instance.SetNewArray(&newArray_maplETStringcOMappingTablemUgR);
      instance.SetDelete(&delete_maplETStringcOMappingTablemUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOMappingTablemUgR);
      instance.SetDestructor(&destruct_maplETStringcOMappingTablemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,MappingTable*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,MappingTable*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOMappingTablemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,MappingTable*>*)0x0)->GetClass();
      maplETStringcOMappingTablemUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOMappingTablemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOMappingTablemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,MappingTable*> : new map<TString,MappingTable*>;
   }
   static void *newArray_maplETStringcOMappingTablemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,MappingTable*>[nElements] : new map<TString,MappingTable*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOMappingTablemUgR(void *p) {
      delete ((map<TString,MappingTable*>*)p);
   }
   static void deleteArray_maplETStringcOMappingTablemUgR(void *p) {
      delete [] ((map<TString,MappingTable*>*)p);
   }
   static void destruct_maplETStringcOMappingTablemUgR(void *p) {
      typedef map<TString,MappingTable*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,MappingTable*>

namespace ROOT {
   static TClass *maplETStringcOMappingSpotmUgR_Dictionary();
   static void maplETStringcOMappingSpotmUgR_TClassManip(TClass*);
   static void *new_maplETStringcOMappingSpotmUgR(void *p = 0);
   static void *newArray_maplETStringcOMappingSpotmUgR(Long_t size, void *p);
   static void delete_maplETStringcOMappingSpotmUgR(void *p);
   static void deleteArray_maplETStringcOMappingSpotmUgR(void *p);
   static void destruct_maplETStringcOMappingSpotmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,MappingSpot*>*)
   {
      map<TString,MappingSpot*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,MappingSpot*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,MappingSpot*>", -2, "map", 96,
                  typeid(map<TString,MappingSpot*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOMappingSpotmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,MappingSpot*>) );
      instance.SetNew(&new_maplETStringcOMappingSpotmUgR);
      instance.SetNewArray(&newArray_maplETStringcOMappingSpotmUgR);
      instance.SetDelete(&delete_maplETStringcOMappingSpotmUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOMappingSpotmUgR);
      instance.SetDestructor(&destruct_maplETStringcOMappingSpotmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,MappingSpot*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,MappingSpot*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOMappingSpotmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,MappingSpot*>*)0x0)->GetClass();
      maplETStringcOMappingSpotmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOMappingSpotmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOMappingSpotmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,MappingSpot*> : new map<TString,MappingSpot*>;
   }
   static void *newArray_maplETStringcOMappingSpotmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,MappingSpot*>[nElements] : new map<TString,MappingSpot*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOMappingSpotmUgR(void *p) {
      delete ((map<TString,MappingSpot*>*)p);
   }
   static void deleteArray_maplETStringcOMappingSpotmUgR(void *p) {
      delete [] ((map<TString,MappingSpot*>*)p);
   }
   static void destruct_maplETStringcOMappingSpotmUgR(void *p) {
      typedef map<TString,MappingSpot*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,MappingSpot*>

namespace {
  void TriggerDictionaryInitialization_Dict__Impl() {
    static const char* headers[] = {
"MappingTableCollection.h",
0
    };
    static const char* includePaths[] = {
"/gpfs/mnt/gpfs02/eic/TEST.RUNS/2019-03-FNAL/root-6.14.00.build/include",
"/gpfs/mnt/gpfs02/eic/TEST.RUNS/2019-03-FNAL/root-6.14.00.build/include",
"/direct/eic+u/perez/mpgdMar2019/mapping/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Dict_ dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate("$clingAutoload$MappingTableCollection.h")))  Cluster;
class __attribute__((annotate("$clingAutoload$MappingTableCollection.h")))  MappingPlane;
class __attribute__((annotate("$clingAutoload$MappingTableCollection.h")))  MappingSpot;
class __attribute__((annotate("$clingAutoload$MappingTableCollection.h")))  MappingTable;
class __attribute__((annotate("$clingAutoload$MappingTableCollection.h")))  MappingTableCollection;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dict_ dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MappingTableCollection.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Cluster", payloadCode, "@",
"MappingPlane", payloadCode, "@",
"MappingSpot", payloadCode, "@",
"MappingTable", payloadCode, "@",
"MappingTableCollection", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dict_",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dict__Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dict__Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dict_() {
  TriggerDictionaryInitialization_Dict__Impl();
}
