vector<int> boardbad[8];

void fillboardbad() {
	boardbad[0].push_back(1415);
	boardbad[1].push_back(1385);
	boardbad[1].push_back(1382);
	boardbad[1].push_back(1361);
	boardbad[1].push_back(1262);
	boardbad[1].push_back(1374);
	boardbad[1].push_back(1370);
	boardbad[1].push_back(1351);
	boardbad[1].push_back(1392);
	boardbad[2].push_back(1137);
	boardbad[2].push_back(1155);
	boardbad[2].push_back(1111);
	boardbad[2].push_back(1112);
	boardbad[2].push_back(1176);
	boardbad[2].push_back(1255);
	boardbad[2].push_back(1256);
	boardbad[2].push_back(1221);
	boardbad[2].push_back(1253);
	boardbad[2].push_back(1258);
	boardbad[2].push_back(1218);
	boardbad[2].push_back(1220);
	boardbad[2].push_back(1254);
	boardbad[2].push_back(1167);
	boardbad[2].push_back(1223);
	boardbad[2].push_back(1116);
	boardbad[2].push_back(1166);
	boardbad[2].push_back(1118);
	boardbad[2].push_back(1119);
	boardbad[3].push_back(1131);
	boardbad[3].push_back(1388);
	boardbad[3].push_back(1531);
	boardbad[3].push_back(1318);
	boardbad[4].push_back(1532);
	boardbad[4].push_back(1517);
	return;
}

bool goodrun(int run, int bd, int opt=0) {
	if(run>1618) return false;
	if((bd==0)&&(run>1464)) return false;
	if((bd==1)&&(run<1209)) return false;
	if((bd==2)&&(run>1291)&&(run<1464)) return false;
	if((bd==3)&&(run<1291)) return false;
	if((bd==3)&&(run>1618)) return false;
	if(bd==4) {
		if(opt==0) {
			if((run>1292)&&(run<1465)) return false;
		}
		if(opt==1) {
			if((run<1292)||(run>1465)) return false;
		}
	}
	for(uint i=0; i!=boardbad[bd].size(); ++i) {
		if( boardbad[bd][i]==run )	return false;
	}
	return true;
};
