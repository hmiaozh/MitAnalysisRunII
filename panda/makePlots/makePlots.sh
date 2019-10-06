#!/bin/sh

export NSEL=$1;
export APPLYSCALING=$2;
export YEAR=$3;

if [ $NSEL == 'wz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWZ_'${YEAR}'_4.root","wz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|m_{ll}-m_{Z}|","GeV","done_ana/histoWZ_'${YEAR}'_9.root","wz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l W}","GeV","done_ana/histoWZ_'${YEAR}'_14.root","wz_wlpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_19.root","wz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{3l}","GeV","done_ana/histoWZ_'${YEAR}'_24.root","wz_m3l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l1 Z}","GeV","done_ana/histoWZ_'${YEAR}'_29.root","wz_z1lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l2 Z}","GeV","done_ana/histoWZ_'${YEAR}'_34.root","wz_z2lpt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{T}","GeV","done_ana/histoWZ_'${YEAR}'_39.root","wz_mt",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_44.root","wz_topsel_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoWZ_'${YEAR}'_49.root","wz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoWZ_'${YEAR}'_54.root","wz_topsel_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWZ_'${YEAR}'_59.root","wz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated p_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_64.root","wz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated p_{T}^{miss}","GeV","done_ana/histoWZ_'${YEAR}'_69.root","wz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Cut evolution","","done_ana/histoWZ_'${YEAR}'_77.root","wz_cutevol",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{#gamma}","GeV","done_ana/histoWZ_'${YEAR}'_78.root","wzgsel_ptg",0,'${YEAR}',"",1,0,"WZ#gamma region",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"|#eta^{#gamma}","","done_ana/histoWZ_'${YEAR}'_79.root","wzgsel_etag",0,'${YEAR}',"",1,0,"WZ#gamma region",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{l#gamma}","GeV","done_ana/histoWZ_'${YEAR}'_80.root","wzgsel_mlg",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zhpaper' ]; then
  export sf_dy=1.0;  
  export isBlinded=0;
  export YEAR=2016;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoWZ_'${YEAR}'_81.root","wz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch1_ch2",0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoZZ_'${YEAR}'_70.root","zz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch1_ch3",0)';
  export YEAR=2017;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoWZ_'${YEAR}'_81.root","wz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch2_ch2",0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoZZ_'${YEAR}'_70.root","zz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch2_ch3",0)';
  export YEAR=2018;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoWZ_'${YEAR}'_81.root","wz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch3_ch2",0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoZZ_'${YEAR}'_70.root","zz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticszh_comb.root","ch3_ch3",0)';
  export YEAR=2019;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoWZ_'${YEAR}'_81.root","wz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"comb/fitDiagnosticszh_comb.root","ch1_ch2",0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Emulated p_{T}^{miss}","GeVBIN","done_ana/histoZZ_'${YEAR}'_70.root","zz_card_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}',"comb/fitDiagnosticszh_comb.root","ch1_ch3",0)';

