CC=gcc
CFLAGS=-I.
DEPS = parse.h y.tab.h log.h
OBJ = y.tab.o lex.yy.o parse.o log.o lisod.o
FLAGS = -g -Wall -Werror

default:lisod

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

lisod: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

example: y.tab.o lex.yy.o parse.o example.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o lisod log.c log.h lex.yy.c y.tab.c y.tab.h
