#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean

	echo make matvec_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matvec_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./matvec_test.exe

	echo make matmat_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matmat_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./matmat_test.exe
    done
done





