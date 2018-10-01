#!/bin/sh

root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+

nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/WHSR.root",      "WH_resolved_2016",     false,false,false,false)' >& train_WH_resolved_2016.txt &
nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/WHFJSR.root",    "WH_boosted_2016",      true ,false,false,false)' >& train_WH_boosted_2016.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/WHVZbbCR.root",  "WHVZbb_resolved_2016", false,false,false,true)'  >& train_WHVZbb_resolved_2016.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2016/WHVZbbFJCR.root","WHVZbb_boosted_2016",  true ,false,false,true)'  >& train_WHVZbb_boosted__2016.txt &

#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/WHSR.root",      "WH_resolved_2017",     false,false,false,false)' >& train_WH_resolved_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/WHFJSR.root",    "WH_boosted_2017",      true ,false,false,false)' >& train_WH_boosted_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/WHVZbbCR.root",  "WHVZbb_resolved_2017", false,false,false,true)'  >& train_WHVZbb_resolved_2017.txt &
#nohup root -b -l -q MitVHBBAnalysis/macros/whbbMVA.C+'("MitVHBBAnalysis/mva_frozen/test2017/WHVZbbFJCR.root","WHVZbb_boosted_2017",  true ,false,false,true)'  >& train_WHVZbb_boosted__2017.txt &
