all:
	@echo "Usage: make <command>"
	@echo ""
	@echo "Commands:"
	@echo "    test        Test if everything's fine"
	@echo "    score       Get score of it"
	@echo "    asm         Get x86 version of ncopy.ys"

test: rebuild
	cd ~/sim/pipe &&\
	~/sim/misc/yas ncopy.ys &&\
	./check-len.pl < ncopy.yo &&\
	./correctness.pl &&\
	(cd ../y86-code; make testpsim) &&\
	(cd ../ptest; make SIM=../pipe/psim TFLAGS=-i) &&\
	./correctness.pl -p



score: rebuild
	cd ~/sim/pipe &&\
	./benchmark.pl

rebuild: ncopy.ys pipe-full.hcl
	cd ~/sim/pipe &&\
	make drivers &&\
	make psim VERSION=full

asm:
	gcc -m32 -S -O3 ncopy.c

.PHONY: test score asm
