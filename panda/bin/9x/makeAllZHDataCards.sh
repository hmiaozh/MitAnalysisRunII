#!/bin/sh

cat > list_of_samples.txt <<EOF
Unpart_ZToLL_SU-0_dU-1p01
Unpart_ZToLL_SU-0_dU-1p02
Unpart_ZToLL_SU-0_dU-1p04
Unpart_ZToLL_SU-0_dU-1p06
Unpart_ZToLL_SU-0_dU-1p09
Unpart_ZToLL_SU-0_dU-1p10
Unpart_ZToLL_SU-0_dU-1p20
Unpart_ZToLL_SU-0_dU-1p30
Unpart_ZToLL_SU-0_dU-1p40
Unpart_ZToLL_SU-0_dU-1p50
Unpart_ZToLL_SU-0_dU-1p60
Unpart_ZToLL_SU-0_dU-1p70
Unpart_ZToLL_SU-0_dU-1p80
Unpart_ZToLL_SU-0_dU-1p90
Unpart_ZToLL_SU-0_dU-2p00
Unpart_ZToLL_SU-0_dU-2p20
ADDMonoZ_MD_1_d_2
ADDMonoZ_MD_1_d_3
ADDMonoZ_MD_1_d_4
ADDMonoZ_MD_1_d_5
ADDMonoZ_MD_1_d_6
ADDMonoZ_MD_1_d_7
ADDMonoZ_MD_2_d_2
ADDMonoZ_MD_2_d_3
ADDMonoZ_MD_2_d_4
ADDMonoZ_MD_2_d_5
ADDMonoZ_MD_2_d_6
ADDMonoZ_MD_2_d_7
ADDMonoZ_MD_3_d_2
ADDMonoZ_MD_3_d_3
ADDMonoZ_MD_3_d_4
ADDMonoZ_MD_3_d_5
ADDMonoZ_MD_3_d_6
ADDMonoZ_MD_3_d_7
EOF

for sampleName; do
  for jetValue in 0 1; do
    for year in 2016 2017 2018; do
      hadd -f zh${sampleName}_${year}_${jetValue}j_input.root zhNoBSM_${year}_${jetValue}j_input.root zhOnly${sampleName}_${year}_${jetValue}j_input.root;
      root -l -q -b MitAnalysisRunII/panda/macros/9x/makeZHYearDataCards.C+'("","zh'${sampleName}'_'${year}'_'${jetValue}'j_input.root",'${jetValue}')';
    done
  done
done
