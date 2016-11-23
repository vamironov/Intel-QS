include ../make.inc

SRC := $(wildcard *.cpp ../util/openmp.cpp ../util/mpi.cpp ../util/utils.cpp)
OBJ := $(addsuffix .o, $(basename $(SRC)))

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c $< -o $@


all: qHiPSTER.a
qHiPSTER.a: $(OBJ) makefile
	ar rcs $@ $^

depend:
	makedepend -Y ${SRC} ${INC}

clean:
	rm -f *.o *.s *.d *~ 
# DO NOT DELETE

qureg_utils.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_utils.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applyctrl1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_applyctrl1qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_applyctrl1qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_measure.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_measure.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_permute.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_permute.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_init.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_init.o: ../util/mpi.hpp ../util/prng_engine.hpp
highperfkernels.o: highperfkernels.hpp qureg.hpp permute.hpp
highperfkernels.o: ../util/utils.hpp ../util/timer.hpp ../util/mpi.hpp
highperfkernels.o: ../util/prng_engine.hpp
qureg_apply1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply1qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_apply1qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_apply2qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply2qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_apply2qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_applydiag.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_applydiag.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applydiag.o: highperfkernels.hpp
qureg_fusion.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_fusion.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applyswap.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_applyswap.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applyswap.o: highperfkernels.hpp
../util/utils.o: ../util/timer.hpp ../util/utils.hpp ../util/mpi.hpp
