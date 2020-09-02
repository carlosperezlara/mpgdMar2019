int plotDeltaEncoder() {
  int nruns = 0;
  TString tmp;
  double run[1000];
  double x[1000], y[1000];
  TString cell[1000];
  TH1D *hFill[10];
  for(int i=0; i!=10; ++i) hFill[i] = new TH1D( Form("HFILL%d",i),"",100,-6,+6 );
  ifstream fin("CONTROL2.dat");
  for(;;) {
    if(!fin.good()) break;
    fin >> run[nruns];
    fin >> tmp >> cell[nruns] >> tmp >> tmp;
    fin >> tmp >> tmp >> tmp >> tmp;
    fin >> tmp >> tmp;
    fin >> x[nruns] >> y[nruns];
    //run[nruns] = nruns;
    if(cell[nruns].Contains('A')) hFill[0]->Fill( x[nruns] );
    if(cell[nruns].Contains('B')) hFill[1]->Fill( x[nruns] );
    if(cell[nruns].Contains('C')) hFill[2]->Fill( x[nruns] );
    if(cell[nruns].Contains('D')) hFill[3]->Fill( x[nruns] );
    if(cell[nruns].Contains('E')) hFill[4]->Fill( x[nruns] );
    if(cell[nruns].Contains('F')) hFill[5]->Fill( x[nruns] );
    if(cell[nruns].Contains('G')) hFill[6]->Fill( x[nruns] );
    if(cell[nruns].Contains('H')) hFill[7]->Fill( x[nruns] );
    if(cell[nruns].Contains('I')) hFill[8]->Fill( x[nruns] );
    if(cell[nruns].Contains('J')) hFill[9]->Fill( x[nruns] );
    nruns++;
  }

  TGraph *grX = new TGraph(nruns,run,x);
  TGraph *grY = new TGraph(nruns,run,y);

  new TCanvas();
  grX->Draw("A*");

  new TCanvas();
  grY->Draw("A*");

  TCanvas *main = new TCanvas();
  main->Divide(4,3);
  for(int i=0; i!=10; ++i) {
    main->cd(i+1);
    hFill[i]->Draw();
  }

  return 0;
}
