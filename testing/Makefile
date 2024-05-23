# -*- MakeFile -*-


objects = memory_safe_obj_test.o


all: memory_safe_obj_test

memory_safe_obj_test : memory_safe_obj_test.o test_location.o
	g++ memory_safe_obj_test.o test_location.o -o memory_safe_obj_test -l m

memory_safe_obj_test.o : ./lib/doctest.h ../src/tasks/memory_mgmt/memory.hpp #../src/tasks/memory_mgmt/memory_safe_obj.hpp
	g++ -c ./src/memory_mgmt/memory_safe_obj_test.cpp -o memory_safe_obj_test.o

test_location.o: ../src/tasks/memory_mgmt/memory.hpp
	g++ -c ./src/memory_mgmt/test_memory_location/test_location.cpp -o test_location.o