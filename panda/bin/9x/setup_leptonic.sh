#!/bin/bash

export PATH=${PATH}:${CMSSW_BASE}/src/PandaCore/bin/

export PANDA="${CMSSW_BASE}/src/PandaAnalysis"
export PANDA_CFG="http://t3serv001.mit.edu/~ceballos/ceballos/catalog/test.cfg"
export PANDA_FLATDIR="/export/data/t3home000/ceballos/panda/v_007_0/"
mkdir -p $PANDA_FLATDIR

export SUBMIT_TMPL="skim_lep_tmpl.py"
#export SUBMIT_TMPL="skim_lepfake_tmpl.py"
export SUBMIT_NAME="v_007_0"
export SUBMIT_WORKDIR="/data/t3serv014/ceballos/condor/"${SUBMIT_NAME}"/work/"
export SUBMIT_LOCKDIR="/data/t3serv014/ceballos/panda/"${SUBMIT_NAME}"/locks/"
export SUBMIT_LOGDIR="/data/t3serv014/ceballos/condor/"${SUBMIT_NAME}"/logs/"
export SUBMIT_OUTDIR="/data/t3serv014/ceballos/panda/"${SUBMIT_NAME}"/batch/"
mkdir -p $SUBMIT_WORKDIR $SUBMIT_LOCKDIR $SUBMIT_LOGDIR $SUBMIT_OUTDIR

export SUBMIT_CONFIG=T2