elif [ $NSEL == 'zz' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done_ana/histoZZ_'${YEAR}'_4.root","zz_mllmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV", "done_ana/histoZZ_'${YEAR}'_9.root","zz_mz",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done_ana/histoZZ_'${YEAR}'_14.root","zz_mzmin",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{4l}","GeV","done_ana/histoZZ_'${YEAR}'_19.root","zz_m4l",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z1}","GeV","done_ana/histoZZ_'${YEAR}'_24.root","zz_ptl1z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z1}","GeV","done_ana/histoZZ_'${YEAR}'_29.root","zz_ptl2z1",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l1 Z2}","GeV","done_ana/histoZZ_'${YEAR}'_34.root","zz_ptl1z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l2 Z2}","GeV","done_ana/histoZZ_'${YEAR}'_39.root","zz_ptl2z2",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_44.root","zz_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histoZZ_'${YEAR}'_49.root","zz_njets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZZ_'${YEAR}'_54.root","zz_nbjets",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated p_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_59.root","zz_zxliketight_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Emulated p_{T}^{miss}","GeV","done_ana/histoZZ_'${YEAR}'_64.root","zz_zxlikeloose_met",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Cut evolution","","done_ana/histoZZ_'${YEAR}'_69.root","zz_cutevol",0,'${YEAR}',"",1,0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zh' ]; then
  export sf_dy=1.0;  
  export isBlinded=0;
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
  hadd -f done_ana/histoZH_'${YEAR}'_5455.root done_ana/histoZH_'${YEAR}'_54.root done_ana/histoZH_'${YEAR}'_55.root 
  hadd -f done_ana/histoZH_'${YEAR}'_5758.root done_ana/histoZH_'${YEAR}'_57.root done_ana/histoZH_'${YEAR}'_58.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6061.root done_ana/histoZH_'${YEAR}'_60.root done_ana/histoZH_'${YEAR}'_61.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6364.root done_ana/histoZH_'${YEAR}'_63.root done_ana/histoZH_'${YEAR}'_64.root 
  hadd -f done_ana/histoZH_'${YEAR}'_6667.root done_ana/histoZH_'${YEAR}'_66.root done_ana/histoZH_'${YEAR}'_67.root 

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_0001.root","zh_zhtightsel_mt",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0304.root","zh_zhsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0607.root","zh_btagsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_0910.root","zh_presel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_1213.root","zh_ww_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_1516.root","zh_zhselnminus1_mz",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_1819.root","zh_zhselnminus1_njets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_2122.root","zh_zhselnminus1_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_2425.root","zh_zhselnminus1_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_2728.root","zh_zhselnminus1_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_3031.root","zh_zhselnminus1_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_3334.root","zh_zhselnminus1_ptll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_3637.root","zh_zhselnminus1_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_3940.root","zh_zhselnminus1_ntau",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_4243.root","zh_zhselnminus1_drll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_4546.root","zh_cutevol",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_5455.root","zh_presel_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_5758.root","zh_presel_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_6061.root","zh_presel_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_6364.root","zh_presel_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZH_'${YEAR}'_6667.root","zh_presel_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_48.root","zhll_zhsel_dphidilepmettight_nj0_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"0 jet category",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_49.root","zhll_zhsel_dphidilepmetloose_nj0_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"0 jet category",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_50.root","zhll_zhsel_dphidilepmettight_nj1_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"1 jet category",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_51.root","zhll_zhsel_dphidilepmetloose_nj1_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"1 jet category",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_52.root","zhem_zhsel_dphidilepmettight_njle1_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"#leq 1 jet category",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_53.root","zhem_zhsel_dphidilepmetloose_njle1_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"#leq 1 jet category",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_45.root","zhmm_cutevol",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_46.root","zhee_cutevol",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZH_'${YEAR}'_47.root","zhem_cutevol",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_54.root","zhmm_presel_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_55.root","zhee_presel_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_56.root","zhem_presel_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_57.root","zhmm_presel_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_58.root","zhee_presel_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_59.root","zhem_presel_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_60.root","zhmm_presel_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_61.root","zhee_presel_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_62.root","zhem_presel_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_63.root","zhmm_presel_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_64.root","zhee_presel_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_65.root","zhem_presel_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZH_'${YEAR}'_66.root","zhmm_presel_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZH_'${YEAR}'_67.root","zhee_presel_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoZH_'${YEAR}'_68.root","zhem_presel_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"No jet selection #eta_{j}","","done_ana/histoZH_'${YEAR}'_69.root","zh_nojetsel_etaj",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection N_{jets}","","done_ana/histoZH_'${YEAR}'_70.root","zh_nojetsel_njets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"No jet selection #Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_71.root","zh_nojetsel_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"No jet selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_72.root","zh_nojetsel_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH selection #phi","","done_ana/histoZH_'${YEAR}'_73.root","zh_zhsel_phi",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{llj}/ H_{T}^{llj}","","done_ana/histoZH_'${YEAR}'_74.root","zh_zhsel_vtptht",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{max}","GeV","done_ana/histoZH_'${YEAR}'_79.root","zh_zhsel_ptl1",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{min}","GeV","done_ana/histoZH_'${YEAR}'_80.root","zh_zhsel_ptl2",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}','${isBlinded}',"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{miss} X 4 regions","","done_ana/histoZH_'${YEAR}'_81.root","zh_card_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_0.root","zhmm_zhtightsel_mt",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_3.root","zhmm_zhsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_6.root","zhmm_btagsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_9.root","zhmm_presel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_12.root","zhmm_ww_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_15.root","zhmm_zhselnminus1_mz",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_18.root","zhmm_zhselnminus1_njets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_21.root","zhmm_zhselnminus1_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_24.root","zhmm_zhselnminus1_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_27.root","zhmm_zhselnminus1_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_30.root","zhmm_zhselnminus1_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_33.root","zhmm_zhselnminus1_ptll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_36.root","zhmm_zhselnminus1_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_39.root","zhmm_zhselnminus1_ntau",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_42.root","zhmm_zhselnminus1_drll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_1.root","zhee_zhtightsel_mt",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_4.root","zhee_zhsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_7.root","zhee_btagsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_10.root","zhee_presel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_13.root","zhee_ww_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_16.root","zhee_zhselnminus1_mz",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_19.root","zhee_zhselnminus1_njets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_22.root","zhee_zhselnminus1_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_25.root","zhee_zhselnminus1_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_28.root","zhee_zhselnminus1_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_31.root","zhee_zhselnminus1_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_34.root","zhee_zhselnminus1_ptll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_37.root","zhee_zhselnminus1_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_40.root","zhee_zhselnminus1_ntau",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_43.root","zhee_zhselnminus1_drll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH tight selection m_{T}","GeV","done_ana/histoZH_'${YEAR}'_2.root","zhem_zhtightsel_mt",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_5.root","zhem_zhsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B-tagged selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_8.root","zhem_btagsel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Preselection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_11.root","zhem_presel_met",1,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"WW-like selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_14.root","zhem_ww_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZH_'${YEAR}'_17.root","zhem_zhselnminus1_mz",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZH_'${YEAR}'_20.root","zhem_zhselnminus1_njets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{miss}","GeV","done_ana/histoZH_'${YEAR}'_23.root","zhem_zhselnminus1_met",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection |p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_ana/histoZH_'${YEAR}'_26.root","zhem_zhselnminus1_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection #Delta#phi_{ll,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_29.root","zhem_zhselnminus1_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZH_'${YEAR}'_32.root","zhem_zhselnminus1_nbjets",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZH_'${YEAR}'_35.root","zhem_zhselnminus1_ptll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZH_'${YEAR}'_38.root","zhem_zhselnminus1_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZH_'${YEAR}'_41.root","zhem_zhselnminus1_ntau",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N-1 ZH selection #Delta R_{ll}","","done_ana/histoZH_'${YEAR}'_44.root","zhem_zhselnminus1_drll",0,'${YEAR}',"Z(ll)H_{125}(inv.)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zhgpaper' ]; then
  export sf_dy=1.0;
  export isBlinded=0;
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_09101112.root  done_ana/histoZHG_mH125_'${YEAR}'_9.root done_ana/histoZHG_mH125_'${YEAR}'_10.root done_ana/histoZHG_mH125_'${YEAR}'_11.root done_ana/histoZHG_mH125_'${YEAR}'_12.root 
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_171819.root   done_ana/histoZHG_mH125_'${YEAR}'_17.root done_ana/histoZHG_mH125_'${YEAR}'_18.root done_ana/histoZHG_mH125_'${YEAR}'_19.root 

  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_2.root","zhg_emusel_mtg_prefit",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{e#mu}{control region}",0,'${APPLYSCALING}',"","",0,"","",1)';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_09101112.root","zhg_wzsel_mtg_prefit",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{WZ}{control region}",0,'${APPLYSCALING}',"","",0,"","")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_171819.root","zhg_zzsel_mtg_prefit",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{ZZ}{control region}",0,'${APPLYSCALING}',"","",0,"","")';

  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_2.root","zhg_emusel_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{e#mu}{control region}",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","",1)';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_09101112.root","zhg_wzsel_mtg_withratio",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{WZ}{control region}",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_171819.root","zhg_zzsel_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{ZZ}{control region}",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","")';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_2.root","zhg_emusel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{e#mu}{control region}",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","",1)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_09101112.root","zhg_wzsel_mtg",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{WZ}{control region}",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINNoBSM","done_ana/histoZHG_mH125_'${YEAR}'_171819.root","zhg_zzsel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"#splitline{ZZ}{control region}",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"","")';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_54.root","zhg_sigsel125200_etaglt1_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| < 1",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH200_2019_54.root","Z(ll)H_{200}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_sigsel125200_etaggt1_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| > 1",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH200_2019_54.root","Z(ll)H_{200}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_54.root","zhg_sigsel125300_etaglt1_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| < 1",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH300_2019_54.root","Z(ll)H_{300}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_sigsel125300_etaggt1_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM}+ bkg.)",'${sf_dy}',0,"|#eta^{#gamma}| > 1",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH300_2019_54.root","Z(ll)H_{300}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM}+ bkg.)")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_54.root","zhg_sigsel125200_etaglt1_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| < 1",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH200_2019_54.root","Z(ll)H_{200}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_sigsel125200_etaggt1_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| > 1",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH200_2019_54.root","Z(ll)H_{200}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_54.root","zhg_sigsel125300_etaglt1_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| < 1",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH300_2019_54.root","Z(ll)H_{300}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
  #root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBINStack","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_sigsel125300_etaggt1_mtg_withratio",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.",'${sf_dy}',0,"|#eta^{#gamma}| > 1",1,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125_obs.root","ZHG_2019_125",0,"done_ana/histoZHG_mH300_2019_54.root","Z(ll)H_{300}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})+ bkg.")';
elif [ $NSEL == 'zhg' ]; then
  export sf_dy=1.0;
  export isBlinded=0;
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_0001.root done_ana/histoZHG_mH125_'${YEAR}'_0.root   done_ana/histoZHG_mH125_'${YEAR}'_1.root 
  hadd -f done_ana/histoZHG_mH200_'${YEAR}'_0001.root done_ana/histoZHG_mH200_'${YEAR}'_0.root   done_ana/histoZHG_mH200_'${YEAR}'_1.root 
  hadd -f done_ana/histoZHG_mH300_'${YEAR}'_0001.root done_ana/histoZHG_mH300_'${YEAR}'_0.root   done_ana/histoZHG_mH300_'${YEAR}'_1.root 

  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_0304.root done_ana/histoZHG_mH125_'${YEAR}'_3.root   done_ana/histoZHG_mH125_'${YEAR}'_4.root 
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_0607.root done_ana/histoZHG_mH125_'${YEAR}'_6.root   done_ana/histoZHG_mH125_'${YEAR}'_7.root 
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_13141516.root done_ana/histoZHG_mH125_'${YEAR}'_13.root done_ana/histoZHG_mH125_'${YEAR}'_14.root done_ana/histoZHG_mH125_'${YEAR}'_15.root done_ana/histoZHG_mH125_'${YEAR}'_16.root
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_2122.root done_ana/histoZHG_mH125_'${YEAR}'_21.root done_ana/histoZHG_mH125_'${YEAR}'_22.root 
  hadd -f done_ana/histoZHG_mH125_'${YEAR}'_3738.root  done_ana/histoZHG_mH125_'${YEAR}'_37.root done_ana/histoZHG_mH125_'${YEAR}'_38.root 

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH125_'${YEAR}'_0001.root","zhg_zh125sel_mtg"   ,0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125.root","ZHG_2019_125")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH200_'${YEAR}'_0001.root","zhg_zh200sel_mtg",0,'${YEAR}',"Z(ll)H_{200}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_200.root","ZHG_2019_200")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH300_'${YEAR}'_0001.root","zhg_zh300sel_mtg",0,'${YEAR}',"Z(ll)H_{300}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_300.root","ZHG_2019_300")';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH125_'${YEAR}'_0304.root","zhg_btagsel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"B tagged region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH125_'${YEAR}'_0607.root","zhg_zllgsel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"Z#gamma region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH125_'${YEAR}'_13141516.root","zhg_wzgsel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"WZ#gamma region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeVBIN","done_ana/histoZHG_mH125_'${YEAR}'_2122.root","zhg_wwsel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"WW region",0,1)';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection |m_{ll}-m_{Z}|","GeV","done_ana/histoZHG_mH125_'${YEAR}'_24.root","zhg_zhselnminus1_mz",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{jets}","","done_ana/histoZHG_mH125_'${YEAR}'_25.root","zhg_zhselnminus1_njets",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection p_{T}^{miss}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_26.root","zhg_zhselnminus1_met",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection |p_{T}^{ll}-p_{T}^{p_{T}^{miss}+E_{T}^{gamma}}|/p_{T}^{ll}","","done_ana/histoZHG_mH125_'${YEAR}'_27.root","zhg_zhselnminus1_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection #Delta#phi_{ll,p_{T}^{miss}+E_{T}^{gamma}}","","done_ana/histoZHG_mH125_'${YEAR}'_28.root","zhg_zhselnminus1_dphidilepmet",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{b jets}","","done_ana/histoZHG_mH125_'${YEAR}'_29.root","zhg_zhselnminus1_nbjets",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"N-1 ZH selection p_{T}^{ll}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_30.root","zhg_zhselnminus1_ptll",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection #Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZHG_mH125_'${YEAR}'_31.root","zhg_zhselnminus1_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection N_{#tau}","","done_ana/histoZHG_mH125_'${YEAR}'_32.root","zhg_zhselnminus1_ntau",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,20,"N-1 ZH selection m_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_33.root","zhg_zhselnminus1_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N-1 ZH selection m_{ll#gamma}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_34.root","zhg_zhselnminus1_mllg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"|#eta^{#gamma}|","","done_ana/histoZHG_mH125_'${YEAR}'_35.root","zhg_zhsel_etag",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125.root","ZHG_2019_125")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH selection Tightphoton veto","","done_ana/histoZHG_mH125_'${YEAR}'_36.root","zhg_zhsel_photonveto",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_mH125_'${YEAR}'_3738.root","zhg_zll_cutevol",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_mH125_'${YEAR}'_37.root","zhg_zmm_cutevol",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_mH125_'${YEAR}'_38.root","zhg_zee_cutevol",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"ZH cut evolution","","done_ana/histoZHG_mH125_'${YEAR}'_39.root","zhg_zem_cutevol",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"ZH #eta_{j}","","done_ana/histoZHG_mH125_'${YEAR}'_40.root","zhg_zhllsel_etaj",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_41.root","zhg_zllhselnminus4_met",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll}-p_{T}^{miss#gamma}|/p_{T}^{ll}","","done_ana/histoZHG_mH125_'${YEAR}'_42.root","zhg_zllhselnminus4_ptfracg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|p_{T}^{ll#gamma}-p_{T}^{miss}|/p_{T}^{ll#gamma}","","done_ana/histoZHG_mH125_'${YEAR}'_43.root","zhg_zllhselnminus4_ptfrac",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll,p_{T}^{miss#gamma}}","","done_ana/histoZHG_mH125_'${YEAR}'_44.root","zhg_zllhselnminus4_dphidilepmetg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll#gamma,p_{T}^{miss}}","","done_ana/histoZHG_mH125_'${YEAR}'_45.root","zhg_zllhselnminus4_dphidilepgmet",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",1,0)';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_46.root","zhg_zllhselnminus4_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"#Delta#phi_{ll,p_{T}^{miss}+E_{T}^{gamma}}","","done_ana/histoZHG_mH125_'${YEAR}'_47.root","zhg_zllhselnminus3_dphidilepmetg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jet,p_{T}^{miss}}","","done_ana/histoZHG_mH125_'${YEAR}'_48.root","zhg_zllhselnminus3_dphijetmet",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_49.root","zhg_zllhselnminus3_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Leading p_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_50.root","zhg_zhgsel_ptl1",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"Signal region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Trailing p_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_51.root","zhg_zhgsel_ptl2",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"Signal region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"WZ selection m_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_52.root","zhg_wzsel_emulation_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"WZ region",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Z+fake photon selection m_{T}","GeV","done_ana/histoZHG_mH125_'${YEAR}'_53.root","zhg_fakesel_mtg",0,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}',0,"WZ region",0,'${APPLYSCALING}')';
  if [ $YEAR != 2019 ]; then
    root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Bin #","","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_card_mt",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"done_ana/fitDiagnosticszhg_comb_125.root","ZHG_'${YEAR}'_125")';
  elif [ $YEAR == 2019 ]; then
    root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Bin #","","done_ana/histoZHG_mH125_'${YEAR}'_55.root","zhg_card_mt",1,'${YEAR}',"Z(ll)H_{125}(#gamma_{D}+#gamma) (0.1 #times #sigma_{SM})",'${sf_dy}','${isBlinded}',"",0,'${APPLYSCALING}',"comb/fitDiagnosticszhg_comb_125.root","ZHG_'${YEAR}'_125")';
  fi

