#!/bin/sh

for i in `seq 0 100`;
do
  ls done/histoZHG_2016_${i}.root done/histoZHG_2017_${i}.root done/histoZHG_2018_${i}.root >& /dev/null
  if [ $? -eq 0 ]; then
    hadd -f done/histoZHG_2019_${i}.root done/histoZHG_2016_${i}.root done/histoZHG_2017_${i}.root done/histoZHG_2018_${i}.root
  fi
done

for i in `seq 0 100`;
do
  ls done/histoZH_2016_${i}.root done/histoZH_2017_${i}.root done/histoZH_2018_${i}.root >& /dev/null
  if [ $? -eq 0 ]; then
    hadd -f done/histoZH_2019_${i}.root done/histoZH_2016_${i}.root done/histoZH_2017_${i}.root done/histoZH_2018_${i}.root
  fi
done

for i in `seq 0 100`;
do
  ls done/histoWZ_2016_${i}.root done/histoWZ_2017_${i}.root done/histoWZ_2018_${i}.root >& /dev/null
  if [ $? -eq 0 ]; then
    hadd -f done/histoWZ_2019_${i}.root done/histoWZ_2016_${i}.root done/histoWZ_2017_${i}.root done/histoWZ_2018_${i}.root
  fi
done

for i in `seq 0 100`;
do
  ls done/histoZZ_2016_${i}.root done/histoZZ_2017_${i}.root done/histoZZ_2018_${i}.root >& /dev/null
  if [ $? -eq 0 ]; then
    hadd -f done/histoZZ_2019_${i}.root done/histoZZ_2016_${i}.root done/histoZZ_2017_${i}.root done/histoZZ_2018_${i}.root
  fi
done

for i in `seq 0 100`;
do
  ls done/histossww_2016_${i}.root done/histossww_2017_${i}.root done/histossww_2018_${i}.root >& /dev/null
  if [ $? -eq 0 ]; then
    hadd -f done/histossww_2019_${i}.root done/histossww_2016_${i}.root done/histossww_2017_${i}.root done/histossww_2018_${i}.root
  fi
done
