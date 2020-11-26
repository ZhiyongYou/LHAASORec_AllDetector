#!/bin/bash

year=2020
Date=`printf %04d $1`

jobdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/jobshow/${year}/${Date}
infiledir=/eos/lhaaso/decode/wcda+wfcta/match202006/match_step3/${year}/${Date}
outdir=/eos/user/y/youzhiyong/LHAASO/LHAASORec_AllDetector/show/${year}/${Date}/pic

for ifile in `ls $infiledir/*.root`
do
	infile=`basename $ifile`
	mkdir -p ${jobdir}
	echo ${jobdir}/${infile}.show.sh
	echo '#!/bin/bash' >${jobdir}/${infile}.show.sh
	echo 'hostname' >>${jobdir}/${infile}.show.sh
	echo 'source /cvmfs/lhaaso.ihep.ac.cn/anysw/slc5_ia64_gcc73/external/envb.sh' >>${jobdir}/${infile}.show.sh
	echo "" >>${jobdir}/${infile}.show.sh
	echo "infile=$infile" >>${jobdir}/${infile}.show.sh
	echo "" >>${jobdir}/${infile}.show.sh
	echo "infiledir=${infiledir}" >>${jobdir}/${infile}.show.sh
	echo "outdir=${outdir}" >>${jobdir}/${infile}.show.sh
	echo "" >>${jobdir}/${infile}.show.sh
	echo 'eos mkdir -p ${outdir}' >>${jobdir}/${infile}.show.sh
	echo 'eos mkdir -p ${outdir}/wcda' >>${jobdir}/${infile}.show.sh
	echo 'eos mkdir -p ${outdir}/wfcta_focus' >>${jobdir}/${infile}.show.sh
	echo 'eos mkdir -p ${outdir}/km2a' >>${jobdir}/${infile}.show.sh
	echo "" >>${jobdir}/${infile}.show.sh
	echo 'uuiddir=`uuidgen`' >>${jobdir}/${infile}.show.sh
	echo 'mkdir -p /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.show.sh
	echo 'cp /eos/user/y/youzhiyong/LHAASORec_AllDetector/config/WCDA/water_eff/0110.txt /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.show.sh
	echo 'cd /eos/user/y/youzhiyong/LHAASORec_AllDetector' >>${jobdir}/${infile}.show.sh
	echo '/eos/user/y/youzhiyong/LHAASORec_AllDetector/eventshow ${infiledir}/$infile ${outdir} /tmp/youzhiyong/$uuiddir/0110.txt' >>${jobdir}/${infile}.show.sh
	echo 'rm -rf /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.show.sh
	chmod 755 ${jobdir}/${infile}.show.sh
done
#	echo 'cd /workfs/ybj/youzhiyong/LHAASO/LHAASORec_AllDetector' >>${jobdir}/${infile}.show.sh
