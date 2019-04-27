#include <iostream>
#include "MappingTableCollection.h"
#include "TFile.h"

int main( int n, char** par ) {
  // Create mapping table collection;
  MappingTableCollection *mcollection = new MappingTableCollection();
  if(n<3) return 1;

  TString board = par[1];
  TString cell = par[2];
  
  std::cout << "BOARD " << board.Data() << std::endl;
  std::cout << "CELL " << cell.Data() << std::endl;
  // Import tagged ROOT files;
  {
    const char *mfiles[] = {"B00e.root",  "B01a.root",  "V00a.root",  "Z03k.A.root",  "Z03k.B.root",  "Z03k.D.root"};

    for(unsigned i=0; i<sizeof(mfiles)/sizeof(mfiles[0]); i++) {
      TFile *ff = new TFile(mfiles[i]);
      MappingTable *mtable = (MappingTable*)ff->Get("MappingTable"); assert(mtable); 
      //printf("\n  %s\n", mtable->GetTag().Data());

      mcollection->AddMappingTable(mtable); 
    } //for i
  }
  // Create direct access lookup tables for all registered [pcb,spot] entries;
  mcollection->CreateLookupTables();
  // Usage example;
  {
    // Get mapping table for a given PCB model (if imported);
    MappingTable *mtable = mcollection->GetMappingTable( board.Data() ); 

    if (mtable) {
      // Get particular spot entry (if exists);
      MappingSpot *mspot = mtable->GetMappingSpot( cell.Data() ); assert(mspot);
      //printf("\n -> %d plane(s)\n", mspot ? mspot->GetPlaneCount() : 0);
      if (mspot) {
	// Spot information;
	for(unsigned pl=0; pl<1; pl++) {
	  const MappingPlane *mplane = mspot->GetMappingPlane(pl);
	  std::cout << "Number of channels" << mplane->GetStripCount() << std::endl;
	  for(int ch=0; ch!=mplane->GetStripCount(); ++ch) {
	    std::cout << " ChannelID" << ch << " " <<  mplane->GetDreamChannel(ch) << std::endl;
	  }
	  std::cout << mplane->GetPitch() << std::endl;
	  // HERE mplane
	} //for pl
      } //if 
    } //if
  }
} // mviewer()
