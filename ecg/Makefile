COMP := gcc

.PHONY: ecg

FILES := $(wildcard ./*.c)

ecg:
	$(COMP) -std=gnu99 $(FILES) -o bin/ecg -lm

ecgd:
	$(COMP) -std=gnu99 -g $(FILES) -o bin/ecg -lm

ecgp:
	$(COMP) -std=gnu99 -pg $(FILES) -o bin/ecg -lm