elif [ $NSEL == 'z' ]; then
  export sf_dy=1.0;

  hadd -f done_dy/histoDY0zll_'${YEAR}'_4243.root done_dy/histoDY0zll_'${YEAR}'_42.root done_dy/histoDY0zll_'${YEAR}'_43.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_4243.root","zll_npv",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,1)';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_2425.root done_dy/histoDY0zll_'${YEAR}'_24.root done_dy/histoDY0zll_'${YEAR}'_25.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_2425.root","zll_metphi",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_87.root","zll_corrmetphi",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_2728.root done_dy/histoDY0zll_'${YEAR}'_27.root done_dy/histoDY0zll_'${YEAR}'_28.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_2728.root","zll_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  hadd -f done_dy/histoDY0zll_'${YEAR}'_3031.root done_dy/histoDY0zll_'${YEAR}'_30.root done_dy/histoDY0zll_'${YEAR}'_31.root
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_3031.root","zll_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_0.root","zmm_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_1.root","zee_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_2.root","zem_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_3.root","zmm_mll_ss",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_4.root","zee_mll_ss",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_5.root","zem_mll_ss",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_6.root","zmm_ncjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_7.root","zee_ncjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{central jets}","","done_dy/histoDY0zll_'${YEAR}'_8.root","zem_ncjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_9.root","zmm_njets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_10.root","zee_njets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoDY0zll_'${YEAR}'_11.root","zem_njets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_12.root","zmm_ptll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_13.root","zee_ptll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_14.root","zem_ptll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_15.root","zmm_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_16.root","zee_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_17.root","zem_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Puppi p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_18.root","zmm_puppimet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Puppi p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_19.root","zee_puppimet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Puppi p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_20.root","zem_puppimet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_21.root","zmm_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_22.root","zee_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"X/Y Corr. p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_23.root","zem_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_24.root","zmm_metphi",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_25.root","zee_metphi",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done_dy/histoDY0zll_'${YEAR}'_26.root","zem_metphi",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_27.root","zmm_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_28.root","zee_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_29.root","zem_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_30.root","zmm_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_31.root","zee_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,X/Y Corr. p_{T}^{miss}}","","done_dy/histoDY0zll_'${YEAR}'_32.root","zem_dphidilepcorrmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_33.root","zmm_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_34.root","zee_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll}","","done_dy/histoDY0zll_'${YEAR}'_35.root","zem_dphill",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_36.root","zmm_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_37.root","zee_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|p_{T}^{ll}-p_{T}^{miss}|/p_{T}^{ll}","","done_dy/histoDY0zll_'${YEAR}'_38.root","zem_ptfrac",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_39.root","zmm_drll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_40.root","zee_drll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta R_{ll}","","done_dy/histoDY0zll_'${YEAR}'_41.root","zem_drll",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_42.root","zmm_npv",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_43.root","zee_npv",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{vtx}","","done_dy/histoDY0zll_'${YEAR}'_44.root","zem_npv",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_45.root","zmm_eta",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_46.root","zee_eta",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Leading #eta_{l}","","done_dy/histoDY0zll_'${YEAR}'_47.root","zem_eta",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l}","GeV","done_dy/histoDY0zll_'${YEAR}'_48.root","zmm_ptl",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l}","GeV","done_dy/histoDY0zll_'${YEAR}'_49.root","zee_ptl",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{l}","GeV","done_dy/histoDY0zll_'${YEAR}'_50.root","zem_ptl",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_51.root","zmm_nlbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_52.root","zee_nlbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Loose b jets}","","done_dy/histoDY0zll_'${YEAR}'_53.root","zem_nlbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_54.root","zmm_nmbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_55.root","zee_nmbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{Medium b jets}","","done_dy/histoDY0zll_'${YEAR}'_56.root","zem_nmbjets",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_57.root","zll_ptj",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag","","done_dy/histoDY0zll_'${YEAR}'_58.root","zll_btag",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#eta^{j}","","done_dy/histoDY0zll_'${YEAR}'_59.root","zll_etaj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi^{j}","","done_dy/histoDY0zll_'${YEAR}'_60.root","zll_phij",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_61.root","zll_etajlt2p5_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_62.root","zll_etajlt2p5_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_63.root","zll_etajlt2p5_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_64.root","zll_etajlt2p5_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_65.root","zll_etajcrack_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_66.root","zll_etajcrack_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_67.root","zll_etajcrack_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_68.root","zll_etajcrack_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_69.root","zll_etajgt3p0_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_70.root","zll_etajgt3p0_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_71.root","zll_etajgt3p0_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_72.root","zll_etajgt3p0_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_73.root","zll_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_74.root","zll_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_75.root","zll_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_76.root","zll_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_77.root","zll_ptjgt100_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_78.root","zll_ptjgt100_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_79.root","zll_ptjgt100_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_80.root","zll_ptjgt100_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_81.root","zll_ptjgt100_etajlt2p5_met",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_82.root","zll_ptjgt100_etajlt2p5_corrmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_83.root","zll_ptjgt100_etajlt2p5_met_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_84.root","zll_ptjgt100_etajlt2p5_corrmet_nonvtx",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Raw p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_85.root","zll_rawmet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,4,"Calo p_{T}^{miss}","GeV","done_dy/histoDY0zll_'${YEAR}'_86.root","zll_calomet",1,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_dy/histoDY0zll_'${YEAR}'_118.root","zll_2j_mjj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#eta_{jj}","","done_dy/histoDY0zll_'${YEAR}'_119.root","zll_2j_detajj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jj}","","done_dy/histoDY0zll_'${YEAR}'_120.root","zll_2j_dphijj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#eta_{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_121.root","zll_2j_etaj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_122.root","zll_2j_ptj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_dy/histoDY0zll_'${YEAR}'_123.root","zll_2j_mjjgt500_mjj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#eta_{jj}","","done_dy/histoDY0zll_'${YEAR}'_124.root","zll_2j_mjjgt500_detajj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#Delta#phi_{jj}","","done_dy/histoDY0zll_'${YEAR}'_125.root","zll_2j_mjjgt500_dphijj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"#eta_{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_126.root","zll_2j_mjjgt500_etaj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{j}","GeV","done_dy/histoDY0zll_'${YEAR}'_127.root","zll_2j_mjjgt500_ptj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'zmass' ]; then
  export sf_dy=1.0;

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_88.root","zmm_mll_88",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_89.root","zmm_mll_89",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_90.root","zmm_mll_90",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_91.root","zmm_mll_91",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_92.root","zmm_mll_92",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_93.root","zee_mll_93",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_94.root","zee_mll_94",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_95.root","zee_mll_95",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_96.root","zee_mll_96",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_97.root","zee_mll_97",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_98.root","zmm_mll_98",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_99.root","zee_mll_99",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_100.root","zmm_mll_100",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_101.root","zee_mll_101",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_102.root","zmm_mll_102",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_103.root","zee_mll_103",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_104.root","zmm_mll_104",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_105.root","zee_mll_105",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_106.root","zmm_mll_106",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_107.root","zee_mll_107",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_108.root","zmm_mll_108",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_109.root","zee_mll_109",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_110.root","zmm_mll_110",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_111.root","zee_mll_111",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_112.root","zmm_mll_112",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_113.root","zee_mll_113",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_114.root","zmm_mll_114",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_115.root","zee_mll_115",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_116.root","zmm_mll_116",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0zll_'${YEAR}'_117.root","zee_mll_117",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'ssww' ]; then
  export isBlinded=1;
  hadd -f done_ana/histossww_'${YEAR}'_000102.root done_ana/histossww_'${YEAR}'_0.root   done_ana/histossww_'${YEAR}'_1.root    done_ana/histossww_'${YEAR}'_2.root 
  hadd -f done_ana/histossww_'${YEAR}'_030405.root done_ana/histossww_'${YEAR}'_3.root   done_ana/histossww_'${YEAR}'_4.root    done_ana/histossww_'${YEAR}'_5.root 
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
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_000102.root","ssww_sswwselnminus1_mll",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{miss}","GeV","done_ana/histossww_'${YEAR}'_030405.root","ssww_sswwselnminus1_met",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_ana/histossww_'${YEAR}'_060708.root","ssww_sswwselnminus1_njets",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done_ana/histossww_'${YEAR}'_091011.root","ssww_sswwselnminus1_detajj",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_121314.root","ssww_sswwselnminus1_mjj",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done_ana/histossww_'${YEAR}'_151617.root","ssww_sswwselnminus1_zstar",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histossww_'${YEAR}'_181920.root","ssww_sswwselnminus1_nbjets",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{#tau}","","done_ana/histossww_'${YEAR}'_212223.root","ssww_sswwselnminus1_ntau",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{leading}","GeV","done_ana/histossww_'${YEAR}'_242526.root","ssww_sswwsel_ptl1",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{trailing}","GeV","done_ana/histossww_'${YEAR}'_272829.root","ssww_sswwsel_ptl2",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_303132.root","ssww_sswwsel_mjj",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_33343536.root","ssww_wzsel_mjj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}',"comb/fitDiagnosticsssww_comb.root","SSWW_2019")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_373839.root","ssww_btagsel_mjj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_404142.root","ssww_sswwsel_mll",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_434445.root","ssww_btagsel_mll",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_464748.root","ssww_sswwsel_etaj",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_495051.root","ssww_btagsel_etaj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"|#Delta#eta_{jj}|","","done_ana/histossww_'${YEAR}'_525354.root","ssww_presel_detajj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_555657.root","ssww_presel_mjj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"Max z^{*}","","done_ana/histossww_'${YEAR}'_585960.root","ssww_presel_zstar",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{loose b jets}","","done_ana/histossww_'${YEAR}'_616263.root","ssww_presel_nlbjets",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done_ana/histossww_'${YEAR}'_646566.root","ssww_presel_nmbjets",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{medium b jets}","","done_ana/histossww_'${YEAR}'_676869.root","ssww_presel_nlbjetsgt0_nmbjets",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{j}","","done_ana/histossww_'${YEAR}'_707172.root","ssww_presel_ptj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#eta^{j}","","done_ana/histossww_'${YEAR}'_737475.root","ssww_presel_etaj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"p_{T}^{l}","GeV","done_ana/histossww_'${YEAR}'_767778.root","ssww_presel_ptl",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"|#eta^{l}|","","done_ana/histossww_'${YEAR}'_798081.root","ssww_presel_etal",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag max","","done_ana/histossww_'${YEAR}'_828384.root","ssww_presel_btagmax",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"B tag min","","done_ana/histossww_'${YEAR}'_858687.root","ssww_presel_btagmin",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,10,"m_{ll}","GeV","done_ana/histossww_'${YEAR}'_888990.root","ssww_zsel_mll",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_91.root","ssww_zzsel_mjj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}',"comb/fitDiagnosticsssww_comb.root","SSWW_2019")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}","GeV","done_ana/histossww_'${YEAR}'_92.root","ssww_wzbsel_mjj",0,'${YEAR}',"H_{125}",1.0,0,"",1,'${APPLYSCALING}',"comb/fitDiagnosticsssww_comb.root","SSWW_2019")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"BDT score","","done_ana/histossww_'${YEAR}'_93.root","ssww_wzsel_bdt",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}',"comb/fitDiagnosticsssww_comb.root","SSWW_2019")';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"m_{jj}Xm_{ll}","","done_ana/histossww_'${YEAR}'_94.root","ssww_datacard",0,'${YEAR}',"H_{125}",1.0,'${isBlinded}',"",1,'${APPLYSCALING}',"comb/fitDiagnosticsssww_comb.root","SSWW_2019")';

