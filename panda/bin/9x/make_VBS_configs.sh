#!/bin/sh

if [ $# == 1 ] && [ $1 == 1 ]; then

#ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Summer16/*root|awk '{print"WWjj_SS_dim8_ewk_Summer16 MC 1 "$9}' > WWjj_SS_dim8_ewk_Summer16.cfg
#ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Summer16/*root|awk '{print"WZjj_dim8_ewk_Summer16 MC 1 "$9}' > WZjj_dim8_ewk_Summer16.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Fall17/*root|awk '{print"WWjj_SS_dim8_ewk_Fall17 MC 1 "$9}' > WWjj_SS_dim8_ewk_Fall17.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Fall17/*root|awk '{print"WZjj_dim8_ewk_Fall17 MC 1 "$9}' > WZjj_dim8_ewk_Fall17.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Autumn18/*root|awk '{print"WWjj_SS_dim8_ewk_Autumn18 MC 1 "$9}' > WWjj_SS_dim8_ewk_Autumn18.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Autumn18/*root|awk '{print"WZjj_dim8_ewk_Autumn18 MC 1 "$9}' > WZjj_dim8_ewk_Autumn18.cfg
wc *.cfg;

#ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Summer16/*root  /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WWjj_SS_dim8_ewk_Summer16/panda/*root|awk '{print"WWjj_SS_dim8_ewk_Summer16 MC 1 "$9}' > WWjj_SS_dim8_ewk_Summer16.cfg
#ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Summer16/*root     /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WZjj_dim8_ewk_Summer16/panda/*root   |awk '{print"WZjj_dim8_ewk_Summer16 MC 1 "$9}' > WZjj_dim8_ewk_Summer16.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Fall17/*root    /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WWjj_SS_dim8_ewk_Fall17/panda/*root  |awk '{print"WWjj_SS_dim8_ewk_Fall17 MC 1 "$9}' > WWjj_SS_dim8_ewk_Fall17.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Fall17/*root       /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WZjj_dim8_ewk_Fall17/panda/*root     |awk '{print"WZjj_dim8_ewk_Fall17 MC 1 "$9}' > WZjj_dim8_ewk_Fall17.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WWjj_SS_dim8_ewk_Autumn18/*root  /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WWjj_SS_dim8_ewk_Autumn18/panda/*root|awk '{print"WWjj_SS_dim8_ewk_Autumn18 MC 1 "$9}' > WWjj_SS_dim8_ewk_Autumn18.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/Panda_Leptonic_WZjj_dim8_ewk_Autumn18/*root     /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WZjj_dim8_ewk_Autumn18/panda/*root   |awk '{print"WZjj_dim8_ewk_Autumn18 MC 1 "$9}' > WZjj_dim8_ewk_Autumn18.cfg
wc *.cfg;

ls -l /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WWjj_SS_dim8_ewk_Summer16_009/panda/*root|awk '{print"WWjj_SS_dim8_ewk_Summer16 MC 1 "$9}' > WWjj_SS_dim8_ewk_Summer16.cfg
ls -l /mnt/hadoop/scratch/bmaier/gridpanda/VBS_Leptonic_WZjj_dim8_ewk_Summer16_DEBUG_009/panda/*root|awk '{print"WZjj_dim8_ewk_Summer16 MC 1 "$9}' > WZjj_dim8_ewk_Summer16.cfg
wc *.cfg;

elif [ $# == 1 ] && [ $1 == 2 ]; then
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_long_Summer16/panda|grep root|awk '{print"WWjj_SS_long_Summer16 MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_long_Summer16/panda/"$1}' > WWjj_SS_long_Summer16.cfg
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_long_Fall17/panda  |grep root|awk '{print"WWjj_SS_long_Fall17   MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_long_Fall17/panda/"$1}'   > WWjj_SS_long_Fall17.cfg
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_long_Autumn18/panda|grep root|awk '{print"WWjj_SS_long_Autumn18 MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_long_Autumn18/panda/"$1}' > WWjj_SS_long_Autumn18.cfg
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_lttt_Summer16/panda|grep root|awk '{print"WWjj_SS_lttt_Summer16 MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_lttt_Summer16/panda/"$1}' > WWjj_SS_lttt_Summer16.cfg
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_lttt_Fall17/panda  |grep root|awk '{print"WWjj_SS_lttt_Fall17   MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_lttt_Fall17/panda/"$1}'   > WWjj_SS_lttt_Fall17.cfg
gfal-ls gsiftp://se01.cmsaf.mit.edu:2811/mnt/hadoop/cms/store/user/bmaier/gridpanda/WWjj_SS_lttt_Autumn18/panda|grep root|awk '{print"WWjj_SS_lttt_Autumn18 MC 1 root://xrootd.cmsaf.mit.edu//store/user/bmaier/gridpanda/WWjj_SS_lttt_Autumn18/panda/"$1}' > WWjj_SS_lttt_Autumn18.cfg

fi
