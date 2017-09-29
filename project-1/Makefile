CC=gcc
CFLAGS=-I.
DEPS = parse.h y.tab.h log.h
OBJ = y.tab.o lex.yy.o parse.o lisod.o
FLAGS = -g -Wall

default:all

all: lisod

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

example: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

lisod: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o lisod echo_client log.c log.h lex.yy.c y.tab.c y.tab.h
