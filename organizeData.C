TTree *tree;
#include "GetConfig.C"

void organizeData(int idx=24, int det = 3 )
{
  fIndex = idx;
  fDet = det;
  GetConfig();
  if(fCell.Length()<2) return 1;

  int inst = 0;
  if(fRun>=1209) inst = 1;
  if(fRun>=1250) inst = 2;
  if(fRun>=1291) inst = 3;
  if(fRun>=1465) inst = 4;
  if(fRun>=1619) inst = 5;
  if(fRun>=1637) inst = 6;
  if(fRun>=1733) inst = 7;

  TString file = Form("%s_%s_D%d_I%d.txt4", fTech.Data(), fBoard.Data(),fDet,inst);
  cout << file.Data() << endl;

  ofstream fout;
  fout.open( file.Data(), std::ofstream::out | std::ofstream::app);
  double yb = 9999;
  if(fYBeat>0.00001) {
    yb = 20./fYBeat;
  }
  fout << Form("%s %.1f %.1f %.1f %.1f %d %d", fCell.Data(), 
	       fGXmin, fGXmax, fGYmin, fGYmax, fRun, fDet) << " ";
  fout << Form("%.2f %.2f %.0f", fXPitch, yb, fXStretch) << endl;

  return 0;
}
