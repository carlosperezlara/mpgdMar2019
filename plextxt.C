int plextxt(TString file = "MM_Z03k.A_INST0") {
  ifstream fin(Form("%s.txt",file.Data()));
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
    ofstream fout( Form("%s.%d.txt",file.Data(),det), std::ofstream::out | std::ofstream::app );
    fout << cell.Data() << " ";
    fout << xmin << " " << xmax << " ";
    fout << ymin << " " << ymax << " ";
    fout <<  run << " " <<  det << " ";
    fout << xp << " " << yb << " " << st << endl;
    fout.close();
  }
  cout << "lines " << n << endl;

  return 0;
}
