#!/bin/bash

export PATH=${PATH}:${CMSSW_BASE}/src/PandaCore/bin/

export PANDA="${CMSSW_BASE}/src/PandaAnalysis"
export PANDA_CFG="http://t3serv001.mit.edu/~ceballos/ceballos/catalog/test3.cfg"
export PANDA_FLATDIR="/data/t3home000/ceballos/panda/v_017_0/"
mkdir -p $PANDA_FLATDIR

export SUBMIT_TMPL="skim_lepfake2018_tmpl.py"
export SUBMIT_NAME="v_017_0"
export SUBMIT_WORKDIR="/data/t3serv014/ceballos/condor/"${SUBMIT_NAME}"/work/"
export SUBMIT_LOCKDIR="/data/t3serv014/ceballos/panda/"${SUBMIT_NAME}"/locks/"
export SUBMIT_LOGDIR="/data/t3serv014/ceballos/condor/"${SUBMIT_NAME}"/logs/"
export SUBMIT_OUTDIR="/mnt/hadoop/cms/store/user/ceballos/panda/"${SUBMIT_NAME}"/batch/"
export SUBMIT_USER=$USER
export SUBMIT_REPORT="t3serv004.mit.edu:5000"
mkdir -p $SUBMIT_WORKDIR $SUBMIT_LOCKDIR $SUBMIT_LOGDIR $SUBMIT_OUTDIR
export SUBMIT_HDFSCACHE=0

export SUBMIT_CONFIG=T2:SL6
export SUBMIT_TEXTLOCK=0
