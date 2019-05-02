#!/usr/bin/env python
import os, time, sys, getopt
import shutil
import json
import glob
import multiprocessing
import datetime
import fileinput
import socket

def doAnalysis(paths_to_watch):

    processesDict  = dict()
    backgroundDict = dict()

    listFiles = sorted(glob.glob(os.path.join(paths_to_watch, 'studyFitResults*.txt')));
    for nFile in range(0, len(listFiles)):
        print listFiles[nFile]
        with open(listFiles[nFile], 'r') as fout:
	    content = fout.read().splitlines()
	
	for nChan in range(0, len(content)):
            theString = content[nChan].split(' ')

            key = theString[0]
	    if(key == "Background"):
                 if key in backgroundDict.keys():
		     var0 = backgroundDict[key][0] + float(theString[1])
		     var1 = backgroundDict[key][1] + float(theString[2])*float(theString[2])-float(theString[3])*float(theString[3])
		     var2 = backgroundDict[key][2] + float(theString[3])*float(theString[3])
		     var3 = backgroundDict[key][3] + float(theString[4])
		     var4 = backgroundDict[key][4] + float(theString[5])*float(theString[5])-float(theString[6])*float(theString[6])
		     var5 = backgroundDict[key][5] + float(theString[6])*float(theString[6])
		     var6 = backgroundDict[key][6] + float(theString[7])
		     var7 = backgroundDict[key][7] + float(theString[8])*float(theString[8])-float(theString[9])*float(theString[9])
		     var8 = backgroundDict[key][8] + float(theString[9])*float(theString[9])
                     backgroundDict.update({key:[var0,var1,var2,var3,var4,var5,var6,var7,var8]})
                 else:
		     var0 = float(theString[1])
		     var1 = float(theString[2])*float(theString[2])-float(theString[3])*float(theString[3])
		     var2 = float(theString[3])*float(theString[3])
		     var3 = float(theString[4])
		     var4 = float(theString[5])*float(theString[5])-float(theString[6])*float(theString[6])
		     var5 = float(theString[6])*float(theString[6])
		     var6 = float(theString[7])
		     var7 = float(theString[8])*float(theString[8])-float(theString[9])*float(theString[9])
		     var8 = float(theString[9])*float(theString[9])
                     backgroundDict.update({key:[var0,var1,var2,var3,var4,var5,var6,var7,var8]})
	    else:
                 if key in processesDict.keys():
		     var0 = processesDict[key][0] + float(theString[1])
		     var1 = processesDict[key][1] + float(theString[2])*float(theString[2])-float(theString[7])*float(theString[7])
		     var2 = processesDict[key][2] + float(theString[3])
		     var3 = processesDict[key][3] + float(theString[4])*float(theString[4])-float(theString[8])*float(theString[8])
		     var4 = processesDict[key][4] + float(theString[5])
		     var5 = processesDict[key][5] + float(theString[6])*float(theString[6])-float(theString[9])*float(theString[9])
		     var6 = processesDict[key][6] + float(theString[7])*float(theString[7])
		     var7 = processesDict[key][7] + float(theString[8])*float(theString[8])
		     var8 = processesDict[key][8] + float(theString[9])*float(theString[9])
                     processesDict.update({key:[var0,var1,var2,var3,var4,var5,var6,var7,var8]})
                 else:
		     var0 = float(theString[1])
		     var1 = float(theString[2])*float(theString[2])-float(theString[7])*float(theString[7])
		     var2 = float(theString[3])
		     var3 = float(theString[4])*float(theString[4])-float(theString[8])*float(theString[8])
		     var4 = float(theString[5])
		     var5 = float(theString[6])*float(theString[6])-float(theString[9])*float(theString[9])
		     var6 = float(theString[7])*float(theString[7])
		     var7 = float(theString[8])*float(theString[8])
		     var8 = float(theString[9])*float(theString[9])
                     processesDict.update({key:[var0,var1,var2,var3,var4,var5,var6,var7,var8]})
	             
    for key in processesDict:
        totalUncPF = pow(processesDict[key][1]+processesDict[key][6],0.5)
        totalUncB  = pow(processesDict[key][3]+processesDict[key][7],0.5)
        totalUncSB = pow(processesDict[key][5]+processesDict[key][8],0.5)
        print "{0:3s}: {1:5.1f} +/- {2:5.1f} ({3:5.1f}) | {4:5.1f} +/- {5:5.1f} ({6:5.1f}) | {7:5.1f} +/- {8:5.1f} ({9:5.1f})".format(key,processesDict[key][0],totalUncPF,pow(processesDict[key][6],0.5),processesDict[key][2],totalUncB,pow(processesDict[key][7],0.5),processesDict[key][4],totalUncSB,pow(processesDict[key][8],0.5))
    for key in backgroundDict:
        totalUncPF = pow(backgroundDict[key][1]+backgroundDict[key][2],0.5)
        totalUncB  = pow(backgroundDict[key][4]+backgroundDict[key][5],0.5)
        totalUncSB = pow(backgroundDict[key][7]+backgroundDict[key][8],0.5)
        print "{0:3s}: {1:5.1f} +/- {2:5.1f} ({3:5.1f}) | {4:5.1f} +/- {5:5.1f} ({6:5.1f}) | {7:5.1f} +/- {8:5.1f} ({9:5.1f})".format(key,backgroundDict[key][0],totalUncPF,pow(backgroundDict[key][2],0.5),backgroundDict[key][3],totalUncB,pow(backgroundDict[key][5],0.5),backgroundDict[key][6],totalUncSB,pow(backgroundDict[key][8],0.5))

"""
Main
"""
valid = ['paths_to_watch=''help']

usage =  "Usage: listdir.py --paths_to_watch=<paths_to_watch>\n"

try:
   opts, args = getopt.getopt(sys.argv[1:], "", valid)
except getopt.GetoptError, ex:
   print usage
   print str(ex)
   sys.exit(1)

paths_to_watch = "."

for opt, arg in opts:
   if opt == "--help":
      print usage
      sys.exit(1)
   if opt == "--paths_to_watch":
      paths_to_watch = arg

doAnalysis(paths_to_watch)
