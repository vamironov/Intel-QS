all:
	cd qureg; make
	cd tests; make
clean:
	cd qureg; make clean
	cd tests; make clean
depend:
	cd qureg; make depend
	cd tests; make depend
