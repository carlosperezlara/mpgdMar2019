TTree *tree;
#include "GetConfig.C"
TDatime dtime;

void fullchambercorrelation2(int idx=140)
{
  fIndex = idx;
  TString Tech[8], Board[8], Cell[8];
  Double_t ChiMax[8], GXmin[8], GXmax[8], GYmin[8], GYmax[8];
  for(int idet=0; idet!=8; ++idet) {
    fDet = idet+1;
    GetConfig();
    if(idet==0)
      std::cout << "Run " << fRun << endl;
    std::cout << "=======" << endl;
    std::cout << "Detector " << fDet << endl;
    std::cout << "CellHeader " << fCellHeader << endl;
    std::cout << "Cell " << fCell << endl;
    std::cout << "Technology " << fTech.Data() << endl;
    std::cout << "Board " << fBoard.Data() << endl;
    std::cout << "xPitch " << fXPitch << endl;
    ChiMax[idet] = fChiMax;
    GXmin[idet]  = fGXmin;
    GXmax[idet]  = fGXmax;
    GYmin[idet]  = fGYmin;
    GYmax[idet]  = fGYmax;
    Tech[idet] = fTech;
    Board[idet] = fBoard;
    Cell[idet] = fCell;
  }

  gStyle->SetOptStat(0);
  gSystem->Load("libfnal4all.so");
  TFile *ff = new TFile( Form("rootfiles/fnal-%05d.root",fRun) );
  tree = (TTree*)ff->Get("ZIGZAG");
  //========================================
  Double_t offset[8]={0,0,0,0,
		      0,0,0,0};
  TCanvas *publish = new TCanvas("pub","pub",800,500);
  TH1D *tmp;
  for(int idet=0; idet!=8; ++idet) {
    TString cuts0 = Form("(okD%d==1)&&(maxD%d<3500)&&(chi2<%f)",
			 idet+1,idet+1,ChiMax[idet]);
    TString cuts1 = Form("%s&&(wdD%d>0)&&(wdD%d<7)",
			 cuts0.Data(),idet+1,idet+1);
    TString cuts2 = Form("%s&&(bxD%d>%f)&&(bxD%d<%f)&&(byD%d>%f)&&(byD%d<%f)",
			 cuts1.Data(),idet+1,GXmin[idet],idet+1,GXmax[idet],
			 idet+1,GYmin[idet],idet+1,GYmax[idet]);
    tree->Draw( Form("dxD%d>>hh%d",idet+1,idet),
		cuts2.Data() );
    tmp=NULL;
    tmp = (TH1D*) gROOT->FindObject( Form("hh%d",idet) );
    if(tmp) {
      offset[idet] = tmp->GetMean();
    }
  }
  publish->Clear();
  publish->SetTopMargin(0.10);
  publish->SetRightMargin(0.10);
  publish->SetBottomMargin(0.30);
  publish->SetLeftMargin(0.25);
  publish->Divide(8,8,0,0);
  cout << "why?" << endl;
  //========================================
  Bool_t okDET[8];
  Int_t maxDET[8], amplDET[8];
  UInt_t wdDET[8];
  Double_t chi2, bxDET[8], byDET[8], dxDET[8], dxDETREF[8], bybeatDET[8], gxDET[8];
  tree->SetBranchAddress(     "chi2",               &chi2);
  for(int iDet=0; iDet!=8; ++iDet) {
    tree->SetBranchAddress(Form("okD%d",iDet+1), &okDET[iDet]);
    tree->SetBranchAddress(Form("maxD%d",iDet+1),&maxDET[iDet]);
    tree->SetBranchAddress(Form("amplD%d",iDet+1),&amplDET[iDet]);
    tree->SetBranchAddress(Form("wdD%d",iDet+1), &wdDET[iDet]);
    tree->SetBranchAddress(Form("bxD%d",iDet+1), &bxDET[iDet]);
    tree->SetBranchAddress(Form("byD%d",iDet+1), &byDET[iDet]);
    tree->SetBranchAddress(Form("bybeatD%d",iDet+1), &bybeatDET[iDet]);
    tree->SetBranchAddress(Form("dxD%d",iDet+1), &dxDET[iDet]);
    tree->SetBranchAddress(Form("gxD%d",iDet+1), &gxDET[iDet]);
  }
  TH2D *hCorrMatrix[8][8];
  Double_t window = 1.0;
  for(int iDet=0; iDet!=8; ++iDet) {
    for(int jDet=0; jDet!=8; ++jDet) {
      //hCorrMatrix[iDet][jDet] = new TH2D(Form("DET_%d_%d",iDet,jDet),Form(";dxD%d;dxD%d",iDet+1,jDet+1),
      //					 200,-window+offset[iDet],+window+offset[iDet],
      //					 200,-window+offset[jDet],+window+offset[jDet]);
      hCorrMatrix[iDet][jDet] = new TH2D(Form("DET_%d_%d",iDet,jDet),Form(";gxD%d;gxD%d",iDet+1,jDet+1),
					 200,-GXmin[iDet],+GXmax[iDet],
					 200,-GXmin[jDet],+GXmax[jDet]);
      hCorrMatrix[iDet][jDet]->GetXaxis()->SetNdivisions(505);
      hCorrMatrix[iDet][jDet]->GetYaxis()->SetNdivisions(505);
      hCorrMatrix[iDet][jDet]->GetXaxis()->SetLabelSize(0.15);
      hCorrMatrix[iDet][jDet]->GetYaxis()->SetLabelSize(0.2);
      hCorrMatrix[iDet][jDet]->GetXaxis()->SetTitleSize(0.2);
      hCorrMatrix[iDet][jDet]->GetYaxis()->SetTitleSize(0.2);
      hCorrMatrix[iDet][jDet]->GetXaxis()->SetTitleOffset(0.9);
      hCorrMatrix[iDet][jDet]->GetYaxis()->SetTitleOffset(0.7);
    }
  }
  Long64_t EndOfLoop = tree->GetEntries();
  for(Long64_t i1=0; i1<EndOfLoop; ++i1) {
    if(i1%10000 == 0) {
      std::cout << " Executing event number :  " << i1 << "/" << EndOfLoop;
      std::cout << Form(" (%.1f)",i1*100.0/EndOfLoop) << std::endl;
    }
    tree->GetEntry(i1);
    //RUN CUTS
    if(chi2>fChiMax) continue;
    //CORRELLATION
    for(int iDet=0; iDet!=8; ++iDet) {
      if(!okDET[iDet] || maxDET[iDet]>3500 ||
	 wdDET[iDet]<=1 || wdDET[iDet]>=7 ||
	 bxDET[iDet]<GXmin[iDet] || bxDET[iDet]>GXmax[iDet] ||
	 byDET[iDet]<GYmin[iDet] || byDET[iDet]>GYmax[iDet] ) {
	continue;
      }
      for(int jDet=0; jDet!=8; ++jDet) {
	if(!okDET[jDet] || maxDET[jDet]>3500 ||
	   wdDET[jDet]<=1 || wdDET[jDet]>=7 ||
	   bxDET[jDet]<GXmin[jDet] || bxDET[jDet]>GXmax[jDet] ||
	   byDET[jDet]<GYmin[jDet] || byDET[jDet]>GYmax[jDet] ) {
	  continue;
	}
	//PLOT
	//hCorrMatrix[iDet][jDet]->Fill( dxDET[iDet], dxDET[jDet] );
	hCorrMatrix[iDet][jDet]->Fill( gxDET[iDet], gxDET[jDet] );
      }
    }
  }
  //---*---
  for(int iDet=0; iDet!=8; ++iDet) {
    for(int jDet=0; jDet!=8; ++jDet) {
      publish->cd( 1+iDet*8+jDet );//->SetLogz(1);
      hCorrMatrix[7-jDet][iDet]->Draw("colz");
    }
  }
  TLatex *tex = new TLatex();
  tex->SetTextSize(0.13);
  double xxx = 0.1;
  for(int iDet=0; iDet!=8; ++iDet) {
    publish->cd( 1+7*8+(7-iDet) );
    tex->DrawLatexNDC(xxx+(iDet==7?0.25:0.0), 0.6, 
		      Form("%s %s %s",Tech[iDet].Data(),Board[iDet].Data(),Cell[iDet].Data()));
    tex->DrawLatexNDC(xxx+(iDet==7?0.25:0.0), 0.5, 
		      Form("[%.1f-%.1f] [%.1f-%.1f]",GXmin[iDet],GXmax[iDet],GYmin[iDet],GYmax[iDet]) );
  }
  tex->SetTextSize(0.18);
  for(int iDet=0; iDet!=7; ++iDet) {
    publish->cd( 1+iDet*8+0 );
    tex->DrawLatexNDC(xxx+0.25, 0.6, 
		      Form("%s %s %s",Tech[iDet].Data(),Board[iDet].Data(),Cell[iDet].Data()));
    tex->DrawLatexNDC(xxx+0.25, 0.4, 
		      Form("[%.1f-%.1f] [%.1f-%.1f]",GXmin[iDet],GXmax[iDet],GYmin[iDet],GYmax[iDet]) );
  }
  publish->SaveAs( Form("res/CORR2_%d.pdf",fRun), "pdf");
  //=====

  return 0;
}
