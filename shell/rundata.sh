#!/bin/bash
indir=/eos/lhaaso/decode/wcda+wfcta/match202006/match_step3/2020/0125
outdir=/workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector
cd /workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector

./main $indir/202001252220.weather.good.root $outdir/202001252220.weather.good.root.rec.root
