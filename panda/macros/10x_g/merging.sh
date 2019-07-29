#!/bin/sh

export NSEL=$1;

if [ $NSEL == '2017' ]; then
hadd -f /data/t3home000/ceballos/panda/v_vbfg_2017_0/data_overlaps.root \
   /scratch5/bmaier/darkg/2017/vbfg_v_012_v5/MET.root \
   /scratch5/bmaier/darkg/2017/vbfg_v_012_v5/SinglePhoton.root

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/v_vbfg_2017_0/data_overlaps.root","/data/t3home000/ceballos/panda/v_vbfg_2017_0/data.root","PandaAnalysis/data/certs/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt")';

elif [ $NSEL == '2018' ]; then
hadd -f /data/t3home000/ceballos/panda/v_vbfg_2018_0/data_overlaps.root \
   /scratch5/bmaier/darkg/2018/vbfg_v_013_v6/MET.root \
   /scratch5/bmaier/darkg/2018/vbfg_v_013_v6/EGamma.root

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/v_vbfg_2018_0/data_overlaps.root","/data/t3home000/ceballos/panda/v_vbfg_2018_0/data.root","PandaAnalysis/data/certs/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt")';

fi
