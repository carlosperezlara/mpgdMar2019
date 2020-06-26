int addConstants3(int iDet=1) {
  int   minrun[100];
  float offsetx[100];
  float offsety[100];
  int nrange=0;
  ifstream fin;
  ofstream fou;
  // read from allignment
  {
    float tmp;
    fin.open( Form("D%d.beamnew_off3",iDet)  );
    for(;;) {
      fin >> minrun[nrange] >> minrun[nrange+1] >> offsetx[nrange];
      fin >> offsety[nrange] >> tmp >> tmp;
      if(!fin.good()) break;
      nrange++;
    }
    fin.close();
    fin.open( Form("D%d.beamnew_off2",iDet)  );
    for(int i=0;i!=nrange;++i) {
      fin >> tmp >> tmp >> tmp;
      if(!fin.good()) break;
      offsetx[i] -= tmp;
      fin >> tmp;
      offsety[i] -= tmp;
      fin >> tmp >> tmp;
    }
    fin.close();

    cout << "Read " << nrange << " ranges" << endl;
  }

  {
    Int_t run;
    float bxMin, bxMax, byMin, byMax;
    fin.open( Form("fiducial.D%d.dat.new2", iDet ) );
    fou.open( Form("fiducial.D%d.dat.new3",iDet ) );
    for(;;) {
      fin >> run >> bxMin >> bxMax >> byMin >> byMax;
      if(!fin.good()) break;
      float offx = 0;
      float offy = 0;
      //cout << run << " ";
      for(int j=0; j!=nrange; ++j) {
	if( run>=minrun[j]&&run<minrun[j+1] ) {
	  offx = offsetx[j];
	  offy = offsety[j];
	  //cout << run << " " << offx << endl;
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
