TTree *tree;
#include "GetConfig.C"
TDatime dtime;

void resolution(int idx=24, int det = 3 )
{
  fIndex = idx;
  fDet = det;
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

  TCanvas *main1 = new TCanvas();
  main1->Divide(4,3);
  TF1 *bx = new TF1("bx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *by = new TF1("by","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *dx = new TF1("dx","[0]*TMath::Gaus(x,[1],[2])+[3]");
  TF1 *mxb = new TF1("mxb","[0]+[1]*x");
  TLine *line = new TLine();
  line->SetLineColor( kRed-3 );
  TString cuts0 = Form("(ok%s==1)&&(max%s<3500)&&(chi2<%f)",
		       fSDet.Data(),fSDet.Data(),fChiMax);
  TString cuts1 = Form("%s&&(wd%s>1)&&(wd%s<7)",
		       cuts0.Data(),fSDet.Data(),fSDet.Data());
  TString cuts2;
  cuts0 = cuts1;
  //=====
  main1->cd(1);
  tree->Draw(Form("ok%s>>hist0(3,-0.5,2.5)",fSDet.Data()),    cuts0.Data());
  TH1D *hist0 = (TH1D*) gROOT->FindObject( "hist0" );
  hist0->GetXaxis()->SetTitle( Form("ok%s",fSDet.Data()) );
  main1->cd(2)->SetLogy(1);
  tree->Draw(Form("wd%s>>hist1(27,-0.5,26.5)",fSDet.Data()),  cuts0.Data());
  TH1D *hist1 = (TH1D*) gROOT->FindObject( "hist1" );
  hist1->GetXaxis()->SetTitle( Form("wd%s",fSDet.Data()) );
  main1->cd(3)->SetLogy(1);
  tree->Draw(Form("ampl%s>>hist2(100,0,1e+5)",fSDet.Data()),  cuts0.Data());
  TH1D *hist2 = (TH1D*) gROOT->FindObject( "hist2" );
  hist2->GetXaxis()->SetTitle( Form("ampl%s",fSDet.Data()) );
  main1->cd(4)->SetLogy(1);
  tree->Draw(Form("max%s>>hist3(100,0,4100)",fSDet.Data()),   cuts0.Data());
  TH1D *hist3 = (TH1D*) gROOT->FindObject( "hist3" );
  hist3->GetXaxis()->SetTitle( Form("max%s",fSDet.Data()) );
  //=====
  main1->cd(5);
  tree->Draw(Form("bx%s>>hist4(100,-20,+20)",fSDet.Data()),   cuts0.Data());
  TH1D *hist4 = (TH1D*) gROOT->FindObject( "hist4" );
  hist4->GetXaxis()->SetTitle( Form("bx%s",fSDet.Data()) );
  bx->SetParameter(1,hist4->GetMean());
  bx->SetParLimits(1,hist4->GetMean()-5,hist4->GetMean()+5);
  bx->SetParameter(2,hist4->GetRMS());
  bx->SetParLimits(2,0.001,2*hist4->GetRMS());
  hist4->Fit(bx);
  Double_t bxsig = bx->GetParameter(2);
  Double_t bxmea = bx->GetParameter(1);
  tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",bx->GetParameter(2),bx->GetParError(2)*100));
  tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",bx->GetParameter(1),bx->GetParError(1)*100));
  //=====
  main1->cd(6);
  tree->Draw(Form("by%s>>hist5(100,-20,+20)",fSDet.Data()),   cuts0.Data());
  TH1D *hist5 = (TH1D*) gROOT->FindObject( "hist5" );
  hist5->GetXaxis()->SetTitle( Form("by%s",fSDet.Data()) );
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
  //cuts1 = Form("%s&&(TMath::Abs(bx%s-%f)<%f)&&(TMath::Abs(by%s-%f)<%f)",
  //	       cuts0.Data(),fSDet.Data(),bxmea,1*bxsig,fSDet.Data(),bymea,1*bysig);
  //=====
  main1->cd(7);
  tree->Draw(Form("bx2mm%s>>hist6",fSDet.Data()),      cuts1.Data());
  TH1D *hist6 = (TH1D*) gROOT->FindObject( "hist6" );
  hist6->GetXaxis()->SetTitle( Form("bx2mm%s",fSDet.Data()) );
  main1->cd(8);
  tree->Draw(Form("by2mm%s>>hist7",fSDet.Data()),      cuts1.Data());
  TH1D *hist7 = (TH1D*) gROOT->FindObject( "hist7" );
  hist7->GetXaxis()->SetTitle( Form("by2mm%s",fSDet.Data()) );
  main1->cd(9);
  tree->Draw(Form("bxpitch%s>>hist8",fSDet.Data()),    cuts1.Data());
  TH1D *hist8 = (TH1D*) gROOT->FindObject( "hist8" );
  hist8->GetXaxis()->SetTitle( Form("bxpitch%s",fSDet.Data()) );
  main1->cd(10);
  tree->Draw(Form("gxpitch%s>>hist9(100,-1.1,+1.1)",fSDet.Data()),    cuts1.Data());
  TH1D *hist9 = (TH1D*) gROOT->FindObject( "hist9" );
  hist9->GetXaxis()->SetTitle( Form("gxpitch%s",fSDet.Data()) );
  main1->cd(11);
  tree->Draw(Form("bybeat%s>>hist10",fSDet.Data()),                   cuts1.Data());
  TH1D *hist10 = (TH1D*) gROOT->FindObject( "hist10" );
  hist10->GetXaxis()->SetTitle( Form("bybeat%s",fSDet.Data()) );
  main1->cd(12)->SetLogy(1);
  tree->Draw(Form("gx%s>>hist11",fSDet.Data()),                       cuts1.Data());
  TH1D *hist11 = (TH1D*) gROOT->FindObject( "hist11" );
  hist11->GetXaxis()->SetTitle( Form("gx%s",fSDet.Data()) );
  Double_t gxmea = hist11->GetMean();
  Double_t gxsig = hist11->GetRMS();
  //=====
  TCanvas *main2 = new TCanvas();
  main2->Divide(3,2);
  main2->cd(1);
  tree->Draw(Form("dx%s>>hist12",fSDet.Data()),        cuts1.Data());
  TH1D *hist12 = (TH1D*) gROOT->FindObject( "hist12" );
  dx->SetParameter(1,hist12->GetMean());
  dx->SetParLimits(1,hist12->GetMean()-3,hist12->GetMean()+3);
  dx->SetParameter(2,hist12->GetRMS());
  dx->SetParLimits(2,0.001,2*hist12->GetRMS());
  hist12->Fit(dx);
  Double_t dxmea = dx->GetParameter(1);
  Double_t dxsig = dx->GetParameter(2);
  tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.2f)",dxsig*1e3,dx->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.2f)",dxmea*1e3,dx->GetParError(1)*1e3));
  //=====
  main2->cd(1);
  tree->Draw(Form("dx3%s>>hist13",fSDet.Data()),       cuts1.Data());
  //=====
  TString var;
  var = Form("by%s:bx%s>>hist14(200,%f,%f,200,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     bxmea-8,bxmea+8,bymea-8,bymea+8);
  main2->cd(1);
  tree->Draw(var.Data(),    cuts1.Data(), "colz");
  line->DrawLine(fGXmin,fGYmin,fGXmin,fGYmax);
  line->DrawLine(fGXmax,fGYmin,fGXmax,fGYmax);
  line->DrawLine(fGXmin,fGYmin,fGXmax,fGYmin);
  line->DrawLine(fGXmin,fGYmax,fGXmax,fGYmax);
  TH2D *hist14 = (TH2D*) gROOT->FindObject( "hist14" );
  hist14->GetXaxis()->SetTitle( Form("bx%s [mm]",fSDet.Data()) );
  hist14->GetYaxis()->SetTitle( Form("by%s [mm]",fSDet.Data()) );
  tex->DrawLatexNDC(0.15,0.85,Form("<x>  %f", hist14->GetMean(1)));
  tex->DrawLatexNDC(0.15,0.80,Form("<y>  %f", hist14->GetMean(2)));
  //=====
  var = Form("dx%s:bx%s>>hist15(200,%f,%f,200,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     bxmea-5,bxmea+5,dxmea-3*dxsig,dxmea+3*dxsig);
  main2->cd(2);
  tree->Draw(var.Data(),    cuts1.Data(), "colz");
  TH2D *hist15 = (TH2D*) gROOT->FindObject( "hist15" );
  TProfile *pro15 = hist15->ProfileX( "prof15" );
  pro15->Draw("SAME");
  line->DrawLine(fGXmin,-10,fGXmin,+10);
  line->DrawLine(fGXmax,-10,fGXmax,+10);
  hist15->GetYaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  hist15->GetXaxis()->SetTitle( Form("bx%s [mm]",fSDet.Data()) );
  //=====
  var = Form("dx%s:by%s>>hist16(200,%f,%f,200,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     bymea-5,bymea+5,dxmea-3*dxsig,dxmea+3*dxsig);
  cuts2 = Form("%s&&(bx%s>%f)&&(bx%s<%f)",
	       cuts1.Data(),fSDet.Data(),fGXmin,fSDet.Data(),fGXmax);
  main2->cd(3);
  tree->Draw(var.Data(),    cuts2.Data(), "colz");
  TH2D *hist16 = (TH2D*) gROOT->FindObject( "hist16" );
  TProfile *pro16 = hist16->ProfileX( "prof16" );
  pro16->Draw("SAME");
  //pro16->Fit(mxb,"R","", bymea-bysig, bymea+bysig );
  //tex->DrawLatexNDC(0.2,0.2,Form("m %.4f +-%.4f",mxb->GetParameter(1),mxb->GetParError(1)));
  //cout << "XI2/NDF = " << mxb->GetChisquare()/mxb->GetNDF() << endl;
  //Double_t chi2 = mxb->GetChisquare()/mxb->GetNDF();
  line->DrawLine(fGYmin,-10,fGYmin,+10);
  line->DrawLine(fGYmax,-10,fGYmax,+10);
  hist16->GetYaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  hist16->GetXaxis()->SetTitle( Form("by%s [mm]",fSDet.Data()) );
  //=====
  var = Form("dx%s:gx%s>>hist17(200,%f,%f,200,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     gxmea-5,gxmea+5,dxmea-3*dxsig,dxmea+3*dxsig);
  main2->cd(4);
  tree->Draw(var.Data(),    cuts1.Data(), "colz");
  TH2D *hist17 = (TH2D*) gROOT->FindObject( "hist17" );
  TProfile *pro17 = hist17->ProfileX( "prof17" );
  pro17->SetMarkerColor(kBlack);
  pro17->SetLineColor(kBlack);
  pro17->Draw("SAME");
  hist17->GetYaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  hist17->GetXaxis()->SetTitle( Form("gx%s [mm]",fSDet.Data()) );
  //=====
  cuts2 = Form("%s&&(bx%s>%f)&&(bx%s<%f)&&(by%s>%f)&&(by%s<%f)",
	       cuts1.Data(),fSDet.Data(),fGXmin,fSDet.Data(),fGXmax,
	       fSDet.Data(),fGYmin,fSDet.Data(),fGYmax);
  //=====
  var = Form("dx%s:gx%s>>hist18(100,%f,%f,100,%f,%f)",
	     fSDet.Data(),fSDet.Data(),
	     gxmea-5,gxmea+5,dxmea-3*dxsig,dxmea+3*dxsig);
  main2->cd(5);
  tree->Draw(var.Data(),    cuts2.Data(), "colz");
  TH2D *hist18 = (TH2D*) gROOT->FindObject( "hist18" );
  //hist18->SetTitle("Residual  dependece  in  X");
  //hist18->SaveAs("fig1.root");
  TProfile *pro18 = hist18->ProfileX( "prof18" );
  pro18->SetMarkerColor(kBlack);
  pro18->SetLineColor(kBlack);
  pro18->Draw("SAME");
  hist18->GetYaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  hist18->GetXaxis()->SetTitle( Form("gx%s [mm]",fSDet.Data()) );
  //=====
  main2->cd(6);
  tree->Draw(Form("dx%s>>hist19(100,%f,%f)",fSDet.Data(),
		  hist12->GetMean()-2*hist12->GetRMS(),
		  hist12->GetMean()+2*hist12->GetRMS()),
	     cuts2.Data());
  TH1D *hist19 = (TH1D*) gROOT->FindObject( "hist19" );
  dx->SetParameter(1,hist19->GetMean());
  dx->SetParLimits(1,hist19->GetMean()-3,hist19->GetMean()+3);
  dx->SetParameter(2,hist19->GetRMS());
  dx->SetParLimits(2,0.001,2*hist19->GetRMS());
  hist19->Fit(dx);
  dxmea = dx->GetParameter(1);
  dxsig = dx->GetParameter(2);
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.60,0.80,Form("#sigma %.1f (%.1f)",dxsig*1e3,dx->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.60,0.75,Form("#mu %.1f (%.1f)",dxmea*1e3,dx->GetParError(1)*1e3));
  tex->SetTextColor(kBlack);
  hist19->GetXaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  tex->DrawLatexNDC(0.15,0.85,Form("%s %s", fSDet.Data(), fTech.Data()));
  tex->DrawLatexNDC(0.15,0.80,Form("Board %s", fBoard.Data()));
  tex->DrawLatexNDC(0.15,0.75,Form("Cell %s", fCell.Data()));
  tex->DrawLatexNDC(0.15,0.70,Form("xPitch %.3f mm", fXPitch));
  tex->DrawLatexNDC(0.15,0.65,Form("xStretch %.1f", fXStretch));
  tex->DrawLatexNDC(0.15,0.60,Form("yBeat %.1f", fYBeat));
  tex->DrawLatexNDC(0.15,0.50,Form("Run %d", fRun));
  tex->DrawLatexNDC(0.15,0.20,Form("Last Updated %d %d", dtime.GetDate(), dtime.GetTime()));

  main1->SaveAs( Form("res/D%d/resolution_%s_%s_%s_%d.pdf[",
		     det,fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		"pdf");

  main1->SaveAs( Form("res/D%d/resolution_%s_%s_%s_%d.pdf",
		     det,fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		"pdf");
  main2->SaveAs( Form("res/D%d/resolution_%s_%s_%s_%d.pdf",
		     det,fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		"pdf");
  main2->SaveAs( Form("res/D%d/FIDUCIAL_D%d_%d.pdf",
		      det,det,fRun),
		"pdf");
  //======
  //======
  //======
  Double_t xmin = dxmea-5*dxsig;
  Double_t xmax = dxmea+5*dxsig;
  TCanvas *main3 = new TCanvas();
  tree->Draw(Form("dx%s>>hist212(100,%f,%f)",fSDet.Data(),xmin,xmax), cuts2.Data(), "E");
  TH1D *hist212 = (TH1D*) gROOT->FindObject( "hist212" );
  hist212->SetTitle("ClusterX - SiliconX");
  hist212->GetXaxis()->SetTitle("Residual  [mm]");
  TF1 *fitdx = new TF1("fitdx","[3]+[0]*TMath::Gaus(x,[1],[2])");
  TF1 *fitdxall = new TF1("fitdxall","[3]+[0]*TMath::Gaus(x,[1],[2])",0,3);
  fitdx->SetLineColor( kRed-3 );
  fitdx->SetParameter(1,dxmea);
  fitdx->SetParLimits(1,dxmea-2*dxsig,dxmea+3*dxsig);
  fitdx->SetParameter(2,dxsig);
  fitdx->SetParLimits(2,0.001,dxsig*5);
  hist212->Fit(fitdx,"RN","",dxmea-3*dxsig,dxmea+3*dxsig);
  Double_t fitdxmea = fitdx->GetParameter(1);
  Double_t fitdxsig = fitdx->GetParameter(2);
  hist212->Fit(fitdx,"RN","",fitdxmea-3*fitdxsig,fitdxmea+3*fitdxsig);
  hist212->Fit(fitdx,"RN","",fitdxmea-3*fitdxsig,fitdxmea+3*fitdxsig);
  fitdxmea = fitdx->GetParameter(1);
  fitdxsig = fitdx->GetParameter(2);
  hist212->Fit(fitdx,"R","",fitdxmea-1.5*fitdxsig,fitdxmea+1.5*fitdxsig);
  fitdxmea = fitdx->GetParameter(1);
  fitdxsig = fitdx->GetParameter(2);
  tex->DrawLatexNDC(0.15,0.85,Form("%s %s", fSDet.Data(), fTech.Data()));
  tex->DrawLatexNDC(0.15,0.80,Form("Board %s", fBoard.Data()));
  tex->DrawLatexNDC(0.15,0.75,Form("Cell %s", fCell.Data()));
  tex->DrawLatexNDC(0.15,0.70,Form("xPitch %.3f mm", fXPitch));
  tex->DrawLatexNDC(0.15,0.65,Form("xStretch %.0f perCent", fXStretch));
  tex->DrawLatexNDC(0.15,0.60,Form("yBeat %.2f ", fYBeat));
  fitdxall->SetParameter( 0, fitdx->GetParameter(0) );
  fitdxall->SetParameter( 1, fitdx->GetParameter(1) );
  fitdxall->SetParameter( 2, fitdx->GetParameter(2) );
  fitdxall->SetParameter( 3, fitdx->GetParameter(3) );
  //==
  tex->DrawLatexNDC(0.75,0.85,Form("Run %d",fRun));
  //==
  Double_t chi2final = fitdx->GetChisquare() / fitdx->GetNDF();
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.15,0.50,"No NL correction");
  tex->DrawLatexNDC(0.15,0.45,Form("#sigma %.0f #mum",fitdxsig*1e3));
  tex->DrawLatexNDC(0.15,0.40,Form("#chi^{2}/NDF %.1f",chi2final));
  tex->DrawLatexNDC(0.15,0.35,Form("#mu %.0f #mum",fitdxmea*1e3));
  //fitdxall->Draw("SAME");
  //main2->SaveAs( "fig2.root", "root" );
  main3->SaveAs( Form("res/D%d/resolution_%s_%s_%s_%d.pdf",
		      det,fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		 "pdf");
  main3->SaveAs( Form("res/D%d/resolution_%s_%s_%s_%d.pdf]",
		      det,fBoard.Data(),fSDet.Data(),fCell.Data(),fRun),
		 "pdf");
  //==
  Double_t resultReso = fitdxsig*1e3;
  std::cout << "Chi2 " << chi2final << std::endl;
  if( (hist212->GetEntries()<100) || (chi2final>2.5) ) {
    resultReso = 0;
  }
  
  ofstream fout( Form("res/D%d/data/reso_%s_%s_run%d.dat",
		      det,fTech.Data(),fBoard.Data(),fRun) );
  std::cout << " RESULTS IN " << Form("res/D%d/data/reso_%s_%s_run%d.dat",
				      det,fTech.Data(),fBoard.Data(),fRun) << std::endl;
  fout << dx->GetParameter(2)*1e3;
  //fout << resultReso;
  fout << " " << fRun;
  fout << " " << fCell;
  fout << " " << fXPitch;
  fout << " " << fYBeat;
  fout << " " << fXStretch;
  fout << endl;
  fout.close();

  return 0;
}
