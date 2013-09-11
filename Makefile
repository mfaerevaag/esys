COMP := clang

.PHONY: day1 ecg

day1:
	$(COMP) -g day1/maxint.c -o bin/maxint

ECG_FILES := $(wildcard ecg/*.c)

ecg:
	$(COMP) -g $(ECG_FILES) -o bin/ecg -lm
