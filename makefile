#<<compiler
CC = g++
#<<file type
TYPE=cc
#<<out bin
TARGET = DES
#<<out directory
OUTDIR = ./bin

#<< flags 
CFLAGS = -g

#<< head file
INCS = -I ./inc

#<< link
LINK  = 

#<< creat forld
CREAT_FORLD = XXX


CFLAGS += $(INCS)


SRC = ./src
OBJ = $(SRC)/obj

#<< all source file(*.c *.cc)
SOURCE =  $(wildcard $(SRC)/*.$(TYPE))
SOURCE := $(notdir $(SOURCE))

#<< all object file (*.o)
OBJS   =  $(patsubst %.$(TYPE),%.o,$(SOURCE))
OBJS   := $(foreach X,$(OBJS),$(OBJ)/$(X))


.PHONY:all
all:$(CREAT_FORLD) $(TARGET)
$(CREAT_FORLD):
	mkdir -p $(OBJ)
#<< creat *.o file
$(OBJ)/%.o:$(SRC)/%.$(TYPE) 
	$(CC) $(CFLAGS) -c -o  $@ $<

#<< creat bin file
$(TARGET):$(OBJS)
	$(CC) -o $(OUTDIR)/$(TARGET) $(OBJS) $(LINK)


.PHONY:clean
clean:
	rm -rf $(OBJ) $(OUTDIR)/$(TARGET)


