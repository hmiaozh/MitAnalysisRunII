#!/bin/sh

export NSEL=$1;
export APPLYSCALING=$2;
export YEAR=$3;

if [ $NSEL == 'wz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWZ_'${YEAR}'_4.root","wz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|m_{ll}-m_{Z}|","GeV","done_ana/histoWZ_'${YEAR}'_9.root","wz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l W}","GeV","done_ana/histoWZ_'${YEAR}'_14.root","wz_wlpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"E_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_19.root","wz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{3l}","GeV","done_ana/histoWZ_'${YEAR}'_24.root","wz_m3l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1 Z}","GeV","done_ana/histoWZ_'${YEAR}'_29.root","wz_z1lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l2 Z}","GeV","done_ana/histoWZ_'${YEAR}'_34.root","wz_z2lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{T}","GeV","done_ana/histoWZ_'${YEAR}'_39.root","wz_mt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"E_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_44.root","wz_topsel_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoWZ_'${YEAR}'_49.root","wz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoWZ_'${YEAR}'_54.root","wz_topsel_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWZ_'${YEAR}'_59.root","wz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_64.root","wz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_69.root","wz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Cut evolution","","done_ana/histoWZ_'${YEAR}'_77.root","wz_cutevol",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{#gamma}","GeV","done_ana/histoWZ_'${YEAR}'_78.root","wzgsel_ptg",0,'${YEAR}',"",1,0,"WZ#gamma region",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"|#eta^{#gamma}","","done_ana/histoWZ_'${YEAR}'_79.root","wzgsel_etag",0,'${YEAR}',"",1,0,"WZ#gamma region",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{l#gamma}","GeV","done_ana/histoWZ_'${YEAR}'_80.root","wzgsel_mlg",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done_ana/histoZZ_'${YEAR}'_4.root","zz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done_ana/histoZZ_'${YEAR}'_9.root","zz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done_ana/histoZZ_'${YEAR}'_14.root","zz_mzmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{4l}","GeV","done_ana/histoZZ_'${YEAR}'_19.root","zz_m4l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z1}","GeV","done_ana/histoZZ_'${YEAR}'_24.root","zz_ptl1z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z1}","GeV","done_ana/histoZZ_'${YEAR}'_29.root","zz_ptl2z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z2}","GeV","done_ana/histoZZ_'${YEAR}'_34.root","zz_ptl1z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z2}","GeV","done_ana/histoZZ_'${YEAR}'_39.root","zz_ptl2z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"E_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_44.root","zz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoZZ_'${YEAR}'_49.root","zz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZZ_'${YEAR}'_54.root","zz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_59.root","zz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_64.root","zz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Cut evolution","","done_ana/histoZZ_'${YEAR}'_69.root","zz_cutevol",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zh' ]; then
  export sf_dy=1.0;
  hadd -f done_ana/histoZH_'${YEAR}'_0001.root done_ana/histoZH_'${YEAR}'_0.root   done_ana/histoZH_'${YEAR}'_1.root 
  hadd -f done_ana/histoZH_'${YEAR}'_0304.root done_ana/histoZH_'${YEAR}'_3.root   done_ana/histoZH_'${YEAR}'_4.root 
  hadd -f done_ana/histoZH_'${YEAR}'_0607.root done_ana/histoZH_'${YEAR}'_6.root   done_ana/histoZH_'${YEAR}'_7.root 
  hadd -f done_ana/histoZH_'${YEAR}'_0910.root done_ana/histoZH_'${YEAR}'_9.root  done_ana/histoZH_'${YEAR}'_10.root 
  hadd -f done_ana/histoZH_'${YEAR}'_1213.root done_ana/histoZH_'${YEAR}'_12.root done_ana/histoZH_'${YEAR}'_13.root 
  hadd -f done_ana/histoZH_'${YEAR}'_1516.root done_ana/histoZH_'${YEAR}'_15.root done_ana/histoZH_'${YEAR}'_16.root 
  hadd -f done_ana/histoZH_'${YEAR}'_1819.root done_ana/histoZH_'${YEAR}'_18.root done_ana/histoZH_'${YEAR}'_19.root 
  hadd -f done_ana/histoZH_'${YEAR}'_2122.root done_ana/histoZH_'${YEAR}'_21.root done_ana/histoZH_'${YEAR}'_22.root 
  hadd -f done_ana/histoZH_'${YEAR}'_2425.root done_ana/histoZH_'${YEAR}'_24.root done_ana/histoZH_'${YEAR}'_25.root 
  hadd -f done_ana/histoZH_'${YEAR}'_2728.root done_ana/histoZH_'${YEAR}'_27.root done_ana/histoZH_'${YEAR}'_28.root 
  hadd -f done_ana/histoZH_'${YEAR}'_3031.root done_ana/histoZH_'${YEAR}'_30.root done_ana/histoZH_'${YEAR}'_31.root 
  hadd -f done_ana/histoZH_'${YEAR}'_3334.root done_ana/histoZH_'${YEAR}'_33.root done_ana/histoZH_'${YEAR}'_34.root 
  hadd -f done_ana/histoZH_'${YEAR}'_3637.root done_ana/histoZH_'${YEAR}'_36.root done_ana/histoZH_'${YEAR}'_37.root 
  hadd -f done_ana/histoZH_'${YEAR}'_3940.root done_ana/histoZH_'${YEAR}'_39.root done_ana/histoZH_'${YEAR}'_40.root 
  hadd -f done_ana/histoZH_'${YEAR}'_4243.root done_ana/histoZH_'${YEAR}'_42.root done_ana/histoZH_'${YEAR}'_43.root 
  hadd -f done_ana/histoZH_'${YEAR}'_4546.root done_ana/histoZH_'${YEAR}'_45.root done_ana/histoZH_'${YEAR}'_46.root 
  hadd -f done_ana/histoZH_'${YEAR}'_4849.root done_ana/histoZH_'${YEAR}'_48.root done_ana/histoZH_'${YEAR}'_49.root 
  hadd -f done_ana/histoZH_'${YEAR}'_5152.root done_ana/histoZH_'${YEAR}'_51.root done_ana/histoZH_'${YEAR}'_52.root 
  hadd -f done_ana/histoZH_'${YEAR}'_5455.root done_ana/histoZH_'${YEAR}'_54.root done_ana/histoZH_'${YEAR}'_55.root 
  hadd -f done_ana/histoZH_'${YEAR}'_5758.root done_ana/histoZH_'${YEAR}'_57.root done_ana/histoZH_'${YEAR}'_58.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6061.root done_ana/histoZH_'${YEAR}'_60.root done_ana/histoZH_'${YEAR}'_61.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6364.root done_ana/histoZH_'${YEAR}'_63.root done_ana/histoZH_'${YEAR}'_64.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6667.root done_ana/histoZH_'${YEAR}'_66.root done_ana/histoZH_'${YEAR}'_67.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6970.root done_ana/histoZH_'${YEAR}'_69.root done_ana/histoZH_'${YEAR}'_70.root 
  hadd -f done_ana/histoZH_'${YEAR}'_7273.root done_ana/histoZH_'${YEAR}'_72.root done_ana/histoZH_'${YEAR}'_73.root 
  hadd -f done_ana/histoZH_'${YEAR}'_7576.root done_ana/histoZH_'${YEAR}'_75.root done_ana/histoZH_'${YEAR}'_76.root 
  hadd -f done_ana/histoZH_'${YEAR}'_7879.root done_ana/histoZH_'${YEAR}'_78.root done_ana/histoZH_'${YEAR}'_79.root 
  hadd -f done_ana/histoZH_'${YEAR}'_8182.root done_ana/histoZH_'${YEAR}'_81.root done_ana/histoZH_'${YEAR}'_82.root 

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_0001.root","zh_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0304.root","zh_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0607.root","zh_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0910.root","zh_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_1213.root","zh_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_1516.root","zh_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_1819.root","zh_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_2122.root","zh_zhselnminus1_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_2425.root","zh_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_2728.root","zh_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_3031.root","zh_zhselnminus1_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_3334.root","zh_zhselnminus1_ptll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_3637.root","zh_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_3940.root","zh_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_4243.root","zh_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_4546.root","zh_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_4849.root","zh_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_5152.root","zh_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_5455.root","zh_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_5758.root","zh_presel_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_6061.root","zh_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_6364.root","zh_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done_ana/histoZH_'${YEAR}'_6667.root","zh_presel_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #eta_{j}","","done_ana/histoZH_'${YEAR}'_6970.root","zh_nojetsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{jets}","","done_ana/histoZH_'${YEAR}'_7273.root","zh_nojetsel_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{central jets}","","done_ana/histoZH_'${YEAR}'_7576.root","zh_nojetsel_ncjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"No jet selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_7879.root","zh_nojetsel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_8182.root","zh_nojetsel_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_45.root","zhmm_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_46.root","zhee_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_47.root","zhem_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_48.root","zhmm_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_49.root","zhee_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_50.root","zhem_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_51.root","zhmm_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_52.root","zhee_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_53.root","zhem_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_54.root","zhmm_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_55.root","zhee_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_56.root","zhem_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_57.root","zhmm_presel_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_58.root","zhee_presel_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_59.root","zhem_presel_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_60.root","zhmm_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_61.root","zhee_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_62.root","zhem_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_63.root","zhmm_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_64.root","zhee_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_65.root","zhem_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done_ana/histoZH_'${YEAR}'_66.root","zhmm_presel_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done_ana/histoZH_'${YEAR}'_67.root","zhee_presel_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done_ana/histoZH_'${YEAR}'_68.root","zhem_presel_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #eta_{j}","","done_ana/histoZH_'${YEAR}'_69.root","zhmm_nojetsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #eta_{j}","","done_ana/histoZH_'${YEAR}'_70.root","zhee_nojetsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #eta_{j}","","done_ana/histoZH_'${YEAR}'_71.root","zhem_nojetsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{jets}","","done_ana/histoZH_'${YEAR}'_72.root","zhmm_nojetsel_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{jets}","","done_ana/histoZH_'${YEAR}'_73.root","zhee_nojetsel_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{jets}","","done_ana/histoZH_'${YEAR}'_74.root","zhem_nojetsel_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{central jets}","","done_ana/histoZH_'${YEAR}'_75.root","zhmm_nojetsel_ncjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{central jets}","","done_ana/histoZH_'${YEAR}'_76.root","zhee_nojetsel_ncjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{central jets}","","done_ana/histoZH_'${YEAR}'_77.root","zhem_nojetsel_ncjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"No jet selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_78.root","zhmm_nojetsel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"No jet selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_79.root","zhee_nojetsel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"No jet selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_80.root","zhem_nojetsel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_81.root","zhmm_nojetsel_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_82.root","zhee_nojetsel_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_83.root","zhem_nojetsel_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"E_{T}^{miss} X 4 regions","","done_ana/histoZH_'${YEAR}'_84.root","zh_card_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_0.root","zhmm_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_3.root","zhmm_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_6.root","zhmm_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_9.root","zhmm_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_12.root","zhmm_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_15.root","zhmm_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_18.root","zhmm_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_21.root","zhmm_zhselnminus1_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_24.root","zhmm_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_27.root","zhmm_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_30.root","zhmm_zhselnminus1_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_33.root","zhmm_zhselnminus1_ptll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_36.root","zhmm_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_39.root","zhmm_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_42.root","zhmm_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_1.root","zhee_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_4.root","zhee_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_7.root","zhee_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_10.root","zhee_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_13.root","zhee_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_16.root","zhee_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_19.root","zhee_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_22.root","zhee_zhselnminus1_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_25.root","zhee_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_28.root","zhee_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_31.root","zhee_zhselnminus1_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_34.root","zhee_zhselnminus1_ptll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_37.root","zhee_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_40.root","zhee_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_43.root","zhee_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_2.root","zhem_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_5.root","zhem_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_8.root","zhem_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_11.root","zhem_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_14.root","zhem_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_17.root","zhem_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_20.root","zhem_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_23.root","zhem_zhselnminus1_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_26.root","zhem_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_29.root","zhem_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_32.root","zhem_zhselnminus1_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_35.root","zhem_zhselnminus1_ptll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_38.root","zhem_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_41.root","zhem_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_44.root","zhem_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zhg' ]; then
  export sf_dy=1.0;
  hadd -f done_ana/histoZHG_'${YEAR}'_0001.root done_ana/histoZHG_'${YEAR}'_0.root   done_ana/histoZHG_'${YEAR}'_1.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_0304.root done_ana/histoZHG_'${YEAR}'_3.root   done_ana/histoZHG_'${YEAR}'_4.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_0607.root done_ana/histoZHG_'${YEAR}'_6.root   done_ana/histoZHG_'${YEAR}'_7.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_09101112.root  done_ana/histoZHG_'${YEAR}'_9.root done_ana/histoZHG_'${YEAR}'_10.root done_ana/histoZHG_'${YEAR}'_11.root done_ana/histoZHG_'${YEAR}'_12.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_13141516.root done_ana/histoZHG_'${YEAR}'_13.root done_ana/histoZHG_'${YEAR}'_14.root done_ana/histoZHG_'${YEAR}'_15.root done_ana/histoZHG_'${YEAR}'_16.root
  hadd -f done_ana/histoZHG_'${YEAR}'_171819.root   done_ana/histoZHG_'${YEAR}'_17.root done_ana/histoZHG_'${YEAR}'_18.root done_ana/histoZHG_'${YEAR}'_19.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_2122.root done_ana/histoZHG_'${YEAR}'_21.root done_ana/histoZHG_'${YEAR}'_22.root 
  hadd -f done_ana/histoZHG_'${YEAR}'_3637.root  done_ana/histoZHG_'${YEAR}'_36.root done_ana/histoZHG_'${YEAR}'_37.root 
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_0001.root","zhg_zhsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"e#mu region m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_2.root","zhg_emusel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"e#mu region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"B tagged selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_0304.root","zhg_btagsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"B tagged region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Z#gamma selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_0607.root","zhg_zllgsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"Z#gamma region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"WZ selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_09101112.root","zhg_wzsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"WZ region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"WZ#gamma selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_13141516.root","zhg_wzgsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"WZ#gamma region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZZ selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_171819.root","zhg_zzsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"ZZ region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"WW selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_2122.root","zhg_wwsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"WW region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZHG_'${YEAR}'_24.root","zhg_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZHG_'${YEAR}'_25.root","zhg_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection E_{T}^{miss}","GeV","done_ana/histoZHG_'${YEAR}'_26.root","zhg_zhselnminus1_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection |p_{T}^{ll#gamma}-E_{T}^{miss}|/p_{T}^{ll#gamma}","","done_ana/histoZHG_'${YEAR}'_27.root","zhg_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection #Delta#phi_{ll#gamma,E_{T}^{miss}}","","done_ana/histoZHG_'${YEAR}'_28.root","zhg_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZHG_'${YEAR}'_29.root","zhg_zhselnminus1_nbjets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZHG_'${YEAR}'_30.root","zhg_zhselnminus1_ptll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done_ana/histoZHG_'${YEAR}'_31.root","zhg_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZHG_'${YEAR}'_32.root","zhg_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,20,"N-1 ZH selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_33.root","zhg_zhselnminus1_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"ZH selection |#eta^{#gamma}|","","done_ana/histoZHG_'${YEAR}'_34.root","zhg_zhsel_etag",0,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH selection Tightphoton veto","","done_ana/histoZHG_'${YEAR}'_35.root","zhg_zhsel_photonveto",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_'${YEAR}'_3637.root","zhg_zll_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_'${YEAR}'_36.root","zhg_zmm_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_'${YEAR}'_37.root","zhg_zee_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_'${YEAR}'_38.root","zhg_zem_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH #eta_{j}","","done_ana/histoZHG_'${YEAR}'_39.root","zhg_zhmmsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH #eta_{j}","","done_ana/histoZHG_'${YEAR}'_40.root","zhg_zheesel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH #eta_{j}","","done_ana/histoZHG_'${YEAR}'_41.root","zhg_zhemsel_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection E_{T}^{miss}","GeV","done_ana/histoZHG_'${YEAR}'_42.root","zhg_zmmhselnminus3_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection E_{T}^{miss}","GeV","done_ana/histoZHG_'${YEAR}'_43.root","zhg_zeehselnminus3_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection E_{T}^{miss}","GeV","done_ana/histoZHG_'${YEAR}'_44.root","zhg_zemhselnminus3_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection |p_{T}^{ll#gamma}-E_{T}^{miss}|/p_{T}^{ll#gamma}","","done_ana/histoZHG_'${YEAR}'_45.root","zhg_zmmhselnminus3_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection |p_{T}^{ll#gamma}-E_{T}^{miss}|/p_{T}^{ll#gamma}","","done_ana/histoZHG_'${YEAR}'_46.root","zhg_zeehselnminus3_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection |p_{T}^{ll#gamma}-E_{T}^{miss}|/p_{T}^{ll#gamma}","","done_ana/histoZHG_'${YEAR}'_47.root","zhg_zemhselnminus3_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection #Delta#phi_{ll#gamma,E_{T}^{miss}}","","done_ana/histoZHG_'${YEAR}'_48.root","zhg_zmmhselnminus3_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection #Delta#phi_{ll#gamma,E_{T}^{miss}}","","done_ana/histoZHG_'${YEAR}'_49.root","zhg_zeehselnminus3_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-3 ZH selection #Delta#phi_{ll#gamma,E_{T}^{miss}}","","done_ana/histoZHG_'${YEAR}'_50.root","zhg_zemhselnminus3_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"WZ selection m_{T}","GeV","done_ana/histoZHG_'${YEAR}'_51.root","zhg_wzsel_emulation_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"WZ region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","","done_ana/histoZHG_'${YEAR}'_52.root","zhg_card_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',1,"",0,'${APPLYSCALING}')';

