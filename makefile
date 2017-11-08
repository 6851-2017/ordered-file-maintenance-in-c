main.exe : main.o foo.o
	gcc main.o foo.o -o main.exe

ofm.o : OrderedFileMaintenance.c
	gcc -c OrderedFileMaintenance.c

testing.o : ofm-testing.c
	gcc -c ofm-testing.c