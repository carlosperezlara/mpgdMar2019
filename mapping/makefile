all:
	rootcint -f Dict_.cpp -c `root-config --cflags` -p MappingTableCollection.h mappingLinkDef.h
	g++ -o mapdreamchannels mviewer.C MappingTableCollection.cc Dict_.cpp -I. `root-config --cflags --glibs`
