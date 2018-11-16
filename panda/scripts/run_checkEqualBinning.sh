#!/bin/sh

hadd plots_ZllHSR_2016.root MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHSR_ZptBin?.root MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHSR_ZptBin?.root
hadd plots_ZllHSR_2017.root MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHSR_ZptBin?.root MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHSR_ZptBin?.root

hadd plots_ZllHFJSR_2016.root MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZeeHFJSR.root MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZmmHFJSR.root
hadd plots_ZllHFJSR_2017.root MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZeeHFJSR.root MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZmmHFJSR.root

hadd plots_WlnHSR_2016.root MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_W?nHSR.root
hadd plots_WlnHSR_2017.root MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_W?nHSR.root

hadd plots_WlnHFJSR_2016.root MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_W?nHFJSR.root
hadd plots_WlnHFJSR_2017.root MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_W?nHFJSR.root

root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_ZllHSR_2016.root",0)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_ZllHSR_2017.root",0)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_ZllHFJSR_2016.root",1)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_ZllHFJSR_2017.root",1)'

root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_WlnHSR_2016.root",0)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_WlnHSR_2017.root",0)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_WlnHFJSR_2016.root",1)'
root -l -q -b MitAnalysisRunII/panda/scripts/checkEqualBinning.C'("plots_WlnHFJSR_2017.root",1)'
