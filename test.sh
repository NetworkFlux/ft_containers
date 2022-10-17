#!/usr/bin/env bash

make
./ft_containers > ft_output.txt
c++ stdOut.cpp
./a.out > std_output.txt
diff ft_output.txt std_output.txt
