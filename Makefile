default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  simple multitask: compile your programs"
	@echo "  runsimple runmultitask:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

simple: simple.c
	gcc -Wall -pthread -o simple simple.c 

multitask: multitask.c
	gcc -Wall -pthread -o multitask multitask.c 

# add your own rules when you create new programs

#########################
## program execution

runsimple: simple
	#time ./simple

runmultitask: multitask
	time ./multitask

#########################
## utilities

# this rule is useful to generate the "project starter kit"
#
# but we could use it in the students->teacher direction too !
package: clean
	mkdir ops-pthread
	cp Makefile generator.cs *.c *.txt ops-pthread
	cp ../tp-pthreads-sujet/tp-pthreads.pdf ops-pthread
	cp README.txt ops-pthread
	tar zcvf ops-pthread.tgz ops-pthread
	rm -rf ops-pthread



clean:
	rm -f simple multitask ops-pthread.tgz

