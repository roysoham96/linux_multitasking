Number generator
----------------

The project is about decomposing  large numbers into prime factors. We
provide you  with a  script which generates  an arbitraty  quantity of
"random"  numbers. Each  number is  scaled  down to  a certain  binary
magnitude (e.g. if you set this parameter to 10, then all your numbers
will  be smaller  than 1024).

The  script  also include  a  "redundancy"  parameter to  artificially
control the "variety" of the results. This feature will only be useful
in the last part of the project.


The script prints out numbers on its standard output, so you should
redirect that into a file:

    ./generator.cs 50 32 0 > fifty_distinct_smallish_numbers.txt

    ./generator.cs 10 64 100 > one_large_number_repeated_ten_times.txt


Makefile
--------

Here are the predefined targets:

- tiny.txt,  small.txt, medium.txt,  large.txt:  invoke the  generator
  with various parameters and save the resulting numbers in text files

- simple, multitask: compile C programs into an executable.

- runsimple, runmultitask: execute programs within the "time" command

- clean: delete generated files