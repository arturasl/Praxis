main : main.asm
	as --gstabs+ main.asm -o main.o
	ld -dynamic-linker /lib/ld-linux.so.2 -lc main.o -o main
