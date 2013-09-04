COMP := clang

.PHONY: day1

day1:
	$(COMP) day1/maxint.c -o bin/maxint
