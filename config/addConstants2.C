int addConstants2(int iDet=1) {
  int   minrun[9]  = { 1080, 1209, 1250, 1291, 1465, 1619, 1637, 1733, 2000};
  float offsetx[8] = {-13.0,-13.0,-13.0,-15.0,-15.0,-15.0,-15.0,-15.0};
  float offsety[8] = {-23.0,-23.0,-23.0,-23.0,-23.0,-23.0,-23.0,-23.0};
  ifstream fin;
  ofstream fou;
  Int_t run;
  float bx, by, bz, ang;
  {
    int i = iDet;
    fin.open( Form("D%d.beamnew_off",i) );
    Int_t nruns=0;
    Int_t runrun[1000];
    Double_t offrunx[1000];
    Double_t offruny[1000];
    for(;;) {
      fin >> run >> run >> bx >> by >> bz >> ang;
      if(!fin.good()) break;
      runrun[nruns] = run;
      offrunx[nruns] = 0;
      offruny[nruns] = 0;
      for(int j=0; j!=9; ++j) {
	if( run>=minrun[j]&&run<minrun[j+1] ) {
	  offrunx[nruns] = offsetx[j]-bx;
	  offruny[nruns] = offsety[j]-by;
	  break;
	}
      }
      nruns++;
    }
    cout << nruns << endl;
    fin.close();
    float bxMin, bxMax, byMin, byMax;
    fin.open( Form("fiducial.D%d.dat.ori", i ) );
    fou.open( Form("fiducial.D%d.dat.new2",i ) );
    for(;;) {
      fin >> run >> bxMin >> bxMax >> byMin >> byMax;
      if(!fin.good()) break;
      float offx = 0;
      float offy = 0;
      //cout << run << " ";
      for(int j=0; j!=nruns; ++j) {
	if( run==runrun[j] ) {
	  offx = offrunx[j];
	  offy = offruny[j];
	  //cout << "FOUND";
	  break;
	}
      }
      //cout << " " << offx << " " << offy << endl;
      fou << run;
      fou << Form("   %+.1f   %+.1f   %+.1f   %+.1f\n",
		  bxMin+offx, bxMax+offx,
		  byMin+offy, byMax+offy);
    }
    fin.close();
    fou.close();
  }
  return 0;
}
