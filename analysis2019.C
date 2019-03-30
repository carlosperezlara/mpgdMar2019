
// =====================================================================================

void analysis2019(unsigned from=1194, unsigned to = -1)
{
  FNAL4ALL *fnal4all = new FNAL4ALL();
  fnal4all->SetStat(30000);
  fnal4all->IgnoreTriggerCountMismatch();

  //fnal4all->RemapDreamEvents();

  //fnal4all->SetTimingWindow("D1", 1, 4);
  //fnal4all->SetThreshold   ("G2", 70);
  //fnal4all->RequestEventHistograms("G2");

  //fnal4all->SetTimingWindow("M1", 0, 6);
  //fnal4all->SetTimingWindow("M2", 0, 6);
  //fnal4all->SetTimingWindow("M3", 0, 6);
    
  fnal4all->SetRcdaqFileNameMask("/home/eic/T1429/2019-03/DATA/beam/beam-%08d-0000.evt");
  fnal4all->SetDreamFileNameMask("/data/eic/fnal_2019/fdf.merged/Ftbf_dream-%08d-merged.root");
  fnal4all->SetSiliconFileNameMask("/home/eic/T1429/2019-03/DATA/SILICON/Converted/Run%d_Converted.root");
  // ------------------------------
  for(unsigned fn=from; fn<=(to == -1 ? from : to); fn++) {
    fnal4all->DoAnalysis(fn);
  }
  exit(0);
} // analysis2019()

// =====================================================================================
