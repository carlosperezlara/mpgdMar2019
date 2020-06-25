int bigtable() {
	const int max = 1000;

	ifstream rf[8];
	int     nnn[8];
	double  tgx[8][max];
	double  tdx[8][max];
	int     trn[8][max];
	TString tcl[8][max];
	double  tpi[8][max];
	double  tyb[8][max];
	double  tst[8][max];

	for(int i=0; i!=8; ++i) {
		rf[i].open( Form("D%d.csv",i+1) );
		nnn[i] = 0;
		for(;nnn[i]!=max;++nnn[i]) {
			rf[i] >> tgx[i][nnn[i]];
			if(!rf[i].good()) break;
			rf[i] >> tdx[i][nnn[i]];
			rf[i] >> tdx[i][nnn[i]];
			rf[i] >> tdx[i][nnn[i]];
			rf[i] >> tdx[i][nnn[i]];
			rf[i] >> trn[i][nnn[i]];
			rf[i] >> tcl[i][nnn[i]];
			rf[i] >> tpi[i][nnn[i]];
			rf[i] >> tyb[i][nnn[i]];
			rf[i] >> tst[i][nnn[i]];
		}
		rf[i].close();
		cout << " * Board" << i << " runs found " << nnn[i] << endl;
	}

	int thisrun;
	ifstream runs("runs.dat.good");
	ofstream fout("all.csv");
	int nruns=0;
	for(; nruns!=max; ++nruns) {
		runs >> thisrun;
		if(!runs.good()) break;
		fout << thisrun << " ";
		for(int bd=0; bd!=8; ++bd) {
			int idx=0;
			for(;idx!=nnn[bd];++idx) {
				if(trn[bd][idx]==thisrun) break;
			}
			if(idx==nnn[bd]) {
				fout << 0 << " " << 0 << " " << 0 << " " << 0 << " ";
				fout << 0 << " " << 0 << " " << 0 << " ";
			} else {
				fout << trn[bd][idx] << " " << Form("%.2f",tgx[bd][idx]) << " " << Form("%.0f",tdx[bd][idx]) << " " << tcl[bd][idx] << " ";
				fout << Form("%.2f",tpi[bd][idx]) << " " << Form("%.2f",tyb[bd][idx]) << " " << Form("%.0f",tst[bd][idx]) << " ";
			}
		}
		fout << endl;
	}
	cout << "runs found " << nruns << endl;
	fout.close();
	return 0;
}
