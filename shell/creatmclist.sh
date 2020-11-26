#!/bin/bash

indir=/eos/lhaaso/simulation/wfctamc/WFCTA_MCdata/wangyd/MC-Match/KM2A-WFCTAV5
mclistdir=/lhaasofs/user/youzhiyong/LHAASO/LHAASORec_AllDetector/mclistdir

Particals="Proton Helium CNO MgAlSi Iron"
energys="1.e13_1.e14 1.e14_1.e15 1.e15_1.e16"

for Partical in $Particals
do
	for energy in $energys
	do
		for irun in `seq 0 99`
		do
			irun=`printf %03d $irun`
			mkdir -p $mclistdir/$Partical/$energy
			ls $indir/$Partical/$energy/run$irun/* >$mclistdir/$Partical/$energy/run${irun}.list
		done
	done
done
