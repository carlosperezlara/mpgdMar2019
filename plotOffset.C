int plotOffset() {
  ifstream fin("res/D1/data/D1stats.dat"); 
  Int_t n=0;
  Float_t mean[1000];
  Float_t res1[1000];
  Float_t run[1000];
  TString cell[1000];
  Float_t xpi[1000];
  Float_t ybe[1000];
  Float_t xst[1000];
  for(;;) {
    fin >> mean[n];
    if(!fin.good()) break;
    fin >> res1[n] >> run[n] >> cell[n];
    fin >> xpi[n] >> ybe[n] >> xst[n];
    if(res1[n]<10) continue;
    ++n;
  }

  TLine *line = new TLine();

  TGraph *grMean = new TGraph(n,run,mean);
  grMean->Draw("A*");
  line->SetLineColor(kRed-3);
  line->DrawLine(1080,-10,1080,+10);
  line->DrawLine(1209,-10,1209,+10);
  line->DrawLine(1250,-10,1250,+10);
  line->DrawLine(1291,-10,1291,+10);
  line->DrawLine(1465,-10,1465,+10);
  line->DrawLine(1619,-10,1619,+10);
  line->DrawLine(1637,-10,1637,+10);
  line->DrawLine(1733,-10,1733,+10);
  line->SetLineColor(kBlue-3);
  line->DrawLine(1355,-10,1355,+10);

  return 0;
}
