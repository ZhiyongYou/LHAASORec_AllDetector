#!/bin/bash
mclistdir=/lhaasofs/user/youzhiyong/LHAASO/LHAASORec_AllDetector/mclistdir
mcjobdir=/lhaasofs/user/youzhiyong/LHAASO/LHAASORec_AllDetector/mcjob

outdir=/eos/user/y/youzhiyong/LHAASO/LHAASORec_AllDetector/simulation
srcdir=/eos/user/y/youzhiyong/LHAASORec_AllDetector

Particals="Proton Helium CNO MgAlSi Iron"
energys="1.e13_1.e14 1.e14_1.e15 1.e15_1.e16"

for Partical in $Particals
do
    for energy in $energys
	do
		for irun in `seq 0 99`
		do
			irun=`printf %03d $irun`
			mkdir -p $mcjobdir/$Partical/$energy
			echo '#!/bin/bash' >$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "mclistdir=$mclistdir/$Partical/$energy" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "outdir=$outdir/$Partical/$energy" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo 'mkdir -p $outdir' >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "ifilelist=run${irun}.list" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo 'ifilerun=${ifilelist%.list}' >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo "cd $srcdir" >>$mcjobdir/$Partical/$energy/run${irun}.sh
			echo './mainmc $mclistdir/$ifilelist $outdir/${ifilerun}.rec.root' >>$mcjobdir/$Partical/$energy/run${irun}.sh
			chmod 755 $mcjobdir/$Partical/$energy/run${irun}.sh
		done
	done
done
