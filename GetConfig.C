Int_t fIndex;
Int_t fRun;
Int_t fDet;
Double_t fXPitch;
Double_t fYBeat;
Double_t fXStretch;
TString fCell;
TString fSDet;
TString fBoard;
TString fTech;
Double_t fGXmin=-10;
Double_t fGXmax=+10;
Double_t fGYmin=-10;
Double_t fGYmax=+10;
Double_t fChiMax = 2;

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

  fSDet = Form("D%d",fDet);

  double tdbl;
  int tint;
  fin.open("track/dat/chi2_stat.dat");
  for(;;) {
    fin >> tint;
    if(!fin.good()) {
      break;
    }
    if(tint==fRun) {
      fin >> fChiMax >> tdbl;
      fChiMax += 3*tdbl;
      break;
    } else {
      fin >> tdbl >> tdbl;
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
  for(;;) {
    fin >> cell >> fXPitch;
    if(!fin.good()) break;
    if(fCell.Contains(cell)) {
      break;
    }
  }
  fin.close();

  fin.open( Form("mapping/%s.dat",fBoard.Data()) );
  for(;;) {
    fin >> cell >> fXPitch >> fYBeat >> fXStretch;
    if(!fin.good()) break;
    if(fCell.Contains(cell)) {
      break;
    }
  }
  fin.close();

  fin.open( Form("config/fiducial.%s.dat",fSDet.Data()) );
  int run;
  double tmp1, tmp2, tmp3, tmp4;
  for(;;) {
    fin >> run >> tmp1 >> tmp2 >> tmp3 >> tmp4;
    if(!fin.good()) break;
    if(fRun==run) { // only if found replace
      fGXmin = tmp1;
      fGXmax = tmp2;
      fGYmin = tmp3;
      fGYmax = tmp4;
      break;
    }
  }
  fin.close();

  std::cout << "Index " << fIndex << endl;
  std::cout << "Run " << fRun << endl;
  std::cout << "Detector " << fDet << endl;
  std::cout << "Tech " << fTech.Data() << endl;
  std::cout << "Board " << fBoard << endl;
  std::cout << "Cell " << fCell << endl;
  std::cout << "XPitch " << fXPitch << endl;
  std::cout << "YBeat " << fYBeat << endl;
  std::cout << "XStretch " << fXStretch << endl;
  std::cout << "ChiMax " << fChiMax << endl;
  std::cout << "GXmin GXmax " << fGXmin << " " << fGXmax << endl;
  std::cout << "GYmin GYmax " << fGYmin << " " << fGYmax << endl;
}
