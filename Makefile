all : vulnerable_program

vulnerable_program : main.c
	gcc -fno-stack-protector -z execstack -no-pie -g -o vulnerable_program main.c

clean : 
	rm vulnerable_program

run :
	./vulnerable_program payload.bin

sec :
	checksec --file=./vulnerable_program

sec_en :
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

gdb : 
	gdb --args vulnerable_program payload.bin

