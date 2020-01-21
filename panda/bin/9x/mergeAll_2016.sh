#!/bin/sh

export NSEL=$1;

if [ $NSEL == 'mc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic ZZJJQCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic ZZJJEWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic ggZZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic WZ
PandaAnalysis/T3/merging/merge.py --cfg leptonic WZ3l_MG_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic WZ3l_MG_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic ggWW
PandaAnalysis/T3/merging/merge.py --cfg leptonic WWdps
PandaAnalysis/T3/merging/merge.py --cfg leptonic VVV
PandaAnalysis/T3/merging/merge.py --cfg leptonic TTV
PandaAnalysis/T3/merging/merge.py --cfg leptonic TT2L
PandaAnalysis/T3/merging/merge.py --cfg leptonic TT
PandaAnalysis/T3/merging/merge.py --cfg leptonic TW
PandaAnalysis/T3/merging/merge.py --cfg leptonic WGstar
PandaAnalysis/T3/merging/merge.py --cfg leptonic VG
PandaAnalysis/T3/merging/merge.py --cfg leptonic VG_M120
PandaAnalysis/T3/merging/merge.py --cfg leptonic H125
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYNJetsToLL
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt0To50
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt50To100 
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt100To250  
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt250To400  
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt400To650  
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_Pt650ToInf  
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToTauTau
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_M-10to50
PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_M-50_NLO
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_M-50_LO_Pt000To050
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_M-50_LO_Pt100to200
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_M-50_LO_Pt200toInf
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToLL_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToMM_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToEE_POWHEG
#PandaAnalysis/T3/merging/merge.py --cfg leptonic ZtoNuNu_pt100to250
#PandaAnalysis/T3/merging/merge.py --cfg leptonic ZtoNuNu_pt250to400
#PandaAnalysis/T3/merging/merge.py --cfg leptonic ZtoNuNu_pt400to650
#PandaAnalysis/T3/merging/merge.py --cfg leptonic ZtoNuNu_pt650toinf
PandaAnalysis/T3/merging/merge.py --cfg leptonic WJets
PandaAnalysis/T3/merging/merge.py --cfg leptonic WpWp_EWK_QCD
PandaAnalysis/T3/merging/merge.py --cfg leptonic WpWp_EWK
PandaAnalysis/T3/merging/merge.py --cfg leptonic WpWp_QCD
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DYJetsToEE_POWHEG_MINLO
PandaAnalysis/T3/merging/merge.py --cfg leptonic ggZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH110inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH125inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH150inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH200inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH300inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH400inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH500inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH600inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH800inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZH1000inv
PandaAnalysis/T3/merging/merge.py --cfg leptonic MET
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p01
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p02
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p04
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p06
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p09
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p10
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p30
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p40
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p50
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p60
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p70
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p80
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-1p90
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-2p00
PandaAnalysis/T3/merging/merge.py --cfg leptonic Unpart_ZToLL_SU-0_dU-2p20
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_1_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_2_d_7
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_2
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_3
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_4
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_5
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_6
PandaAnalysis/T3/merging/merge.py --cfg leptonic ADDMonoZ_MD_3_d_7
#PandaAnalysis/T3/merging/merge.py --cfg leptonic SingleMuon           
#PandaAnalysis/T3/merging/merge.py --cfg leptonic SingleElectron     
#PandaAnalysis/T3/merging/merge.py --cfg leptonic MuonEG       
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DoubleEG     
#PandaAnalysis/T3/merging/merge.py --cfg leptonic DoubleMuon

elif [ $NSEL == 'specialmc' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic ZH_ZToLL_HToGDarkG_M125
PandaAnalysis/T3/merging/merge.py --cfg leptonic ZH_ZToLL_HToGDarkG_M200
PandaAnalysis/T3/merging/merge.py --cfg leptonic ZH_ZToLL_HToGDarkG_M300

elif [ $NSEL == 'dim8' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic WWjj_SS_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic WZjj_dim8_ewk
PandaAnalysis/T3/merging/merge.py --cfg leptonic WWjj_SS_long
PandaAnalysis/T3/merging/merge.py --cfg leptonic WWjj_SS_lttt

elif [ $NSEL == 'da' ]; then
PandaAnalysis/T3/merging/merge.py --cfg leptonic data_overlaps

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data_overlaps.root","${PANDA_FLATDIR}/data.root","MitAnalysisRunII/json/80x/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt")'
fi
