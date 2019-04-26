int recenter(TString dir="") {
  gStyle->SetOptStat(0);
  ifstream fin("elog/runs.dat.good");
  ifstream frun;
  int n=0;
  Double_t Run[1000];
  Double_t Det[8][3][1000];
  for(int det=0;det!=8;++det)
    for(int i=0; i!=1000; ++i) {
      Det[det][0][i] = 0;
      Det[det][1][i] = 0;
      Det[det][2][i] = 0;
    }

  for(;;) {
    int run;
    fin >> run;
    if(!fin.good()) break;
    Run[n] = run;
    //===== LOGBXY
    frun.open( Form("logBXY/%s/bxy_%d.dat",dir.Data(),run) );
    for(int det=0;det!=8;++det) {
      Double_t tmpX, tmpY;
      frun >> tmpX >> tmpY;
      if(!frun.good()) break;
      Det[det][0][n] = tmpX;
      Det[det][1][n] = tmpY;
      //cout << " [LOADING] " << endl;
    }
    frun.close();
    //===== LOGANG
    frun.open( Form("logANG/%s/ang_avg_%d.dat",dir.Data(),run) );
    Double_t tmpA;
    frun >> tmpA;
    if(frun.good()) {
      Det[0][2][n] = tmpA;
    }
    frun.close();
    //===== LOGBXYAVG
    frun.open( Form("logBXY/%s/bxy_avg_%d.dat",dir.Data(),run) );
    Double_t tmpX, tmpY;
    frun >> tmpX >> tmpY;
    if(frun.good()) {
      Det[1][2][n] = tmpX;
      Det[2][2][n] = tmpY;
    }
    frun.close();

    n++;
  }
  Int_t col[8] = {kRed,kBlue,kMagenta,kCyan,
		  kOrange,kGreen,kGray,kBlack};
  Int_t mar[8]  {24,25,26,27,28,30,2,3};
  TGraph *gr[8][3];
  TH2F *axis1 = new TH2F("axis1","bxD# ;run  number;Gaussian  mean",100,1000.,1850.,100,-10.,+20.);
  TH2F *axis2 = new TH2F("axis2","byD# ;run  number;Gaussian  mean",100,1000.,1850.,100,-5.,+20.);
  TH2F *axis3 = new TH2F("axis3","angD# ;run  number;slope",100,1000.,1850.,100,-1.,+1.);
  TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
  leg->SetNColumns(3);

  TCanvas *main1 = new TCanvas();
  axis1->Draw();
  for(int det=0; det!=8; ++det) {
    gr[det][0] = new TGraph(n,Run,Det[det][0]);
    gr[det][0]->SetLineColor( col[det] );
    gr[det][0]->SetFillColor(kWhite);
    gr[det][0]->SetMarkerSize( 2 );
    gr[det][0]->SetMarkerColor( col[det] );
    gr[det][0]->SetMarkerStyle( mar[det] );
    gr[det][0]->Draw("PSAME");
    leg->AddEntry( gr[det][0], Form("D%d",det)  );
  }
  leg->Draw();

  TCanvas *main2 = new TCanvas();
  axis2->Draw();
  for(int det=0; det!=8; ++det) {
    gr[det][1] = new TGraph(n,Run,Det[det][1]);
    gr[det][1]->SetLineColor( col[det] );
    gr[det][1]->SetFillColor(kWhite);
    gr[det][1]->SetMarkerSize( 2 );
    gr[det][1]->SetMarkerColor( col[det] );
    gr[det][1]->SetMarkerStyle( mar[det] );
    gr[det][1]->Draw("PSAME");
  }
  leg->Draw();

  TCanvas *main3 = new TCanvas();
  axis3->Draw();
  gr[0][2] = new TGraph(n,Run,Det[0][2]);
  gr[0][2]->SetLineColor( kRed-3 );
  gr[0][2]->SetFillColor(kWhite);
  gr[0][2]->SetMarkerSize( 2 );
  gr[0][2]->SetMarkerColor( kRed-3 );
  gr[0][2]->SetMarkerStyle( 20 );
  gr[0][2]->Draw("PSAME");

  TCanvas *main4 = new TCanvas();
  axis1->Draw();
  gr[1][2] = new TGraph(n,Run,Det[1][2]);
  gr[1][2]->SetLineColor( kRed-3 );
  gr[1][2]->SetFillColor(kWhite);
  gr[1][2]->SetMarkerSize( 2 );
  gr[1][2]->SetMarkerColor( kRed-3 );
  gr[1][2]->SetMarkerStyle( 20 );
  gr[1][2]->Draw("PSAME");

  TCanvas *main5 = new TCanvas();
  axis2->Draw();
  gr[2][2] = new TGraph(n,Run,Det[2][2]);
  gr[2][2]->SetLineColor( kRed-3 );
  gr[2][2]->SetFillColor(kWhite);
  gr[2][2]->SetMarkerSize( 2 );
  gr[2][2]->SetMarkerColor( kRed-3 );
  gr[2][2]->SetMarkerStyle( 20 );
  gr[2][2]->Draw("PSAME");

  main1->SaveAs("beamX.jpg","jpg");
  main2->SaveAs("beamY.jpg","jpg");
  main3->SaveAs("beamA.jpg","jpg");
  main4->SaveAs("beamXA.jpg","jpg");
  main5->SaveAs("beamYA.jpg","jpg");

  Double_t Zpos[8] = { -210, -135, -60, +15,
		       +90, +165, +240, +323};
  ofstream outf;
  for(int det=0; det!=8; ++det) {
    outf.open( Form("D%d.beamnew",det+1) );
    for(int irun=0; irun!=n; ++irun) {
      outf << " " << Run[irun] << " " << Run[irun] << " ";
      outf << Form(" %.1f ",-15.2 + Det[1][2][irun]);
      outf << Form(" %.1f ",-23.4 - Det[2][2][irun]);
      outf << " " << Zpos[det];
      outf << Form(" %.1f ", 8.1 + Det[0][2][irun] ) << endl;
    }
    outf.close();
  }

  return 0;
}