elif [ $NSEL == 'zlg' ]; then
  export sf_dy=1.0;

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0MGStudy_'${YEAR}'_0.root","zmg_mmg",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{T}^{#mu#gamma}","GeV","done_dy/histoDY0MGStudy_'${YEAR}'_1.root","zmg_mt",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_0.root","zlg_mee",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_2.root","zlg_ptee",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_3.root","zlg_ptee_0",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_4.root","zlg_ptee_1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_5.root","zlg_ptee_2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_6.root","zlg_ptee_3",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_1.root","zlg_meg",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_7.root","zlg_pteg",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_8.root","zlg_pteg_0",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_9.root","zlg_pteg_1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_10.root","zlg_pteg_2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"p_{T}^{ll}","GeV","done_dy/histoDY0EGStudy_'${YEAR}'_11.root","zlg_pteg_3",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_0.root","zlg_meg_0",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_1.root","zlg_meg_1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_2.root","zlg_meg_2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_3.root","zlg_meg_3",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_4.root","zlg_meg_4",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_5.root","zlg_meg_5",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_6.root","zlg_meg_6",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_7.root","zlg_meg_7",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_8.root","zlg_meg_8",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_9.root","zlg_meg_9",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_10.root","zlg_meg_10",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_11.root","zlg_meg_11",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_12.root","zlg_meg_12",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_13.root","zlg_meg_13",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_14.root","zlg_meg_14",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_15.root","zlg_meg_15",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_16.root","zlg_meg_16",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_17.root","zlg_meg_17",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_18.root","zlg_meg_18",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_19.root","zlg_meg_19",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_20.root","zlg_meg_20",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_21.root","zlg_meg_21",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_22.root","zlg_meg_22",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_23.root","zlg_meg_23",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_24.root","zlg_meg_24",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_25.root","zlg_meg_25",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_26.root","zlg_meg_26",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ee}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_27.root","zlg_meg_27",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_28.root","zlg_meg_28",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_29.root","zlg_meg_29",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_30.root","zlg_meg_30",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_31.root","zlg_meg_31",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_32.root","zlg_meg_32",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_33.root","zlg_meg_33",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_34.root","zlg_meg_34",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_35.root","zlg_meg_35",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_36.root","zlg_meg_36",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_37.root","zlg_meg_37",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_38.root","zlg_meg_38",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_39.root","zlg_meg_39",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_40.root","zlg_meg_40",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_41.root","zlg_meg_41",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_42.root","zlg_meg_42",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_43.root","zlg_meg_43",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_44.root","zlg_meg_44",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_45.root","zlg_meg_45",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_46.root","zlg_meg_46",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_47.root","zlg_meg_47",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_48.root","zlg_meg_48",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_49.root","zlg_meg_49",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_50.root","zlg_meg_50",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_51.root","zlg_meg_51",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_52.root","zlg_meg_52",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_53.root","zlg_meg_53",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_54.root","zlg_meg_54",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{l#gamma}","GeV","done_dy/histoDY0EGStudyMass_'${YEAR}'_55.root","zlg_meg_55",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",0,'${APPLYSCALING}')';

elif [ $NSEL == 'zhem1516' ]; then
  export sf_dy=1.0;
  export YEAR=2018;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_0.root","zll_hem0_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_1.root","zll_hem1_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{l}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_2.root","zll_hem0_ptl",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{l}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_3.root","zll_hem1_ptl",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_4.root","zll_hem0_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_5.root","zll_hem1_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoHEMDY0zll_'${YEAR}'_6.root","zll_hem0_nj1_njets",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done_dy/histoHEMDY0zll_'${YEAR}'_7.root","zll_hem1_nj1_njets",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_8.root","zll_hem0_nj1_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_9.root","zll_hem1_nj1_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{j}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_10.root","zll_hem0_nj1_ptj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{j}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_11.root","zll_hem1_nj1_ptj",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{l}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_12.root","zll_hem0_nj1_ptl",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{l}","GeV","done_dy/histoHEMDY0zll_'${YEAR}'_13.root","zll_hem1_nj1_ptl",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#mu #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_14.root","zll_hem_phi_m",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"e #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_15.root","zll_hem_phi_e",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#gamma #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_16.root","zll_hem_phi_p",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Jet #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_17.root","zll_hem_phi_j",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Jet #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_18.root","zll_hem0_met50_phi_j",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta #phi_{jet,p_{T}^{miss}}","","done_dy/histoHEMDY0zll_'${YEAR}'_19.root","zll_hem0_met50_dphijetmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Jet #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_20.root","zll_hem1_met50_phi_j",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta #phi_{jet,p_{T}^{miss}}","","done_dy/histoHEMDY0zll_'${YEAR}'_21.root","zll_hem1_met50_dphijetmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"Jet #phi","","done_dy/histoHEMDY0zll_'${YEAR}'_22.root","zll_hem1_met50_dphijetmetgt2p6_phi_j",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

elif [ $NSEL == 'ww' ]; then
  export sf_dy=1.0;
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_0.root","wwmm_0j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_1.root","wwee_0j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_2.root","wwem_0j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_3.root","wwmm_1j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_4.root","wwee_1j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_5.root","wwem_1j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_6.root","wwmm_2j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_7.root","wwee_2j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_8.root","wwem_2j_allbutmll_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_9.root", "wwmm_0j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_10.root","wwee_0j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_11.root","wwem_0j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_12.root","wwmm_1j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_13.root","wwee_1j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_14.root","wwem_1j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_15.root","wwmm_2j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_16.root","wwee_2j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"MINPMET","GeV","done_ana/histoWW_'${YEAR}'_17.root","wwem_2j_allbutminpmet_minpmet",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_18.root","wwmm_0j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_19.root","wwee_0j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_20.root","wwem_0j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_21.root","wwmm_1j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_22.root","wwee_1j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_23.root","wwem_1j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_24.root","wwmm_2j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_25.root","wwee_2j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{miss}","GeV","done_ana/histoWW_'${YEAR}'_26.root","wwem_2j_allbutminpmet_met",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_27.root","wwmm_0j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_28.root","wwee_0j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_29.root","wwem_0j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_30.root","wwmm_1j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_31.root","wwee_1j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_32.root","wwem_1j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_33.root","wwmm_2j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_34.root","wwee_2j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_35.root","wwem_2j_dysel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_36.root","wwmm_0j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_37.root","wwee_0j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_38.root","wwem_0j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_39.root","wwmm_1j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_40.root","wwee_1j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_41.root","wwem_1j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_42.root","wwmm_2j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_43.root","wwee_2j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done_ana/histoWW_'${YEAR}'_44.root","wwem_2j_allbutptll_ptll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_45.root","wwmm_0j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_46.root","wwee_0j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_47.root","wwem_0j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_48.root","wwmm_1j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_49.root","wwee_1j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_50.root","wwem_1j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_51.root","wwmm_2j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_52.root","wwee_2j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{b jets}","","done_ana/histoWW_'${YEAR}'_53.root","wwem_2j_allbutbtag_nbtag",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_54.root","wwmm_0j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_55.root","wwee_0j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_56.root","wwem_0j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_57.root","wwmm_1j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_58.root","wwee_1j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_59.root","wwem_1j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_60.root","wwmm_2j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_61.root","wwee_2j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_62.root","wwem_2j_wwsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_63.root","wwmm_0j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_64.root","wwee_0j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_65.root","wwem_0j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_66.root","wwmm_1j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_67.root","wwee_1j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_68.root","wwem_1j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_69.root","wwmm_2j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_70.root","wwee_2j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_71.root","wwem_2j_wwsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_72.root","wwmm_0j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_73.root","wwee_0j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_74.root","wwem_0j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_75.root","wwmm_1j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_76.root","wwee_1j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_77.root","wwem_1j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_78.root","wwmm_2j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_79.root","wwee_2j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_80.root","wwem_2j_wwsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_81.root","wwmm_0j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_82.root","wwee_0j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_83.root","wwem_0j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_84.root","wwmm_1j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_85.root","wwee_1j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_86.root","wwem_1j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_87.root","wwmm_2j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_88.root","wwee_2j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_89.root","wwem_2j_wwsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_90.root","wwmm_0j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_91.root","wwee_0j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_92.root","wwem_0j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_93.root","wwmm_1j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_94.root","wwee_1j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_95.root","wwem_1j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_96.root","wwmm_2j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_97.root","wwee_2j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_98.root","wwem_2j_sssel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_99.root","wwmm_0j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_100.root","wwee_0j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_101.root","wwem_0j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_102.root","wwmm_1j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_103.root","wwee_1j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_104.root","wwem_1j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_105.root","wwmm_2j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_106.root","wwee_2j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_107.root","wwem_2j_sssel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_108.root","wwmm_0j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_109.root","wwee_0j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_110.root","wwem_0j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_111.root","wwmm_1j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_112.root","wwee_1j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_113.root","wwem_1j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_114.root","wwmm_2j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_115.root","wwee_2j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_116.root","wwem_2j_sssel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_117.root","wwmm_0j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_118.root","wwee_0j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_119.root","wwem_0j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_120.root","wwmm_1j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_121.root","wwee_1j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_122.root","wwem_1j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_123.root","wwmm_2j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_124.root","wwee_2j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_125.root","wwem_2j_sssel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_126.root","wwmm_0j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_127.root","wwee_0j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_128.root","wwem_0j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_129.root","wwmm_1j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_130.root","wwee_1j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_131.root","wwem_1j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_132.root","wwmm_2j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_133.root","wwee_2j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{leading}","GeV","done_ana/histoWW_'${YEAR}'_134.root","wwem_2j_topsel_ptl1",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_135.root","wwmm_0j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_136.root","wwee_0j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_137.root","wwem_0j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_138.root","wwmm_1j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_139.root","wwee_1j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_140.root","wwem_1j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_141.root","wwmm_2j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_142.root","wwee_2j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{trailing}","GeV","done_ana/histoWW_'${YEAR}'_143.root","wwem_2j_topsel_ptl2",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_144.root","wwmm_0j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_145.root","wwee_0j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_146.root","wwem_0j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_147.root","wwmm_1j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_148.root","wwee_1j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_149.root","wwem_1j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_150.root","wwmm_2j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_151.root","wwee_2j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"m_{ll}","GeV","done_ana/histoWW_'${YEAR}'_152.root","wwem_2j_topsel_mll",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_153.root","wwmm_0j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_154.root","wwee_0j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_155.root","wwem_0j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_156.root","wwmm_1j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_157.root","wwee_1j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_159.root","wwem_1j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_159.root","wwmm_2j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_160.root","wwee_2j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"#Delta#phi_{ll}","dg.","done_ana/histoWW_'${YEAR}'_161.root","wwem_2j_topsel_dphill",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_162.root","wwmm_wwsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_163.root","wwee_wwsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_164.root","wwem_wwsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_165.root","wwmm_topsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_166.root","wwee_topsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{WW}","GeV","done_ana/histoWW_'${YEAR}'_167.root","wwem_topsel_ptww",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"Channel","","done_ana/histoWW_'${YEAR}'_168.root","ww_datacard",0,'${YEAR}',"H_{125}",'${sf_dy}',0,"",1,'${APPLYSCALING}',"done_ana/fitDiagnosticsww_'${YEAR}'.root","ch1",1)';

fi
