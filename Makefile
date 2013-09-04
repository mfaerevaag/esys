COMP := clang

.PHONY: one run

one:
	$(COMP) one.c -o one

run:
	one
	./one ARG="test"
