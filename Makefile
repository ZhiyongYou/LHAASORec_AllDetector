inc_dir = include/
src_dir = src/
obj_dir = obj/
CCOMPILER  = g++
DEBUG = -O2 #-ggdb  #-g -gstabs -gstabs+ -ggdb -glevel

object = $(obj_dir)G4KM2A_Geometry.o $(obj_dir)G4KM2A_Reconstruction.o \
		 $(obj_dir)WFCTARec.o \
		 $(obj_dir)WCDARec.o \
		 $(obj_dir)CollectIntensity.o $(obj_dir)WFCTAMap.o $(obj_dir)astro.o \
		 $(obj_dir)LHAASOEventRec.o $(obj_dir)LHAASOEventShow.o \
		 $(obj_dir)EventDict.o $(obj_dir)LHEvent.o $(obj_dir)LHRecEvent.o $(obj_dir)KM2AEvent.o \
		 $(obj_dir)LHAASOEvent.o $(obj_dir)LaserEvent.o \
		 $(obj_dir)WFCTAMcEvent.o \
		 $(obj_dir)WCDAMcEvent.o $(obj_dir)WCDAEventRec.o \
		 $(obj_dir)WFCTAMcRecEvent.o

all:main mainmc rec_mc rec_showmc eventshow eventshowmc

eventshowmc: $(obj_dir)eventshowmc.a
	$(CCOMPILER) -o eventshowmc $(obj_dir)eventshowmc.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)eventshowmc.a: $(obj_dir)eventshowmc.o $(object)
	ar -r $(obj_dir)eventshowmc.a $(obj_dir)eventshowmc.o $(object)

$(obj_dir)eventshowmc.o: eventshowmc.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

eventshow: $(obj_dir)eventshow.a
	$(CCOMPILER) -o eventshow $(obj_dir)eventshow.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)eventshow.a: $(obj_dir)eventshow.o $(object)
	ar -r $(obj_dir)eventshow.a $(obj_dir)eventshow.o $(object)

$(obj_dir)eventshow.o: eventshow.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

rec_showmc: $(obj_dir)rec_showmc.a
	$(CCOMPILER) -o rec_showmc $(obj_dir)rec_showmc.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)rec_showmc.a: $(obj_dir)rec_showmc.o $(object)
	ar -r $(obj_dir)rec_showmc.a $(obj_dir)rec_showmc.o $(object)

$(obj_dir)rec_showmc.o: rec_showmc.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

rec_mc: $(obj_dir)rec_mc.a
	$(CCOMPILER) -o rec_mc $(obj_dir)rec_mc.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)rec_mc.a: $(obj_dir)rec_mc.o $(object)
	ar -r $(obj_dir)rec_mc.a $(obj_dir)rec_mc.o $(object)

$(obj_dir)rec_mc.o: rec_mc.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

mainmc: $(obj_dir)mainmc.a
	$(CCOMPILER) -o mainmc $(obj_dir)mainmc.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)mainmc.a: $(obj_dir)mainmc.o $(object)
	ar -r $(obj_dir)mainmc.a $(obj_dir)mainmc.o $(object)

$(obj_dir)mainmc.o: mainmc.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

main: $(obj_dir)main.a
	$(CCOMPILER) -o main $(obj_dir)main.a `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)main.a: $(obj_dir)main.o $(object)
	ar -r $(obj_dir)main.a $(obj_dir)main.o $(object)

$(obj_dir)main.o: main.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)G4KM2A_Geometry.o: $(src_dir)G4KM2A_Geometry.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir)

$(obj_dir)G4KM2A_Reconstruction.o: $(src_dir)G4KM2A_Reconstruction.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs` -lMinuit -lMatrix

$(obj_dir)WFCTARec.o: $(src_dir)WFCTARec.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WCDARec.o: $(src_dir)WCDARec.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)CollectIntensity.o: $(src_dir)CollectIntensity.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WFCTAMap.o: $(src_dir)WFCTAMap.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)astro.o: $(src_dir)astro.c Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LHAASOEventRec.o: $(src_dir)LHAASOEventRec.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LHAASOEventShow.o: $(src_dir)LHAASOEventShow.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)EventDict.o: $(src_dir)EventDict.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LHEvent.o: $(src_dir)LHEvent.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LHRecEvent.o: $(src_dir)LHRecEvent.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)KM2AEvent.o: $(src_dir)KM2AEvent.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LHAASOEvent.o: $(src_dir)LHAASOEvent.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)LaserEvent.o: $(src_dir)LaserEvent.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WFCTAMcEvent.o: $(src_dir)WFCTAMcEvent.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WCDAMcEvent.o: $(src_dir)WCDAMcEvent.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WCDAEventRec.o: $(src_dir)WCDAEventRec.cpp Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

$(obj_dir)WFCTAMcRecEvent.o: $(src_dir)WFCTAMcRecEvent.cc Makefile $(inc_dir)
	$(CCOMPILER) $(DEBUG) -c $< -o $@ -DSCAN -I $(inc_dir) `root-config --cflags --libs`

.PHONY : clean
 clean :
	rm main mainmc rec_mc rec_showmc eventshow EventDict_rdict.pcm obj/*
