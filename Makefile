COMP := clang

.PHONY: day1 ecg

day1:
	$(COMP) -g day1/maxint.c -o bin/maxint

ecg:
	$(COMP) -g ecg/main.c ecg/sensor.c -o bin/ecg
