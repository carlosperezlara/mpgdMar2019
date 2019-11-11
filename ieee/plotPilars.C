int plotPilars() {
  gStyle->SetOptStat(0);
  Double_t xx[4] = {1,2,3,4};
  //Double_t yy[4] = {102,105,108,108};
  //Double_t yy1[4] = {98,102,105,103};
  //Double_t yy2[4] = {102,113,110,120};
  Double_t yy[4] =  {94.3,96.4,98.9,99.2};
  Double_t yy1[4] = {92.9, 97.0, 93.9, 97.5};
  Double_t yy2[4] = {97.1,103.4,111.4,102.7};
  
  TGraph *gr0 = new TGraph(4,xx,yy);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerColor(kBlue-3);
  gr0->SetLineColor(kBlue-3);
  gr0->SetFillColor(kWhite);

  TGraph *gr1 = new TGraph(4,xx,yy1);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(kGreen-3);
  gr1->SetLineColor(kGreen-3);
  gr1->SetFillColor(kWhite);

  TGraph *gr2 = new TGraph(4,xx,yy2);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerColor(kRed-3);
  gr2->SetLineColor(kRed-3);
  gr2->SetFillColor(kWhite);

  TF1 *ft1 = new TF1("ft1","[0]+[1]*x+[2]*x*x");
  TF1 *ft2 = new TF1("ft2","[0]+[1]*x+[2]*x*x");
  ft1->SetLineColor(kGreen-3);
  ft2->SetLineColor(kRed-3);
  //gr1->Fit("ft1");
  //gr2->Fit("ft2");
  
  TCanvas *main = new TCanvas("main","main",800,500);
  main->SetTopMargin(0.05);
  main->SetBottomMargin(0.15);
  main->SetLeftMargin(0.15);
  main->SetRightMargin(0.05);
  
  TH2F *axis = new TH2F("axis",";Pillar  configuration;#sigma  [#mum]",4,0.5,4.5,100,80,130);
  axis->GetYaxis()->SetNdivisions(507);
  axis->GetXaxis()->SetTitleSize(0.08);
  axis->GetXaxis()->SetTitleOffset(0.7);
  axis->GetYaxis()->SetTitleOffset(0.8);
  axis->GetYaxis()->SetTitleSize(0.08);
  axis->GetXaxis()->SetLabelSize(0.08);
  axis->GetYaxis()->SetLabelSize(0.08);
  axis->GetXaxis()->SetBinLabel(1,"A");
  axis->GetXaxis()->SetBinLabel(2,"B");
  axis->GetXaxis()->SetBinLabel(3,"C");
  axis->GetXaxis()->SetBinLabel(4,"D");
  axis->Draw();
  gr0->Draw("plsame");
  //gr1->Draw("plsame");
  gr2->Draw("plsame");


  TLegend *leg = new TLegend(0.18,0.66,0.48,0.93);
  leg->SetBorderSize(0);
  leg->AddEntry(gr0,"Full area");
  leg->AddEntry(gr2,"Only pillars");
  //leg->AddEntry(gr1,"Excluding pillars");
  leg->Draw();
  
  return 0;
}
