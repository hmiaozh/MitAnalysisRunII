#!/bin/sh

root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+

nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin0.root", "ZH_ZptBin0_2016", true,false,false,false)' >& train_ZptBin0_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin1.root", "ZH_ZptBin1_2016", true,false,false,false)' >& train_ZptBin1_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin2.root", "ZH_ZptBin2_2016", true,false,false,false)' >& train_ZptBin2_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHFJSR.root",               "ZH_boosted_2016", true,true ,false,false)' >& train_boosted_2016.txt &

#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin0.root", "ZH_ZptBin0_2017", true,false,false,false)' >& train_ZptBin0_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin1.root", "ZH_ZptBin1_2017", true,false,false,false)' >& train_ZptBin1_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin2.root", "ZH_ZptBin2_2017", true,false,false,false)' >& train_ZptBin2_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHFJSR.root",               "ZH_boosted_2017", true,true ,false,false)' >& train_boosted_2017.txt &

nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin0.root", "VZ_ZptBin0_2016", false,false,false,false)' >& train_VZ_ZptBin0_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin1.root", "VZ_ZptBin1_2016", false,false,false,false)' >& train_VZ_ZptBin1_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHSR_mvaTree_ZptBin2.root", "VZ_ZptBin2_2016", false,false,false,false)' >& train_VZ_ZptBin2_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/ZllHFJSR.root",               "VZ_boosted_2016", false,true ,false,false)' >& train_VZ_boosted_2016.txt &

#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin0.root", "VZ_ZptBin0_2017", false,false,false,false)' >& train_VZ_ZptBin0_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin1.root", "VZ_ZptBin1_2017", false,false,false,false)' >& train_VZ_ZptBin1_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHSR_mvaTree_ZptBin2.root", "VZ_ZptBin2_2017", false,false,false,false)' >& train_VZ_ZptBin2_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/zhbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/ZllHFJSR.root",               "VZ_boosted_2017", false,true ,false,false)' >& train_VZ_boosted_2017.txt &
