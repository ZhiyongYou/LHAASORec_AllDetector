#!/bin/bash
inlistdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/shell
outdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/shell/pic

mkdir -p $outdir
mkdir -p $outdir/wfcta_focus
mkdir -p $outdir/km2a


ifilelist=mcsingle.list
ifilerun=${ifilelist%.list}

cd /eos/user/y/youzhiyong/LHAASORec_AllDetector
./rec_showmc $inlistdir/$ifilelist $outdir
