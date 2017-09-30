CC=gcc
CFLAGS=-I.
<<<<<<< HEAD
DEPS = parse.h y.tab.h log.h
OBJ = y.tab.o lex.yy.o parse.o log.o lisod.o
=======
DEPS = parse.h y.tab.h log.h process_request.h
OBJ = y.tab.o lex.yy.o parse.o log.o process_request.o lisod.o
>>>>>>> 7f71dbb677470bbec27570681c90e61070dd4985
FLAGS = -g -Wall

default:lisod

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

lisod: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o lisod log.c log.h process_request.c process_request.h lex.yy.c y.tab.c y.tab.h
