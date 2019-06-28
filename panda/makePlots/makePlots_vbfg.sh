#!/bin/sh

export NSEL=$1;
export APPLYSCALING=$2;
export YEAR=$3;

if [ $NSEL == 'vbfg' ]; then
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{T}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_0.root","vbfg_sel0_mtg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{T}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_1.root","vbfg_sel1_mtg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{T}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_2.root","vbfg_sel2_mtg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{T}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_3.root","vbfg_sel3_mtg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{T}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_4.root","vbfg_sel4_mtg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{miss}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_5.root","vbfg_sel0_met",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{miss}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_6.root","vbfg_sel1_met",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{miss}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_7.root","vbfg_sel2_met",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{miss}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_8.root","vbfg_sel3_met",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{miss}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_9.root","vbfg_sel4_met",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{j}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_10.root","vbfg_sel0_njets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{j}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_11.root","vbfg_sel1_njets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{j}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_12.root","vbfg_sel2_njets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{j}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_13.root","vbfg_sel3_njets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{j}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_14.root","vbfg_sel4_njets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-p_{T}^{miss})","","done_vbfg/histoVBFG_mH125_'${YEAR}'_15.root","vbfg_sel0_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-p_{T}^{miss})","","done_vbfg/histoVBFG_mH125_'${YEAR}'_16.root","vbfg_sel1_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-p_{T}^{miss})","","done_vbfg/histoVBFG_mH125_'${YEAR}'_17.root","vbfg_sel2_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-p_{T}^{miss})","","done_vbfg/histoVBFG_mH125_'${YEAR}'_18.root","vbfg_sel3_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-p_{T}^{miss})","","done_vbfg/histoVBFG_mH125_'${YEAR}'_19.root","vbfg_sel4_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{jj}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_20.root","vbfg_sel0_mjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{jj}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_21.root","vbfg_sel1_mjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{jj}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_22.root","vbfg_sel2_mjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{jj}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_23.root","vbfg_sel3_mjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"m_{jj}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_24.root","vbfg_sel4_mjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta R_{jj}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_25.root","vbfg_sel0_drjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta R_{jj}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_26.root","vbfg_sel1_drjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta R_{jj}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_27.root","vbfg_sel2_drjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta R_{jj}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_28.root","vbfg_sel3_drjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta R_{jj}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_29.root","vbfg_sel4_drjj",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"Cut evolution","","done_vbfg/histoVBFG_mH125_'${YEAR}'_30.root","vbfg_sel0_cutevol",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"Cut evolution","","done_vbfg/histoVBFG_mH125_'${YEAR}'_31.root","vbfg_sel1_cutevol",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"Cut evolution","","done_vbfg/histoVBFG_mH125_'${YEAR}'_32.root","vbfg_sel2_cutevol",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"Cut evolution","","done_vbfg/histoVBFG_mH125_'${YEAR}'_33.root","vbfg_sel3_cutevol",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"Cut evolution","","done_vbfg/histoVBFG_mH125_'${YEAR}'_34.root","vbfg_sel4_cutevol",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{b jets}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_35.root","vbfg_sel0_nbjets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{b jets}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_36.root","vbfg_sel1_nbjets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{b jets}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_37.root","vbfg_sel2_nbjets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{b jets}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_38.root","vbfg_sel3_nbjets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{b jets}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_39.root","vbfg_sel4_nbjets",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{#tau}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_40.root","vbfg_sel0_ntau",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{#tau}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_41.root","vbfg_sel1_ntau",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{#tau}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_42.root","vbfg_sel2_ntau",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{#tau}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_43.root","vbfg_sel3_ntau",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"N_{#tau}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_44.root","vbfg_sel4_ntau",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"|#eta^{#gamma}|","","done_vbfg/histoVBFG_mH125_'${YEAR}'_45.root","vbfg_sel0_etag",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"|#eta^{#gamma}|","","done_vbfg/histoVBFG_mH125_'${YEAR}'_46.root","vbfg_sel1_etag",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"|#eta^{#gamma}|","","done_vbfg/histoVBFG_mH125_'${YEAR}'_47.root","vbfg_sel2_etag",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"|#eta^{#gamma}|","","done_vbfg/histoVBFG_mH125_'${YEAR}'_48.root","vbfg_sel3_etag",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"|#eta^{#gamma}|","","done_vbfg/histoVBFG_mH125_'${YEAR}'_49.root","vbfg_sel4_etag",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{#gamma}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_50.root","vbfg_sel0_ptg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{#gamma}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_51.root","vbfg_sel1_ptg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{#gamma}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_52.root","vbfg_sel2_ptg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{#gamma}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_53.root","vbfg_sel3_ptg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"p_{T}^{#gamma}","GeV","done_vbfg/histoVBFG_mH125_'${YEAR}'_54.root","vbfg_sel4_ptg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_55.root","vbfg_sel0_dphijg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_56.root","vbfg_sel1_dphijg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_57.root","vbfg_sel2_dphijg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_58.root","vbfg_sel3_dphijg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_59.root","vbfg_sel4_dphijg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#DeltaR(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_60.root","vbfg_sel0_drjg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#DeltaR(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_61.root","vbfg_sel1_drjg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#DeltaR(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_62.root","vbfg_sel2_drjg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#DeltaR(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_63.root","vbfg_sel3_drjg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#DeltaR(jet-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_64.root","vbfg_sel4_drjg",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(p_{T}^{miss}-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_65.root","vbfg_sel0_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(p_{T}^{miss}-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_66.root","vbfg_sel1_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(p_{T}^{miss}-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_67.root","vbfg_sel2_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(p_{T}^{miss}-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_68.root","vbfg_sel3_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"#Delta#phi(p_{T}^{miss}-#gamma)","","done_vbfg/histoVBFG_mH125_'${YEAR}'_69.root","vbfg_sel4_dphijmet",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"z^{*}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_70.root","vbfg_sel0_gzep",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"z^{*}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_71.root","vbfg_sel1_gzep",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"z^{*}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_72.root","vbfg_sel2_gzep",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"z^{*}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_73.root","vbfg_sel3_gzep",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"z^{*}","","done_vbfg/histoVBFG_mH125_'${YEAR}'_74.root","vbfg_sel4_gzep",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot_vbfg.C+'(0,1,"card","","done_vbfg/histoVBFG_mH125_'${YEAR}'_75.root","vbfg_sel_card",0,'${YEAR}',"qqH_{125}(inv.)",1,0,"",1,'${APPLYSCALING}')';

fi
