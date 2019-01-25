#!/bin/sh

export YEAR=$1

if [ ${YEAR} == "999" ]; then
#rm MitVHBBAnalysis/datacards/zhbb/testcondor201?/plots_ZemH*

hadd -f plots_WlnHSR_2016.root   MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_W?nHSR.root
hadd -f plots_WlnHSR_2017.root   MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_W?nHSR.root
hadd -f plots_WlnHFJSR_2016.root MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_W?nHFJSR.root
hadd -f plots_WlnHFJSR_2017.root MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_W?nHFJSR.root

hadd -f plots_ZllHFJSR_2017.root MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_Z??HFJSR.root
hadd -f plots_ZllHFJSR_2016.root MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_Z??HFJSR.root
hadd -f plots_ZllHSR_2017.root   MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_Z??HSR_ZptBin?.root
hadd -f plots_ZllHSR_2016.root   MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_Z??HSR_ZptBin?.root

else
hadd -f  		MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnH2TopCR.root			   MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnH2TopCR.root  		      MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenH2TopCR.root
hadd -f  		  MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHFJSR.root			     MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHFJSR.root  			MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHFJSR.root
hadd -f        MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHHeavyFlavorFJCR.root		  MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHHeavyFlavorFJCR.root  	     MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHHeavyFlavorFJCR.root
hadd -f  	 MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHHeavyFlavorCR.root		    MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHHeavyFlavorCR.root  	       MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHHeavyFlavorCR.root
hadd -f  	 MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHLightFlavorCR.root		    MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHLightFlavorCR.root  	       MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHLightFlavorCR.root
hadd -f        MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHLightFlavorFJCR.root		  MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHLightFlavorFJCR.root  	     MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHLightFlavorFJCR.root
hadd -f  		    MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHSR.root			       MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHSR.root  			  MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHSR.root
hadd -f  	      MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WlnHTT2bFJCR.root			 MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WmnHTT2bFJCR.root  		    MitVHBBAnalysis/datacards/whbb/testcondor${YEAR}/plots_WenHTT2bFJCR.root

hadd -f  	MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllH2TopCR_ZptBin0.root		   MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmH2TopCR_ZptBin0.root  	      MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeH2TopCR_ZptBin0.root
hadd -f  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHFJSR.root			     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHFJSR.root  			MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHFJSR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorCR_ZptBin0.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorCR_ZptBin0.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorCR_ZptBin0.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorFJCR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorCR_ZptBin0.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorCR_ZptBin0.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorCR_ZptBin0.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorFJCR.root
hadd -f  	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHSR_ZptBin0.root		       MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHSR_ZptBin0.root  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHSR_ZptBin0.root

hadd -f  	MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllH2TopCR_ZptBin1.root		   MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmH2TopCR_ZptBin1.root  	      MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeH2TopCR_ZptBin1.root
hadd -f  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHFJSR.root			     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHFJSR.root  			MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHFJSR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorCR_ZptBin1.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorCR_ZptBin1.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorCR_ZptBin1.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorFJCR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorCR_ZptBin1.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorCR_ZptBin1.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorCR_ZptBin1.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorFJCR.root
hadd -f  	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHSR_ZptBin1.root		       MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHSR_ZptBin1.root  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHSR_ZptBin1.root

hadd -f  	MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllH2TopCR_ZptBin2.root		   MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmH2TopCR_ZptBin2.root  	      MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeH2TopCR_ZptBin2.root
hadd -f  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHFJSR.root			     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHFJSR.root  			MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHFJSR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorCR_ZptBin2.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorCR_ZptBin2.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorCR_ZptBin2.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHHeavyFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHHeavyFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHHeavyFlavorFJCR.root
hadd -f  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorCR_ZptBin2.root	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorCR_ZptBin2.root         MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorCR_ZptBin2.root
hadd -f        MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHLightFlavorFJCR.root		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHLightFlavorFJCR.root  	     MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHLightFlavorFJCR.root
hadd -f  	    MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZllHSR_ZptBin2.root		       MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZmmHSR_ZptBin2.root  		  MitVHBBAnalysis/datacards/zhbb/testcondor${YEAR}/plots_ZeeHSR_ZptBin2.root

fi
