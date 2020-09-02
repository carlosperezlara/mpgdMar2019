int makeAlignment(int det=1,TString tag="Static4") {
  int runmin[100], runmax[100];
  double x[100], y[100], z[100], ang[100];
  int n=0, run;

  ifstream fin( Form("D%d_%s.txt",det,tag.Data()) );
  for(;;) {
    fin >> runmin[n] >> runmax[n] >> x[n] >> y[n] >> z[n] >> ang[n];
    if(!fin.good()) break;
    cout << runmin[n] << " " << runmax[n] << endl;
    n++;
  }
  fin.close();
  cout << "==>" << n << endl;

  ofstream fout( Form("D%d_%s.dep",det,tag.Data()) );
  fin.open("../elog/runs.dat.good");
  for(;;) {
    int m=0;
    fin >> run;
    if(!fin.good()) break;
    for(int i=0; i!=n; ++i) {
      if( (run>=runmin[i])&&(run<=runmax[i]) ) {
	m=i;
	//cout << "*****" << m << endl;
	break;
      }
    }
    double xxx = x[m];
    int drun = run - runmin[m];
    xxx += drun*1.0/100.0;
    fout << Form("%d %d %.1f %.1f %.1f %.1f\n",run,run,xxx,y[m],z[m],ang[m]);
  }
  fout.close();

  return 0;
}
