COMP := gcc

.PHONY: ecg

FILES := $(wildcard ./*.c)

COMMON := -std=gnu99 $(FILES) -o bin/ecg -lm -lncurses

ecg:
	$(COMP) $(COMMON)

ecgd:
	$(COMP) $(COMMON) -g

ecgp:
	$(COMP) $(COMMON) -pg
