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

int plot() {
  gStyle->SetOptStat(0);
  //GEM_B01a_D5_I4.dat  MM_Z03k.A_DA_IA_12mm.dat  uRW_B01a_DA_IA.dat
  TGraph *gGEM1 = read("GEM_B01a_D5_I4.dat",0,kRed-3,20);
  TGraph *gGEM2 = read("GEM_B01a_D5_I4.dat",1,kRed-3,20);
  TGraph *gGEM3 = read("GEM_B01a_D5_I4.dat",2,kRed-3,20);
  TGraph *gMMM1 = read("MM_Z03k.A_DA_IA_12mm.dat",0,kBlue-3,21);
  TGraph *gMMM2 = read("MM_Z03k.A_DA_IA_12mm.dat",1,kBlue-3,21);
  TGraph *gMMM3 = read("MM_Z03k.A_DA_IA_12mm.dat",2,kBlue-3,21);
  TGraph *gURW1 = read("uRW_B01a_DA_IA.dat",0,kGreen-3,22);
  TGraph *gURW2 = read("uRW_B01a_DA_IA.dat",1,kGreen-3,22);
  TGraph *gURW3 = read("uRW_B01a_DA_IA.dat",2,kGreen-3,22);
  TF1 *fGEM1 = new TF1("fGEM1","[0]+[1]*x+[2]*x*x"); fGEM1->SetLineColor(kRed-3);
  TF1 *fGEM2 = new TF1("fGEM2","[0]+[1]*x+[2]*x*x"); fGEM2->SetLineColor(kRed-3);
  TF1 *fGEM3 = new TF1("fGEM3","[0]+[1]*x+[2]*x*x"); fGEM3->SetLineColor(kRed-3);
  TF1 *fMMM1 = new TF1("fMMM1","[0]+[1]*x+[2]*x*x"); fMMM1->SetLineColor(kBlue-3);
  TF1 *fMMM2 = new TF1("fMMM2","[0]+[1]*x+[2]*x*x"); fMMM2->SetLineColor(kBlue-3);
  TF1 *fMMM3 = new TF1("fMMM3","[0]+[1]*x+[2]*x*x"); fMMM3->SetLineColor(kBlue-3);
  TF1 *fURW1 = new TF1("fURW1","[0]+[1]*x+[2]*x*x"); fURW1->SetLineColor(kGreen-3);
  TF1 *fURW2 = new TF1("fURW2","[0]+[1]*x+[2]*x*x"); fURW2->SetLineColor(kGreen-3);
  TF1 *fURW3 = new TF1("fURW3","[0]+[1]*x+[2]*x*x"); fURW3->SetLineColor(kGreen-3);
  
  TH2F *axis = new TH2F("axis",";stretch  [%];#sigma   [#mum]",100,-12,+22,100,0,250);
  axis->GetXaxis()->SetTitleSize(0.07);
  axis->GetXaxis()->SetLabelSize(0.07);
  axis->GetYaxis()->SetTitleSize(0.07);
  axis->GetYaxis()->SetLabelSize(0.07);
  axis->GetYaxis()->SetTitleOffset(1.0);

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.06);
  tex->SetTextFont(42);
  
  TCanvas *m1 = new TCanvas();
  m1->SetTopMargin(0.05);
  m1->SetBottomMargin(0.15);
  m1->SetLeftMargin(0.15);
  m1->SetRightMargin(0.05);
  axis->Draw();
  gGEM1->Draw("PSAME");
  gMMM1->Draw("PSAME");
  gURW1->Draw("PSAME");
  gGEM1->Fit(fGEM1);
  gMMM1->Fit(fMMM1);
  gURW1->Fit(fURW1);
  TLegend *leg1 = new TLegend(0.18,0.18,0.48,0.38);
  leg1->SetBorderSize(0);
  leg1->AddEntry( gGEM1, "4-GEM" );
  leg1->AddEntry( gMMM1, "Micromegas" );
  leg1->AddEntry( gURW1, "#muRWELL" );
  leg1->Draw();
  tex->DrawLatexNDC(0.65,0.88,"X-pitch  2 mm");
  tex->DrawLatexNDC(0.65,0.80,"Y-period  0.5 mm");
  m1->SaveAs("m1.pdf");
  
  TCanvas *m2 = new TCanvas();
  m2->SetTopMargin(0.05);
  m2->SetBottomMargin(0.15);
  m2->SetLeftMargin(0.15);
  m2->SetRightMargin(0.05);
  axis->Draw();
  gGEM2->Draw("PSAME");
  gMMM2->Draw("PSAME");
  gURW2->Draw("PSAME");
  gGEM2->Fit(fGEM2);
  gMMM2->Fit(fMMM2);
  gURW2->Fit(fURW2);
  TLegend *leg2 = new TLegend(0.18,0.67,0.52,0.93,"X Corrected");
  leg2->SetBorderSize(0);
  leg2->AddEntry( gGEM2, "4-GEM" );
  leg2->AddEntry( gMMM2, "Micromegas" );
  leg2->AddEntry( gURW2, "#muRWELL" );
  leg2->Draw();
  tex->DrawLatexNDC(0.65,0.88,"X-pitch  2 mm");
  tex->DrawLatexNDC(0.65,0.80,"Y-period  0.5 mm");
  m2->SaveAs("m2.pdf");

  TCanvas *m3 = new TCanvas();
  m3->SetTopMargin(0.05);
  m3->SetBottomMargin(0.15);
  m3->SetLeftMargin(0.15);
  m3->SetRightMargin(0.05);
  axis->Draw();
  gGEM3->Draw("PSAME");
  gMMM3->Draw("PSAME");
  gURW3->Draw("PSAME");
  gGEM3->Fit(fGEM3);
  gMMM3->Fit(fMMM3);
  gURW3->Fit(fURW3);
  TLegend *leg3 = new TLegend(0.18,0.67,0.52,0.93,"XY Corrected");
  leg3->SetBorderSize(0);
  leg3->AddEntry( gGEM3, "4-GEM" );
  leg3->AddEntry( gMMM3, "Micromegas" );
  leg3->AddEntry( gURW3, "#muRWELL" );
  leg3->Draw();
  tex->DrawLatexNDC(0.65,0.88,"X-pitch  2 mm");
  tex->DrawLatexNDC(0.65,0.80,"Y-period  0.5 mm");
  m3->SaveAs("m3.pdf");
  
  return 0;
}

