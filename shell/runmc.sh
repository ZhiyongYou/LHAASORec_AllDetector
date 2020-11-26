#!/bin/bash
inlistdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/shell
outdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/shell/rootfile

mkdir -p $outdir

ifilelist=run000.list
ifilerun=${ifilelist%.list}

cd /eos/user/y/youzhiyong/LHAASORec_AllDetector
./mainmc $inlistdir/$ifilelist $outdir/${ifilerun}.rec.root
