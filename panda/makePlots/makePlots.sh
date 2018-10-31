#!/bin/sh

export NSEL=$1;
export APPLYSCALING=$2;
export YEAR=$3;

if [ $NSEL == 'wz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done/histoWZ_'${YEAR}'_4.root","wz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|m_{ll}-m_{Z}|","GeV","done/histoWZ_'${YEAR}'_9.root","wz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l W}","GeV","done/histoWZ_'${YEAR}'_14.root","wz_wlpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"E_{T}^{miss}","GeV","done/histoWZ_'${YEAR}'_19.root","wz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{3l}","GeV","done/histoWZ_'${YEAR}'_24.root","wz_m3l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1 Z}","GeV","done/histoWZ_'${YEAR}'_29.root","wz_z1lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l2 Z}","GeV","done/histoWZ_'${YEAR}'_34.root","wz_z2lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{T}","GeV","done/histoWZ_'${YEAR}'_39.root","wz_mt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"E_{T}^{miss}","GeV","done/histoWZ_'${YEAR}'_44.root","wz_topsel_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoWZ_'${YEAR}'_49.root","wz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoWZ_'${YEAR}'_54.root","wz_topsel_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done/histoWZ_'${YEAR}'_59.root","wz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done/histoWZ_'${YEAR}'_64.root","wz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done/histoWZ_'${YEAR}'_69.root","wz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done/histoZZ_'${YEAR}'_4.root","zz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done/histoZZ_'${YEAR}'_9.root","zz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done/histoZZ_'${YEAR}'_14.root","zz_mzmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done/histoZZ_'${YEAR}'_19.root","zz_m4l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z1}","GeV","done/histoZZ_'${YEAR}'_24.root","zz_ptl1z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z1}","GeV","done/histoZZ_'${YEAR}'_29.root","zz_ptl2z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z2}","GeV","done/histoZZ_'${YEAR}'_34.root","zz_ptl1z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z2}","GeV","done/histoZZ_'${YEAR}'_39.root","zz_ptl2z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"E_{T}^{miss}","GeV","done/histoZZ_'${YEAR}'_44.root","zz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoZZ_'${YEAR}'_49.root","zz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done/histoZZ_'${YEAR}'_54.root","zz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done/histoZZ_'${YEAR}'_59.root","zz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated E_{T}^{miss}","GeV","done/histoZZ_'${YEAR}'_64.root","zz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zh' ]; then
  export sf_dy=1.0;
  hadd -f done/histoZH_'${YEAR}'_0001.root done/histoZH_'${YEAR}'_0.root   done/histoZH_'${YEAR}'_1.root 
  hadd -f done/histoZH_'${YEAR}'_0304.root done/histoZH_'${YEAR}'_3.root   done/histoZH_'${YEAR}'_4.root 
  hadd -f done/histoZH_'${YEAR}'_0607.root done/histoZH_'${YEAR}'_6.root   done/histoZH_'${YEAR}'_7.root 
  hadd -f done/histoZH_'${YEAR}'_0910.root done/histoZH_'${YEAR}'_9.root  done/histoZH_'${YEAR}'_10.root 
  hadd -f done/histoZH_'${YEAR}'_1213.root done/histoZH_'${YEAR}'_12.root done/histoZH_'${YEAR}'_13.root 
  hadd -f done/histoZH_'${YEAR}'_1516.root done/histoZH_'${YEAR}'_15.root done/histoZH_'${YEAR}'_16.root 
  hadd -f done/histoZH_'${YEAR}'_1819.root done/histoZH_'${YEAR}'_18.root done/histoZH_'${YEAR}'_19.root 
  hadd -f done/histoZH_'${YEAR}'_2122.root done/histoZH_'${YEAR}'_21.root done/histoZH_'${YEAR}'_22.root 
  hadd -f done/histoZH_'${YEAR}'_2425.root done/histoZH_'${YEAR}'_24.root done/histoZH_'${YEAR}'_25.root 
  hadd -f done/histoZH_'${YEAR}'_2728.root done/histoZH_'${YEAR}'_27.root done/histoZH_'${YEAR}'_28.root 
  hadd -f done/histoZH_'${YEAR}'_3031.root done/histoZH_'${YEAR}'_30.root done/histoZH_'${YEAR}'_31.root 
  hadd -f done/histoZH_'${YEAR}'_3334.root done/histoZH_'${YEAR}'_33.root done/histoZH_'${YEAR}'_34.root 
  hadd -f done/histoZH_'${YEAR}'_3637.root done/histoZH_'${YEAR}'_36.root done/histoZH_'${YEAR}'_37.root 
  hadd -f done/histoZH_'${YEAR}'_3940.root done/histoZH_'${YEAR}'_39.root done/histoZH_'${YEAR}'_40.root 
  hadd -f done/histoZH_'${YEAR}'_4243.root done/histoZH_'${YEAR}'_42.root done/histoZH_'${YEAR}'_43.root 

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done/histoZH_'${YEAR}'_0001.root","zh_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_0304.root","zh_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_0607.root","zh_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_0910.root","zh_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_1213.root","zh_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done/histoZH_'${YEAR}'_1516.root","zh_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done/histoZH_'${YEAR}'_1819.root","zh_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_2122.root","zh_zhselnminus1_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_2425.root","zh_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_2728.root","zh_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done/histoZH_'${YEAR}'_3031.root","zh_zhselnminus1_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done/histoZH_'${YEAR}'_3334.root","zh_zhselnminus1_ptll",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_3637.root","zh_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done/histoZH_'${YEAR}'_3940.root","zh_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done/histoZH_'${YEAR}'_4243.root","zh_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done/histoZH_'${YEAR}'_45.root","zhmm_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done/histoZH_'${YEAR}'_46.root","zhee_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done/histoZH_'${YEAR}'_47.root","zhem_cutevol",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#eta_{j}","","done/histoZH_'${YEAR}'_48.root","zhmm_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#eta_{j}","","done/histoZH_'${YEAR}'_49.root","zhee_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#eta_{j}","","done/histoZH_'${YEAR}'_50.root","zhem_etaj",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_51.root","zhmm_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_52.root","zhee_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_53.root","zhem_dphilmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done/histoZH_'${YEAR}'_53.root","zhmm_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done/histoZH_'${YEAR}'_55.root","zhee_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{l,track E_{T}^{miss}}","","done/histoZH_'${YEAR}'_56.root","zhem_dphiltrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done/histoZH_'${YEAR}'_57.root","zhmm_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done/histoZH_'${YEAR}'_58.root","zhee_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"#Delta#phi_{track E_{T}^{miss},E_{T}^{miss}}","","done/histoZH_'${YEAR}'_59.root","zhem_dphimettrkmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_72.root","zh_card_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done/histoZH_'${YEAR}'_0.root","zhmm_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_3.root","zhmm_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_6.root","zhmm_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_9.root","zhmm_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_12.root","zhmm_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done/histoZH_'${YEAR}'_15.root","zhmm_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done/histoZH_'${YEAR}'_18.root","zhmm_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_21.root","zhmm_zhselnminus1_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_24.root","zhmm_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_27.root","zhmm_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done/histoZH_'${YEAR}'_30.root","zhmm_zhselnminus1_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done/histoZH_'${YEAR}'_33.root","zhmm_zhselnminus1_ptll",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_36.root","zhmm_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done/histoZH_'${YEAR}'_39.root","zhmm_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done/histoZH_'${YEAR}'_42.root","zhmm_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_60.root","zhmm_presel_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_63.root","zhmm_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_66.root","zhmm_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done/histoZH_'${YEAR}'_69.root","zhmm_presel_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done/histoZH_'${YEAR}'_1.root","zhee_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_4.root","zhee_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_7.root","zhee_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_10.root","zhee_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_13.root","zhee_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done/histoZH_'${YEAR}'_16.root","zhee_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done/histoZH_'${YEAR}'_19.root","zhee_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_22.root","zhee_zhselnminus1_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_25.root","zhee_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_28.root","zhee_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done/histoZH_'${YEAR}'_31.root","zhee_zhselnminus1_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done/histoZH_'${YEAR}'_34.root","zhee_zhselnminus1_ptll",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_37.root","zhee_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done/histoZH_'${YEAR}'_40.root","zhee_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done/histoZH_'${YEAR}'_43.root","zhee_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_61.root","zhee_presel_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_64.root","zhee_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_67.root","zhee_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done/histoZH_'${YEAR}'_70.root","zhee_presel_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done/histoZH_'${YEAR}'_2.root","zhem_zhtightsel_mt",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_5.root","zhem_zhsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_8.root","zhem_btagsel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_11.root","zhem_presel_met",1,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_14.root","zhem_ww_met",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done/histoZH_'${YEAR}'_17.root","zhem_zhselnminus1_mz",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done/histoZH_'${YEAR}'_20.root","zhem_zhselnminus1_njets",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_23.root","zhem_zhselnminus1_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_26.root","zhem_zhselnminus1_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_29.root","zhem_zhselnminus1_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done/histoZH_'${YEAR}'_32.root","zhem_zhselnminus1_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done/histoZH_'${YEAR}'_35.root","zhem_zhselnminus1_ptll",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_38.root","zhem_zhselnminus1_dphijetmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done/histoZH_'${YEAR}'_41.root","zhem_zhselnminus1_ntau",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done/histoZH_'${YEAR}'_44.root","zhem_zhselnminus1_drll",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection E_{T}^{miss}","GeV","done/histoZH_'${YEAR}'_62.root","zhem_presel_met",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection |p_{T}^{ll}-E_{T}^{miss}|/p_{T}^{ll}","","done/histoZH_'${YEAR}'_65.root","zhem_presel_ptfrac",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH preselection #Delta#phi_{ll,E_{T}^{miss}}","","done/histoZH_'${YEAR}'_68.root","zhem_presel_dphidilepmet",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH preselection N_{b jets}","","done/histoZH_'${YEAR}'_71.root","zhem_presel_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"ZH(inv)",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zhg' ]; then
  export sf_dy=1.0;
  hadd -f done/histoZHG_'${YEAR}'_0001.root done/histoZHG_'${YEAR}'_0.root   done/histoZHG_'${YEAR}'_1.root 
  hadd -f done/histoZHG_'${YEAR}'_0304.root done/histoZHG_'${YEAR}'_3.root   done/histoZHG_'${YEAR}'_4.root 
  hadd -f done/histoZHG_'${YEAR}'_0607.root done/histoZHG_'${YEAR}'_6.root   done/histoZHG_'${YEAR}'_7.root 
  hadd -f done/histoZHG_'${YEAR}'_09101112.root  done/histoZHG_'${YEAR}'_9.root done/histoZHG_'${YEAR}'_10.root done/histoZHG_'${YEAR}'_11.root done/histoZHG_'${YEAR}'_12.root 
  hadd -f done/histoZHG_'${YEAR}'_13141516.root done/histoZHG_'${YEAR}'_13.root done/histoZHG_'${YEAR}'_14.root done/histoZHG_'${YEAR}'_15.root done/histoZHG_'${YEAR}'_16.root
  hadd -f done/histoZHG_'${YEAR}'_171819.root   done/histoZHG_'${YEAR}'_17.root done/histoZHG_'${YEAR}'_18.root done/histoZHG_'${YEAR}'_19.root 
  hadd -f done/histoZHG_'${YEAR}'_2122.root done/histoZHG_'${YEAR}'_21.root done/histoZHG_'${YEAR}'_22.root 
  hadd -f done/histoZHG_'${YEAR}'_223.root  done/histoZHG_'${YEAR}'_18.root done/histoZHG_'${YEAR}'_19.root 
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"ZH selection m_{T}","GeV","done/histoZHG_'${YEAR}'_0001.root","zhg_zhsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"B tagged selection m_{T}","GeV","done/histoZHG_'${YEAR}'_0304.root","zhg_btagsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"Z#gamma selection m_{T}","GeV","done/histoZHG_'${YEAR}'_0607.root","zhg_zllgsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"WZ selection m_{T}","GeV","done/histoZHG_'${YEAR}'_09101112.root","zhg_wzsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"WZ#gamma selection m_{T}","GeV","done/histoZHG_'${YEAR}'_13141516.root","zhg_wzgsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"ZZ selection m_{T}","GeV","done/histoZHG_'${YEAR}'_171819.root","zhg_zzsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,25,"WW selection m_{T}","GeV","done/histoZHG_'${YEAR}'_2122.root","zhg_wwsel_mtg",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done/histoZHG_'${YEAR}'_24.root","zhg_zhselnminus1_mz",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done/histoZHG_'${YEAR}'_25.root","zhg_zhselnminus1_njets",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection E_{T}^{miss}","GeV","done/histoZHG_'${YEAR}'_26.root","zhg_zhselnminus1_met",1,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll#gamma}-E_{T}^{miss}|/p_{T}^{ll#gamma}","","done/histoZHG_'${YEAR}'_27.root","zhg_zhselnminus1_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection #Delta#phi_{ll#gamma,E_{T}^{miss}}","","done/histoZHG_'${YEAR}'_28.root","zhg_zhselnminus1_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done/histoZHG_'${YEAR}'_29.root","zhg_zhselnminus1_nbjets",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection p_{T}^{ll}","GeV","done/histoZHG_'${YEAR}'_30.root","zhg_zhselnminus1_ptll",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection #Delta#phi_{jet,E_{T}^{miss}}","","done/histoZHG_'${YEAR}'_31.root","zhg_zhselnminus1_dphijetmet",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done/histoZHG_'${YEAR}'_32.root","zhg_zhselnminus1_ntau",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,20,"N-1 ZH selection m_{T}","GeV","done/histoZHG_'${YEAR}'_33.root","zhg_zhselnminus1_mtg",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection |#eta^{#gamma}|","","done/histoZHG_'${YEAR}'_34.root","zhg_zhsel_etag",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH selection Tightphoton veto","","done/histoZHG_'${YEAR}'_35.root","zhg_zhsel_photonveto",0,'${YEAR}',"",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeV","done/histoZHG_'${YEAR}'_36.root","zhg_card_mt",0,'${YEAR}',"ZH(inv)",'${sf_dy}',0,"",0,'${APPLYSCALING}')';

