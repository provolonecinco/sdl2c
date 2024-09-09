.PHONY: all clean dir run

OUTPUT 	:= build
EXE	:= $(OUTPUT)/sdl2c	
FLAGS	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SRCDIR 	:= src
OBJDIR 	:= $(OUTPUT)/obj

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: dir $(EXE)

clean:
	@rmdir /s /q $(OUTPUT)

dir:
	@mkdir build
	@mkdir build\obj

run:
	@$(EXE)

# Link object files into executable
$(EXE): $(OBJFILES)
	gcc $^ $(FLAGS) -o $@ 

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc -c $< $(FLAGS) -o $@ 