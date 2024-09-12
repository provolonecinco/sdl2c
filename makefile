.PHONY: all clean dir run

OUTPUT 	:= build
EXE	:= $(OUTPUT)/sdl2c.exe	
FLAGS	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -I.\src\include -I.\lib

SRCDIR 	:= src
OBJDIR 	:= $(OUTPUT)/obj

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

all: $(EXE)

clean:
	@rmdir /s /q $(OUTPUT)

dir:
	@mkdir build
	@mkdir build\obj

run: $(EXE)
	@$(EXE)

# Link object files into executable
$(EXE): $(OBJFILES)
	@echo Linking: $(EXE)
	@gcc $^ $(FLAGS) -o $@ 

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling: $<
	@gcc -c $< $(FLAGS) -o $@ 
