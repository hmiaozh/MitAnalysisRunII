#!/bin/sh

export NSEL=$1;

if [ $NSEL == 'mc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ZZJJQCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ZZJJEWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 qqZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ggZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZno3l
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZ3l_powheg_mll1
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZ3l_powheg
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZ3l_amcnlo
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZ3l_MG_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZ3l_MG_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 qqWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ggWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WWdps
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 VVV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 TTV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 TTVV
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 TT2L
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 TT1L
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 TW
###PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WGstar
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 VG
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 VG_M120
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 H125
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYNJetsToLL
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYNJetsToLL_NLO
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt0To50
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt50To100 
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt100To250  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt250To400  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt400To650  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_Pt650ToInf  
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToTauTau
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_M-10to50
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_M-50_NLO
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_M-50_LO
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToLL_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToMM_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DYJetsToEE_POWHEG
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WJets
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 MET
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p01
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p02
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p04
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p06
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p09
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p10
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p30
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p40
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p50
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p60
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p70
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p80
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-1p90
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-2p00
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 Unpart_ZToLL_SU-0_dU-2p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_1_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_2_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ADDMonoZ_MD_3_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ggZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 qqZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WpWp_EWK_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WpWp_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WpWp_QCD
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 SingleMuon           
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 SingleElectron     
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 MuonEG       
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DoubleEG     
#PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 DoubleMuon

elif [ $NSEL == 'specialmc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ZH_ZToLL_HToGDarkG_M125
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ZH_ZToLL_HToGDarkG_M200
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 ZH_ZToLL_HToGDarkG_M300

elif [ $NSEL == 'dim8' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WWjj_SS_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZjj_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WWjj_SS_dim8_ewk_ext
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WZjj_dim8_ewk_ext
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WWjj_SS_long
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 WWjj_SS_lttt

elif [ $NSEL == 'da' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic_2017 data_overlaps

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data_overlaps.root","${PANDA_FLATDIR}/data.root","PandaAnalysis/data/certs/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt")'
fi
