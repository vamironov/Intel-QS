include ../make.inc

LDFLAGS =   -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_ilp64 -lpthread

LDFLAGS = -L$(MKLROOT)lib/intel64 -lmkl_cdft_core -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_lp64 -lpthread \

ifdef memcheck
 LDFLAGS := ${LDFLAGS} /home/msmelyan/valgrind-3.11.0/installed/lib/valgrind/libmpiwrap-amd64-linux.so
endif

EXECS := benchgates.exe\
	 testgates.exe\
	 qft_test.exe\
	 expect_value_test.exe\
	 noisy_circuit_test.exe

all: ${EXECS}

benchgates.exe: benchgates.o makefile ../qureg/qHiPSTER.a
	$(CC) -o benchgates.exe ${CFLAGS} benchgates.o ${LDFLAGS} ../qureg/qHiPSTER.a
testgates.exe: testgates.o makefile ../qureg/qHiPSTER.a
	$(CC) -o testgates.exe ${CFLAGS} testgates.o ${LDFLAGS} ../qureg/qHiPSTER.a
qft_test.exe: qft_test.o makefile  ../qureg/qHiPSTER.a
	$(CC) -o qft_test.exe ${CFLAGS} qft_test.o ${LDFLAGS} ../qureg/qHiPSTER.a
expect_value_test.exe: expect_value_test.o makefile ../qureg/qHiPSTER.a
	$(CC) -o expect_value_test.exe ${CFLAGS} expect_value_test.o ${LDFLAGS} ../qureg/qHiPSTER.a
noisy_circuit_test.exe: noisy_circuit_test.o makefile ../qureg/qHiPSTER.a
	$(CC) -o noisy_circuit_test.exe ${CFLAGS} noisy_circuit_test.o ${LDFLAGS} ../qureg/qHiPSTER.a

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} ${LDFLAGS} -c $< -o $@

clean:
	rm -f *.o *.s *.d *~ ${EXECS}

depend:
	makedepend -Y ${SRC} ${INC}
# DO NOT DELETE
