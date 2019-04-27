Int_t fIndex;
Int_t fRun;
Int_t fDet;
Double_t fXPitch;
TString fCell;
TString fSDet;
TString fBoard;
TString fTech;
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

  fin.open("elog/runs.dat.evt.cel");
  index = fIndex;
  for(;;--index) {
    fin >> fCell;
    if(index==0) {
      break;
    }
  }
  fin.close();

  fin.open( Form("elog/aquaconf/run_0000%d.p907",fRun) );
  index = fDet;
  std::string line;
  for(;;--index) {
    std::getline(fin,line);
    if(index==0) {
      break;
    }
    fin.clear();
  }
  TString tline = line;
  fBoard = ( (TObjString*) (tline.Tokenize(" "))->At(0) )->GetString();
  fTech = ( (TObjString*) (tline.Tokenize(" "))->At(4) )->GetString();
  fin.close();

  fin.open( Form("mapping/pitch_%s.dat",fBoard.Data()) );
  TString cell;
  for(;;--index) {
    fin >> cell >> fXPitch;
    if(fCell.Contains(cell)) {
      break;
    }
    fin.clear();
  }
  fin.close();

}


void resolution(int idx=24, int det = 3 )
{
  fIndex = idx;
  fDet = det;
  fSDet = Form("D%d",det);
  GetConfig();
  std::cout << "Run " << fRun << endl;
  std::cout << "Cell " << fCell << endl;
  std::cout << "Detector " << fDet << endl;
  std::cout << "Technology " << fTech.Data() << endl;
  std::cout << "Board " << fBoard.Data() << endl;
  std::cout << "xPitch " << fXPitch << endl;

  gStyle->SetOptStat(0);
  gSystem->Load("libfnal4all.so");
  TFile *ff = new TFile( Form("rootfiles/fnal-%05d.root",fRun) );
  tree = (TTree*)ff->Get("ZIGZAG");

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.05);

  TCanvas *main = new TCanvas();
  main->Divide(4,4);
  TF1 *bx = new TF1("bx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *by = new TF1("by","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *dx = new TF1("dx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *mxb = new TF1("mxb","[0]+[1]*x");
  TLine *line = new TLine();
  line->SetLineColor( kRed-3 );
  TString cuts0 = Form("(ok%s==1)&&(max%s<3500)&&(chi2<2)",
		       fSDet.Data(),fSDet.Data());
  
  TString cuts1 = Form("%s&&(TMath::Abs(bx%s)<2)&&(TMath::Abs(by%s)<2)",
		       cuts0.Data(),fSDet.Data(),fSDet.Data());
  TString cuts2 = Form("%s&&(wd%s>1)&&(wd%s<7)",
		       cuts1.Data(),fSDet.Data(),fSDet.Data());
  cuts0 = cuts1 = cuts2;
  //=====
  main->cd(1);
  tree->Draw(Form("ok%s>>hist0(3,-0.5,2.5)",fSDet.Data()),    cuts0.Data());
  main->cd(2)->SetLogy(1);
  tree->Draw(Form("wd%s>>hist1(27,-0.5,26.5)",fSDet.Data()),  cuts0.Data());
  main->cd(3)->SetLogy(1);
  tree->Draw(Form("ampl%s>>hist2(100,0,1e+5)",fSDet.Data()),  cuts0.Data());
  main->cd(4)->SetLogy(1);
  tree->Draw(Form("max%s>>hist3(100,0,4100)",fSDet.Data()),   cuts0.Data());
  //=====
  main->cd(5);
  tree->Draw(Form("bx%s>>hist4(100,-20,+20)",fSDet.Data()),   cuts0.Data());
  TH1D *hist4 = (TH1D*) gROOT->FindObject( "hist4" );
  bx->SetParameter(1,hist4->GetMean());
  bx->SetParLimits(1,hist4->GetMean()-5,hist4->GetMean()+5);
  bx->SetParameter(2,hist4->GetRMS());
  bx->SetParLimits(2,0.001,2*hist4->GetRMS());
  hist4->Fit(bx);
  tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",bx->GetParameter(2),bx->GetParError(2)*100));
  tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",bx->GetParameter(1),bx->GetParError(1)*100));
  //=====
  main->cd(6);
  tree->Draw(Form("by%s>>hist5(100,-20,+20)",fSDet.Data()),   cuts0.Data());
  TH1D *hist5 = (TH1D*) gROOT->FindObject( "hist5" );
  by->SetParameter(1,hist5->GetMean());
  by->SetParLimits(1,hist5->GetMean()-5,hist5->GetMean()+5);
  by->SetParameter(2,hist5->GetRMS());
  by->SetParLimits(2,0.001,2*hist5->GetRMS());
  hist5->Fit(by);
  Double_t bysig = by->GetParameter(2);
  Double_t bymea = by->GetParameter(1);
  tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",by->GetParameter(2),by->GetParError(2)*100));
  tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",by->GetParameter(1),by->GetParError(1)*100));
  //=====
  main->cd(7);
  tree->Draw(Form("bx2mm%s>>hist6",fSDet.Data()),      cuts0.Data());
  main->cd(8);
  tree->Draw(Form("by2mm%s>>hist7",fSDet.Data()),      cuts0.Data());
  main->cd(9);
  tree->Draw(Form("bxpitch%s>>hist8",fSDet.Data()),    cuts0.Data());
  main->cd(10);
  tree->Draw(Form("gxpitch%s>>hist9(100,-1.1,+1.1)",fSDet.Data()),    cuts0.Data());
  main->cd(11);
  tree->Draw(Form("bybeat%s>>hist10",fSDet.Data()),                   cuts0.Data());
  main->cd(12)->SetLogy(1);
  tree->Draw(Form("gx%s>>hist11(100,-50,+50)",fSDet.Data()),          cuts0.Data());
  TH1D *hist11 = (TH1D*) gROOT->FindObject( "hist11" );
  Double_t gxmea = hist11->GetMean();
  Double_t gxsig = hist11->GetRMS();
  //=====
  main->cd(13);
  tree->Draw(Form("dx%s>>hist12",fSDet.Data()),        cuts0.Data());
  TH1D *hist12 = (TH1D*) gROOT->FindObject( "hist12" );
  dx->SetParameter(1,hist12->GetMean());
  dx->SetParLimits(1,hist12->GetMean()-3,hist12->GetMean()+3);
  dx->SetParameter(2,hist12->GetRMS());
  dx->SetParLimits(2,0.001,2*hist12->GetRMS());
  hist12->Fit(dx);
  Double_t dxmea = dx->GetParameter(1);
  Double_t dxsig = dx->GetParameter(2);
  tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",dxsig*1e3,dx->GetParError(2)*1e5));
  tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",dxmea*1e3,dx->GetParError(1)*1e5));
  //=====
  main->cd(14);
  tree->Draw(Form("dx3%s>>hist13",fSDet.Data()),       cuts0.Data());
  //=====
  TString var = Form("dx%s:by%s>>hist14(1000,%f,%f,1000,%f,%f)",
		     fSDet.Data(),fSDet.Data(),
		     bymea-3*bysig,bymea+3*bysig,dxmea-3*dxsig,dxmea+3*dxsig);
  main->cd(15);
  tree->Draw(var.Data(),    cuts0.Data(), "colz");
  TH2D *hist14 = (TH2D*) gROOT->FindObject( "hist14" );
  TProfile *pro14 = hist14->ProfileX( "prof14" );
  pro14->Draw("SAME");
  pro14->Fit(mxb,"R","", bymea-bysig, bymea+bysig );
  tex->DrawLatexNDC(0.2,0.2,Form("m %.4f +-%.4f",mxb->GetParameter(1),mxb->GetParError(1)));
  cout << "XI2/NDF = " << mxb->GetChisquare()/mxb->GetNDF() << endl;
  Double_t chi2 = mxb->GetChisquare()/mxb->GetNDF();
  //=====
  var = Form("dx%s:gx%s>>hist15(1000,%f,%f,1000,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     gxmea-5*gxsig,gxmea+5*gxsig,dxmea-3*dxsig,dxmea+3*dxsig);
  main->cd(16);
  tree->Draw(var.Data(),    cuts0.Data(), "colz");
  //TH2D *hist14 = (TH2D*) gROOT->FindObject( Form("hist14_%d",i) );
  //TProfile *pro14 = hist14->ProfileX( Form("prof14_%d",i) );
  //pro14->Draw("SAME");
  //pro14->Fit(mxb,"R","", bymea-bysig, bymea+bysig );
  //tex->DrawLatexNDC(0.2,0.2,Form("m %.4f +-%.4f",mxb->GetParameter(1),mxb->GetParError(1)));
  main->SaveAs( Form("resolution_%s_%s_%s_%d.pdf[",
		     fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		"pdf");

  main->SaveAs( Form("resolution_%s_%s_%s_%d.pdf",
		     fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		"pdf");
  Double_t xmin = dxmea-5*dxsig;
  Double_t xmax = dxmea+5*dxsig;
  TCanvas *main2 = new TCanvas();
  tree->Draw(Form("dx%s>>hist212(100,%f,%f)",fSDet.Data(),xmin,xmax),        cuts0.Data());
  TH1D *hist212 = (TH1D*) gROOT->FindObject( "hist212" );
  hist212->SetTitle("ClusterX - SiliconX");
  hist212->GetXaxis()->SetTitle("[mm]");
  TF1 *fitdx = new TF1("fitdx","[4]+[3]*TMath::Gaus(x,[1],[2])");
  fitdx->SetLineColor( kRed-3 );
  fitdx->SetParameter(1,dxmea);
  fitdx->SetParLimits(1,dxmea-dxsig,dxmea+dxsig);
  fitdx->SetParameter(2,dxsig);
  fitdx->SetParLimits(2,0.001,dxsig*2);
  hist212->Fit(fitdx,"R","",dxmea-2*dxsig,dxmea+2*dxsig);
  Double_t fitdxmea = dx->GetParameter(1);
  Double_t fitdxsig = dx->GetParameter(2);

  tex->DrawLatexNDC(0.15,0.85,Form("%s %s", fSDet.Data(), fTech.Data()));
  tex->DrawLatexNDC(0.15,0.80,Form("Board %s", fBoard.Data()));
  tex->DrawLatexNDC(0.15,0.75,Form("Cell %s", fCell.Data()));
  tex->DrawLatexNDC(0.15,0.70,Form("xPitch %.3f mm", fXPitch));
  //==
  tex->DrawLatexNDC(0.75,0.85,Form("Run %d",fRun));
  //==
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.15,0.50,"No NL correction");
  tex->DrawLatexNDC(0.15,0.45,Form("#sigma %.0f #mum",fitdxsig*1e3));
  //tex->DrawLatexNDC(0.15,0.40,Form("#mu %.0f #mum",fitdxmea*1e3));

  main2->SaveAs( Form("resolution_%s_%s_%s_%d.pdf",
		      fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		 "pdf");
  main2->SaveAs( Form("resolution_%s_%s_%s_%d.pdf]",
		      fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		 "pdf");

  ofstream fout( Form("res/data/reso_%s_%s_run%d.dat",
		      fTech.Data(),fBoard.Data(),fRun) );
  fout << fitdxsig*1e3;
  fout << " " << fRun;
  fout << " " << fCell;
  fout << " " << fXPitch;
  fout << endl;
  fout.close();

  return 0;
}
