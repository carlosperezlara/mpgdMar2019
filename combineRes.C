const int kMAX = 2000;

int combineRes() {
  TString what = "uRW_B01a_GROUP012";
  //TString what = "GEM.C2_Z03k.D_GROUP4";
  Double_t res[kMAX];
  Int_t run[kMAX];
  TString cel[kMAX];
  Double_t xpi[kMAX];
  Double_t ybe[kMAX];
  Double_t xst[kMAX];
  ifstream fin( Form("res/data/%s.dat",what.Data()) );
  int n=0;
  for(;;) {
    fin >> res[n] >> run[n] >> cel[n] >> xpi[n] >> ybe[n] >> xst[n];
    if(!fin.good()) break;
    if(res[n]>400) continue;
    if(res[n]<20) continue;
    n++;
    if(n>=kMAX) break;
  }
  fin.close();

  TCanvas *main = new TCanvas();
  TGraph *all = new TGraph(n,xpi,res);
  all->SetLineColor(kBlue-3);
  all->SetMarkerColor(kBlue-3);
  all->SetMarkerStyle(4);
  all->Draw("AP");
  all->SetTitle( what.Data() /*"uRW  B01a  GROUP012"*/);
  all->GetXaxis()->SetTitle("xPitch  [mm]");
  all->GetYaxis()->SetTitle("#sigma_{(Cluster_{X} - Silicon_{X})}  [#mum]");

  TLatex *tex = new TLatex();
  tex->SetTextColor(kGreen-3);
  tex->SetTextSize(0.02);
  for(int i=0; i!=n; ++i) {
    tex->DrawLatex(xpi[i]+0.05, res[i], Form("%s %d",cel[i].Data(),run[i]) );
  }
  
  main->SaveAs( Form("%s.pdf",what.Data()) ,"pdf");
  return 0;
}
