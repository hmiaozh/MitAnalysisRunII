#!/bin/sh

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2016_0001.root", "done_ana/fitDiagnosticszhg_comb_125.root", "ZHG_2016_125")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2017_0001.root", "done_ana/fitDiagnosticszhg_comb_125.root", "ZHG_2017_125")';
mv studyFitResults.txt studyFitResults_2017.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2018_0001.root", "done_ana/fitDiagnosticszhg_comb_125.root", "ZHG_2018_125")';
mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2019_0001.root", "comb/fitDiagnosticszhg_comb_125.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(1, "done_ana/histoZHG_mH125_2019_2.root", "comb/fitDiagnosticszhg_comb_125.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(2, "done_ana/histoZHG_mH125_2019_09101112.root", "comb/fitDiagnosticszhg_comb_125.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(3, "done_ana/histoZHG_mH125_2019_171819.root", "comb/fitDiagnosticszhg_comb_125.root", "ZHG_2019_125")';
rm -f studyFitResults*.txt;
