over: calc_4.1.1_release
	~/F/PortableGit/week_4/calc_4.1.1_release
calc_4.1.1_release: SeqStack.o WriteCompound.o main.o
	gcc SeqStack.o WriteCompound.o main.o -o calc_4.1.1_release
main.o: main.c
	gcc main.c -c -o main.o
SeqStack.o: SeqStack.c
	gcc SeqStack.c -c -o SeqStack.o
WriteCompound.o: WriteCompound.c
	gcc WriteCompound.c -c -o WriteCompound.o
clean:
	rm calc_4.1.1_release  main.o SeqStack.o WriteCompound.o