elif [ $NSEL == 'z' ]; then
  export sf_dy=1.0;

  hadd -f done_dy/histoDY0zll_'${YEAR}'_4243.root done_dy/histoDY0zll_'${YEAR}'_42.root done_dy/histoDY0zll_'${YEAR}'_43.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_4243.root","zll_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,1)';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_2425.root done_dy/histoDY0zll_'${YEAR}'_24.root done_dy/histoDY0zll_'${YEAR}'_25.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi E_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_2425.root","zll_metphi",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi E_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_87.root","zll_corrmetphi",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_2728.root done_dy/histoDY0zll_'${YEAR}'_27.root done_dy/histoDY0zll_'${YEAR}'_28.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_2728.root","zll_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_3031.root done_dy/histoDY0zll_'${YEAR}'_30.root done_dy/histoDY0zll_'${YEAR}'_31.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_3031.root","zll_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_0.root","zmm_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_1.root","zee_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_2.root","zem_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_3.root","zmm_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_4.root","zee_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_5.root","zem_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_6.root","zmm_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_7.root","zee_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_8.root","zem_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_9.root","zmm_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_10.root","zee_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_11.root","zem_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_12.root","zmm_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_13.root","zee_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_14.root","zem_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_15.root","zmm_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_16.root","zee_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_17.root","zem_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Track E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_18.root","zmm_trackmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Track E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_19.root","zee_trackmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Track E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_20.root","zem_trackmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_21.root","zmm_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_22.root","zee_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_23.root","zem_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi E_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_24.root","zmm_metphi",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi E_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_25.root","zee_metphi",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi E_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_26.root","zem_metphi",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_27.root","zmm_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_28.root","zee_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_29.root","zem_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_30.root","zmm_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_31.root","zee_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. E_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_32.root","zem_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_33.root","zmm_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_34.root","zee_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_35.root","zem_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_36.root","zmm_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_37.root","zee_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_38.root","zem_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_39.root","zmm_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_40.root","zee_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_41.root","zem_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_42.root","zmm_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_43.root","zee_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_44.root","zem_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_45.root","zmm_eta",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_46.root","zee_eta",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_47.root","zem_eta",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1}","GeV","done_dy/histoDY0zll_'${YEAR}'_48.root","zmm_ptl",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1}","GeV","done_dy/histoDY0zll_'${YEAR}'_49.root","zee_ptl",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1}","GeV","done_dy/histoDY0zll_'${YEAR}'_50.root","zem_ptl",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_51.root","zmm_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_52.root","zee_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_53.root","zem_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_54.root","zmm_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_55.root","zee_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_56.root","zem_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_57.root","zll_ptj",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag","","done_dy/histoDY0zll_'${YEAR}'_58.root","zll_btag",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#eta^{j}","","done_dy/histoDY0zll_'${YEAR}'_59.root","zll_etaj",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi^{j}","","done_dy/histoDY0zll_'${YEAR}'_60.root","zll_phij",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_61.root","zll_etajlt2p5_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_62.root","zll_etajlt2p5_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_63.root","zll_etajlt2p5_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_64.root","zll_etajlt2p5_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_65.root","zll_etajcrack_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_66.root","zll_etajcrack_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_67.root","zll_etajcrack_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_68.root","zll_etajcrack_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_69.root","zll_etajgt3p0_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_70.root","zll_etajgt3p0_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_71.root","zll_etajgt3p0_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_72.root","zll_etajgt3p0_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_73.root","zll_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_74.root","zll_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_75.root","zll_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_76.root","zll_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_77.root","zll_ptjgt100_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_78.root","zll_ptjgt100_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_79.root","zll_ptjgt100_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_80.root","zll_ptjgt100_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_81.root","zll_ptjgt100_etajlt2p5_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_82.root","zll_ptjgt100_etajlt2p5_corrmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_83.root","zll_ptjgt100_etajlt2p5_met_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_84.root","zll_ptjgt100_etajlt2p5_corrmet_nonvtx",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Raw E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_85.root","zll_rawmet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Calo E_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_86.root","zll_calomet",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'ssww' ]; then
  hadd -f done_ana/histossww_'${YEAR}'_000102.root done_ana/histossww_'${YEAR}'_0.root   done_ana/histossww_'${YEAR}'_1.root    done_ana/histossww_'${YEAR}'_2.root 
  hadd -f done_ana/histossww_'${YEAR}'_030407.root done_ana/histossww_'${YEAR}'_3.root   done_ana/histossww_'${YEAR}'_4.root    done_ana/histossww_'${YEAR}'_5.root 
  hadd -f done_ana/histossww_'${YEAR}'_060708.root done_ana/histossww_'${YEAR}'_6.root   done_ana/histossww_'${YEAR}'_7.root    done_ana/histossww_'${YEAR}'_8.root 
  hadd -f done_ana/histossww_'${YEAR}'_091011.root done_ana/histossww_'${YEAR}'_9.root   done_ana/histossww_'${YEAR}'_10.root   done_ana/histossww_'${YEAR}'_11.root 
  hadd -f done_ana/histossww_'${YEAR}'_121314.root done_ana/histossww_'${YEAR}'_12.root  done_ana/histossww_'${YEAR}'_13.root   done_ana/histossww_'${YEAR}'_14.root 
  hadd -f done_ana/histossww_'${YEAR}'_151617.root done_ana/histossww_'${YEAR}'_15.root  done_ana/histossww_'${YEAR}'_16.root   done_ana/histossww_'${YEAR}'_17.root 
  hadd -f done_ana/histossww_'${YEAR}'_181920.root done_ana/histossww_'${YEAR}'_18.root  done_ana/histossww_'${YEAR}'_19.root   done_ana/histossww_'${YEAR}'_20.root 
  hadd -f done_ana/histossww_'${YEAR}'_212223.root done_ana/histossww_'${YEAR}'_21.root  done_ana/histossww_'${YEAR}'_22.root   done_ana/histossww_'${YEAR}'_23.root 
  hadd -f done_ana/histossww_'${YEAR}'_242526.root done_ana/histossww_'${YEAR}'_24.root  done_ana/histossww_'${YEAR}'_25.root   done_ana/histossww_'${YEAR}'_26.root 
  hadd -f done_ana/histossww_'${YEAR}'_272829.root done_ana/histossww_'${YEAR}'_27.root  done_ana/histossww_'${YEAR}'_28.root   done_ana/histossww_'${YEAR}'_29.root 
  hadd -f done_ana/histossww_'${YEAR}'_303132.root done_ana/histossww_'${YEAR}'_30.root  done_ana/histossww_'${YEAR}'_31.root   done_ana/histossww_'${YEAR}'_32.root
  hadd -f done_ana/histossww_'${YEAR}'_33343536.root done_ana/histossww_'${YEAR}'_33.root  done_ana/histossww_'${YEAR}'_34.root   done_ana/histossww_'${YEAR}'_35.root done_ana/histossww_'${YEAR}'_36.root
  hadd -f done_ana/histossww_'${YEAR}'_373839.root done_ana/histossww_'${YEAR}'_37.root  done_ana/histossww_'${YEAR}'_38.root   done_ana/histossww_'${YEAR}'_39.root
  hadd -f done_ana/histossww_'${YEAR}'_404142.root done_ana/histossww_'${YEAR}'_40.root  done_ana/histossww_'${YEAR}'_41.root   done_ana/histossww_'${YEAR}'_42.root
  hadd -f done_ana/histossww_'${YEAR}'_434445.root done_ana/histossww_'${YEAR}'_43.root  done_ana/histossww_'${YEAR}'_44.root   done_ana/histossww_'${YEAR}'_45.root
  hadd -f done_ana/histossww_'${YEAR}'_464748.root done_ana/histossww_'${YEAR}'_46.root  done_ana/histossww_'${YEAR}'_47.root   done_ana/histossww_'${YEAR}'_48.root
  hadd -f done_ana/histossww_'${YEAR}'_495051.root done_ana/histossww_'${YEAR}'_49.root  done_ana/histossww_'${YEAR}'_50.root   done_ana/histossww_'${YEAR}'_51.root
  hadd -f done_ana/histossww_'${YEAR}'_525354.root done_ana/histossww_'${YEAR}'_52.root  done_ana/histossww_'${YEAR}'_53.root   done_ana/histossww_'${YEAR}'_54.root
  hadd -f done_ana/histossww_'${YEAR}'_555657.root done_ana/histossww_'${YEAR}'_55.root  done_ana/histossww_'${YEAR}'_56.root   done_ana/histossww_'${YEAR}'_57.root
  hadd -f done_ana/histossww_'${YEAR}'_585960.root done_ana/histossww_'${YEAR}'_58.root  done_ana/histossww_'${YEAR}'_59.root   done_ana/histossww_'${YEAR}'_60.root
  hadd -f done_ana/histossww_'${YEAR}'_616263.root done_ana/histossww_'${YEAR}'_61.root  done_ana/histossww_'${YEAR}'_62.root   done_ana/histossww_'${YEAR}'_63.root
  hadd -f done_ana/histossww_'${YEAR}'_646566.root done_ana/histossww_'${YEAR}'_64.root  done_ana/histossww_'${YEAR}'_65.root   done_ana/histossww_'${YEAR}'_66.root
  hadd -f done_ana/histossww_'${YEAR}'_676869.root done_ana/histossww_'${YEAR}'_67.root  done_ana/histossww_'${YEAR}'_68.root   done_ana/histossww_'${YEAR}'_69.root
  hadd -f done_ana/histossww_'${YEAR}'_707172.root done_ana/histossww_'${YEAR}'_70.root  done_ana/histossww_'${YEAR}'_71.root   done_ana/histossww_'${YEAR}'_72.root
  hadd -f done_ana/histossww_'${YEAR}'_737475.root done_ana/histossww_'${YEAR}'_73.root  done_ana/histossww_'${YEAR}'_74.root   done_ana/histossww_'${YEAR}'_75.root
  hadd -f done_ana/histossww_'${YEAR}'_767778.root done_ana/histossww_'${YEAR}'_76.root  done_ana/histossww_'${YEAR}'_77.root   done_ana/histossww_'${YEAR}'_78.root
  hadd -f done_ana/histossww_'${YEAR}'_798081.root done_ana/histossww_'${YEAR}'_79.root  done_ana/histossww_'${YEAR}'_80.root   done_ana/histossww_'${YEAR}'_81.root
  hadd -f done_ana/histossww_'${YEAR}'_828384.root done_ana/histossww_'${YEAR}'_82.root  done_ana/histossww_'${YEAR}'_83.root   done_ana/histossww_'${YEAR}'_84.root
  hadd -f done_ana/histossww_'${YEAR}'_858687.root done_ana/histossww_'${YEAR}'_85.root  done_ana/histossww_'${YEAR}'_86.root   done_ana/histossww_'${YEAR}'_87.root
  hadd -f done_ana/histossww_'${YEAR}'_888990.root done_ana/histossww_'${YEAR}'_88.root  done_ana/histossww_'${YEAR}'_89.root   done_ana/histossww_'${YEAR}'_90.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_000102.root","ssww_sswwselnminus1_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,20,"E_{T}^{miss}","GeV","done_ana/histossww_'${YEAR}'_030407.root","ssww_sswwselnminus1_met",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histossww_'${YEAR}'_060708.root","ssww_sswwselnminus1_njets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done_ana/histossww_'${YEAR}'_091011.root","ssww_sswwselnminus1_detajj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_121314.root","ssww_sswwselnminus1_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done_ana/histossww_'${YEAR}'_151617.root","ssww_sswwselnminus1_zstar",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histossww_'${YEAR}'_181920.root","ssww_sswwselnminus1_nbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{#tau}","","done_ana/histossww_'${YEAR}'_212223.root","ssww_sswwselnminus1_ntau",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{leading}","GeV","done_ana/histossww_'${YEAR}'_242526.root","ssww_sswwsel_ptl1",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{trailing}","GeV","done_ana/histossww_'${YEAR}'_272829.root","ssww_sswwsel_ptl2",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_303132.root","ssww_sswwsel_mjj",0,'${YEAR}',"H(125)",1.0,1,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_33343536.root","ssww_wzsel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_373839.root","ssww_btagsel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_404142.root","ssww_sswwsel_mll",0,'${YEAR}',"H(125)",1.0,1,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_434445.root","ssww_btagsel_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_464748.root","ssww_sswwsel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_495051.root","ssww_btagsel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done_ana/histossww_'${YEAR}'_525354.root","ssww_presel_detajj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_555657.root","ssww_presel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done_ana/histossww_'${YEAR}'_585960.root","ssww_presel_zstar",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{loose b jets}","","done_ana/histossww_'${YEAR}'_616263.root","ssww_presel_nlbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done_ana/histossww_'${YEAR}'_646566.root","ssww_presel_nmbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done_ana/histossww_'${YEAR}'_676869.root","ssww_presel_nlbjetsgt0_nmbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{j}","","done_ana/histossww_'${YEAR}'_707172.root","ssww_presel_ptj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_737475.root","ssww_presel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l}","GeV","done_ana/histossww_'${YEAR}'_767778.root","ssww_presel_ptl",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|#eta^{l}|","","done_ana/histossww_'${YEAR}'_798081.root","ssww_presel_etal",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag max","","done_ana/histossww_'${YEAR}'_828384.root","ssww_presel_btagmax",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag min","","done_ana/histossww_'${YEAR}'_858687.root","ssww_presel_btagmin",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_888990.root","ssww_zsel_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}Xm_{ll}","","done_ana/histossww_'${YEAR}'_91.root","ssww_datacard",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zlg' ]; then
  export sf_dy=1.0;

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_0.root","zlg_mee",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_2.root","zlg_ptee",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_3.root","zlg_ptee_0",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_4.root","zlg_ptee_1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_5.root","zlg_ptee_2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_6.root","zlg_ptee_3",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_7.root","zlg_ptee_4",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_1.root","zlg_meg",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_8.root","zlg_pteg",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_9.root","zlg_pteg_0",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_10.root","zlg_pteg_1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_11.root","zlg_pteg_2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_12.root","zlg_pteg_3",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0LGStudy_'${YEAR}'_13.root","zlg_pteg_4",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_0.root","zlg_meg_0",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_1.root","zlg_meg_1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_2.root","zlg_meg_2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_3.root","zlg_meg_3",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_4.root","zlg_meg_4",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_5.root","zlg_meg_5",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_6.root","zlg_meg_6",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_7.root","zlg_meg_7",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_8.root","zlg_meg_8",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_9.root","zlg_meg_9",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_10.root","zlg_meg_10",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_11.root","zlg_meg_11",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_12.root","zlg_meg_12",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_13.root","zlg_meg_13",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_14.root","zlg_meg_14",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_15.root","zlg_meg_15",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_16.root","zlg_meg_16",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_17.root","zlg_meg_17",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_18.root","zlg_meg_18",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_19.root","zlg_meg_19",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_20.root","zlg_meg_20",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_21.root","zlg_meg_21",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_22.root","zlg_meg_22",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_23.root","zlg_meg_23",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_24.root","zlg_meg_24",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_25.root","zlg_meg_25",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_26.root","zlg_meg_26",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_27.root","zlg_meg_27",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_28.root","zlg_meg_28",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_29.root","zlg_meg_29",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_30.root","zlg_meg_30",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_31.root","zlg_meg_31",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_32.root","zlg_meg_32",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_33.root","zlg_meg_33",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_34.root","zlg_meg_34",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_35.root","zlg_meg_35",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_36.root","zlg_meg_36",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_37.root","zlg_meg_37",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_38.root","zlg_meg_38",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_49.root","zlg_meg_49",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_40.root","zlg_meg_40",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_41.root","zlg_meg_41",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_42.root","zlg_meg_42",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_43.root","zlg_meg_43",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_44.root","zlg_meg_44",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_45.root","zlg_meg_45",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_46.root","zlg_meg_46",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_47.root","zlg_meg_47",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_48.root","zlg_meg_48",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0LGStudyLMG_'${YEAR}'_49.root","zlg_meg_49",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
fi
