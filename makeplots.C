TString thisfile;
vector<Int_t> arun[10][10];
vector<TString> scell[10][10];
vector<Double_t> axp[10][10];
vector<Double_t> ayb[10][10];
vector<Int_t> ast[10][10];
vector<Double_t> ares1[10][10];
vector<Double_t> ares2[10][10];
vector<Double_t> ares3[10][10];
vector<Double_t> ares4[10][10];

void FindCoord(TString cell, int &row, int &col) {
  TString srow = cell[1];
  char ccol = cell[0];
  char mask[10]={'A','B','C','D','E',
		 'F','G','H','I','J'};
  row = srow.Atoi();
  for(int i=0; i!=10; ++i) {
    if(ccol==mask[i]) {
      col = i;
      break;
    }
  }
}

TCanvas* makeFixXPYB( Double_t fixxp = 2.0, Double_t fixyb = 0.5) {//Double_t fixyb = 0.8;
  Int_t    fixxp_n = 0;
  Double_t fixxp_x_st[1000];
  Double_t fixxp_y_r1[1000];
  Double_t fixxp_y_r2[1000];
  Double_t fixxp_y_r3[1000];
  Double_t fixxp_y_r4[1000];
  TString fixxp_lab[1000];
  for(int r=0; r!=10; ++r) {
    for(int c=0; c!=10; ++c) {
      if(scell[r][c].size()<1) continue;
      for(uint l=0; l!=scell[r][c].size(); ++l) {
	if(ares1[r][c][l]<5) continue;
	cout << endl;
	cout << "XP " << Form("%1.3f",axp[r][c][l]);
	cout << "; YB " << Form("%6.1f",ayb[r][c][l]);
	cout << "; ST " << Form("%03d",ast[r][c][l]);
	cout << "; R1 " << ares1[r][c][l];
	cout << "; R2 " << ares2[r][c][l];
	cout << "; R3 " << ares3[r][c][l];
	cout << "; R4 " << ares4[r][c][l];
	if(!TMath::AreEqualAbs( axp[r][c][l], fixxp, 0.01 )) continue;
	if(!TMath::AreEqualAbs( ayb[r][c][l], fixyb, 0.05 )) continue;
	cout << " [GOOD] ";
	//cout << ares1[r][c][l] << " " << ares2[r][c][l] << " " << ares3[r][c][l] << " " << ares4[r][c][l] << endl;
	fixxp_x_st[ fixxp_n ] = ast[r][c][l];
	fixxp_y_r1[ fixxp_n ] = ares1[r][c][l];
	fixxp_y_r2[ fixxp_n ] = ares2[r][c][l];
	fixxp_y_r3[ fixxp_n ] = ares3[r][c][l];
	fixxp_y_r4[ fixxp_n ] = ares4[r][c][l];
	fixxp_lab[ fixxp_n ] = Form("%d_%s",arun[r][c][l],scell[r][c][l].Data());
	fixxp_n++;
      }
    }
  }

  cout << endl << fixxp_n << " points" << endl;
  TCanvas *main1 = new TCanvas();
  if(fixxp_n<1) return NULL; 

  TGraph *gres1 = new TGraph(fixxp_n,fixxp_x_st,fixxp_y_r1);
  TGraph *gres2 = new TGraph(fixxp_n,fixxp_x_st,fixxp_y_r2);
  TGraph *gres3 = new TGraph(fixxp_n,fixxp_x_st,fixxp_y_r3);
  TGraph *gres4 = new TGraph(fixxp_n,fixxp_x_st,fixxp_y_r4);
  gres1->SetMarkerStyle(20); gres1->SetMarkerColor(kBlue-3);
  gres2->SetMarkerStyle(20); gres2->SetMarkerColor(kRed-3);
  gres3->SetMarkerStyle(20); gres3->SetMarkerColor(kGreen-3);
  gres4->SetMarkerStyle(20); gres4->SetMarkerColor(kBlue-3);

  TH2D *axisST = new TH2D("axisST",";X  Stretch  [%];Resolution  [um]",
			  100,-30.0,+30.0,100,0.0,200.0);

  axisST->Draw();
  gres1->Draw("PSAME");
  gres2->Draw("PSAME");
  gres3->Draw("PSAME");
  //gres4->Draw("PSAME");

  TLegend *leg = new TLegend(0.4,0.7,0.6,0.9);
  leg->AddEntry(gres1,"NC");
  leg->AddEntry(gres2,"XC");
  leg->AddEntry(gres3,"XYC");
  leg->Draw();

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.04);
  tex->DrawTextNDC(0.65,0.85,thisfile.Data());
  tex->DrawTextNDC(0.65,0.80,Form("XP = %f",fixxp));
  tex->DrawTextNDC(0.65,0.75,Form("YB = %f",fixyb));

  tex->SetTextSize(0.02);
  double xoff = 0.5;
  for(int i=0; i!=fixxp_n; ++i) {
    tex->SetTextColor( kBlue-3 );
    tex->DrawText(fixxp_x_st[i]+xoff,fixxp_y_r1[i],fixxp_lab[i]);
    tex->SetTextColor( kRed-3 );
    tex->DrawText(fixxp_x_st[i]+xoff,fixxp_y_r2[i],fixxp_lab[i]);
    tex->SetTextColor( kGreen-3 );
    tex->DrawText(fixxp_x_st[i]+xoff,fixxp_y_r3[i],fixxp_lab[i]);
  }

  return main1;
}


