#!/usr/bin/env python

from PandaCore.Tools.script import * 
from PandaCore.Tools.root_interface import Selector 
import PandaCore.Tools.Functions
import numpy as np
import json 
import os

args = parse('--basedir', '--out', '--name', '--json', '--prefix', '--sel')

try:
    os.makedirs(args.out+'/'+args.prefix)
except OSError:
    pass

with open(args.json) as jsonfile:
    payload = json.load(jsonfile)
    weight = payload['weight']
    if(args.sel == "ZH_boosted"):
        features = payload['features_ZH_boosted']
        cut = payload['cut_ZH_boosted']
    elif(args.sel == "ZH_resolved"):
        features = payload['features_ZH_resolved']
        cut = payload['cut_ZH_resolved']
    elif(args.sel == "WH_boosted"):
        features = payload['features_WH_boosted']
        cut = payload['cut_WH_boosted']
    elif(args.sel == "WH_resolved"):
        features = payload['features_WH_resolved']
        cut = payload['cut_WH_resolved']
    else:
        logger.error(sys.argv[0], 'Could not identify selection '+args.sel)
        sys.exit(1)

    for i,s in enumerate(payload['samples']):
        if s['name'] == args.name:
            samples = s['samples']
            y = i
            break
    else:
        logger.error(sys.argv[0], 'Could not identify process '+args.name)
        sys.exit(1)

s = Selector()
chain = root.TChain('mvaTree')
for sample in samples:
    chain.AddFile(args.basedir + '/' + args.prefix + '_' + sample + '.root')

logger.info(sys.argv[0], 'Reading files for process '+args.name)
s.read_tree(chain, branches=(features+[weight]), cut=cut)

X = np.vstack([s[f] for f in features]).T 
W = s[weight]
#W *= 1000 / W.sum()
Y = y * np.ones(shape=W.shape)

def save(arr, label):
    theName = args.name
    theName = theName.replace('_forZH_2016','')
    theName = theName.replace('_forZH_2017','')
    theName = theName.replace('_forWH_2016','')
    theName = theName.replace('_forWH_2017','')
    theName = theName.replace('_forZH','')
    theName = theName.replace('_forWH','')
    fout = args.out+'/'+args.prefix+'/'+theName+'_'+label+'.npy'
    np.save(fout, arr)
    logger.info(sys.argv[0], 'Saved to '+fout)

save(X, 'x')
save(Y, 'y')
save(W, 'w')
