CC = g++
CC = mpicxx 
CC = CC -mkl -no-ipo
CC = mpiicpc 


OPTS = -g
OPTS = -O3
VECS = -qopt-report-phase=vec -qopt-report=2
DEFS = -DUSE_MM_MALLOC -DSTANDALONE -DOPENQU_HAVE_MPI -DMKL_ILP64

CFLAGS = ${OPTS} ${DEFS} \
         -Wall -std=c++11 -fasm-blocks -qopenmp -restrict


CFLAGS += ${OPTFLAGS}  
INC = -I./ -I../
