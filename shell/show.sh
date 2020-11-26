#!/bin/bash
indir=/eos/lhaaso/decode/wcda+wfcta/match202006/match_step3/2020/0125
outdir=/workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector/pic
water_eff_file=/lhaasofs/user/youzhiyong/LHAASO/LHAASORec_AllDetector/software/config/WCDA/water_eff/0110.txt
cd /workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector

./eventshow $indir/202001252150.weather.good.root $outdir $water_eff_file
