Int_t fIndex;
Int_t fRun;
Double_t fChiMax=2;
TTree *tree;

void GetConfig() {
  ifstream fin("elog/runs.dat.evt.num");
  Int_t index = fIndex;
  for(;;--index) {
    fin >> fRun;
    if(index==0) {
      break;
    }
  }
  fin.close();

  double tdbl;
  int tint;
  fin.open("track/dat/chi2_stat.dat");
  for(;;) {
    fin >> tint;
    if(!fin.good()) {
      break;
    }
    if(tint==fRun) {
      fin >> fChiMax >> tdbl;
      fChiMax += 3*tdbl;
      break;
    } else {
      fin >> tdbl >> tdbl;
    }
  }
  fin.close();
}
//=================================
void track(int idx ) {
  fIndex = idx;
  GetConfig();
  std::cout << "Run " << fRun << endl;
  gStyle->SetOptStat(0);
  gSystem->Load("libfnal4all.so");
  TLatex *tex = new TLatex();
  TFile *ff = new TFile( Form("rootfiles/fnal-%05d.root",fRun) );
  tree = (TTree*)ff->Get("ZIGZAG");
  TCanvas *main = new TCanvas();
  main->Divide(3,1);
  //=====
  main->cd(1);
  tree->Draw("bx");
  tree->Draw("bx>>histX", Form("chi2<%f",fChiMax), "SAME" );
  main->cd(2);
  tree->Draw("by");
  tree->Draw("by>>histY", Form("chi2<%f",fChiMax), "SAME" );
  main->cd(3);
  tree->Draw("chi2>>histC(100,0,20)");
  tree->Draw("chi2>>histS(100,0,20)", Form("chi2<%f",fChiMax), "SAME");
  TH1D *histC = (TH1D*) gROOT->FindObject( "histC" );
  TH1D *histX = (TH1D*) gROOT->FindObject( "histX" );
  TH1D *histY = (TH1D*) gROOT->FindObject( "histY" );
  TH1D *histS = (TH1D*) gROOT->FindObject( "histS" );
  histX->SetLineColor(kRed-3);
  histY->SetLineColor(kRed-3);
  histS->SetLineColor(kRed-3);
  if(histC->GetEntries()<10) return 1;
  tex->DrawLatexNDC(0.5,0.8, Form("Mean  %.3f",histC->GetMean()) );
  tex->DrawLatexNDC(0.5,0.7, Form("RMS  %.3f",histC->GetRMS()) );
  main->cd(1);
  tex->DrawLatexNDC(0.5,0.8, Form("Mean  %.3f",histX->GetMean()) );
  tex->DrawLatexNDC(0.5,0.7, Form("RMS  %.3f",histX->GetRMS()) );
  main->cd(2);
  tex->DrawLatexNDC(0.5,0.8, Form("Mean  %.3f",histY->GetMean()) );
  tex->DrawLatexNDC(0.5,0.7, Form("RMS  %.3f",histY->GetRMS()) );

  main->SaveAs( Form("track/track_%d.pdf", fRun), "pdf");
  main->SaveAs( Form("track/track_%d.root", fRun), "root");

  ofstream fout( Form("track/dat/chi2_stat_%d.dat",fRun) );
  fout << fRun;
  fout << " " << histC->GetMean() << " " << histC->GetRMS();
  fout << " " << histX->GetMean() << " " << histX->GetRMS();
  fout << " " << histY->GetMean() << " " << histY->GetRMS();
  fout << endl;
  fout.close();
  return 0;
}
