TGraph* read(TString filename, int res, int color, int style) {
  Int_t nGEM = 0;
  Double_t xGEM[1000];
  Double_t y1GEM[1000];
  Double_t y2GEM[1000];
  Double_t y3GEM[1000];
  TString tmp;
  ifstream fin;
  fin.open( filename.Data() );
  for(;;) {
    fin >> tmp >> tmp >> tmp >> tmp >> tmp;
    if(!fin.good()) break;
    fin >> xGEM[nGEM] >> tmp;
    fin >> y1GEM[nGEM] >> tmp;
    fin >> y2GEM[nGEM] >> tmp;
    fin >> y3GEM[nGEM] >> tmp;
    fin >> tmp >> tmp >> tmp;
    //cout << nGEM << " " << xGEM[nGEM] << " " << y1GEM[nGEM] << endl;
    nGEM++;
  }
  TGraph *gGEM;
  if(res==0) gGEM = new TGraph(nGEM,xGEM,y1GEM);
  if(res==1) gGEM = new TGraph(nGEM,xGEM,y2GEM);
  if(res==2) gGEM = new TGraph(nGEM,xGEM,y3GEM);
  gGEM->SetFillColor( kWhite );
  gGEM->SetLineColor( color );
  gGEM->SetMarkerColor( color );
  gGEM->SetMarkerStyle( style );

  return gGEM;
}

int plot2() {
  gStyle->SetOptStat(0);
  TGraph *gGEM1 = read("MM_Z03k.A_DA_IA_5mm_Nom.dat",0,kCyan-3,20);
  TGraph *gGEM2 = read("MM_Z03k.A_DA_IA_5mm_Nom.dat",1,kCyan-3,20);
  TGraph *gGEM3 = read("MM_Z03k.A_DA_IA_5mm_Nom.dat",2,kCyan-3,20);
  TGraph *gMMM1 = read("MM_Z03k.A_DA_IA_12mm.dat",0,kBlue-3,21);
  TGraph *gMMM2 = read("MM_Z03k.A_DA_IA_12mm.dat",1,kBlue-3,21);
  TGraph *gMMM3 = read("MM_Z03k.A_DA_IA_12mm.dat",2,kBlue-3,21);
  TF1 *fGEM1 = new TF1("fGEM1","[0]+[1]*x+[2]*x*x"); fGEM1->SetLineColor(kCyan-3);
  TF1 *fGEM2 = new TF1("fGEM2","[0]+[1]*x+[2]*x*x"); fGEM2->SetLineColor(kCyan-3);
  TF1 *fGEM3 = new TF1("fGEM3","[0]+[1]*x+[2]*x*x"); fGEM3->SetLineColor(kCyan-3);
  TF1 *fMMM1 = new TF1("fMMM1","[0]+[1]*x+[2]*x*x"); fMMM1->SetLineColor(kBlue-3);
  TF1 *fMMM2 = new TF1("fMMM2","[0]+[1]*x+[2]*x*x"); fMMM2->SetLineColor(kBlue-3);
  TF1 *fMMM3 = new TF1("fMMM3","[0]+[1]*x+[2]*x*x"); fMMM3->SetLineColor(kBlue-3);
  
  TH2F *axis = new TH2F("axis",";X-Stretch  [%];#sigma  [um]",100,-12,+22,100,0,250);
  
  TCanvas *m1 = new TCanvas();
  axis->Draw();
  gGEM1->Draw("PSAME");
  gMMM1->Draw("PSAME");
  gGEM1->Fit(fGEM1);
  gMMM1->Fit(fMMM1);
  TLegend *leg1 = new TLegend(0.14,0.14,0.63,0.28);
  leg1->AddEntry( gGEM1, "Micromegas  ArIso(9505)  DG: 5 mm" );
  leg1->AddEntry( gMMM1, "Micromegas  ArCO2(7030)  DG: 12 mm" );
  leg1->Draw();
  m1->SaveAs("m1.pdf");
  
  TCanvas *m2 = new TCanvas();
  axis->Draw();
  gGEM2->Draw("PSAME");
  gMMM2->Draw("PSAME");
  gGEM2->Fit(fGEM2);
  gMMM2->Fit(fMMM2);
  TLegend *leg2 = new TLegend(0.14,0.14,0.63,0.28,"NLX Corrected");
  leg2->AddEntry( gGEM1, "Micromegas  ArIso(9505)  DG: 5 mm" );
  leg2->AddEntry( gMMM2, "Micromegas  ArCO2(7030)  DG: 12 mm" );
  leg2->Draw();
  m2->SaveAs("m2.pdf");

  TCanvas *m3 = new TCanvas();
  axis->Draw();
  gGEM3->Draw("PSAME");
  gMMM3->Draw("PSAME");
  gGEM3->Fit(fGEM3);
  gMMM3->Fit(fMMM3);
  TLegend *leg3 = new TLegend(0.14,0.14,0.63,0.28,"NLXY Corrected");
  leg3->AddEntry( gGEM1, "Micromegas  ArIso(9505)  DG: 5 mm" );
  leg3->AddEntry( gMMM3, "Micromegas  ArCO2(7030)  DG: 12 mm" );
  leg3->Draw();
  m3->SaveAs("m3.pdf");
  
  return 0;
}

