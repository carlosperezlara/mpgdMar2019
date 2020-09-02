TTree *tree;
#include "GetConfig.C"
TDatime dtime;
TH1D *fCorX[8];
TH1D *fCorXY[8];

void Format(TH1 *thisguy) {
  thisguy->GetXaxis()->SetNdivisions(505);
  thisguy->GetYaxis()->SetNdivisions(505);
  thisguy->GetXaxis()->SetLabelSize(0.08);
  thisguy->GetYaxis()->SetLabelSize(0.08);
  thisguy->GetXaxis()->SetTitleSize(0.08);
  thisguy->GetYaxis()->SetTitleSize(0.08);
  thisguy->GetXaxis()->SetTitleOffset(-0.3);
  thisguy->GetYaxis()->SetTitleOffset(-0.3);
}

void FinalResults(int idx=54, int detfinal=1, int detaux=3)
{
  fIndex = idx;
  TString Tech[8], Board[8], Cell[8];
  Int_t NDim[8], NGap[8];
  Double_t XPitch[8], YBeat[8], XStretch[8];
  Double_t ChiMax[8], GXmin[8], GXmax[8], GYmin[8], GYmax[8];
  Double_t Res_Mu[8], Res_Sg[8], Res_Sg3[8];
  Int_t detarray[2] = {detfinal,detaux};
  for(int aidet=0; aidet!=2; ++aidet) {
    fDet = detarray[aidet];
    int idet = detarray[aidet]-1;
    GetConfig();
    if(idet==0)
      std::cout << "Run " << fRun << endl;
    //std::cout << "=======" << endl;
    //std::cout << "Detector " << fDet << endl;
    //std::cout << "CellHeader " << fCellHeader << endl;
    //std::cout << "Cell " << fCell << endl;
    //std::cout << "Technology " << fTech.Data() << endl;
    //std::cout << "Board " << fBoard.Data() << endl;
    //std::cout << "xPitch " << fXPitch << endl;
    ChiMax[idet] = fChiMax;
    GXmin[idet]  = fGXmin;
    GXmax[idet]  = fGXmax;
    GYmin[idet]  = fGYmin;
    GYmax[idet]  = fGYmax;
    NDim[idet] = fNDim;
    NGap[idet] = fNGap;
    Tech[idet] = fTech;
    Board[idet] = fBoard;
    Cell[idet] = fCell;
    XPitch[idet] = fXPitch;
    YBeat[idet] = fYBeat;
    XStretch[idet] = fXStretch;

    Int_t nbin_c;
    Double_t xxxx[1000];
    Double_t yyyy[1000];
    Double_t tmp;
    ifstream fcorin;
    Double_t delta;

    Res_Sg[idet] = (GXmax[idet] - GXmin[idet])/5;
    Res_Sg3[idet] = (GXmax[idet] - GXmin[idet])/5;

    fcorin.open( Form("res/D%d/data/reso_%s_%s_run%d.dat",fDet,fTech.Data(),fBoard.Data(),fRun) );
    fcorin >> Res_Mu[idet];
    if(fcorin.good()) {
      fcorin >> Res_Sg[idet] >> Res_Sg3[idet] >> Res_Sg3[idet];
      fcorin.close();
      Res_Sg[idet] *= 1e-3;
      Res_Sg3[idet] *= 1e-3;
    } else {
      Res_Mu[idet] = 0;
    }
    cout << "R " << Res_Mu[idet] << " " << Res_Sg[idet] << endl;
    GXmin[idet] += Res_Mu[idet];
    GXmax[idet] += Res_Mu[idet];

    //cout << "D" << fDet << " CORR ";
    nbin_c = 0;
    fcorin.open( Form("res/D%d/CORXY/CORX_D%d_%d.dat",fDet,fDet,fRun) );
    for(;;) {
      fcorin >> tmp;
      if(!fcorin.good()) break;
      xxxx[nbin_c] = tmp;
      fcorin >> tmp;
      yyyy[nbin_c] = tmp;
      nbin_c++;
    }
    fcorin.close();
    if(nbin_c>2) {
      delta = xxxx[1] - xxxx[0];
      fCorX[fDet-1] = new TH1D( Form("CORX_%d_%d",fDet,aidet), "", nbin_c,
			      xxxx[0] - delta, xxxx[nbin_c-1] + delta);
      for(int iiii=0; iiii!=nbin_c; ++iiii) {
	fCorX[fDet-1]->SetBinContent(iiii+1,yyyy[iiii]);
      }
    } else {
      fCorX[fDet-1] = new TH1D( Form("CORX_%d_%d",fDet,aidet), "", 1,
			      -1000,+1000);
    }
    //cout << nbin_c << " ";

    nbin_c = 0;
    fcorin.open( Form("res/D%d/CORXY/CORXY_D%d_%d.dat",fDet,fDet,fRun) );
    for(;;) {
      fcorin >> tmp;
      if(!fcorin.good()) break;
      xxxx[nbin_c] = tmp;
      fcorin >> tmp;
      yyyy[nbin_c] = tmp;
      nbin_c++;
    }
    fcorin.close();
    if(nbin_c>2) {
      delta = xxxx[1] - xxxx[0];
      fCorXY[fDet-1] = new TH1D( Form("CORXY_%d_%d",fDet,aidet), "", nbin_c,
			       xxxx[0] - delta, xxxx[nbin_c-1] + delta);
      for(int iiii=0; iiii!=nbin_c; ++iiii) {
        fCorXY[fDet-1]->SetBinContent(iiii+1,yyyy[iiii]);
      }
    } else {
      fCorXY[fDet-1] = new TH1D( Form("CORXY_%d_%d",fDet,aidet), "", 1,
			       -1000,+1000);
    }
    //cout << nbin_c << endl;
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
  for(int aidet=0; aidet!=2; ++aidet) {
    int idet = detarray[aidet]-1;
    if(fCorX[idet]->GetXaxis()->GetNbins()>5) continue;
    TString cuts0 = Form("(okD%d==1)&&(maxD%d<3500)&&(chi2<%f)",
			 idet+1,idet+1,ChiMax[idet]);
    TString cuts1 = Form("%s&&(wdD%d>0)&&(wdD%d<7)",
			 cuts0.Data(),idet+1,idet+1);
    TString cuts2 = Form("%s&&(bxD%d>%f)&&(bxD%d<%f)&&(byD%d>%f)&&(byD%d<%f)",
			 cuts1.Data(),idet+1,GXmin[idet],idet+1,GXmax[idet],
			 idet+1,GYmin[idet],idet+1,GYmax[idet]);
    tree->Draw( Form("dxD%d>>hh%d",idet+1,idet), cuts2.Data() );
    //tree->Draw( Form("gxD%d>>hh%d",idet+1,idet), cuts2.Data() );
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
  publish->Divide(4,4);
  cout << "why?" << endl;
  //========================================
  Bool_t okDET[8];
  Int_t maxDET[8], amplDET[8];
  UInt_t wdDET[8];
  Double_t chi2, gxDET[8], bxDET[8], byDET[8], dxDET[8], dxDETREF[8], bxpitchDET[8], bybeatDET[8];
  tree->SetBranchAddress(     "chi2",               &chi2);
  for(int iDet=0; iDet!=8; ++iDet) {
    tree->SetBranchAddress(Form("okD%d",iDet+1), &okDET[iDet]);
    tree->SetBranchAddress(Form("maxD%d",iDet+1),&maxDET[iDet]);
    tree->SetBranchAddress(Form("amplD%d",iDet+1),&amplDET[iDet]);
    tree->SetBranchAddress(Form("wdD%d",iDet+1), &wdDET[iDet]);
    tree->SetBranchAddress(Form("gxD%d",iDet+1), &gxDET[iDet]);
    tree->SetBranchAddress(Form("bxD%d",iDet+1), &bxDET[iDet]);
    tree->SetBranchAddress(Form("byD%d",iDet+1), &byDET[iDet]);
    tree->SetBranchAddress(Form("bxpitchD%d",iDet+1), &bxpitchDET[iDet]);
    tree->SetBranchAddress(Form("bybeatD%d",iDet+1), &bybeatDET[iDet]);
    tree->SetBranchAddress(Form("dxD%d",iDet+1), &dxDET[iDet]);
  }
  int iDet = detfinal-1;
  int jDet = detaux-1;
  TH2D *hCorrMatrix[8][8];
  //Double_t window = 1.0;
  Double_t window = 3.0;
  hCorrMatrix[iDet][jDet] = new TH2D(Form("DET_%d_%d",iDet,jDet),Form(";dxD%d;dxD%d",iDet+1,jDet+1),
				     100,-window+offset[iDet],+window+offset[iDet],
				     100,-window+offset[jDet],+window+offset[jDet]);
  Format(hCorrMatrix[iDet][jDet]);
  TH1D *hDXRaw = new TH1D("hDXRaw","hDXRaw;dx  [mm]",
			  100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRaw);
  TH2D *hDXRawBXins = new TH2D("hDXRawBXins","hDXRawBXins;bx  [mm];dx  [mm]",
			       int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet]-5,GXmax[iDet]+5,
			       100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRawBXins);
  TH2D *hDXRawBYins = new TH2D("hDXRawBYins","hDXRawBYins;by  [mm];dx  [mm]",
			       int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet]-5,GYmax[iDet]+5,
			       100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRawBYins);
  TH2D *h2DHitsIns = new TH2D("h2DHitsIns","h2DHitsIns;bx  [mm];by  [mm]",
			      int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet]-5,GXmax[iDet]+5,
			      int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet]-5,GYmax[iDet]+5);
  Format(h2DHitsIns);

  TH2D *hDXRawBX = new TH2D("hDXRawBX","hDXRawBX;bx  [mm];dx  [mm]",
			    int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet],GXmax[iDet],
			    100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRawBX);
  TH2D *hDXRawBY = new TH2D("hDXRawBY","hDXRawBY;by  [mm];dx  [mm]",
			    int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet],GYmax[iDet],
			    100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRawBY);
  TH1D *hDXAux = new TH1D("hDXAux","hDXAux;dx  [mm]",
			  100, Res_Mu[jDet]-5*Res_Sg[jDet], Res_Mu[jDet]+5*Res_Sg[jDet]);
  Format(hDXAux);
  TH1D *hDXAuxCut = new TH1D("hDXAuxCut","hDXAuxCut;dx  [mm]",
			  100, Res_Mu[jDet]-5*Res_Sg[jDet], Res_Mu[jDet]+5*Res_Sg[jDet]);
  Format(hDXAuxCut);
  TH1D *hDXRawCut = new TH1D("hDXRawCut","hDXRawCut;dx  [mm]",
			  100, Res_Mu[iDet]-5*Res_Sg[iDet], Res_Mu[iDet]+5*Res_Sg[iDet]);
  Format(hDXRawCut);
  TProfile2D *p2D = new TProfile2D("p2D","p2D;bx  [mm];by  [mm]",
				   TMath::Min( int(XPitch[iDet]/0.01), 100 ),-XPitch[iDet]/2,XPitch[iDet]/2,
				   TMath::Min( int(10.0/YBeat[iDet]/0.01), 100 ),-10/YBeat[iDet],10/YBeat[iDet]);
				   //10,-fXPitch/2,fXPitch/2,
				   //10,-10/fYBeat,10/fYBeat);
				   //int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet],GXmax[iDet],
				   //int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet],GYmax[iDet]);
  Format(p2D);
  TH2D *h2DHitsC = new TH2D("h2DHitsC","h2DHitsRaw;bx  [mm];by  [mm]",
				   int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet],GXmax[iDet],
				   int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet],GYmax[iDet]);
  Format(h2DHitsC);
  TH2D *h2DHitsB = new TH2D("h2DHitsB","h2DHitsBefore;bx  [mm];by  [mm]",
				   int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet],GXmax[iDet],
				   int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet],GYmax[iDet]);
  Format(h2DHitsB);
  TH2D *h2DHitsA = new TH2D("h2DHitsA","h2DHitsAfter;bx  [mm];by  [mm]",
				   int((GXmax[iDet]-GXmin[iDet])/0.100),GXmin[iDet],GXmax[iDet],
				   int((GYmax[iDet]-GYmin[iDet])/0.100),GYmin[iDet],GYmax[iDet]);
  Format(h2DHitsA);
  TH1D *hDXFinal = new TH1D("hDXFinal","hDXFinal;dx  [mm]",
			    100, -5*Res_Sg3[iDet], +5*Res_Sg3[iDet]);
  Format(hDXFinal);

  for(int i=0; i!=8; ++i) {
    //cout << " iDet " << i << fCorX[i]->GetXaxis()->GetNbins();
    //cout << " " << fCorXY[i]->GetXaxis()->GetNbins() << endl;
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
    if(!okDET[iDet] || maxDET[iDet]>3500 ||
       wdDET[iDet]<1 || wdDET[iDet]>=7 ) {
      continue;
    }
    h2DHitsIns->Fill( bxDET[iDet], byDET[iDet]  );
    hDXRawBXins->Fill( bxDET[iDet], dxDET[iDet]  );
    if(bxDET[iDet]<GXmin[iDet] || bxDET[iDet]>GXmax[iDet] ) {
      continue;
    }
    hDXRawBYins->Fill( byDET[iDet], dxDET[iDet]  );
    if(byDET[iDet]<GYmin[iDet] || byDET[iDet]>GYmax[iDet] ) {
      continue;
    }
    // extra cut for rows 2 and 7 due to HV film gap
    if(Cell[iDet].Contains("7") || Cell[iDet].Contains("2")) {
      if(TMath::Abs(byDET[iDet])<0.5) continue;
    }

    h2DHitsC->Fill( bxDET[iDet], byDET[iDet]  );
    hDXRawBX->Fill( bxDET[iDet], dxDET[iDet] );
    hDXRawBY->Fill( byDET[iDet], dxDET[iDet] );
    hDXRaw->Fill( dxDET[iDet] );
    if(!okDET[jDet] || maxDET[jDet]>3500 ||
       wdDET[jDet]<1 || wdDET[jDet]>=7 ||
       bxDET[jDet]<GXmin[jDet] || bxDET[jDet]>GXmax[jDet] ||
       byDET[jDet]<GYmin[jDet] || byDET[jDet]>GYmax[jDet] ) {
      continue;
    }
    //CORR
    int bin1X = fCorX[iDet]->FindBin( bxDET[iDet] );
    int bin1XY = fCorXY[iDet]->FindBin( bxDET[iDet] );
    int bin2X = fCorX[jDet]->FindBin( bxDET[jDet] );
    int bin2XY = fCorXY[jDet]->FindBin( bxDET[jDet] );
    Double_t corr1 = fCorX[iDet]->GetBinContent(bin1X) + fCorXY[iDet]->GetBinContent(bin1XY);
    Double_t corr2 = fCorX[jDet]->GetBinContent(bin2X) + fCorXY[jDet]->GetBinContent(bin2XY);
    hDXAux->Fill( dxDET[jDet]-corr2 );
    hCorrMatrix[iDet][jDet]->Fill( dxDET[iDet]-corr1, dxDET[jDet]-corr2 );
    if( TMath::Abs( dxDET[jDet]-corr2 ) > 3*Res_Sg[jDet] ) {
      continue;
    }
    hDXAuxCut->Fill( dxDET[jDet]-corr2 );
    hDXRawCut->Fill( dxDET[iDet] );
    //cout << bxpitchDET[iDet] << " " << bybeatDET[iDet] << endl;
    h2DHitsB->Fill( bxDET[iDet], byDET[iDet]  );
    p2D->Fill( bxpitchDET[iDet], bybeatDET[iDet], dxDET[iDet]  );
    //p2D->Fill( bxDET[iDet], byDET[iDet], dxDET[iDet]  );
    //p2D->Fill( bxreduced, byreduced, dxDET[iDet]  );
  }
  for(Long64_t i1=0; i1<EndOfLoop; ++i1) {
    if(i1%10000 == 0) {
      std::cout << " Executing event number :  " << i1 << "/" << EndOfLoop;
      std::cout << Form(" (%.1f)",i1*100.0/EndOfLoop) << std::endl;
    }
    tree->GetEntry(i1);
    //RUN CUTS
    if(chi2>fChiMax) continue;
    //CORRELLATION
    if(!okDET[iDet] || maxDET[iDet]>3500 ||
       wdDET[iDet]<1 || wdDET[iDet]>=7 ||
       bxDET[iDet]<GXmin[iDet] || bxDET[iDet]>GXmax[iDet] ||
       byDET[iDet]<GYmin[iDet] || byDET[iDet]>GYmax[iDet] ) {
      continue;
    }
    // extra cut for rows 2 and 7 due to HV film gap
    if(Cell[iDet].Contains("7") || Cell[iDet].Contains("2")) {
      if(TMath::Abs(byDET[iDet])<0.5) continue;
    }
    if(!okDET[jDet] || maxDET[jDet]>3500 ||
       wdDET[jDet]<1 || wdDET[jDet]>=7 ||
       bxDET[jDet]<GXmin[jDet] || bxDET[jDet]>GXmax[jDet] ||
       byDET[jDet]<GYmin[jDet] || byDET[jDet]>GYmax[jDet] ) {
      continue;
    }
    //CORR
    int bin1X = fCorX[iDet]->FindBin( bxDET[iDet] );
    int bin1XY = fCorXY[iDet]->FindBin( bxDET[iDet] );
    int bin2X = fCorX[jDet]->FindBin( bxDET[jDet] );
    int bin2XY = fCorXY[jDet]->FindBin( bxDET[jDet] );
    Double_t corr1 = fCorX[iDet]->GetBinContent(bin1X) + fCorXY[iDet]->GetBinContent(bin1XY);
    Double_t corr2 = fCorX[jDet]->GetBinContent(bin2X) + fCorXY[jDet]->GetBinContent(bin2XY);
    if( TMath::Abs( dxDET[jDet]-corr2 ) > 3*Res_Sg[jDet] ) {
      continue;
    }
    Int_t binbin = p2D->FindBin( bxpitchDET[iDet], bybeatDET[iDet] );
    if( p2D->GetBinEntries(binbin)<2 ) continue;
    Double_t corrcorr = p2D->GetBinContent( binbin );
    h2DHitsA->Fill( bxDET[iDet], byDET[iDet]  );
    hDXFinal->Fill( dxDET[iDet]-corrcorr );
  }

  //---*---
  TF1 *fit1 = new TF1("fit1","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *fit2 = new TF1("fit2","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *fit3 = new TF1("fit3","[0]*TMath::Gaus(x,[1],[2])");
  fit1->SetParameter(0,hDXRaw->GetMaximum()); fit1->SetParLimits(0,10,20000);
  fit2->SetParameter(0,hDXRawCut->GetMaximum()); fit2->SetParLimits(0,10,20000);
  fit3->SetParameter(0,hDXFinal->GetMaximum()); fit3->SetParLimits(0,10,20000);
  fit1->SetParameter(1,hDXRaw->GetMean()); fit1->SetParLimits(1,-6,+6);
  fit2->SetParameter(1,hDXRawCut->GetMean()); fit2->SetParLimits(1,-6,+6);
  fit3->SetParameter(1,hDXFinal->GetMean()); fit3->SetParLimits(1,-2,+2);
  fit1->SetParameter(2,0.050); fit1->SetParLimits(2,0.010,0.400);
  fit2->SetParameter(2,0.050); fit2->SetParLimits(2,0.010,0.400);
  fit3->SetParameter(2,0.050); fit3->SetParLimits(2,0.010,0.400);

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.12);
  TLine *lin = new TLine();
  lin->SetLineColor(kRed-3);
  double xxx = 0.1;
  publish->cd(1); h2DHitsIns->Draw("colz");
  publish->cd(2); hDXRawBXins->Draw("colz");
  lin->DrawLine( GXmin[iDet], -100, GXmin[iDet], +100);
  lin->DrawLine( GXmax[iDet], -100, GXmax[iDet], +100);
  publish->cd(3); hDXRawBYins->Draw("colz");
  lin->DrawLine( GYmin[iDet], -100, GYmin[iDet], +100);
  lin->DrawLine( GYmax[iDet], -100, GYmax[iDet], +100);
  publish->cd(5); h2DHitsC->Draw("colz");
  publish->cd(6); hDXRawBX->Draw("colz");
  publish->cd(7); hDXRawBY->Draw("colz");
  publish->cd(8); hDXRaw->Draw(); hDXRaw->Fit(fit1,"EMW");
  tex->DrawLatexNDC(0.2, 0.8, Form("#sigma %.0f",fit1->GetParameter(2)*1e3) );
  publish->cd(9); hDXAux->Draw();
  publish->cd(10); hCorrMatrix[iDet][jDet]->Draw("colz");
  publish->cd(11); hDXAuxCut->Draw();
  publish->cd(12); hDXRawCut->Draw(); hDXRawCut->Fit(fit2,"EMW");
  tex->DrawLatexNDC(0.2, 0.8, Form("#sigma %.0f",fit2->GetParameter(2)*1e3) );
  publish->cd(13); h2DHitsB->Draw("colz");
  publish->cd(14); p2D->Draw("colz");
  publish->cd(15); h2DHitsA->Draw("colz");
  publish->cd(16); hDXFinal->Draw(); hDXFinal->Fit(fit3,"EMW");
  tex->DrawLatexNDC(0.2, 0.8, Form("#sigma %.0f",fit3->GetParameter(2)*1e3) );
  publish->cd(4);
  tex->DrawLatexNDC(xxx, 0.9, Form("Target Det%d         %d",iDet+1,fRun) );
  tex->DrawLatexNDC(xxx, 0.8, 
		    Form("%s %s %s",Tech[iDet].Data(),Board[iDet].Data(),Cell[iDet].Data()));
  tex->DrawLatexNDC(xxx, 0.7, 
		    Form("XP %.2f   YP %.2f   ST %.0f  (%d,%d)",
			 XPitch[iDet],20/YBeat[iDet],XStretch[iDet],NDim[iDet],NGap[iDet]));
  tex->DrawLatexNDC(xxx, 0.6, 
		    Form("[%.1f:%.1f] [%.1f:%.1f]",GXmin[iDet],GXmax[iDet],GYmin[iDet],GYmax[iDet]) );
  tex->DrawLatexNDC(xxx, 0.4, Form("Auxiliary Det%d",jDet+1) );
  tex->DrawLatexNDC(xxx, 0.3, 
		    Form("%s %s %s",Tech[jDet].Data(),Board[jDet].Data(),Cell[jDet].Data()));
  tex->DrawLatexNDC(xxx, 0.2, 
		    Form("XP %.2f   YP %.2f   ST %.0f  (%d,%d)",
			 XPitch[jDet],20/YBeat[jDet],XStretch[jDet],NDim[jDet],NGap[jDet]));
  tex->DrawLatexNDC(xxx, 0.1, 
		    Form("[%.1f:%.1f] [%.1f:%.1f]",GXmin[jDet],GXmax[jDet],GYmin[jDet],GYmax[jDet]) );
  if( 
     (hDXRaw->GetEntries()<10) ||
     (hDXRawCut->GetEntries()<10) ||
     (hDXFinal->GetEntries()<10)
      ) return 1;

  TString ofile = Form("res/RES_%s_%s_D%dCell%s_D%dCell%s_Run%d",
		       Tech[iDet].Data(),Board[iDet].Data(),
		       iDet+1,Cell[iDet].Data(),
		       jDet+1,Cell[jDet].Data(),
		       fRun);
  publish->SaveAs( Form("%s.pdf",ofile.Data()), "pdf" );
  ofstream fout( Form("%s.dat",ofile.Data()) );
  fout << fit1->GetParameter(1) << " " << fit1->GetParameter(2) << " ";
  fout << fit2->GetParameter(1) << " " << fit2->GetParameter(2) << " ";
  fout << fit3->GetParameter(1) << " " << fit3->GetParameter(2) << " ";
  fout << Tech[iDet].Data() << " " << Board[iDet].Data() << " ";
  fout << "Det" << iDet+1 << "(" << Cell[iDet].Data() << ") ";
  fout << "Aux" << jDet+1 << "(" << Cell[jDet].Data() << ") ";
  fout << fRun << endl;
  fout.close();
  //=====

  return 0;
}
