COMP := gcc

.PHONY: all ecg ecgd ecgp ecgo

FILES := $(wildcard ./src/*.c)

COMMON := -std=gnu99 $(FILES) -lm -lncurses

OPT := -O3

all: ecg ecgo ecgd ecgp ecgo0 ecgo1 ecgo2 ecgo3

ecg:
	$(COMP) $(COMMON) -o bin/ecg 

ecgo%:
	$(COMP) $(COMMON) -O$* -o bin/$@

ecgd:
	$(COMP) $(COMMON) -g -o bin/ecgd

ecgp:
	$(COMP) $(COMMON) $(OPT) -pg -o bin/ecgp 

prof: ecgp
	bin/ecgp -f test_data/ECG10800K.txt -l 10800000
	gprof bin/ecgp -b > output/prof.stats
	cat output/prof.stats

proft:
	time bin/ecgo

