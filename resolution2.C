TTree *tree;
#include "GetConfig.C"
TDatime dtime;

void resolution2(int idx=24, int det = 3 )
{
  fIndex = idx;
  fDet = det;
  GetConfig();

  if(fGXmax<fGXmin) {
    cout << " **** SKIP RUN **** " << endl;
    return 1;
  }

  //reduce fiducial by 10%
  {
    double dGX = fGXmax - fGXmin;
    fGXmin = fGXmin + dGX*0.05;
    fGXmax = fGXmax - dGX*0.05;
  }

  std::cout << "Run " << fRun << endl;
  std::cout << "CellHeader " << fCellHeader << endl;
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

  TCanvas *publish = new TCanvas("pub","pub",800,500);
  publish->SetTopMargin(0.05);
  publish->SetRightMargin(0.05);
  publish->SetBottomMargin(0.15);
  publish->SetLeftMargin(0.15);
  publish->cd();
  tree->Draw(Form("bx%s>>histBXD(200,-10,+10)",fSDet.Data()));
  publish->SaveAs( Form("hist/D%d/BX_%d.root",det,fRun), "root");

  TCanvas *main1 = new TCanvas();
  main1->Divide(4,3);
  TF1 *bx = new TF1("bx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *by = new TF1("by","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *dx = new TF1("dx","[0]*TMath::Gaus(x,[1],[2])+[3]");
  TF1 *dxX  = new TF1("dxX" ,"[0]*TMath::Gaus(x,[1],[2])+[3]");
  TF1 *dxY  = new TF1("dxY" ,"[0]*TMath::Gaus(x,[1],[2])+[3]");
  TF1 *dxXY = new TF1("dxXY","[0]*TMath::Gaus(x,[1],[2])+[3]");
  dx->SetLineColor(kRed-3);
  dxX->SetLineColor(kGreen-3);
  dxY->SetLineColor(kBlue-3);
  dxXY->SetLineColor(kCyan-3);
  dx->SetParameter(3,0);   dx->SetParLimits(3,+1,-1); 
  dxX->SetParameter(3,0);  dxX->SetParLimits(3,+1,-1); 
  dxY->SetParameter(3,0);  dxY->SetParLimits(3,+1,-1); 
  dxXY->SetParameter(3,0); dxXY->SetParLimits(3,+1,-1); 
  TF1 *mxb = new TF1("mxb","[0]+[1]*x");
  TLine *line = new TLine();
  line->SetLineColor( kRed-3 );
  TString cuts0 = Form("(ok%s==1)&&(max%s<3500)&&(chi2<%f)",
		       fSDet.Data(),fSDet.Data(),fChiMax);
  //TString cuts1 = Form("%s&&(wd%s>0)&&(wd%s<7)",
  TString cuts1 = Form("%s&&(wd%s>0)&&(wd%s<20)",
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
  main2->Divide(4,4);
  main2->cd(1);
  tree->Draw(Form("dx%s>>hist12",fSDet.Data()),        cuts1.Data());
  TH1D *hist12 = (TH1D*) gROOT->FindObject( "hist12" );
  if(hist12->GetEntries()<100) return 1;
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
	     bxmea-7,bxmea+7,dxmea-5*dxsig,dxmea+5*dxsig);
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
	     bymea-7,bymea+7,dxmea-5*dxsig,dxmea+5*dxsig);
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
  cuts2 = Form("%s&&(bx%s>%f)&&(bx%s<%f)&&(by%s>%f)&&(by%s<%f)",
	       cuts1.Data(),fSDet.Data(),fGXmin,fSDet.Data(),fGXmax,
	       fSDet.Data(),fGYmin,fSDet.Data(),fGYmax);

  main1->cd(2);
  tree->Draw(Form("wd%s>>hist1FINAL(27,-0.5,26.5)",fSDet.Data()),  cuts2.Data(),"SAME");
  TH1D *hist1FINAL = (TH1D*) gROOT->FindObject( "hist1FINAL" );
  hist1FINAL->SetLineColor(kRed-3);
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.6,0.8,Form("%.1f",hist1FINAL->GetMean()));
  main1->cd(3);
  tree->Draw(Form("ampl%s>>hist2FINAL(100,0,1e+5)",fSDet.Data()),  cuts2.Data(),"SAME");
  TH1D *hist2FINAL = (TH1D*) gROOT->FindObject( "hist2FINAL" );
  hist2FINAL->SetLineColor(kRed-3);
  tex->DrawLatexNDC(0.6,0.8,Form("%.0f",hist2FINAL->GetMean()));

  //=====
  main2->cd(4);
  tree->Draw(Form("dx%s>>hist19(100,%f,%f)",fSDet.Data(),
		  hist12->GetMean()-2*hist12->GetRMS(),
		  hist12->GetMean()+2*hist12->GetRMS()),
	     cuts2.Data());
  TH1D *hist19 = (TH1D*) gROOT->FindObject( "hist19" );
  if(hist19->GetEntries()<100) return 1;
  dx->SetParameter(1,hist19->GetMean());
  dx->SetParLimits(1,hist19->GetMean()-3,hist19->GetMean()+3);
  dx->SetParameter(2,hist19->GetRMS());
  dx->SetParLimits(2,0.001,2*hist19->GetRMS());
  hist19->Fit(dx);
  dxmea = dx->GetParameter(1);
  dxsig = dx->GetParameter(2);
  tree->Draw(Form("dx%s>>histDX19(200,%f,%f)",fSDet.Data(),
		  dxmea-5*dxsig,
		  dxmea+5*dxsig),
	     cuts2.Data());
  hist19 = (TH1D*) gROOT->FindObject( "histDX19" );
  hist19->Fit(dx);
  dxmea = dx->GetParameter(1);
  dxsig = dx->GetParameter(2);
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.60,0.80,Form("#sigma %.1f (%.1f)",dxsig*1e3,dx->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.60,0.75,Form("#mu %.1f (%.1f)",dxmea*1e3,dx->GetParError(1)*1e3));
  tex->SetTextColor(kBlack);
  hist19->GetXaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  //=====
  int nbinsX = (fGXmax-fGXmin)/0.05;///fXPitch; // each 50 microns
  int nbinsY = (fGYmax-fGYmin)/0.05;///(20/fYBeat); // each 50 microns
  main2->cd(13);
  tex->SetTextSize(0.07);
  tex->DrawLatexNDC(0.15,0.90,Form("%s %s", fSDet.Data(), fTech.Data()));
  tex->DrawLatexNDC(0.15,0.80,Form("Board %s", fBoard.Data()));
  tex->DrawLatexNDC(0.15,0.70,Form("Cell %s => %s", fCellHeader.Data(), fCell.Data()));
  tex->DrawLatexNDC(0.15,0.60,Form("xPitch %.1f mm", fXPitch));
  tex->DrawLatexNDC(0.15,0.50,Form("xStretch %.1f", fXStretch));
  tex->DrawLatexNDC(0.15,0.40,Form("yBeat %.1f mm", 20/fYBeat));
  tex->DrawLatexNDC(0.15,0.30,Form("Run %d", fRun));

  tex->DrawLatexNDC(0.15,0.15,"Last Updated:");  
  tex->DrawLatexNDC(0.65,0.15,Form("%d/%d/%d", dtime.GetMonth(), dtime.GetDay(), dtime.GetYear()));  
  tex->DrawLatexNDC(0.65,0.05,Form("%02d:%02d:%02d", dtime.GetHour(), dtime.GetMinute(), dtime.GetSecond()));  
  tex->SetTextSize(0.05);
  //=====
  main2->cd(6);
  tree->Draw(Form("dx%s:bx%s>>histO17(%d,%f,%f,%d,%f,%f)",fSDet.Data(),fSDet.Data(),
		  nbinsX,fGXmin,fGXmax,200,dxmea-5*dxsig,dxmea+5*dxsig),
             cuts2.Data(),"colz");
  TH2D *histO17 = (TH2D*) gROOT->FindObject( "histO17" );
  histO17->GetYaxis()->SetTitle( Form("dx%s [mm]",fSDet.Data()) );
  histO17->GetXaxis()->SetTitle( Form("bx%s [mm]",fSDet.Data()) );  
  TProfile *pro17 = histO17->ProfileX( "prof17" );
  pro17->SetMarkerColor(kBlack);
  pro17->SetLineColor(kBlack);
  TF1 *dxVX = new TF1("dxVX",
		      Form("[0]*TMath::Cos(x*TMath::TwoPi()/%f)+[1]*TMath::Sin(x*TMath::TwoPi()/%f)+[2]",fXPitch,fXPitch)
		      );
  pro17->Fit(dxVX);
  histO17->Draw("colz");
  pro17->Draw("SAME");

  //---*---
  publish->cd();
  tree->Draw( Form("gx%s:bx%s>>histGXvsBX(%d,%f,%f,%d,%f,%f)",fSDet.Data(),fSDet.Data(),
                   2*nbinsX,fGXmin,fGXmax,2*nbinsX,fGXmin,fGXmax),
              cuts2.Data(), "col");
  TH2D *GXvsBX = (TH2D*) gROOT->FindObject( "histGXvsBX" );
  GXvsBX->GetXaxis()->SetTitle( "BX  [mm]" );
  GXvsBX->GetYaxis()->SetTitle( "GX  [mm]" );
  tree->Draw( Form("dx%s:bx%s>>histDXMBX(%d,%f,%f,%d,%f,%f)",fSDet.Data(),fSDet.Data(),
		   2*nbinsX,fGXmin,fGXmax,200,dxmea-0.75,dxmea+0.75),
	      cuts2.Data(), "col");
  TH2D *DXMBX = (TH2D*) gROOT->FindObject( "histDXMBX" );
  DXMBX->SetTitle( "" );
  DXMBX->GetYaxis()->SetLabelSize(0.07);
  DXMBX->GetXaxis()->SetLabelSize(0.07);
  DXMBX->GetYaxis()->SetTitleSize(0.07);
  DXMBX->GetXaxis()->SetTitleSize(0.07);
  DXMBX->GetYaxis()->SetTitleOffset(1.0);
  DXMBX->GetXaxis()->SetTitle( "BeamX  [mm]" );
  DXMBX->GetYaxis()->SetTitle( "Residual  [mm]" );
  DXMBX->GetXaxis()->SetNdivisions(508);
  publish->SaveAs( Form("res/D%d/DXBXP_D%d_%d.pdf",det,det,fRun), "pdf");
  //=====
  main2->cd(5);
  DXMBX->Draw("col");
  GXvsBX->Draw("col");
  //=====

  //=====
  TH2D *histR17 = new TH2D("histR17",
			   Form(";bx%s [mm];dx%s - NL(bxD)  [mm]",fSDet.Data(),fSDet.Data()),
			   nbinsX,fGXmin,fGXmax,200,-5*dxsig,5*dxsig);
  TH1D *histDX17 = new TH1D("histDX17",
			    Form(";dx%s - NL(bXD)  [mm]",fSDet.Data()),
			    200,-5*dxsig,+5*dxsig);
  histDX17->SetLineColor(kBlack);
  TH1D *histDX17Slice = new TH1D("histDX17Slice",
				 Form(";dx%s - NL(bXD)  [mm]",fSDet.Data()),
				 200,-5*dxsig,+5*dxsig);
  //======
  TH2D *histO18 = new TH2D("histO18",
			   Form(";by%s [mm];dx%s - NL(bxD)  [mm]",fSDet.Data(),fSDet.Data()),
			   nbinsY,fGYmin,fGYmax,200,-5*dxsig,+5*dxsig);
  TH2D *histR18 = new TH2D("histR18",
			   Form(";by%s [mm];dx%s - NL(bxD) - NL(byD)  [mm]",fSDet.Data(),fSDet.Data()),
			   nbinsY,fGYmin,fGYmax,200,-5*dxsig,+5*dxsig);
  TH1D *histDX18 = new TH1D("histDX18",
			    Form(";dx%s - NL(bxD) - NL(byD)  [mm]",fSDet.Data()),
			    200,-5*dxsig,+5*dxsig);
  histDX18->SetLineColor(kBlack);

  TH2D *histDXMBY = new TH2D("histDXMBY",
			     ";BeamY  [mm];Residual  -  Corr(X)  [mm]",
			     2*nbinsY,fGYmin,fGYmax,200,-0.75,+0.75);
  histDXMBY->GetYaxis()->SetTitleOffset(0.8);

  Double_t corrX = 0;
  Double_t corrXY = 0;
  Bool_t okDET;
  Int_t maxDET, amplDET;
  UInt_t wdDET;
  Double_t chi2, bxDET, byDET, dxDET, dxDETREF, bybeatDET;
  tree->SetBranchAddress(     "chi2",               &chi2);
  tree->SetBranchAddress(Form("ok%s",fSDet.Data()), &okDET);
  tree->SetBranchAddress(Form("max%s",fSDet.Data()),&maxDET);
  tree->SetBranchAddress(Form("ampl%s",fSDet.Data()),&amplDET);
  tree->SetBranchAddress(Form("wd%s",fSDet.Data()), &wdDET);
  tree->SetBranchAddress(Form("bx%s",fSDet.Data()), &bxDET);
  tree->SetBranchAddress(Form("by%s",fSDet.Data()), &byDET);
  tree->SetBranchAddress(Form("bybeat%s",fSDet.Data()), &bybeatDET);
  tree->SetBranchAddress(Form("dx%s",fSDet.Data()), &dxDET);
  int refDet = (fDet+2)%8;
  tree->SetBranchAddress( Form("dxD%d",refDet), &dxDETREF);
  Long64_t EndOfLoop = tree->GetEntries();
  for(Long64_t i1=0; i1<EndOfLoop; ++i1) {
    if(i1%10000 == 0) {
      std::cout << " Executing event number :  " << i1 << "/" << EndOfLoop;
      std::cout << Form(" (%.1f)",i1*100.0/EndOfLoop) << std::endl;
    }
    tree->GetEntry(i1);
    //cout << chi2 << "|"<< maxDET << "|"<< wdDET << "|"<< bxDET << endl;
    //CUTS
    if(!okDET || maxDET>3500 || chi2>fChiMax ||
       wdDET<=1 || wdDET>=7 || bxDET<fGXmin ||
       bxDET>fGXmax || byDET<fGYmin || byDET>fGYmax ) {
      continue;
    }
    //PLOT
    if(0) {
      corrX = dxVX->Eval(bxDET);
    } else {
      int binXcor = pro17->FindBin( bxDET );
      corrX = pro17->GetBinContent(binXcor);
    }
    histR17->Fill( bxDET, dxDET-corrX );
    histDX17->Fill( dxDET-corrX );
    if(bxDET>1.5&&bxDET<1.8)
      histDX17Slice->Fill( dxDET-corrX );

    histO18->Fill( byDET, dxDET-corrX );
    histDXMBY->Fill( byDET, dxDET-corrX );
  }
  //---*---
  publish->cd();
  tree->Draw(Form("gx%s>>histGXD(200,-10,+10)",fSDet.Data()), cuts2.Data());
  publish->SaveAs( Form("hist/D%d/GX_%d.root",det,fRun), "root");
  tree->Draw(Form("dx%s>>histDXD(200,-10,+10)",fSDet.Data()), cuts2.Data());
  publish->SaveAs( Form("hist/D%d/DX_%d.root",det,fRun), "root");

  histDXMBY->GetYaxis()->SetLabelSize(0.07);
  histDXMBY->GetXaxis()->SetLabelSize(0.07);
  histDXMBY->GetYaxis()->SetTitleOffset(1.0);
  histDXMBY->GetYaxis()->SetTitleSize(0.07);
  histDXMBY->GetXaxis()->SetTitleSize(0.07);
  histDXMBY->GetXaxis()->SetNdivisions(508);
  histDXMBY->Draw("col");
  publish->SaveAs( Form("res/D%d/DXBYP_D%d_%d.pdf",det,det,fRun), "pdf");
  //=====
  main2->cd(9);
  histDXMBY->Draw("col");
  //=====
  main2->cd(7);
  histR17->Draw("colz");
  //=====
  main2->cd(8);
  histDX17->Draw();
  dxX->SetParameter(1,0); dxX->SetParLimits(1,-1,+1);
  dxX->SetParameter(2,dx->GetParameter(2)); dxX->SetParLimits(2,0.001,1.5*dx->GetParameter(2));
  histDX17->Fit(dxX);
  tex->SetTextColor(kGreen-3);
  tex->DrawLatexNDC(0.60,0.80,Form("#sigma %.1f (%.1f)",dxX->GetParameter(2)*1e3,
				   dxX->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.60,0.75,Form("#mu %.1f (%.1f)",dxX->GetParameter(1)*1e3,
				   dxX->GetParError(1)*1e3));
  tex->SetTextColor(kBlack);
  //=====
  main2->cd(14);
  tree->Draw(Form("wd%s>>Fhist1(10,-0.5,9.5)",fSDet.Data()),  cuts2.Data());
  tree->Draw(Form("ampl%s>>Fhist2(100,0,1e+5)",fSDet.Data()),  cuts2.Data());
  TH1D *Fhist1 = (TH1D*) gROOT->FindObject("Fhist1");
  TH1D *Fhist2 = (TH1D*) gROOT->FindObject("Fhist2");
  Fhist1->GetXaxis()->SetTitle( Form("wd%s",fSDet.Data()) );
  Fhist2->GetXaxis()->SetTitle( Form("ampl%s",fSDet.Data()) );
  main2->cd(14);
  Fhist1->DrawNormalized();
  main2->cd(15);
  Fhist2->Draw();
  //=====
  main2->cd(10);
  histO18->Draw("colz");
  TProfile *pro18 = histO18->ProfileX( "prof18" );
  pro18->SetMarkerColor(kBlack);
  pro18->SetLineColor(kBlack);
  pro18->Draw("SAME");
  TF1 *dxVY = new TF1("dxVY",
		      Form("[0]*TMath::Cos(x*TMath::TwoPi()/%f)+[1]*TMath::Sin(x*TMath::TwoPi()/%f)+[2]",
			   20/fYBeat,20/fYBeat)
		      );
  pro18->Fit(dxVY);

  TH2D *hMAXvsBX = new TH2D("hMAXvsBX","hMAXvsBX;bx;max",200,fGXmin,fGXmax,100,0,4096);
  TH2D *hDXvsMAX = new TH2D("hDXvsMAX","hDXvsMAX;max;dx",100,0,4096,100,-1,+1);
  TH2D *hDXvsAMPL = new TH2D("hDXvsAMPL","hDXvsAMPL;ampl;dx",100,0,5e4,100,-1,+1);
  TH2D *hDXvsMAXAMPL = new TH2D("hDXvsMAXAMPL","hDXvsMAXAMPL;max/ampl;dx",100,0,0.3,100,-1,+1);
  TH2D *hDXvsMAXAMPLWD = new TH2D("hDXvsMAXAMPLWD","hDXvsMAXAMPLWD;max/ampl*wd;dx",100,0,1,100,-1,+1);
  TH2D *hDXvsWD = new TH2D("hDXvsWD","hDXvsWD;wd;dx",10,-0.5,9.5,100,-1,+1);
  TH2D *hDXvsCHI2 = new TH2D("hDXvsCHI2","hDXvsCHI2;chi2;dx",100,0,20,100,-1,+1);

  //=====
  for(Long64_t i1=0; i1<EndOfLoop; ++i1) {
    if(i1%10000 == 0) {
      std::cout << " Executing event number :  " << i1 << "/" << EndOfLoop;
      std::cout << Form(" (%.1f)",i1*100.0/EndOfLoop) << std::endl;
    }
    tree->GetEntry(i1);
    //cout << chi2 << "|"<< maxDET << "|"<< wdDET << "|"<< bxDET << endl;
    //CUTS
    if(!okDET || maxDET>3500 || chi2>fChiMax ||
       wdDET<=1 || wdDET>=7 || bxDET<fGXmin ||
       bxDET>fGXmax || byDET<fGYmin || byDET>fGYmax ) {
      continue;
    }
    //PLOT
    if(0) {
      corrX = dxVX->Eval(bxDET);
      corrXY = dxVY->Eval(byDET);
    } else {
      int binXcor = pro17->FindBin( bxDET );
      corrX = pro17->GetBinContent(binXcor);
      int binYcor = pro18->FindBin( byDET );
      corrXY = pro18->GetBinContent(binYcor);
    }
    histR18->Fill( byDET, dxDET-corrX-corrXY );
    histDX18->Fill( dxDET-corrX-corrXY );
    //=====
    //cout << amplDET << endl;
    hDXvsCHI2->Fill( chi2, dxDET-corrX-corrXY );
    hDXvsWD->Fill( wdDET, dxDET-corrX-corrXY );
    hDXvsMAX->Fill( maxDET, dxDET-corrX-corrXY );
    hDXvsAMPL->Fill( amplDET, dxDET-corrX-corrXY );
    hDXvsMAXAMPL->Fill( maxDET/double(amplDET), dxDET-corrX-corrXY );
    hDXvsMAXAMPLWD->Fill( maxDET/double(amplDET)*wdDET, dxDET-corrX-corrXY );
    hMAXvsBX->Fill( bxDET, maxDET );
  }
  //====
  ofstream fcorout;
  // CORR-X
  fcorout.open( Form("res/D%d/CORXY/CORX_D%d_%d.dat",det,det,fRun) );
  for(int ib=0; ib!=pro17->GetXaxis()->GetNbins(); ++ib) {
    fcorout << " " << pro17->GetBinCenter( ib+1 );
    fcorout << " " << pro17->GetBinContent( ib+1 );
    fcorout << endl;
  }
  fcorout.close();
  // CORR-XY
  fcorout.open( Form("res/D%d/CORXY/CORXY_D%d_%d.dat",det,det,fRun) );
  for(int ib=0; ib!=pro18->GetXaxis()->GetNbins(); ++ib) {
    fcorout << " " << pro18->GetBinCenter( ib+1 );
    fcorout << " " << pro18->GetBinContent( ib+1 );
    fcorout << endl;
  }
  fcorout.close();
  //====

  //====
  main2->cd(11);
  histR18->Draw("colz");
  //=====
  main2->cd(12);
  histDX18->Draw();
  dxY->SetParameter(1,0); dxY->SetParLimits(1,-1,+1);
  dxY->SetParameter(2,dx->GetParameter(2)); dxY->SetParLimits(2,0.001,1.5*dx->GetParameter(2));
  histDX18->Fit(dxY);
  tex->SetTextColor(kBlue-3);
  tex->DrawLatexNDC(0.60,0.80,Form("#sigma %.1f (%.1f)",dxY->GetParameter(2)*1e3,
				   dxY->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.60,0.75,Form("#mu %.1f (%.1f)",dxY->GetParameter(1)*1e3,
				   dxY->GetParError(1)*1e3));
  tex->SetTextColor(kBlack);

  //---*---
  tex->SetTextSize(0.08);

  publish->cd();
  histDX18->SetTitle("");
  histDX18->Draw();
  histDX18->GetYaxis()->SetLabelSize(0.07);
  histDX18->GetXaxis()->SetLabelSize(0.07);
  histDX18->GetXaxis()->SetTitleSize(0.07);
  histDX18->GetYaxis()->SetTitleOffset(1.0);
  histDX18->GetYaxis()->SetTitleSize(0.07);
  histDX18->GetXaxis()->SetTitle("Residual -  Corr(x,y)    [mm]");
  histDX18->GetYaxis()->SetTitle("Events");
  histDX18->GetXaxis()->SetNdivisions(508);
  tex->SetTextColor(kBlue-3);
  tex->DrawLatexNDC(0.65,0.80,Form("#sigma  %.0f#mum",dxY->GetParameter(2)*1e3));
  tex->SetTextColor(kBlack);
  tex->DrawLatexNDC(0.16,0.88,Form("Run %d", fRun));
  tex->DrawLatexNDC(0.16,0.81,Form("%s %s", fSDet.Data(), fTech.Data()));
  tex->DrawLatexNDC(0.16,0.74,Form("Board %s", fBoard.Data()));
  tex->DrawLatexNDC(0.16,0.67,Form("Cell %s > %s", fCellHeader.Data(), fCell.Data()));
  tex->DrawLatexNDC(0.16,0.60,Form("xPitch %.3f", fXPitch));
  tex->DrawLatexNDC(0.16,0.53,Form("xStretch %.0f", fXStretch));
  tex->DrawLatexNDC(0.16,0.46,Form("yPeriod %.3f", 20/fYBeat));

  publish->SaveAs( Form("res/D%d/DX3_D%d_%d.pdf",det,det,fRun), "pdf");
  hist19->Draw();
  hist19->SetTitle("");
  hist19->GetYaxis()->SetLabelSize(0.07);
  hist19->GetXaxis()->SetLabelSize(0.07);
  hist19->GetXaxis()->SetTitleSize(0.07);
  hist19->GetYaxis()->SetTitleOffset(1.0);
  hist19->GetYaxis()->SetTitleSize(0.07);
  hist19->GetXaxis()->SetTitle("Residual  (ClusterX  -  BeamX)    [mm]");
  hist19->GetYaxis()->SetTitle("Events");
  hist19->GetXaxis()->SetNdivisions(508);
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.65,0.80,Form("#sigma  %.0f#mum",dx->GetParameter(2)*1e3));
  publish->SaveAs( Form("res/D%d/DX1_D%d_%d.pdf",det,det,fRun), "pdf");

  //=====
  /*
  main2->cd(12);
  histDX19->Draw();
  dxXY->SetParameter(1,dx->GetParameter(1));
  dxXY->SetParLimits(1,dx->GetParameter(1)-3,dx->GetParameter(1)+3);
  dxXY->SetParameter(2,dx->GetParameter(2));
  dxXY->SetParLimits(2,0.001,2*dx->GetParameter(2));
  histDX19->Fit(dxXY);
  tex->SetTextColor(kRed-3);
  tex->DrawLatexNDC(0.60,0.80,Form("#sigma %.1f (%.1f)",dxXY->GetParameter(2)*1e3,
				   dxXY->GetParError(2)*1e3));
  tex->DrawLatexNDC(0.60,0.75,Form("#mu %.1f (%.1f)",dxXY->GetParameter(1)*1e3,
				   dxXY->GetParError(1)*1e3));
  tex->SetTextColor(kBlack);
  */
  //=====
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
  TCanvas *mainExtra = new TCanvas();
  mainExtra->Divide(3,3);
  mainExtra->cd(1);//->SetLogz(1);
  hDXvsMAX->Draw("colz");
  mainExtra->cd(2);//->SetLogz(1);
  hDXvsAMPL->Draw("colz");
  mainExtra->cd(3);//->SetLogz(1);
  hDXvsMAXAMPL->Draw("colz");
  mainExtra->cd(4);//->SetLogz(1);
  hDXvsWD->Draw("colz");
  mainExtra->cd(5);//->SetLogz(1);
  hDXvsCHI2->Draw("colz");
  mainExtra->cd(6);//->SetLogz(1);
  hDXvsMAXAMPLWD->Draw("colz");
  mainExtra->cd(8);//->SetLogz(1);
  hMAXvsBX->Draw("colz");
  TProfile *pMAXvsBX = hMAXvsBX->ProfileX("pMAXvsBX");
  pMAXvsBX->SetLineColor(kRed-3);
  pMAXvsBX->SetMarkerColor(kRed-3);
  pMAXvsBX->SetMarkerStyle(20);
  pMAXvsBX->Draw("same");
  mainExtra->SaveAs(Form("res/D%d/qaextra_%s_%s_%s_%d.pdf",
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
  fout << " " << dx->GetParameter(1);
  fout << " " << dx->GetParameter(2)*1e3;
  fout << " " << dxX->GetParameter(2)*1e3;
  fout << " " << dxY->GetParameter(2)*1e3;
  fout << " " << dxY->GetParameter(2)*1e3;
  //fout << resultReso;
  fout << " " << fRun;
  fout << " " << fCell;
  fout << " " << fXPitch;
  fout << " " << fYBeat;
  fout << " " << fXStretch;
  fout << " " << fTech.Data();
  fout << " " << fBoard.Data();
  fout << " " << hist1FINAL->GetMean();
  fout << " " << hist2FINAL->GetMean();
  fout << " " << Form("%.0f",histDX18->GetEntries());
  fout << endl;
  fout.close();

  histDX17Slice->SaveAs("slice.root","root");
  return 0;
}
