TTree *tree;
#include "GetConfig.C"

void organizeData(int idx=24, int det = 3 )
{
  fIndex = idx;
  fDet = det;
  GetConfig();

  TString file = Form("%s_%s.txt", fTech.Data(), fBoard.Data());
  cout << file.Data() << endl;
  if(fCell.Length()<2) return 1;
  ofstream fout;
  fout.open( file.Data(), std::ofstream::out | std::ofstream::app);
  fout << Form("%s %.1f %.1f %.1f %.1f %d %d", fCell.Data(), 
	       fGXmin, fGXmax, fGYmin, fGYmax, fRun, fDet) << " ";
  fout << Form("%.2f %.2f %.0f", fXPitch, 20./fYBeat, fXStretch) << endl;

  return 0;
}
