#!/bin/sh

export YEAR="";

if [ $# -lt 1 ]; then
   echo "TOO FEW PARAMETERS"
   exit
fi

export MLFITWH2016="";
export MLFITVZ2016="";
export MLFITWH2017="";
export MLFITVZ2017="";
if [ $# -eq 2 ]; then
  echo "USING MLFIT RESULTS"
  export MLFITWH2016="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/default/inputs_wh_2016/fitDiagnosticsWH.root";
  export MLFITWH2017="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/default/inputs_wh_2017/fitDiagnosticsWH.root";
fi

### 2016
if [ $1 == "2016" ]; then
export YEAR=2016;
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHSR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHSR.root",  "W(#mu#nu)H SR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHFJSR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHFJSR.root","W(#mu#nu)H SR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHSR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHSR.root",  "W(e#nu)H SR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHFJSR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHFJSR.root","W(e#nu)H SR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHLightFlavorCR.root",  "W(#mu#nu)H Light Flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHLightFlavorFJCR.root","W(#mu#nu)H Light Flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHLightFlavorCR.root",  "W(e#nu)H Light Flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHLightFlavorFJCR.root","W(e#nu)H Light Flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHHeavyFlavorCR.root",  "W(#mu#nu)H Heavy flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHHeavyFlavorFJCR.root","W(#mu#nu)H Heavy flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHHeavyFlavorCR.root",  "W(e#nu)H Heavy flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHHeavyFlavorFJCR.root","W(e#nu)H Heavy flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWH2TopCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnH2TopCR.root",  "W(#mu#nu)H Top CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHTT2bFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WmnHTT2bFJCR.root","W(#mu#nu)H Top CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWH2TopCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenH2TopCR.root",  "W(e#nu)H Top CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHTT2bFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WenHTT2bFJCR.root","W(e#nu)H Top CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITWH2016}'",'${YEAR}')'

### 2017
elif [ $1 == "2017" ]; then
export YEAR=2017;
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHSR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHSR.root",  "W(#mu#nu)H SR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHFJSR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHFJSR.root","W(#mu#nu)H SR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHSR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHSR.root",  "W(e#nu)H SR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHFJSR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHFJSR.root","W(e#nu)H SR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHLightFlavorCR.root",  "W(#mu#nu)H Light Flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHLightFlavorFJCR.root","W(#mu#nu)H Light Flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHLightFlavorCR.root",  "W(e#nu)H Light Flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHLightFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHLightFlavorFJCR.root","W(e#nu)H Light Flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHHeavyFlavorCR.root",  "W(#mu#nu)H Heavy flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHHeavyFlavorFJCR.root","W(#mu#nu)H Heavy flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHHeavyFlavorCR.root",  "W(e#nu)H Heavy flavor CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHHeavyFlavorFJCR.root","W(e#nu)H Heavy flavor CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWH2TopCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnH2TopCR.root",  "W(#mu#nu)H Top CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHTT2bFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WmnHTT2bFJCR.root","W(#mu#nu)H Top CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWH2TopCR,  "MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenH2TopCR.root",  "W(e#nu)H Top CR selection, resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kWHTT2bFJCR,"MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WenHTT2bFJCR.root","W(e#nu)H Top CR selection, boosted",  "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITWH2017}'",'${YEAR}')'

fi
