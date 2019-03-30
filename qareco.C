
TTree *tree;

void qareco(unsigned fnum=1437, int detO = -1)
{
  gSystem->Load("libfnal4all.so");

  char fname[1024];
  sprintf(fname, "./rootfiles/fnal-%05d.root", fnum);
  TFile *ff = new TFile(fname);

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.1);
  TCanvas *main = new TCanvas();
  main->Divide(3,2);

  main->SaveAs( Form("qareco_%d.pdf[",fnum), "pdf");
  for(int i=0; i!=8; ++i) {
    if(detO>-1) {
      if(detO!=i) continue;
    }
    TString det = Form("D%d",i+1);
    cout << det.Data() << endl;
    //=====
    TH1D *noise = (TH1D*) ff->Get( Form("Noise%s",det.Data()) );
    TH1D *qbin = (TH1D*) ff->Get( Form("Qbin%s",det.Data()) );
    TH1D *qstrip = (TH1D*) ff->Get( Form("Qstrip%s",det.Data()) );
    TH1D *stripmap = (TH1D*) ff->Get( Form("StripMap%s",det.Data()) );
    TH1D *qcluster = (TH1D*) ff->Get( Form("Qcluster%s",det.Data()) );
    TH1D *timing = (TH1D*) ff->Get( Form("Timing%s",det.Data()) );
    //====
    main->cd(1); noise->Draw();
    main->cd(2); qbin->Draw();
    main->cd(3); qstrip->Draw();
    main->cd(4); stripmap->Draw();
    main->cd(5); qcluster->Draw();
    main->cd(6); timing->Draw();
    //====
    main->SaveAs( Form("qareco_%d.pdf",fnum), "pdf");
  }
  main->SaveAs( Form("qareco_%d.pdf]",fnum), "pdf");
} // plot2019()