elif [ $NSEL == 'z' ]; then
  export sf_dy=1.0;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_0.root","zmm_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_1.root","zee_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_2.root","zem_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_3.root","zmm_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_4.root","zee_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0zll_'${YEAR}'_5.root","zem_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done/histoDY0zll_'${YEAR}'_6.root","zmm_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done/histoDY0zll_'${YEAR}'_7.root","zee_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done/histoDY0zll_'${YEAR}'_8.root","zem_ncjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoDY0zll_'${YEAR}'_9.root","zmm_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoDY0zll_'${YEAR}'_10.root","zee_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoDY0zll_'${YEAR}'_11.root","zem_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done/histoDY0zll_'${YEAR}'_12.root","zmm_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done/histoDY0zll_'${YEAR}'_13.root","zee_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done/histoDY0zll_'${YEAR}'_14.root","zem_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"E_{T}^{miss}","GeV","done/histoDY0zll_'${YEAR}'_15.root","zmm_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"E_{T}^{miss}","GeV","done/histoDY0zll_'${YEAR}'_16.root","zee_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"E_{T}^{miss}","GeV","done/histoDY0zll_'${YEAR}'_17.root","zem_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done/histoDY0zll_'${YEAR}'_30.root","zmm_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done/histoDY0zll_'${YEAR}'_31.root","zee_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,E_{T}^{miss}}","","done/histoDY0zll_'${YEAR}'_32.root","zem_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done/histoDY0zll_'${YEAR}'_45.root","zmm_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done/histoDY0zll_'${YEAR}'_46.root","zee_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done/histoDY0zll_'${YEAR}'_47.root","zem_drll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{NPV}","","done/histoDY0zll_'${YEAR}'_48.root","zmm_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{NPV}","","done/histoDY0zll_'${YEAR}'_49.root","zee_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{NPV}","","done/histoDY0zll_'${YEAR}'_50.root","zem_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{m}","","done/histoDY0zll_'${YEAR}'_51.root","zmm_eta1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{e}","","done/histoDY0zll_'${YEAR}'_52.root","zee_eta1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{e}","","done/histoDY0zll_'${YEAR}'_53.root","zem_eta1",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Trailing #eta_{m}","","done/histoDY0zll_'${YEAR}'_54.root","zmm_eta2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Trailing #eta_{e}","","done/histoDY0zll_'${YEAR}'_55.root","zee_eta2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Trailing #eta_{e}","","done/histoDY0zll_'${YEAR}'_56.root","zem_eta2",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done/histoDY0zll_'${YEAR}'_63.root","zmm_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done/histoDY0zll_'${YEAR}'_64.root","zee_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done/histoDY0zll_'${YEAR}'_65.root","zem_nlbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done/histoDY0zll_'${YEAR}'_66.root","zmm_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done/histoDY0zll_'${YEAR}'_67.root","zee_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done/histoDY0zll_'${YEAR}'_68.root","zem_nmbjets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'ssww' ]; then
  hadd -f done/histossww_'${YEAR}'_000102.root done/histossww_'${YEAR}'_0.root   done/histossww_'${YEAR}'_1.root    done/histossww_'${YEAR}'_2.root 
  hadd -f done/histossww_'${YEAR}'_030407.root done/histossww_'${YEAR}'_3.root   done/histossww_'${YEAR}'_4.root    done/histossww_'${YEAR}'_5.root 
  hadd -f done/histossww_'${YEAR}'_060708.root done/histossww_'${YEAR}'_6.root   done/histossww_'${YEAR}'_7.root    done/histossww_'${YEAR}'_8.root 
  hadd -f done/histossww_'${YEAR}'_091011.root done/histossww_'${YEAR}'_9.root   done/histossww_'${YEAR}'_10.root   done/histossww_'${YEAR}'_11.root 
  hadd -f done/histossww_'${YEAR}'_121314.root done/histossww_'${YEAR}'_12.root  done/histossww_'${YEAR}'_13.root   done/histossww_'${YEAR}'_14.root 
  hadd -f done/histossww_'${YEAR}'_151617.root done/histossww_'${YEAR}'_15.root  done/histossww_'${YEAR}'_16.root   done/histossww_'${YEAR}'_17.root 
  hadd -f done/histossww_'${YEAR}'_181920.root done/histossww_'${YEAR}'_18.root  done/histossww_'${YEAR}'_19.root   done/histossww_'${YEAR}'_20.root 
  hadd -f done/histossww_'${YEAR}'_212223.root done/histossww_'${YEAR}'_21.root  done/histossww_'${YEAR}'_22.root   done/histossww_'${YEAR}'_23.root 
  hadd -f done/histossww_'${YEAR}'_242526.root done/histossww_'${YEAR}'_24.root  done/histossww_'${YEAR}'_25.root   done/histossww_'${YEAR}'_26.root 
  hadd -f done/histossww_'${YEAR}'_272829.root done/histossww_'${YEAR}'_27.root  done/histossww_'${YEAR}'_28.root   done/histossww_'${YEAR}'_29.root 
  hadd -f done/histossww_'${YEAR}'_303132.root done/histossww_'${YEAR}'_30.root  done/histossww_'${YEAR}'_31.root   done/histossww_'${YEAR}'_32.root
  hadd -f done/histossww_'${YEAR}'_33343536.root done/histossww_'${YEAR}'_33.root  done/histossww_'${YEAR}'_34.root   done/histossww_'${YEAR}'_35.root done/histossww_'${YEAR}'_36.root
  hadd -f done/histossww_'${YEAR}'_373839.root done/histossww_'${YEAR}'_37.root  done/histossww_'${YEAR}'_38.root   done/histossww_'${YEAR}'_39.root
  hadd -f done/histossww_'${YEAR}'_404142.root done/histossww_'${YEAR}'_40.root  done/histossww_'${YEAR}'_41.root   done/histossww_'${YEAR}'_42.root
  hadd -f done/histossww_'${YEAR}'_434445.root done/histossww_'${YEAR}'_43.root  done/histossww_'${YEAR}'_44.root   done/histossww_'${YEAR}'_45.root
  hadd -f done/histossww_'${YEAR}'_464748.root done/histossww_'${YEAR}'_46.root  done/histossww_'${YEAR}'_47.root   done/histossww_'${YEAR}'_48.root
  hadd -f done/histossww_'${YEAR}'_495051.root done/histossww_'${YEAR}'_49.root  done/histossww_'${YEAR}'_50.root   done/histossww_'${YEAR}'_51.root
  hadd -f done/histossww_'${YEAR}'_525354.root done/histossww_'${YEAR}'_52.root  done/histossww_'${YEAR}'_53.root   done/histossww_'${YEAR}'_54.root
  hadd -f done/histossww_'${YEAR}'_555657.root done/histossww_'${YEAR}'_55.root  done/histossww_'${YEAR}'_56.root   done/histossww_'${YEAR}'_57.root
  hadd -f done/histossww_'${YEAR}'_585960.root done/histossww_'${YEAR}'_58.root  done/histossww_'${YEAR}'_59.root   done/histossww_'${YEAR}'_60.root
  hadd -f done/histossww_'${YEAR}'_616263.root done/histossww_'${YEAR}'_61.root  done/histossww_'${YEAR}'_62.root   done/histossww_'${YEAR}'_63.root
  hadd -f done/histossww_'${YEAR}'_646566.root done/histossww_'${YEAR}'_64.root  done/histossww_'${YEAR}'_65.root   done/histossww_'${YEAR}'_66.root
  hadd -f done/histossww_'${YEAR}'_676869.root done/histossww_'${YEAR}'_67.root  done/histossww_'${YEAR}'_68.root   done/histossww_'${YEAR}'_69.root
  hadd -f done/histossww_'${YEAR}'_707172.root done/histossww_'${YEAR}'_70.root  done/histossww_'${YEAR}'_71.root   done/histossww_'${YEAR}'_72.root
  hadd -f done/histossww_'${YEAR}'_737475.root done/histossww_'${YEAR}'_73.root  done/histossww_'${YEAR}'_74.root   done/histossww_'${YEAR}'_75.root
  hadd -f done/histossww_'${YEAR}'_767778.root done/histossww_'${YEAR}'_76.root  done/histossww_'${YEAR}'_77.root   done/histossww_'${YEAR}'_78.root
  hadd -f done/histossww_'${YEAR}'_798081.root done/histossww_'${YEAR}'_79.root  done/histossww_'${YEAR}'_80.root   done/histossww_'${YEAR}'_81.root
  hadd -f done/histossww_'${YEAR}'_828384.root done/histossww_'${YEAR}'_82.root  done/histossww_'${YEAR}'_83.root   done/histossww_'${YEAR}'_84.root
  hadd -f done/histossww_'${YEAR}'_858687.root done/histossww_'${YEAR}'_85.root  done/histossww_'${YEAR}'_86.root   done/histossww_'${YEAR}'_87.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done/histossww_'${YEAR}'_000102.root","ssww_sswwselnminus1_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,20,"E_{T}^{miss}","GeV","done/histossww_'${YEAR}'_030407.root","ssww_sswwselnminus1_met",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histossww_'${YEAR}'_060708.root","ssww_sswwselnminus1_njets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done/histossww_'${YEAR}'_091011.root","ssww_sswwselnminus1_detajj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done/histossww_'${YEAR}'_121314.root","ssww_sswwselnminus1_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done/histossww_'${YEAR}'_151617.root","ssww_sswwselnminus1_zstar",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done/histossww_'${YEAR}'_181920.root","ssww_sswwselnminus1_nbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{#tau}","","done/histossww_'${YEAR}'_212223.root","ssww_sswwselnminus1_ntau",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{leading}","GeV","done/histossww_'${YEAR}'_242526.root","ssww_sswwsel_ptl1",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{trailing}","GeV","done/histossww_'${YEAR}'_272829.root","ssww_sswwsel_ptl2",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done/histossww_'${YEAR}'_303132.root","ssww_sswwsel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done/histossww_'${YEAR}'_33343536.root","ssww_wzsel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done/histossww_'${YEAR}'_373839.root","ssww_btagsel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done/histossww_'${YEAR}'_404142.root","ssww_sswwsel_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done/histossww_'${YEAR}'_434445.root","ssww_btagsel_mll",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done/histossww_'${YEAR}'_464748.root","ssww_sswwsel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done/histossww_'${YEAR}'_495051.root","ssww_btagsel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done/histossww_'${YEAR}'_525354.root","ssww_presel_detajj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done/histossww_'${YEAR}'_555657.root","ssww_presel_mjj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done/histossww_'${YEAR}'_585960.root","ssww_presel_zstar",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{loose b jets}","","done/histossww_'${YEAR}'_616263.root","ssww_presel_nlbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done/histossww_'${YEAR}'_646566.root","ssww_presel_nmbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done/histossww_'${YEAR}'_676869.root","ssww_presel_nlbjetsgt0_nmbjets",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{j}","","done/histossww_'${YEAR}'_707172.root","ssww_presel_ptj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done/histossww_'${YEAR}'_737475.root","ssww_presel_etaj",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l}","GeV","done/histossww_'${YEAR}'_767778.root","ssww_presel_ptl",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|#eta^{l}|","","done/histossww_'${YEAR}'_798081.root","ssww_presel_etal",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag max","","done/histossww_'${YEAR}'_828384.root","ssww_presel_btagmax",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag min","","done/histossww_'${YEAR}'_858687.root","ssww_presel_btagmin",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}Xm_{ll}","","done/histossww_'${YEAR}'_88.root","ssww_datacard",0,'${YEAR}',"H(125)",1.0,0,"",1,'${APPLYSCALING}')';

fi
