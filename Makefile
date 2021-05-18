CC = gcc
CFLAGS = -g
OBJ = hello.o mylib.o
TARGET = hello

hello : hello.o mylib.o
	# $@ : TARGET, $^ : make를 위한 코드 리스트
	$(CC) -o $@ $(OBJ)

clean :
	$(RM) $(OBJ) $(TARGET)

hello.o : hello.c myHeader.h
mylib.o : mylib.c
