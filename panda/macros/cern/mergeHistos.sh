#!/bin/sh

export YEAR=$1;

for i in `seq 0 100`;
do
  ls histoDY1_${YEAR}_${i}.root histoDY2_${YEAR}_${i}.root histoDY3_${YEAR}_${i}.root >& /dev/null;
  if [ $? -eq 0 ]; then
    hadd -f histoDY0_${YEAR}_${i}.root histoDY1_${YEAR}_${i}.root histoDY2_${YEAR}_${i}.root histoDY3_${YEAR}_${i}.root;
  fi
done
