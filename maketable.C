void FindCoord(TString cell, int &row, int &col) {
  TString srow = cell[1];
  char ccol = cell[0];
  char mask[10]={'A','B','C','D','E',
		 'F','G','H','I','J'};
  row = srow.Atoi();
  for(int i=0; i!=10; ++i) {
    if(ccol==mask[i]) {
      col = i;
      break;
    }
  }
}

int maketable(TString file = "GEM_V00a_D8_I0") {
  TString myfile = file(0,file.Last('I')-4);
  cout << myfile.Data() << endl;

  ifstream fin(Form("%s.txt4",file.Data()));
  TString cell;
  double xmin, xmax, ymin, ymax, xp, yb;
  int run, det, st;
  int n = 0;
  vector<TString> data[10][10];
  vector<TString> scell[10][10];
  vector<TString> specs[10][10];
  vector<TString> xcuts[10][10];
  vector<TString> ycuts[10][10];
  vector<TString> link[10][10];
  vector<TString> rmea[10][10];
  vector<TString> res1[10][10];
  vector<TString> res2[10][10];
  vector<TString> res3[10][10];
  vector<TString> res4[10][10];
  vector<TString> pdf_fiducial[10][10];

  for(;;++n) {
    fin >> cell >> xmin >> xmax >> ymin >> ymax >> run >> det >> xp >> yb >> st;
    if(!fin.good()) {
      cout << "BROKE AT " << cell.Data() << " " << run << endl;
      break;
    }
    if(xmin>xmax) continue;
    int row, col;
    FindCoord(cell,row,col);
    cout << cell.Data() << " R:" << row << " C:" << col << endl;
    data[row][col].push_back( Form("%d %d | %.1f %.1f | %.1f %.1f | %.3f %.3f %d",
				   run,det,xmin,xmax,ymin,ymax,xp,yb,st) );
    scell[row][col].push_back( cell.Data() );
    specs[row][col].push_back( Form("%.1f %.1f %d",xp,yb,st) );
    xcuts[row][col].push_back( Form("%+3.1f %+3.1f",xmin,xmax) );
    ycuts[row][col].push_back( Form("%+3.1f %+3.1f",ymin,ymax) );
    link[row][col].push_back( Form("%d_%d",run,det) );
    pdf_fiducial[row][col].push_back( Form("res/D%d/FIDUCIAL_D%d_%d.pdf",det,det,run) );
    TString sres1 = Form("res/D%d/data/reso_%s_run%d.dat",det,myfile.Data(),run);
    //cout << sres1.Data() << endl;
    ifstream fres1(sres1.Data());
    float mean;
    float dres1=0, dres2=0, dres3=0, dres4=0;
    fres1 >> mean >> dres1 >> dres2 >> dres3 >> dres4;
    fres1.close();
    rmea[row][col].push_back( Form("%.1f",mean) );
    res1[row][col].push_back( Form("%.1f",dres1) );
    res2[row][col].push_back( Form("%.1f",dres2) );
    res3[row][col].push_back( Form("%.1f",dres3) );
    res4[row][col].push_back( Form("%.1f",dres4) );
  }
  cout << "lines " << n << endl;

  ofstream fout( Form("%s.html",file.Data()) );
  fout << "<!DOCTYPE html>" << endl;
  fout << "<html>" << endl;

  fout << "<style>" << endl;
  fout << "   table {" << endl;
  fout << "  font-family: arial, sans-serif;" << endl;
  //fout << "  font-size:8px;" << endl;
  fout << "  font-size:10px;" << endl;
  fout << "  border-collapse: collapse;" << endl;
  fout << " width: 100%;" << endl;
  fout << " }" << endl;

  fout << " td, th {" << endl;
  fout << " border: 1px solid #dddddd;" << endl;
  fout << "   text-align: left;" << endl;
  fout << " padding: 8px;" << endl;
  fout << " }" << endl;

  fout << " tr:nth-child(even) {" << endl;
  fout << "   background-color: #dddddd;" << endl;
  fout << " }" << endl;
  fout << "</style>" << endl;


  fout << "<body>" << endl;
  fout << "<table style=\"width:100%\">" << endl;
  fout << "<tr>" << endl;
  fout << "<td></td>" << endl;
  fout << "<td><h3>A</h3></td>" << endl;
  fout << "<td><h3>B</h3></td>" << endl;
  fout << "<td><h3>C</h3></td>" << endl;
  fout << "<td><h3>D</h3></td>" << endl;
  fout << "<td><h3>E</h3></td>" << endl;
  fout << "<td><h3>F</h3></td>" << endl;
  fout << "<td><h3>J</h3></td>" << endl;
  fout << "<td><h3>H</h3></td>" << endl;
  fout << "<td><h3>I</h3></td>" << endl;
  fout << "<td><h3>J</h3></td>" << endl;
  fout << "</tr>" << endl;  
  for(int r=9; r!=-1; --r) {
    fout << "<tr>" << endl;
    fout << "<td><h3>"<< Form("%d",r) << "</h3></td>" << endl;
    for(int c=0; c!=10; ++c) {
      fout << "<td>" << endl;
      cout << "**** COL " << c << " ROW " << r << endl;
      //fout << "**** COL " << c << " ROW " << r << endl;
      if(scell[r][c].size()<1) continue;
      bool foundone = false;
      for(uint l=0; l!=data[r][c].size(); ++l) {
	cout << data[r][c][l].Data() << endl;
	if(res1[r][c][l]=="0.0") continue;
	if(!foundone) {
	  fout << scell[r][c][0].Data() << "  ";
	  fout << specs[r][c][0].Data() << "<BR>";
	  foundone=true;
	}
	fout << "<a href=\"";
	fout << pdf_fiducial[r][c][l].Data() << "\">";
	fout << link[r][c][l].Data() << "</a> : ";
	//fout << rmea[r][c][l].Data() << "|";
	//==
	fout << "<font color=\"red\">";
	fout << res1[r][c][l].Data();
	fout << "</font> ";
	//==
	fout << "<font color=\"green\">";
	fout << res2[r][c][l].Data();
	fout << "</font> ";
	//==
	//fout << "<font color=\"green\">";
	//fout << res3[r][c][l].Data();
	//fout << "</font> ";
	//==
	fout << "<font color=\"blue\">";
	fout << res4[r][c][l].Data();
	fout << "</font>";
	//==
	fout << "<BR>|";
	fout << xcuts[r][c][l].Data() << "|";
	fout << ycuts[r][c][l].Data() << "|";
	fout << "<BR>" << endl;
	
      }
      fout << "</td>" << endl;
    }
    fout << "</tr>" << endl;
  }
  fout << "</body>" << endl;
  fout << "</html>" << endl;
  fout.close();
  return 0;
}
