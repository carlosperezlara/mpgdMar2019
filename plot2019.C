
TTree *tree;

void plot2019(unsigned fnum=1437, int detO = -1)
{
  gSystem->Load("libfnal4all.so");

  char fname[1024];
  sprintf(fname, "./rootfiles/fnal-%05d.root", fnum);
  TFile *ff = new TFile(fname);
  tree = (TTree*)ff->Get("ZIGZAG");
  TLatex *tex = new TLatex();
  tex->SetTextSize(0.1);
  TCanvas *main = new TCanvas();
  main->Divide(4,4);

  ofstream finBXY( Form("logBXY/bxy_%d.dat",fnum) );
  ofstream finANG( Form("logANG/ang_%d.dat",fnum) );

  TF1 *bx = new TF1("bx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *by = new TF1("by","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *dx = new TF1("dx","[0]*TMath::Gaus(x,[1],[2])");
  TF1 *mxb = new TF1("mxb","[0]+[1]*x");
  Double_t sumbx=0;
  Double_t sumby=0;
  Int_t nbx=0;
  Int_t nby=0;
  main->SaveAs( Form("quicklook_%d.pdf[",fnum), "pdf");
  for(int i=0; i!=8; ++i) {
    if(detO>-1) {
      if(detO!=i) continue;
    }
    TString det = Form("D%d",i+1);
    cout << det.Data() << endl;
    //=====
    main->cd(1);              tree->Draw(Form("ok%s>>hist0_%d(3,-0.5,2.5)",det.Data(),i));
    main->cd(2)->SetLogy(1);  tree->Draw(Form("wd%s>>hist1_%d(27,-0.5,26.5)",det.Data(),i));
    main->cd(3)->SetLogy(1);  tree->Draw(Form("ampl%s>>hist2_%d(100,0,1e+5)",det.Data(),i));
    main->cd(4)->SetLogy(1);  tree->Draw(Form("max%s>>hist3_%d(100,0,4100)",det.Data(),i));
    //=====
    main->cd(5);  tree->Draw(Form("bx%s>>hist4_%d(100,-20,+20)",det.Data(),i));
    TH1D *hist4 = (TH1D*) gROOT->FindObject( Form("hist4_%d",i) );
    bx->SetParameter(1,hist4->GetMean());
    bx->SetParLimits(1,hist4->GetMean()-5,hist4->GetMean()+5);
    bx->SetParameter(2,hist4->GetRMS());
    bx->SetParLimits(2,0.001,2*hist4->GetRMS());
    hist4->Fit(bx);
    tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",bx->GetParameter(2),bx->GetParError(2)*100));
    tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",bx->GetParameter(1),bx->GetParError(1)*100));
    finBXY << bx->GetParameter(1) << " ";
    if( (det.Contains("D4")&&fnum<1292) || (det.Contains("D1")&&fnum>1465) ) {
      //ignore the rotated chambers                                                                                                    
    } else {
      sumbx += bx->GetParameter(1);
      nbx += 1;
    }
    //=====
    main->cd(6);  tree->Draw(Form("by%s>>hist5_%d(100,-20,+20)",det.Data(),i));
    TH1D *hist5 = (TH1D*) gROOT->FindObject( Form("hist5_%d",i) );
    by->SetParameter(1,hist5->GetMean());
    by->SetParLimits(1,hist5->GetMean()-5,hist5->GetMean()+5);
    by->SetParameter(2,hist5->GetRMS());
    by->SetParLimits(2,0.001,2*hist5->GetRMS());
    hist5->Fit(by);
    Double_t bysig = by->GetParameter(2);
    Double_t bymea = by->GetParameter(1);
    tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",by->GetParameter(2),by->GetParError(2)*100));
    tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",by->GetParameter(1),by->GetParError(1)*100));
    finBXY << by->GetParameter(1) << " ";
    if( (det.Contains("D4")&&fnum<1292) || (det.Contains("D1")&&fnum>1465) ) {
      //ignore the rotated chambers                                                                                                    
    } else {
      sumby += by->GetParameter(1);
      nby += 1;
    }
    //=====
    main->cd(7);  tree->Draw(Form("bx2mm%s>>hist6_%d",det.Data(),i));
    main->cd(8);  tree->Draw(Form("by2mm%s>>hist7_%d",det.Data(),i));
    main->cd(9);  tree->Draw(Form("bxpitch%s>>hist8_%d",det.Data(),i));
    main->cd(10); tree->Draw(Form("gxpitch%s>>hist9_%d(100,-1.1,+1.1)",det.Data(),i));
    main->cd(11); tree->Draw(Form("bybeat%s>>hist10_%d",det.Data(),i));
    main->cd(12)->SetLogy(1); tree->Draw(Form("gx%s>>hist11_%d(100,-50,+50)",det.Data(),i));
    TH1D *hist11 = (TH1D*) gROOT->FindObject( Form("hist11_%d",i) );
    Double_t gxmea = hist11->GetMean();
    Double_t gxsig = hist11->GetRMS();
    //=====
    main->cd(13); tree->Draw(Form("dx%s>>hist12_%d(100,-1,+1)",det.Data(),i));
    TH1D *hist12 = (TH1D*) gROOT->FindObject( Form("hist12_%d",i) );
    dx->SetParameter(1,hist12->GetMean());
    dx->SetParLimits(1,hist12->GetMean()-3,hist12->GetMean()+3);
    dx->SetParameter(2,hist12->GetRMS());
    dx->SetParLimits(2,0.001,2*hist12->GetRMS());
    hist12->Fit(dx);
    Double_t dxmea = dx->GetParameter(1);
    Double_t dxsig = dx->GetParameter(2);
    tex->DrawLatexNDC(0.5,0.4,Form("#sigma %.1f (%.0f)",dxsig*1e3,dx->GetParError(2)*1e5));
    tex->DrawLatexNDC(0.5,0.5,Form("#mu %.1f (%.0f)",dxmea*1e3,dx->GetParError(1)*1e5));
    //=====
    main->cd(14); tree->Draw(Form("dx3%s>>hist13_%d(100,-1,+1)",det.Data(),i));
    //=====
    TString var = Form("dx%s:by%s>>hist14_%d(1000,%f,%f,1000,%f,%f)",det.Data(),det.Data(),i,bymea-3*bysig,bymea+3*bysig,dxmea-3*dxsig,dxmea+3*dxsig);
    TString cut = Form("TMath::Abs(by%s+%f)<3*%f",det.Data(),-bymea,bysig);
    cout << cut.Data() << endl;
    main->cd(15); tree->Draw(Form(var.Data(),det.Data(),det.Data(),i),cut.Data(),"colz");
    TH2D *hist14 = (TH2D*) gROOT->FindObject( Form("hist14_%d",i) );
    TProfile *pro14 = hist14->ProfileX( Form("prof14_%d",i) );
    pro14->Draw("SAME");
    pro14->Fit(mxb,"R","", bymea-bysig, bymea+bysig );
    tex->DrawLatexNDC(0.2,0.2,Form("m %.4f +-%.4f",mxb->GetParameter(1),mxb->GetParError(1)));
    finANG << mxb->GetParameter(1) << " ";
    //=====
    var = Form("dx%s:gx%s>>hist15_%d(1000,%f,%f,1000,%f,%f)",det.Data(),det.Data(),i,gxmea-3*gxsig,gxmea+3*gxsig,dxmea-3*dxsig,dxmea+3*dxsig);
    cut = Form("TMath::Abs(by%s+%f)<3*%f",det.Data(),-bymea,bysig);
    cout << cut.Data() << endl;
    main->cd(16); tree->Draw(Form(var.Data(),det.Data(),det.Data(),i),cut.Data(),"colz");
    //TH2D *hist14 = (TH2D*) gROOT->FindObject( Form("hist14_%d",i) );
    //TProfile *pro14 = hist14->ProfileX( Form("prof14_%d",i) );
    //pro14->Draw("SAME");
    //pro14->Fit(mxb,"R","", bymea-bysig, bymea+bysig );
    //tex->DrawLatexNDC(0.2,0.2,Form("m %.4f +-%.4f",mxb->GetParameter(1),mxb->GetParError(1)));

    main->SaveAs( Form("quicklook_%d.pdf",fnum), "pdf");
  }
  finBXY << std::endl;
  finANG << std::endl;
  main->SaveAs( Form("quicklook_%d.pdf]",fnum), "pdf");

  cout << nbx << " " << nby << endl;
  if(nbx>0) {
    ofstream fangout( Form("logBXY/bxy_avg_%d.dat",fnum) );
    cout << sumbx/nbx << " " << sumby/nby << endl;
    fangout << sumbx/nbx << " " << sumby/nby  << endl;
    fangout.close();
  }

} // plot2019()
