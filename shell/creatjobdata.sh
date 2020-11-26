#!/bin/bash

year=2020
Date=`printf %04d $1`

#jobdir=/lhaasofs/user/youzhiyong/LHAASO/LHAASORec_AllDetector/job/${year}/${Date}
jobdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector/job/${year}/${Date}
infiledir=/eos/lhaaso/decode/wcda+wfcta/match202006/match_step3/${year}/${Date}
#outdir=/lhaasofs/user/youzhiyong/WFCTATrigger/Data/rootv2/${year}/${Date}
outdir=/eos/user/y/youzhiyong/LHAASO/LHAASORec_AllDetector/${year}/${Date}

for ifile in `ls $infiledir/*.root`
do
	infile=`basename $ifile`
	mkdir -p ${jobdir}
	echo ${jobdir}/${infile}.sh
	echo '#!/bin/bash' >${jobdir}/${infile}.sh
	echo 'hostname' >>${jobdir}/${infile}.sh
	echo 'source /cvmfs/lhaaso.ihep.ac.cn/anysw/slc5_ia64_gcc73/external/envb.sh' >>${jobdir}/${infile}.sh
	echo "" >>${jobdir}/${infile}.sh
	echo "infile=$infile" >>${jobdir}/${infile}.sh
	echo "" >>${jobdir}/${infile}.sh
	echo "infiledir=${infiledir}" >>${jobdir}/${infile}.sh
	echo "outdir=${outdir}" >>${jobdir}/${infile}.sh
	echo "" >>${jobdir}/${infile}.sh
	echo 'eos mkdir -p ${outdir}' >>${jobdir}/${infile}.sh
	echo "" >>${jobdir}/${infile}.sh
	echo 'uuiddir=`uuidgen`' >>${jobdir}/${infile}.sh
	echo 'mkdir -p /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.sh
	echo 'cp /eos/user/y/youzhiyong/LHAASORec_AllDetector/config/WCDA/water_eff/0110.txt /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.sh
	echo 'cd /eos/user/y/youzhiyong/LHAASORec_AllDetector' >>${jobdir}/${infile}.sh
	echo '/eos/user/y/youzhiyong/LHAASORec_AllDetector/main ${infiledir}/$infile ${outdir}/${infile}.rec.root /tmp/youzhiyong/$uuiddir/0110.txt' >>${jobdir}/${infile}.sh
	echo 'rm -rf /tmp/youzhiyong/$uuiddir' >>${jobdir}/${infile}.sh
	chmod 755 ${jobdir}/${infile}.sh
done
