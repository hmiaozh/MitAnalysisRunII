#!/bin/sh

export NSEL=$1;

if [ $NSEL == 'mc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ZZJJ
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 qqZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ggZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZno3l
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZ3l_powheg_mll1
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZ3l_powheg
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZ3l_amcnlo
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZ3l_MG_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZ3l_MG_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 qqWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ggWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WWdps
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 VVV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TTV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TTVV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TT2L
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TT1L
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TW
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 TWlx
###PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WGstar
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 VG
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 VG_M120
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 H125
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYNJetsToLL
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYNJetsToLL_NLO
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt0To50
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt50To100 
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt100To250  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt250To400  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt400To650  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_Pt650ToInf  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToTauTau
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_M-10to50
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_M-50_NLO
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_M-50_LO
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToLL_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToMM_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 DYJetsToEE_POWHEG
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WJets
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ggZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 qqZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 MET
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p01
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p02
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p04
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p06
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p09
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p10
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p30
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p40
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p50
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p60
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p70
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p80
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-1p90
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-2p00
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 Unpart_ZToLL_SU-0_dU-2p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_1_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_2_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ADDMonoZ_MD_3_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WpWp_EWK_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WpWp_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WpWp_QCD

elif [ $NSEL == 'specialmc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ZH_ZToLL_HToGDarkG_M125
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ZH_ZToLL_HToGDarkG_M200
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 ZH_ZToLL_HToGDarkG_M300

elif [ $NSEL == 'dim8' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WWjj_SS_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WZjj_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WWjj_SS_long
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 WWjj_SS_lttt

elif [ $NSEL == 'da' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2018 data_2018_overlaps

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data_2018_overlaps.root","${PANDA_FLATDIR}/data.root","PandaAnalysis/data/certs/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt")'
fi
