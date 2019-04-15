#!/bin/sh

export NSEL='z';
export APPLYSCALING=1;
export YEAR=$1;

if [ $NSEL == 'z' ]; then
  export sf_dy=1.0;

  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0_'${YEAR}'_0.root","zmm_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0_'${YEAR}'_1.root","zee_mll",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0_'${YEAR}'_2.root","zmm_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"m_{ll}","GeV","done/histoDY0_'${YEAR}'_3.root","zee_mll_ss",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoDY0_'${YEAR}'_4.root","zmm_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,1,"N_{jets}","","done/histoDY0_'${YEAR}'_5.root","zee_njets",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done/histoDY0_'${YEAR}'_6.root","zmm_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,5,"p_{T}^{ll}","GeV","done/histoDY0_'${YEAR}'_7.root","zee_ptll",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done/histoDY0_'${YEAR}'_8.root","zmm_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"p_{T}^{miss}","GeV","done/histoDY0_'${YEAR}'_9.root","zee_met",1,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done/histoDY0_'${YEAR}'_10.root","zmm_phimet",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#phi p_{T}^{miss}","","done/histoDY0_'${YEAR}'_11.root","zee_phimet",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done/histoDY0_'${YEAR}'_12.root","zmm_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"#Delta#phi_{ll,p_{T}^{miss}}","","done/histoDY0_'${YEAR}'_13.root","zee_dphidilepmet",0,'${YEAR}',"",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{NPV}","","done/histoDY0_'${YEAR}'_14.root","zmm_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';
  root -q -b -l MitAnalysisRunII/panda/makePlots/finalPlot.C+'(0,2,"N_{NPV}","","done/histoDY0_'${YEAR}'_15.root","zee_npv",0,'${YEAR}',"H(125)",'${sf_dy}',0,"",1,'${APPLYSCALING}')';

fi
