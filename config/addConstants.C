int addConstants() {
  int   minrun[10] = {1080,1209,1250,1291,1355,1465,1619,1637,1733,2000};
  float offset[9] = { 2.0, 2.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.0, 0.0};
  ifstream fin;
  ofstream fou;
  int run;
  float bx, by, bz, ang;
  for(int i=1; i!=9; ++i) {
    fin.open( Form("D%d.beamnew",i) );
    fou.open( Form("D%d.beamnew_off",i) );
    for(;;) {
      fin >> run >> run >> bx >> by >> bz >> ang;
      if(!fin.good()) break;
      float off = 0;
      for(int j=0; j!=9; ++j) {
	if( run>=minrun[j]&&run<minrun[j+1] ) {
	  off = offset[j];
	  break;
	}
      }
      //cout << run << " " << off << endl;
      fou << " " << run << " " << run;
      fou << Form("  %.1f  %.1f  %.0f %.1f\n", bx-off, by, bz, ang);
    }
    fin.close();
    fou.close();
  }
  return 0;
}
