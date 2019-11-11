int plotStraight() {
  gStyle->SetOptStat(0);
  TFile *file = new TFile("straight.root");
  TCanvas *c1 = (TCanvas*) file->Get("c1");
  c1->Draw();
  TH2F *frame = (TH2F*) c1->GetListOfPrimitives()->FindObject("hframe");
  TGraphErrors *gr0 = (TGraphErrors*) c1->GetListOfPrimitives()->FindObject("Graph0");
  TGraphErrors *gr1 = (TGraphErrors*) c1->GetListOfPrimitives()->FindObject("Graph1");
  gr0->SetMarkerStyle(20);
  gr1->SetMarkerStyle(20);
  gr0->SetMarkerColor(kBlue-3);
  gr1->SetMarkerColor(kRed-3);
  gr0->SetFillColor(kWhite);
  gr1->SetFillColor(kWhite);
  
  TF1 *fst = new TF1("fst","x/sqrt(12)",0.3,1.5);
  TF1 *f0 = new TF1("f0","[0]+[1]*x+[2]*x*x"); f0->SetLineColor(kBlue-3);
  TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x"); f1->SetLineColor(kRed-3);
  fst->SetLineColor(kBlack);
  fst->SetLineStyle(9);
  gr0->Fit(f0);
  gr1->Fit(f1);
  
  TCanvas *main = new TCanvas("main","main",800,400);
  main->SetTopMargin(0.05);
  main->SetBottomMargin(0.18);
  main->SetLeftMargin(0.10);
  main->SetRightMargin(0.05);
  
  TH2F *axis = new TH2F("axis",";pitch  [mm];#sigma  [mm]",100,0,4.0,100,0,0.4);
  axis->GetYaxis()->SetNdivisions(507);
  axis->GetXaxis()->SetTitleSize(0.08);
  axis->GetXaxis()->SetTitleOffset(1.0);
  axis->GetYaxis()->SetTitleSize(0.08);
  axis->GetYaxis()->SetTitleOffset(0.6);
  axis->GetXaxis()->SetLabelSize(0.08);
  axis->GetYaxis()->SetLabelSize(0.08);
  axis->Draw();
  gr0->Draw("psame");
  gr1->Draw("psame");
  fst->Draw("same");

  TLegend *leg = new TLegend(0.62,0.24,0.92,0.52);
  leg->SetBorderSize(0);
  leg->AddEntry(fst,"pitch/#sqrt{12}");
  leg->AddEntry(gr0,"Rectangular pads");
  leg->AddEntry(gr1,"Zigzag pads");
  leg->Draw();
  
  return 0;
}
