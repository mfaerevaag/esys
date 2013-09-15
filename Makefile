COMP := gcc

.PHONY: day1 ecg

day1:
	$(COMP) -g day1/maxint.c -o bin/maxint


ECG_FILES := $(wildcard ecg/*.c)

ecg:
	$(COMP) -std=gnu99 $(ECG_FILES) -o bin/ecg -lm

ecgd:
	$(COMP) -std=gnu99 -g $(ECG_FILES) -o bin/ecg -lm

ecgp:
	$(COMP) -std=gnu99 -pg $(ECG_FILES) -o bin/ecg -lm
