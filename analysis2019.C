
// =====================================================================================

void analysis2019(unsigned fnum=1194)
{
  FNAL4ALL *fnal4all = new FNAL4ALL();
  //fnal4all->SetStat(30000);
  fnal4all->IgnoreTriggerCountMismatch();
  //fnal4all->RemapDreamEvents();

  //fnal4all->SetRcdaqFileNameMask("/direct/eic+u/perez/mpgdMar2019/data/beam/beam-%08d-0000.evt");
  //fnal4all->SetDreamFileNameMask("/direct/eic+u/perez/mpgdMar2019/data/fdf.merged/Ftbf_dream-%08d-merged.root");
  //fnal4all->SetSiliconFileNameMask("/direct/eic+u/perez/mpgdMar2019/data/SILICON/Converted/Run%d_Converted.root");
  //fnal4all->SetSiliconFileNameMask("/gpfs/mnt/gpfs02/eic/TEST.RUNS/2019-03-FNAL/DATA/Converted/v01/Run%d_Converted.root");
  // ------------------------------
  fnal4all->SetRcdaqFileNameMask("/eic/data/T1429/fnal/beam/beam-%08d-0000.evt");
  fnal4all->SetDreamFileNameMask("/eic/data/T1429/fnal/fdf.merged/Ftbf_dream-%08d-merged.root");
  //fnal4all->SetSiliconFileNameMask("/eic/data/T1429/fnal/SILICON/Converted/Run%d_Converted.root");
  fnal4all->SetSiliconFileNameMask("/gpfs/mnt/gpfs02/eic/TEST.RUNS/2019-03-FNAL/DATA/Converted/v01/Run%d_Converted.root");

  fnal4all->ExtractBeamSpotAndChamberTags(fnum);
  //fnal4all->SetTimingWindow("D1", 1, 4);
  //fnal4all->SetThreshold   ("G2", 70);
  //fnal4all->RequestEventHistograms("G2");

  //fnal4all->SetTimingWindow("M1", 0, 6);
  //fnal4all->SetTimingWindow("M2", 0, 6);
  //fnal4all->SetTimingWindow("M3", 0, 6);


  fnal4all->DoAnalysis(fnum);
  //fnal4all->DoAnalysis(fnum,"D1");
  exit(0);
} // analysis2019()
