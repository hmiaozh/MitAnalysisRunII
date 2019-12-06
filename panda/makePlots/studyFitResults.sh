#!/bin/sh

export NSEL=$1
 
if [ $NSEL == 'zhg' ]; then
echo "***************ZHG*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2016_0001.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2016_125")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_0.root histoDatacard_zhg_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2017_0001.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2017_125")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_0.root histoDatacard_zhg_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2018_0001.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2018_125")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_0.root histoDatacard_zhg_2018.root

hadd -f histoDatacard_zhg_2019.root histoDatacard_zhg_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(0, "done_ana/histoZHG_mH125_2019_0001.root", "comb/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(1, "done_ana/histoZHG_mH125_2019_2.root", "comb/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(2, "done_ana/histoZHG_mH125_2019_09101112.root", "comb/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2019_125")';
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(3, "done_ana/histoZHG_mH125_2019_171819.root", "comb/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2019_125")';
rm -f studyFitResults*.txt;
rm -f histoDatacard_*.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(4, "done_ana/histoZHG_mH125_2016_54.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2016_125")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_4.root histoDatacard_zhg_etaglt1_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(4, "done_ana/histoZHG_mH125_2017_54.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2017_125")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_4.root histoDatacard_zhg_etaglt1_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(4, "done_ana/histoZHG_mH125_2018_54.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2018_125")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_4.root histoDatacard_zhg_etaglt1_2018.root

hadd -f histoDatacard_zhg_etaglt1_2019.root histoDatacard_zhg_etaglt1_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
rm -f histoDatacard_?.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(5, "done_ana/histoZHG_mH125_2016_55.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2016_125")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_5.root histoDatacard_zhg_etaggt1_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(5, "done_ana/histoZHG_mH125_2017_55.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2017_125")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_5.root histoDatacard_zhg_etaggt1_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(5, "done_ana/histoZHG_mH125_2018_55.root", "ana_zhg/fitDiagnosticszhg_comb_125_obs.root", "ZHG_2018_125")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_5.root histoDatacard_zhg_etaggt1_2018.root

hadd -f histoDatacard_zhg_etaggt1_2019.root histoDatacard_zhg_etaggt1_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
rm -f histoDatacard_?.root

elif [ $NSEL == 'ssww' ]; then
echo "***************SSWW SR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2016_0.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2016")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_10.root histoDatacard_ssww_wwsr_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2017_0.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2017")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_10.root histoDatacard_ssww_wwsr_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(10, "done_ana/histossww_2018_0.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2018")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_10.root histoDatacard_ssww_wwsr_2018.root

hadd -f histoDatacard_ssww_wwsr_2019.root histoDatacard_ssww_wwsr_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
rm -f histoDatacard_*.root

echo "***************SSWW BTAG CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2016_1.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2016")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_11.root histoDatacard_ssww_btag_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2017_1.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2017")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_11.root histoDatacard_ssww_btag_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(11, "done_ana/histossww_2018_1.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2018")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_11.root histoDatacard_ssww_btag_2018.root

hadd -f histoDatacard_ssww_btag_2019.root histoDatacard_ssww_btag_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
rm -f histoDatacard_*.root

echo "***************SSWW ZZ CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2016_2.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2016")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_12.root histoDatacard_ssww_zz_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2017_2.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2017")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_12.root histoDatacard_ssww_zz_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(12, "done_ana/histossww_2018_2.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2018")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_12.root histoDatacard_ssww_zz_2018.root

hadd -f histoDatacard_ssww_zz_2019.root histoDatacard_ssww_zz_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW WZb CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2016_3.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2016")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_13.root histoDatacard_ssww_wzb_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2017_3.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2017")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_13.root histoDatacard_ssww_wzb_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(13, "done_ana/histossww_2018_3.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2018")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_13.root histoDatacard_ssww_wzb_2018.root

hadd -f histoDatacard_ssww_wzb_2019.root histoDatacard_ssww_wzb_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;

echo "***************SSWW WZ CR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2016_77.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2016")';
mv studyFitResults.txt studyFitResults_2016.txt;
mv histoDatacard_14.root histoDatacard_ssww_wz_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2017_77.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2017")';
mv studyFitResults.txt studyFitResults_2017.txt;
mv histoDatacard_14.root histoDatacard_ssww_wz_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(14, "done_ana/histossww_2018_77.root", "ana_ssww/fitDiagnosticsssww_comb_wwwz_obs.root", "SSWW_2018")';
mv studyFitResults.txt studyFitResults_2018.txt;
mv histoDatacard_14.root histoDatacard_ssww_wz_2018.root

hadd -f histoDatacard_ssww_wz_2019.root histoDatacard_ssww_wz_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;


elif [ $NSEL == 'zh' ]; then
echo "***************ZH SR*****"
root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2016_48.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2016")';
mv studyFitResults.txt studyFitResults_0j_2016.txt;
mv histoDatacard_21.root histoDatacard_zh_0j_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2016_50.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2016")';
mv studyFitResults.txt studyFitResults_1j_2016.txt;
mv histoDatacard_22.root histoDatacard_zh_1j_2016.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2017_48.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2017")';
mv studyFitResults.txt studyFitResults_0j_2017.txt;
mv histoDatacard_21.root histoDatacard_zh_0j_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2017_50.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2017")';
mv studyFitResults.txt studyFitResults_1j_2017.txt;
mv histoDatacard_22.root histoDatacard_zh_1j_2017.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(21, "done_ana/histoZH_2018_48.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2018")';
mv studyFitResults.txt studyFitResults_0j_2018.txt;
mv histoDatacard_21.root histoDatacard_zh_0j_2018.root

root -l -q -b MitAnalysisRunII/panda/makePlots/studyFitResults.C+'(22, "done_ana/histoZH_2018_50.root", "ana_zh/fitDiagnosticszh_comb_obs.root", "ZH_2018")';
mv studyFitResults.txt studyFitResults_1j_2018.txt;
mv histoDatacard_22.root histoDatacard_zh_1j_2018.root

hadd -f histoDatacard_zh_0j_2019.root histoDatacard_zh_0j_201[6-8].root
hadd -f histoDatacard_zh_1j_2019.root histoDatacard_zh_1j_201[6-8].root
hadd -f histoDatacard_zh_nj_2019.root histoDatacard_zh_?j_201[6-8].root

python MitAnalysisRunII/panda/makePlots/studyFitResults.py;
rm -f studyFitResults*.txt;
rm -f histoDatacard_??.root
fi
