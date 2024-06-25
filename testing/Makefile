# -*- MakeFile -*-


objects = memory_safe_obj_test.o


all: memory_safe_obj_test atomic_test

memory_safe_obj_test : memory_safe_obj_test.o test_location.o
	g++ -g memory_safe_obj_test.o test_location.o -o memory_safe_obj_test -l m

atomic_test: atomic_test.o
	g++ -g atomic_test.o -o atomic_test -l m

memory_safe_obj_test.o : ./lib/doctest.h ../src/tasks/memory_mgmt/memory.hpp #../src/tasks/memory_mgmt/memory_safe_obj.hpp
	g++ -g -c ./src/memory_mgmt/memory_safe_obj_test.cpp -o memory_safe_obj_test.o

test_location.o: ../src/tasks/memory_mgmt/memory.hpp
	g++ -g -c ./src/memory_mgmt/test_memory_location/test_location.cpp -o test_location.o

atomic_test.o: ./src/memory_mgmt/memory_safe_obj_test.cpp
	g++ -g -c ./src/memory_mgmt/atomic_test.cpp

