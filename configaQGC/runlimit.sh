#!/bin/bash

ParaName=$1;
RangeLow=$2;
RangeHigh=$3;


echo "Step1: prepare quadratic files"
cp ../data/anomalousCoupling/signal_proc_aqgc_2016_histo_WWjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2016_histo_WWjj.root
cp ../data/anomalousCoupling/signal_proc_aqgc_2016_histo_WZjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2016_histo_WZjj.root
cp ../data/anomalousCoupling/signal_proc_aqgc_2017_histo_WWjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2017_histo_WWjj.root
cp ../data/anomalousCoupling/signal_proc_aqgc_2017_histo_WZjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2017_histo_WZjj.root
cp ../data/anomalousCoupling/signal_proc_aqgc_2018_histo_WWjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2018_histo_WWjj.root
cp ../data/anomalousCoupling/signal_proc_aqgc_2018_histo_WZjj_$ParaName\.root ../data/anomalousCoupling/signal_proc_aqgc_2018_histo_WZjj.root


echo "Step2: prepare cards"
python buildWorkspace_AC.py --config=conf_v4_2016_ww
python buildWorkspace_AC.py --config=conf_v4_2016_wz
python buildWorkspace_AC.py --config=conf_v4_2017_ww
python buildWorkspace_AC.py --config=conf_v4_2017_wz
python buildWorkspace_AC.py --config=conf_v4_2018_ww
python buildWorkspace_AC.py --config=conf_v4_2018_wz


echo "Step3: combine cards"
combineCards.py aC_aqgc_2016_histo_WWjj.txt > aC_aqgc_2016_histo_WWjj_$ParaName\.txt
combineCards.py aC_aqgc_2016_histo_WZjj.txt > aC_aqgc_2016_histo_WZjj_$ParaName\.txt

combineCards.py aC_aqgc_2017_histo_WWjj.txt > aC_aqgc_2017_histo_WWjj_$ParaName\.txt
combineCards.py aC_aqgc_2017_histo_WZjj.txt > aC_aqgc_2017_histo_WZjj_$ParaName\.txt

combineCards.py aC_aqgc_2018_histo_WWjj.txt > aC_aqgc_2018_histo_WWjj_$ParaName\.txt
combineCards.py aC_aqgc_2018_histo_WZjj.txt > aC_aqgc_2018_histo_WZjj_$ParaName\.txt

combineCards.py aC_aqgc_2016_histo_WWjj.txt aC_aqgc_2016_histo_WZjj.txt > aC_aqgc_2016_histo_comb_$ParaName\.txt
combineCards.py aC_aqgc_2017_histo_WWjj.txt aC_aqgc_2017_histo_WZjj.txt > aC_aqgc_2017_histo_comb_$ParaName\.txt
combineCards.py aC_aqgc_2018_histo_WWjj.txt aC_aqgc_2018_histo_WZjj.txt > aC_aqgc_2018_histo_comb_$ParaName\.txt

combineCards.py aC_aqgc_2016_histo_WWjj.txt aC_aqgc_2017_histo_WWjj.txt aC_aqgc_2018_histo_WWjj.txt > aC_aqgc_RUN2_histo_ww_$ParaName\.txt
combineCards.py aC_aqgc_2016_histo_WZjj.txt aC_aqgc_2017_histo_WZjj.txt aC_aqgc_2018_histo_WZjj.txt > aC_aqgc_RUN2_histo_wz_$ParaName\.txt

combineCards.py aC_aqgc_2016_histo_WWjj.txt aC_aqgc_2016_histo_WZjj.txt aC_aqgc_2017_histo_WWjj.txt aC_aqgc_2017_histo_WZjj.txt aC_aqgc_2018_histo_WWjj.txt aC_aqgc_2018_histo_WZjj.txt > aC_aqgc_RUN2_histo_comb_$ParaName\.txt

echo "Step3: t2w"
text2workspace.py -m 126 aC_aqgc_2016_histo_WWjj_$ParaName\.txt -o Example_aC_aqgc_2016_histo_WWjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WWjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_2016_histo_WZjj_$ParaName\.txt -o Example_aC_aqgc_2016_histo_WZjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

text2workspace.py -m 126 aC_aqgc_2017_histo_WWjj_$ParaName\.txt -o Example_aC_aqgc_2017_histo_WWjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2017_histo_WWjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_2017_histo_WZjj_$ParaName\.txt -o Example_aC_aqgc_2017_histo_WZjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2017_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

text2workspace.py -m 126 aC_aqgc_2018_histo_WWjj_$ParaName\.txt -o Example_aC_aqgc_2018_histo_WWjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2018_histo_WWjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_2018_histo_WZjj_$ParaName\.txt -o Example_aC_aqgc_2018_histo_WZjj_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2018_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

text2workspace.py -m 126 aC_aqgc_2016_histo_comb_$ParaName\.txt -o Example_aC_aqgc_2016_histo_comb_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WWjj,aqgc_2016_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_2017_histo_comb_$ParaName\.txt -o Example_aC_aqgc_2017_histo_comb_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2017_histo_WWjj,aqgc_2017_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_2018_histo_comb_$ParaName\.txt -o Example_aC_aqgc_2018_histo_comb_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2018_histo_WWjj,aqgc_2018_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

