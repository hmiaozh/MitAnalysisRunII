#!/bin/sh

export YEAR="";

if [ $# -lt 1 ]; then
   echo "TOO FEW PARAMETERS"
   exit
fi

export MLFITZH2016="";
export MLFITVZ2016="";
export MLFITZH2017="";
export MLFITVZ2017="";
if [ $# -eq 2 ]; then
  echo "USING MLFIT RESULTS"
  export MLFITZH2016="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/inputs_zh_2016/fitDiagnosticsZH.root";
  export MLFITVZ2016="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/inputs_vz_2016/fitDiagnosticsVZbb.root";
  export MLFITZH2017="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/inputs_zh_2017/fitDiagnosticsZH.root";
  export MLFITVZ2017="/home/ceballos/releases/CMSSW_8_1_0/src/cards/cards_vh/inputs_vz_2017/fitDiagnosticsVZbb.root";
fi

### 2016
if [ $1 == "2016" ]; then
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHSR_ZptBin0.root", "Z(#mu#mu)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHSR_ZptBin1.root", "Z(#mu#mu)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHSR_ZptBin2.root", "Z(#mu#mu)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHFJSR.root",       "Z(#mu#mu)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHSR_ZptBin0.root", "Z(ee)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHSR_ZptBin1.root", "Z(ee)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHSR_ZptBin2.root", "Z(ee)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHFJSR.root",       "Z(ee)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHSR_ZptBin0.root", "Z(e#mu)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHSR_ZptBin1.root", "Z(e#mu)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHSR_ZptBin2.root", "Z(e#mu)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHFJSR.root",       "Z(e#mu)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHLightFlavorCR_ZptBin0.root", "Z(#mu#mu)H Light Flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHLightFlavorCR_ZptBin1.root", "Z(#mu#mu)H Light Flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHLightFlavorCR_ZptBin2.root", "Z(#mu#mu)H Light Flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHLightFlavorFJCR.root",       "Z(#mu#mu)H Light Flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHLightFlavorCR_ZptBin0.root", "Z(ee)H Light Flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHLightFlavorCR_ZptBin1.root", "Z(ee)H Light Flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHLightFlavorCR_ZptBin2.root", "Z(ee)H Light Flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHLightFlavorFJCR.root",       "Z(ee)H Light Flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHHeavyFlavorCR_ZptBin0.root", "Z(#mu#mu)H Heavy flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHHeavyFlavorCR_ZptBin1.root", "Z(#mu#mu)H Heavy flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHHeavyFlavorCR_ZptBin2.root", "Z(#mu#mu)H Heavy flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHHeavyFlavorFJCR.root",       "Z(#mu#mu)H Heavy flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHHeavyFlavorCR_ZptBin0.root", "Z(ee)H Heavy flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHHeavyFlavorCR_ZptBin1.root", "Z(ee)H Heavy flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHHeavyFlavorCR_ZptBin2.root", "Z(ee)H Heavy flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHHeavyFlavorFJCR.root",       "Z(ee)H Heavy flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmH2TopCR_ZptBin0.root", "Z(#mu#mu)H Top CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmH2TopCR_ZptBin1.root", "Z(#mu#mu)H Top CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmH2TopCR_ZptBin2.root", "Z(#mu#mu)H Top CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
#root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHTT1bFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHTT1bFJCR.root",       "Z(#mu#mu)H Top CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeH2TopCR_ZptBin0.root", "Z(ee)H Top CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeH2TopCR_ZptBin1.root", "Z(ee)H Top CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeH2TopCR_ZptBin2.root", "Z(ee)H Top CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'
#root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHTT1bFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHTT1bFJCR.root",       "Z(ee)H Top CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITZH2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHVZbbCR_ZptBin0.root", "Z(#mu#mu)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHVZbbCR_ZptBin1.root", "Z(#mu#mu)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHVZbbCR_ZptBin2.root", "Z(#mu#mu)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHVZbbFJCR.root", "Z(#mu#mu)H VZ CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHVZbbCR_ZptBin0.root", "Z(e#mu)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHVZbbCR_ZptBin1.root", "Z(e#mu)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZemHVZbbCR_ZptBin2.root", "Z(e#mu)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHVZbbCR_ZptBin0.root", "Z(ee)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHVZbbCR_ZptBin1.root", "Z(ee)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHVZbbCR_ZptBin2.root", "Z(ee)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHVZbbFJCR.root", "Z(ee)H VZ CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2016","'${MLFITVZ2016}'")'

### 2017
elif [ $1 == "2017" ]; then
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHSR_ZptBin0.root", "Z(#mu#mu)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHSR_ZptBin1.root", "Z(#mu#mu)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHSR_ZptBin2.root", "Z(#mu#mu)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHFJSR.root",       "Z(#mu#mu)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHSR_ZptBin0.root", "Z(ee)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHSR_ZptBin1.root", "Z(ee)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHSR_ZptBin2.root", "Z(ee)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHFJSR.root",       "Z(ee)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHSR_ZptBin0.root", "Z(e#mu)H SR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHSR_ZptBin1.root", "Z(e#mu)H SR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHSR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHSR_ZptBin2.root", "Z(e#mu)H SR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHFJSR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHFJSR.root",       "Z(e#mu)H SR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHLightFlavorCR_ZptBin0.root", "Z(#mu#mu)H Light Flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHLightFlavorCR_ZptBin1.root", "Z(#mu#mu)H Light Flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHLightFlavorCR_ZptBin2.root", "Z(#mu#mu)H Light Flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHLightFlavorFJCR.root",       "Z(#mu#mu)H Light Flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHLightFlavorCR_ZptBin0.root", "Z(ee)H Light Flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHLightFlavorCR_ZptBin1.root", "Z(ee)H Light Flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHLightFlavorCR_ZptBin2.root", "Z(ee)H Light Flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHLightFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHLightFlavorFJCR.root",       "Z(ee)H Light Flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHHeavyFlavorCR_ZptBin0.root", "Z(#mu#mu)H Heavy flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHHeavyFlavorCR_ZptBin1.root", "Z(#mu#mu)H Heavy flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHHeavyFlavorCR_ZptBin2.root", "Z(#mu#mu)H Heavy flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHHeavyFlavorFJCR.root",       "Z(#mu#mu)H Heavy flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHHeavyFlavorCR_ZptBin0.root", "Z(ee)H Heavy flavor CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHHeavyFlavorCR_ZptBin1.root", "Z(ee)H Heavy flavor CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHHeavyFlavorCR_ZptBin2.root", "Z(ee)H Heavy flavor CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHHeavyFlavorFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHHeavyFlavorFJCR.root",       "Z(ee)H Heavy flavor CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmH2TopCR_ZptBin0.root", "Z(#mu#mu)H Top CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmH2TopCR_ZptBin1.root", "Z(#mu#mu)H Top CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmH2TopCR_ZptBin2.root", "Z(#mu#mu)H Top CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
#root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHTT1bFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHTT1bFJCR.root",       "Z(#mu#mu)H Top CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeH2TopCR_ZptBin0.root", "Z(ee)H Top CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeH2TopCR_ZptBin1.root", "Z(ee)H Top CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllH2TopCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeH2TopCR_ZptBin2.root", "Z(ee)H Top CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'
#root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHTT1bFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHTT1bFJCR.root",       "Z(ee)H Top CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITZH2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHVZbbCR_ZptBin0.root", "Z(#mu#mu)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHVZbbCR_ZptBin1.root", "Z(#mu#mu)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHVZbbCR_ZptBin2.root", "Z(#mu#mu)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHVZbbFJCR.root", "Z(#mu#mu)H VZ CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHVZbbCR_ZptBin0.root", "Z(e#mu)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHVZbbCR_ZptBin1.root", "Z(e#mu)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZemHVZbbCR_ZptBin2.root", "Z(e#mu)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'

root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHVZbbCR_ZptBin0.root", "Z(ee)H VZ CR selection, low p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHVZbbCR_ZptBin1.root", "Z(ee)H VZ CR selection, medium p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbCR,  "MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHVZbbCR_ZptBin2.root", "Z(ee)H VZ CR selection, high p_{T} resolved", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'
root -q -b -l MitVHBBAnalysis/macros/finalPlot2018.C+'(kZllHVZbbFJCR,"MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHVZbbFJCR.root", "Z(ee)H VZ CR selection, boosted", "", false, false, "MitVHBBAnalysis/plots2017","'${MLFITVZ2017}'")'

### log(1+s/b) plot
elif [ $# -eq 2 ] && [ $1 == "stob" ]; then
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("'${MLFITZH2016}'","stob_ZH2016",false)';
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("'${MLFITZH2017}'","stob_ZH2017",false)';
hadd -f stob_ZHcomb.root stob_ZH2016.root stob_ZH2017.root;
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("","stob_ZHcomb",false,true,true)'; # mlfitResult/outputFileName/isZHSignal/doRatioPad/isBlinded
mv plot_stob_ZHcomb.pdf plot_stob_ZHcomb_exp.pdf;
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("","stob_ZHcomb",false,true,false)';
mv plot_stob_ZHcomb.pdf plot_stob_ZHcomb_obs.pdf;

root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("'${MLFITVZ2016}'","stob_VZ2016",true)';
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("'${MLFITVZ2017}'","stob_VZ2017",true)';
hadd -f stob_VZcomb.root stob_VZ2016.root stob_VZ2017.root;
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("","stob_VZcomb",false,true,true)';
mv plot_stob_VZcomb.pdf plot_stob_VZcomb_exp.pdf;
root -q -b -l MitAnalysisRunII/panda/scripts/signalToBackground.C+'("","stob_VZcomb",false,true,false)';
mv plot_stob_VZcomb.pdf plot_stob_VZcomb_obs.pdf;

rm -f stob_*;

fi