//int makeplots(TString file = "GEM_B00e_INST01") {
int makeplots(TString file = "GEM_V00a_D1_I0") {
//int makeplots(TString file = "uRW_B01a_INST02") {
//int makeplots(TString file = "MM_B01a_INST34") {
//int makeplots(TString file = "MM_Z03k.A_INST02.4") {
  thisfile = file;
  gStyle->SetOptStat(0);
  TString myfile = file(0,file.Last('I')-4);
  cout << myfile.Data() << endl;

  ifstream fin(Form("%s.txt4",file.Data()));
  TString cell;
  double xmin, xmax, ymin, ymax, xp, yb;
  int run, det, st;
  int n = 0;
  for(;;++n) {
    fin >> cell >> xmin >> xmax >> ymin >> ymax >> run >> det >> xp >> yb >> st;
    if(!fin.good()) {
      cout << "BROKE AT " << cell.Data() << " " << run << endl;
      break;
    }
    int row, col;
    FindCoord(cell,row,col);
    //cout << cell.Data() << " R:" << row << " C:" << col << endl;
    arun[row][col].push_back( run );
    scell[row][col].push_back( cell.Data() );
    axp[row][col].push_back( xp );
    ayb[row][col].push_back( yb );
    ast[row][col].push_back( st );
    TString sres1 = Form("res/D%d/data/reso_%s_run%d.dat",det,myfile.Data(),run);
    //cout << sres1.Data() << endl;
    ifstream fres1(sres1.Data());
    float mean;
    Double_t dres1=0, dres2=0, dres3=0, dres4=0;
    fres1 >> mean >> dres1 >> dres2 >> dres3 >> dres4;
    fres1.close();
    //cout << dres1 << " " << dres2 << " " << dres3 << " " << dres4 << endl;
    ares1[row][col].push_back( dres1 );
    ares2[row][col].push_back( dres2 );
    ares3[row][col].push_back( dres3 );
    ares4[row][col].push_back( dres4 );
  }
  cout << "lines " << n << endl;

  TCanvas *xy1 = makeFixXPYB(2.0,1.0);
  TCanvas *xy2 = makeFixXPYB(2.0,0.77);
  TCanvas *xy3 = makeFixXPYB(2.0,0.5);
  TCanvas *xy4 = makeFixXPYB(2.0,0.4);
  TCanvas *xy5 = makeFixXPYB(2.0,0.3);

  if(xy1) {
    xy1->Draw();
    xy1->SaveAs( Form("XPYB1_%s.pdf",file.Data()) );
  }
  if(xy2) {
    xy2->Draw();
    xy2->SaveAs( Form("XPYB2_%s.pdf",file.Data()) );
  }
  if(xy3) {
    xy3->Draw();
    xy3->SaveAs( Form("XPYB3_%s.pdf",file.Data()) );
  }
  if(xy4) {
    xy4->Draw();
    xy4->SaveAs( Form("XPYB4_%s.pdf",file.Data()) );
  }
  if(xy5) {
    xy5->Draw();
    xy5->SaveAs( Form("XPYB5_%s.pdf",file.Data()) );
  }

  return 0;
}

