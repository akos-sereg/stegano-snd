PROGRAM = stegano-snd
OBJS = 	$(PROGRAM).o misc.o snd.o key.o io.o
LIBS = -lsndfile -lm
CC = gcc

all: $(PROGRAM)
$(PROGRAM): $(OBJS) $(LIBS)

clean:
	@rm *.o
	@rm $(PROGRAM)
	

