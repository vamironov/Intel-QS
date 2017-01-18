include ../make.inc

LDFLAGS =   -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_ilp64 -lpthread

#LDFLAGS = -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_lp64 -lpthread \

EXEC = qasm_interface.exe

$(EXEC): makefile qasm_interface.o
	$(CC) -o $(EXEC) ${CFLAGS} ${LDFLAGS} qasm_interface.o ../qureg/qHiPSTER.a

qasm_interface.o: qasm_interface.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c qasm_interface.cpp

clean:
	rm -f *.o *.s *.d *~ 

depend:
	makedepend -Y ${SRC} ${INC}
# DO NOT DELETE
