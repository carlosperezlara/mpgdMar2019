int plotResMean() {
  gStyle->SetOptStat(0);
  Double_t x[8][1000], y[8][1000];
  Int_t n[8];
  int color[8] = {kRed-3, kBlue-3, kCyan-3, kOrange-3, kMagenta-3, kGreen-3, kGray, kBlack };
  TString tmp;
  Double_t lead;
  TGraph *gr[8];
  ifstream fin;
  for(int i=0; i!=8; ++i) {
    //fin.open( Form("D%d/reso40.dat",i+1) );
    //fin.open( Form("D%d/reso_StaticMotor.dat",i+1) );
    //fin.open( Form("D%d/reso_StaticEncoder.dat",i+1) );
    //fin.open( Form("D%d/reso_Static4Encoder.dat",i+1) );
    fin.open( Form("D%d/reso_Static4EncoderDEP.dat",i+1) );
    n[i]=0;
    for(;;) {
      fin >> y[i][ n[i] ];
      if(!fin.good()) break;
      fin >> tmp >> tmp >> tmp;
      fin >> lead;
      fin >> x[i][ n[i] ] >> tmp >> tmp >> tmp >> tmp;
      if(lead<10 || lead > 300) continue;
      n[i]++;
    }
    fin.close();
    cout << i << " " << n[i] << endl;
    gr[i] = new TGraph(n[i],x[i],y[i]);
    gr[i]->SetMarkerStyle(20);
    gr[i]->SetMarkerColor( color[i] );
    gr[i]->SetLineColor( color[i] );
  }

  TH2D *axis = new TH2D("axis","",600,1100,1700,100,-6,+9);
  axis->Draw();
  TLegend *leg = new TLegend(0.1,0.1,0.8,0.2);
  for(int i=0; i!=8; ++i) {
    gr[i]->Draw("PLSAME");
    leg->AddEntry(gr[i],Form("Det%d",i+1));
  }
  leg->SetNColumns(4);
  leg->Draw();
  return 0;
}
