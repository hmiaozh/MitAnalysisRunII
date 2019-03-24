#!/bin/sh

export NSEL=$1;
export YEAR=$2;

if [ $NSEL == 0 ]; then
  root -q -l -b MitAnalysisRunII/panda/skimming/skimmingAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/skimming/skimmingAnalysis.C+'('${YEAR}')' >& log_skimming_${YEAR} &

elif [ $NSEL == 1 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/triggerAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/triggerAnalysis.C+'('${YEAR}')' >& log_trigger_${YEAR} &

elif [ $NSEL == 2 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/fakeRateAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/fakeRateAnalysis.C+'('${YEAR}')'   >& log_fake_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/fakeRateAnalysis.C+'('${YEAR}',1)' >& log_fake_${YEAR}_btagged &

elif [ $NSEL == 3 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+'('${YEAR}')'     >& log_z_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+'('${YEAR}',0,1)' >& log_z_${YEAR}_0_1 &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+'('${YEAR}',0,2)' >& log_z_${YEAR}_0_2 &

elif [ $NSEL == 4 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/wwAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/wzAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zzAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/wwAnalysis.C+'('${YEAR}')'       >& log_ww_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',1)'   >& log_ssww_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',1,1)' >& log_ssww_fid_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/wzAnalysis.C+'('${YEAR}',1)'     >& log_wz_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zzAnalysis.C+'('${YEAR}',1)'     >& log_zz_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1)'     >& log_zh_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+'('${YEAR}',1)'    >& log_zhg_${YEAR} &

fi