text2workspace.py -m 126 aC_aqgc_RUN2_histo_ww_$ParaName\.txt -o Example_aC_aqgc_RUN2_histo_ww_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WWjj,aqgc_2017_histo_WWjj,aqgc_2018_histo_WWjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh
text2workspace.py -m 126 aC_aqgc_RUN2_histo_wz_$ParaName\.txt -o Example_aC_aqgc_RUN2_histo_wz_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WZjj,aqgc_2017_histo_WZjj,aqgc_2018_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

text2workspace.py -m 126 aC_aqgc_RUN2_histo_comb_$ParaName\.txt -o Example_aC_aqgc_RUN2_histo_comb_$ParaName\.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=aqgc_2016_histo_WWjj,aqgc_2016_histo_WZjj,aqgc_2017_histo_WWjj,aqgc_2017_histo_WZjj,aqgc_2018_histo_WWjj,aqgc_2018_histo_WZjj --PO poi=$ParaName --PO range_$ParaName=$RangeLow,$RangeHigh

echo "Step3-exp combine"
combine Example_aC_aqgc_2016_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2016_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_2016_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2016_$ParaName\_exp -t -1 --expectSignal=1

combine Example_aC_aqgc_2017_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2017_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_2017_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2017_$ParaName\_exp -t -1 --expectSignal=1

combine Example_aC_aqgc_2018_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2018_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_2018_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2018_$ParaName\_exp -t -1 --expectSignal=1

combine Example_aC_aqgc_2016_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2016_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_2017_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2017_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_2018_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2018_$ParaName\_exp -t -1 --expectSignal=1


combine Example_aC_aqgc_RUN2_histo_ww_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n ww_RUN2_$ParaName\_exp -t -1 --expectSignal=1
combine Example_aC_aqgc_RUN2_histo_wz_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n wz_RUN2_$ParaName\_exp -t -1 --expectSignal=1

combine Example_aC_aqgc_RUN2_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_RUN2_$ParaName\_exp -t -1 --expectSignal=1 #-S 0

echo "Step3-obs combine"
combine Example_aC_aqgc_2016_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2016_$ParaName\_obs
combine Example_aC_aqgc_2016_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2016_$ParaName\_obs

combine Example_aC_aqgc_2017_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2017_$ParaName\_obs
combine Example_aC_aqgc_2017_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2017_$ParaName\_obs

combine Example_aC_aqgc_2018_histo_WWjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WW_2018_$ParaName\_obs
combine Example_aC_aqgc_2018_histo_WZjj_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n WZ_2018_$ParaName\_obs

combine Example_aC_aqgc_2016_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2016_$ParaName\_obs
combine Example_aC_aqgc_2017_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2017_$ParaName\_obs
combine Example_aC_aqgc_2018_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_2018_$ParaName\_obs


combine Example_aC_aqgc_RUN2_histo_ww_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n ww_RUN2_$ParaName\_obs
combine Example_aC_aqgc_RUN2_histo_wz_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n wz_RUN2_$ParaName\_obs


combine Example_aC_aqgc_RUN2_histo_comb_$ParaName\.root -M MultiDimFit -P $ParaName --floatOtherPOIs=0 --algo=grid --points=1500 --minimizerStrategy=2 -n comb_RUN2_$ParaName\_obs

sleep 10

echo "Step4: limits-exp"
echo "Step4: 2016: ww"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2016_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2016: wz"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2016_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017: ww"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2017_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017: wz"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2017_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018: ww"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2018_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018: wz"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2018_$ParaName\_exp.MultiDimFit.mH120.root $ParaName

echo "Step4: 2016"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2016_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2017_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2018_$ParaName\_exp.MultiDimFit.mH120.root $ParaName

echo "Step4: ww"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineww_RUN2_$ParaName\_exp.MultiDimFit.mH120.root $ParaName
echo "Step4: wz"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinewz_RUN2_$ParaName\_exp.MultiDimFit.mH120.root $ParaName

echo "Step4: all run2"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_RUN2_$ParaName\_exp.MultiDimFit.mH120.root $ParaName

echo "Step4: limits-obs"
echo "Step4: 2016: ww obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2016_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2016: wz obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2016_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017: ww obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2017_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017: wz obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2017_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018: ww obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWW_2018_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018: wz obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineWZ_2018_$ParaName\_obs.MultiDimFit.mH120.root $ParaName

echo "Step4: 2016 obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2016_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2017 obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2017_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: 2018 obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_2018_$ParaName\_obs.MultiDimFit.mH120.root $ParaName

echo "Step4: ww obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombineww_RUN2_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
echo "Step4: wz obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinewz_RUN2_$ParaName\_obs.MultiDimFit.mH120.root $ParaName

echo "Step4: all run2 obs"
python build1DInterval.py $RangeLow $RangeHigh higgsCombinecomb_RUN2_$ParaName\_obs.MultiDimFit.mH120.root $ParaName
