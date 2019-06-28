#!/bin/sh

export NSEL=$1
 
if [ $NSEL == 'zhg' ]; then
echo "***************ZHG*****"
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

elif [ $NSEL == 'ssww' ]; then
echo "***************SSWW SR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2016_303132.root", "done_ana/fitDiagnosticsssww_comb.root", "ch1")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2017_303132.root", "done_ana/fitDiagnosticsssww_comb.root", "ch2")';

mv studyFitResults.txt studyFitResults_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2018_303132.root", "done_ana/fitDiagnosticsssww_comb.root", "ch3")';

mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW BTAG CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2016_373839.root", "done_ana/fitDiagnosticsssww_comb.root", "ch1")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2017_373839.root", "done_ana/fitDiagnosticsssww_comb.root", "ch2")';

mv studyFitResults.txt studyFitResults_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2018_373839.root", "done_ana/fitDiagnosticsssww_comb.root", "ch3")';

mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW ZZ CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2016_91.root", "done_ana/fitDiagnosticsssww_comb.root", "ch1")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2017_91.root", "done_ana/fitDiagnosticsssww_comb.root", "ch2")';

mv studyFitResults.txt studyFitResults_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2018_91.root", "done_ana/fitDiagnosticsssww_comb.root", "ch3")';

mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW WZb CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2016_92.root", "done_ana/fitDiagnosticsssww_comb.root", "ch1")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2017_92.root", "done_ana/fitDiagnosticsssww_comb.root", "ch2")';

mv studyFitResults.txt studyFitResults_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2018_92.root", "done_ana/fitDiagnosticsssww_comb.root", "ch3")';

mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW WZ CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2016_93.root", "done_ana/fitDiagnosticsssww_comb.root", "ch1")';
mv studyFitResults.txt studyFitResults_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2017_93.root", "done_ana/fitDiagnosticsssww_comb.root", "ch2")';

mv studyFitResults.txt studyFitResults_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2018_93.root", "done_ana/fitDiagnosticsssww_comb.root", "ch3")';

mv studyFitResults.txt studyFitResults_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;


elif [ $NSEL == 'zh' ]; then
echo "***************ZH SR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2016_48.root", "done_ana/fitDiagnosticszh_comb.root", "ch1_ch1")';
mv studyFitResults.txt studyFitResults_0j_2016.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2016_49.root", "done_ana/fitDiagnosticszh_comb.root", "ch1_ch1")';
mv studyFitResults.txt studyFitResults_1j_2016.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2017_48.root", "done_ana/fitDiagnosticszh_comb.root", "ch2_ch1")';
mv studyFitResults.txt studyFitResults_0j_2017.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2017_49.root", "done_ana/fitDiagnosticszh_comb.root", "ch2_ch1")';
mv studyFitResults.txt studyFitResults_1j_2017.txt;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2018_48.root", "done_ana/fitDiagnosticszh_comb.root", "ch3_ch1")';
mv studyFitResults.txt studyFitResults_0j_2018.txt;
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2018_49.root", "done_ana/fitDiagnosticszh_comb.root", "ch3_ch1")';
mv studyFitResults.txt studyFitResults_1j_2018.txt;

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
fi
