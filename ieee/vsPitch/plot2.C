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
    fin >> tmp;
    if(!fin.good()) break;
    fin >> xGEM[nGEM] >> tmp;
    fin >> tmp >> tmp >> tmp >> tmp;
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
  //GEM_B01a_D5_I4.dat  MM_Z03k.A_DA_IA_12mm.dat  uRW_B01a_DA_IA.dat
  TGraph *gGEM1 = read("GEM_B01a_D5_I4.dat",0,kRed-3,20);
  TGraph *gGEM2 = read("GEM_B01a_D5_I4.dat",1,kRed-3,20);
  TGraph *gGEM3 = read("GEM_B01a_D5_I4.dat",2,kRed-3,20);
  TGraph *gMMM1 = read("GEM_V00a_DA_IA.dat",0,kOrange-3,21);
  TGraph *gMMM2 = read("GEM_V00a_DA_IA.dat",1,kOrange-3,21);
  TGraph *gMMM3 = read("GEM_V00a_DA_IA.dat",2,kOrange-3,21);
  TF1 *fGEM1 = new TF1("fGEM1","[0]+[1]*x+[2]*x*x"); fGEM1->SetLineColor(kRed-3);
  TF1 *fGEM2 = new TF1("fGEM2","[0]+[1]*x+[2]*x*x"); fGEM2->SetLineColor(kRed-3);
  TF1 *fGEM3 = new TF1("fGEM3","[0]+[1]*x+[2]*x*x"); fGEM3->SetLineColor(kRed-3);
  TF1 *fMMM1 = new TF1("fMMM1","[0]+[1]*x+[2]*x*x"); fMMM1->SetLineColor(kOrange-3);
  TF1 *fMMM2 = new TF1("fMMM2","[0]+[1]*x+[2]*x*x"); fMMM2->SetLineColor(kOrange-3);
  TF1 *fMMM3 = new TF1("fMMM3","[0]+[1]*x+[2]*x*x"); fMMM3->SetLineColor(kOrange-3);
  
  TH2F *axis = new TH2F("axis",";X-pitch  [mm];#sigma  [#mum]",100,0,3.5,100,0,250);
  axis->GetXaxis()->SetTitleSize(0.07);
  axis->GetXaxis()->SetLabelSize(0.07);
  axis->GetYaxis()->SetTitleSize(0.07);
  axis->GetYaxis()->SetLabelSize(0.07);
  axis->GetYaxis()->SetTitleOffset(1.0);

  TCanvas *m1 = new TCanvas();
  m1->SetTopMargin(0.05);
  m1->SetBottomMargin(0.15);
  m1->SetLeftMargin(0.15);
  m1->SetRightMargin(0.05);
  axis->Draw();
  gGEM1->Draw("PSAME");
  gMMM1->Draw("PSAME");
  gGEM1->Fit(fGEM1);
  gMMM1->Fit(fMMM1);
  TLegend *leg1 = new TLegend(0.18,0.52,0.52,0.88);
  leg1->SetBorderSize(0);
  leg1->AddEntry( gGEM1, "#splitline{4-GEM  65#mum gap}{Chemically etched}" );
  leg1->AddEntry( gMMM1, "#splitline{4-GEM  20#mum gap}{Laser etched}" );
  leg1->Draw();
  m1->SaveAs("m1.pdf");
  
  TCanvas *m2 = new TCanvas();
  m2->SetTopMargin(0.05);
  m2->SetBottomMargin(0.15);
  m2->SetLeftMargin(0.15);
  m2->SetRightMargin(0.05);
  axis->Draw();
  gGEM2->Draw("PSAME");
  gMMM2->Draw("PSAME");
  gGEM2->Fit(fGEM2);
  gMMM2->Fit(fMMM2);
  TLegend *leg2 = new TLegend(0.18,0.62,0.58,0.88,"X Corrected");
  leg2->SetBorderSize(0);
  leg2->AddEntry( gGEM1, "4-GEM  65#mum gap" );
  leg2->AddEntry( gMMM1, "4-GEM  20#mum gap" );
  leg2->Draw();
  m2->SaveAs("m2.pdf");

  TCanvas *m3 = new TCanvas();
  m3->SetTopMargin(0.05);
  m3->SetBottomMargin(0.15);
  m3->SetLeftMargin(0.15);
  m3->SetRightMargin(0.05);
  axis->Draw();
  gGEM3->Draw("PSAME");
  gMMM3->Draw("PSAME");
  gGEM3->Fit(fGEM3);
  gMMM3->Fit(fMMM3);
  TLegend *leg3 = new TLegend(0.18,0.62,0.58,0.88,"XY Corrected");
  leg3->SetBorderSize(0);
  leg3->AddEntry( gGEM1, "4-GEM  65#mum gap" );
  leg3->AddEntry( gMMM1, "4-GEM  20#mum gap" );
  leg3->Draw();
  m3->SaveAs("m3.pdf");
  
  return 0;
}

