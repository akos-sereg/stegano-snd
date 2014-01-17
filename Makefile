PROGRAM = stegano-snd
SRCDIR = src
COMMAND = make

all: $(PROGRAM)

$(PROGRAM): 
	@cd $(SRCDIR); $(COMMAND)
	@cd $(SRCDIR); cp $(PROGRAM) ../stegano-snd

clean:
	@cd $(SRCDIR); rm *.o
	@cd $(SRCDIR); rm $(PROGRAM)
	@rm $(PROGRAM)
	@echo "Cleaned."

