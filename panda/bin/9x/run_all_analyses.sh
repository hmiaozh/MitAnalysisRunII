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
  if [ $# == 3 ] && [ $3 == 1 ]; then
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+'('${YEAR}',0,1)' >& log_z_${YEAR}_0_1 &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zAnalysis.C+'('${YEAR}',0,2)' >& log_z_${YEAR}_0_2 &
  fi

elif [ $NSEL == 4 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/wwAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/wwAnalysis.C+'('${YEAR}')'       >& log_ww_${YEAR} &

elif [ $NSEL == 5 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/wzAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zzAnalysis.C+
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/wzAnalysis.C+'('${YEAR}',1)'     >& log_wz_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zzAnalysis.C+'('${YEAR}',1)'     >& log_zz_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1)'     >& log_zh_${YEAR} &
  if [ $# == 3 ] && [ $3 == 1 ]; then
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p01")' >& log_zhUnpart_ZToLL_SU-0_dU-1p01_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p02")' >& log_zhUnpart_ZToLL_SU-0_dU-1p02_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p04")' >& log_zhUnpart_ZToLL_SU-0_dU-1p04_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p06")' >& log_zhUnpart_ZToLL_SU-0_dU-1p06_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p09")' >& log_zhUnpart_ZToLL_SU-0_dU-1p09_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p10")' >& log_zhUnpart_ZToLL_SU-0_dU-1p10_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p20")' >& log_zhUnpart_ZToLL_SU-0_dU-1p20_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p30")' >& log_zhUnpart_ZToLL_SU-0_dU-1p30_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p40")' >& log_zhUnpart_ZToLL_SU-0_dU-1p40_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p50")' >& log_zhUnpart_ZToLL_SU-0_dU-1p50_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p60")' >& log_zhUnpart_ZToLL_SU-0_dU-1p60_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p70")' >& log_zhUnpart_ZToLL_SU-0_dU-1p70_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p80")' >& log_zhUnpart_ZToLL_SU-0_dU-1p80_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-1p90")' >& log_zhUnpart_ZToLL_SU-0_dU-1p90_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-2p00")' >& log_zhUnpart_ZToLL_SU-0_dU-2p00_${YEAR} &
    nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"Unpart_ZToLL_SU-0_dU-2p20")' >& log_zhUnpart_ZToLL_SU-0_dU-2p20_${YEAR} &

    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_2")' >& log_zhADDMonoZ_MD_1_d_2_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_3")' >& log_zhADDMonoZ_MD_1_d_3_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_4")' >& log_zhADDMonoZ_MD_1_d_4_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_5")' >& log_zhADDMonoZ_MD_1_d_5_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_6")' >& log_zhADDMonoZ_MD_1_d_6_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_1_d_7")' >& log_zhADDMonoZ_MD_1_d_7_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_2")' >& log_zhADDMonoZ_MD_2_d_2_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_3")' >& log_zhADDMonoZ_MD_2_d_3_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_4")' >& log_zhADDMonoZ_MD_2_d_4_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_5")' >& log_zhADDMonoZ_MD_2_d_5_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_6")' >& log_zhADDMonoZ_MD_2_d_6_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_2_d_7")' >& log_zhADDMonoZ_MD_2_d_7_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_2")' >& log_zhADDMonoZ_MD_3_d_2_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_3")' >& log_zhADDMonoZ_MD_3_d_3_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_4")' >& log_zhADDMonoZ_MD_3_d_4_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_5")' >& log_zhADDMonoZ_MD_3_d_5_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_6")' >& log_zhADDMonoZ_MD_3_d_6_${YEAR} &
    #nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhAnalysis.C+'('${YEAR}',1,"ADDMonoZ_MD_3_d_7")' >& log_zhADDMonoZ_MD_3_d_7_${YEAR} &
  fi

elif [ $NSEL == 6 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',0,1)' >& log_ssww_fid0_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',1,1)' >& log_ssww_fid1_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',2,1)' >& log_ssww_fid2_${YEAR} &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/sswwAnalysis.C+'('${YEAR}',3,1)' >& log_ssww_fid3_${YEAR} &

elif [ $NSEL == 7 ]; then
  root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+'('${YEAR}',1,125)'    >& log_zhg_${YEAR}_125 &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+'('${YEAR}',1,200)'    >& log_zhg_${YEAR}_200 &
  nohup time root -q -l -b MitAnalysisRunII/panda/macros/9x/zhgAnalysis.C+'('${YEAR}',1,300)'    >& log_zhg_${YEAR}_300 &

fi
