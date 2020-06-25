#include "bad.C"

bool filterKeyRuns(int run) {
	if(run==1173) return true; // 0% 2.00
	if(run==1113) return true; // 0% 0.83
	if(run==1175) return true; // 0% 1.25

	if(run==1152) return true; // 10% 1.67
	if(run==1163) return true; // 10% 2.00
	if(run==1153) return true; // 10% 1.25

	if(run==1161) return true; // 5% 2.00
	if(run==1164) return true; // 5% 1.67
	if(run==1165) return true; // 5% 1.25
	if(run==1115) return true; // 5% 0.83
	//if(run==1268) return true; // 5% 1.00

	if(run==1399) return true; // st 1.00
	if(run==1136) return true; // st 0.83
	if(run==1154) return true; // st 1.00
	return false;
}

int D3_uRW_B01a_XP() {
	fillboardbad();
	gStyle->SetOptStat(0);
	const int max = 1000;
	const double maxY = 150;
	ifstream rf[8];
	int     nnn[8];
	double  tgx[8][max];
	double  tdx[8][max];
	double  tdxC[8][max];
	int     trn[8][max];
	TString tcl[8][max];
	double  tpi[8][max];
	double  tyb[8][max];
	double  tst[8][max];
	TString tte[8][max];
	TString tty[8][max];
	double  twi[8][max];
	double  tam[8][max];
	double  ten[8][max];

	for(int i=0; i!=8; ++i) {
		rf[i].open( Form("D%d.csv",i+1) );
		nnn[i] = 0;
		for(;nnn[i]!=max;++nnn[i]) {
			rf[i] >> tgx[i][nnn[i]];
			if(!rf[i].good()) break;
			rf[i] >> tdx[i][nnn[i]];
			rf[i] >> tdxC[i][nnn[i]];
			rf[i] >> tdxC[i][nnn[i]];
			rf[i] >> tdxC[i][nnn[i]];
			rf[i] >> trn[i][nnn[i]];
			rf[i] >> tcl[i][nnn[i]];
			rf[i] >> tpi[i][nnn[i]];
			rf[i] >> tyb[i][nnn[i]];
			rf[i] >> tst[i][nnn[i]];
			rf[i] >> tte[i][nnn[i]];
			rf[i] >> tty[i][nnn[i]];
			rf[i] >> twi[i][nnn[i]];
			rf[i] >> tam[i][nnn[i]];
			rf[i] >> ten[i][nnn[i]];
		}
		rf[i].close();
		cout << " * Board" << i << " runs found " << nnn[i] << endl;
	}

	int n[5];
	double xxx[5][100];
	double yyy[5][100];
	double yyyC[5][100];
	TGraph *gr[5];
	TGraph *grC[5];
	TF1 *fit[5];
	int color[5] = {kRed-3, kBlue-3, kGreen-3, kOrange-3, kCyan-3};
	int cut1[5] = {0,40,40,40,40};
	int cut2[5] = {0,0,5,10,20};

	for(int id=0; id!=4; ++id) {
		int bd=2;
		n[id] = 0;
		for(int idx=0;idx!=nnn[bd];++idx) {
			if( (tyb[bd][idx]==cut1[id])
				&&
				(tst[bd][idx]==cut2[id])
				&&
				(ten[bd][idx]>2000)
				&&
				(tdx[bd][idx]<maxY)
				) {
				if(!goodrun(trn[bd][idx],bd)) continue;
				if(!filterKeyRuns(trn[bd][idx])) continue;
				xxx[id][n[id]] = tpi[bd][idx];
				yyy[id][n[id]] = tdx[bd][idx];
				yyyC[id][n[id]] = tdxC[bd][idx];
				n[id]++;
				cout << "    ";
				cout << "CELL " << tcl[bd][idx].Data() << "  ";
				cout << "XP " << Form("%.2f",tpi[bd][idx]) << "  ";
				cout << "YB " << Form("%.2f",tyb[bd][idx]) << "  ";
				cout << "ST " << Form("%.0f",tst[bd][idx]) << "  ";
				cout << "RES " << Form("%4.0f",tdx[bd][idx]) << "  ";
				cout << "RESC " << Form("%4.0f",tdxC[bd][idx]) << "  ";
				cout << "WID " << Form("%.1f",twi[bd][idx]) << "  ";
				cout << "AMP " << Form("%.0f",tam[bd][idx]) << "  ";
				cout << "ENT " << Form("%.0f",ten[bd][idx]) << "  ";
				cout << "resolution_" << tty[bd][idx];
				cout << "_D" << bd+1 << "_" << tcl[bd][idx];
				cout << "_" << trn[bd][idx] << ".pdf" << endl;
			}
		}
		cout << " Point assigned to graphic " << id << ": " << n[id] << endl;
		gr[id] = new TGraph(n[id],xxx[id],yyy[id]);
		gr[id]->SetMarkerColor(color[id]);
		gr[id]->SetLineColor(color[id]);
		gr[id]->SetMarkerSize(1.5);
		gr[id]->SetMarkerStyle(20);
		grC[id] = new TGraph(n[id],xxx[id],yyyC[id]);
		grC[id]->SetMarkerColor(color[id]);
		grC[id]->SetMarkerSize(1.5);
		grC[id]->SetMarkerStyle(24);
		fit[id] = new TF1( Form("fit%d",id), "[0]+[1]*x+[2]*x*x" );
		fit[id]->SetLineColor(color[id]);
	}


	TH2D *axis = new TH2D("axis",";xpitch  (mm);resolution  (um)",100,0.5,2.25,100,0,maxY);
	axis->Draw();
	gr[0]->Fit(fit[0],"Q");
	gr[1]->Fit(fit[1],"Q");
    gr[2]->Fit(fit[2],"Q");
    //gr[3]->Fit(fit[3],"Q");
	gr[0]->Draw("PSAME");
	gr[1]->Draw("PSAME");
    gr[2]->Draw("PSAME");
    gr[3]->Draw("PSAME");
	//grC[0]->Draw("PSAME");
	//grC[1]->Draw("PSAME");
    //grC[2]->Draw("PSAME");
    //grC[3]->Draw("PSAME");
	TGraph *dummy = new TGraph();
	dummy->SetMarkerColor(kBlack);
	dummy->SetMarkerStyle(24);
	dummy->SetMarkerSize(1.5);
	dummy->SetLineWidth(0);	TLegend *leg = new TLegend(0.15,0.70,0.33,0.87);
	leg->AddEntry( gr[0], "Straight" );
	leg->AddEntry( gr[1], "yb=40 ; st=0" );
    leg->AddEntry( gr[2], "yb=40 ; st=5" );
    leg->AddEntry( gr[3], "yb=40 ; st=10" );
	//leg->AddEntry( dummy, "NL corrected" );
	leg->Draw();

	return 0;
}
