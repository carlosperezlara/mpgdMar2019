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
  TF1 *fGEM1 = new TF1("fGEM1","[0]+[1]*x+0*x*x"); fGEM1->SetLineColor(kRed-3);
  TF1 *fGEM2 = new TF1("fGEM2","[0]+[1]*x+0*x*x"); fGEM2->SetLineColor(kRed-3);
  TF1 *fGEM3 = new TF1("fGEM3","[0]+[1]*x+0*x*x"); fGEM3->SetLineColor(kRed-3);
  TF1 *fMMM1 = new TF1("fMMM1","[0]+[1]*x+0*x*x"); fMMM1->SetLineColor(kBlue-3);
  TF1 *fMMM2 = new TF1("fMMM2","[0]+[1]*x+0*x*x"); fMMM2->SetLineColor(kBlue-3);
  TF1 *fMMM3 = new TF1("fMMM3","[0]+[1]*x+0*x*x"); fMMM3->SetLineColor(kBlue-3);
  TF1 *fURW1 = new TF1("fURW1","[0]+[1]*x+0*x*x"); fURW1->SetLineColor(kGreen-3);
  TF1 *fURW2 = new TF1("fURW2","[0]+[1]*x+0*x*x"); fURW2->SetLineColor(kGreen-3);
  TF1 *fURW3 = new TF1("fURW3","[0]+[1]*x+0*x*x"); fURW3->SetLineColor(kGreen-3);
  
  TH2F *axis = new TH2F("axis",";Pitch  [mm];#sigma  [um]",100,0,3.5,100,0,250);
  
  TCanvas *m1 = new TCanvas();
  axis->Draw();
  gGEM1->Draw("PSAME");
  gMMM1->Draw("PSAME");
  gURW1->Draw("PSAME");
  gGEM1->Fit(fGEM1,"R","",0.9,3.4);
  gMMM1->Fit(fMMM1,"R","",0.9,3.4);
  gURW1->Fit(fURW1,"R","",0.9,3.4);
  TLegend *leg1 = new TLegend(0.14,0.66,0.38,0.88);
  leg1->AddEntry( gGEM1, "GEM" );
  leg1->AddEntry( gMMM1, "MicroMega" );
  leg1->AddEntry( gURW1, "MicroRWell" );
  leg1->Draw();
  m1->SaveAs("m1.pdf");
  
  TCanvas *m2 = new TCanvas();
  axis->Draw();
  gGEM2->Draw("PSAME");
  gMMM2->Draw("PSAME");
  gURW2->Draw("PSAME");
  gGEM2->Fit(fGEM2,"R","",0.9,3.4);
  gMMM2->Fit(fMMM2,"R","",0.9,3.4);
  gURW2->Fit(fURW2,"R","",0.9,3.4);
  TLegend *leg2 = new TLegend(0.14,0.66,0.38,0.88,"NLX Corrected");
  leg2->AddEntry( gGEM2, "GEM" );
  leg2->AddEntry( gMMM2, "MicroMega" );
  leg2->AddEntry( gURW2, "MicroRWell" );
  leg2->Draw();
  m2->SaveAs("m2.pdf");

  TCanvas *m3 = new TCanvas();
  axis->Draw();
  gGEM3->Draw("PSAME");
  gMMM3->Draw("PSAME");
  gURW3->Draw("PSAME");
  gGEM3->Fit(fGEM3,"R","",0.9,3.4);
  gMMM3->Fit(fMMM3,"R","",0.9,3.4);
  gURW3->Fit(fURW3,"R","",0.9,3.4);
  TLegend *leg3 = new TLegend(0.14,0.66,0.38,0.88,"NLXY Corrected");
  leg3->AddEntry( gGEM3, "GEM" );
  leg3->AddEntry( gMMM3, "MicroMega" );
  leg3->AddEntry( gURW3, "MicroRWell" );
  leg3->Draw();
  m3->SaveAs("m3.pdf");
  
  return 0;
}

