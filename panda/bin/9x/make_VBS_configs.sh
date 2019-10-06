#!/bin/sh

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

