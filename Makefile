NAME		= LaRoue
OUTPUT		?= $(NAME)

CC		?= gcc

CXX		?= g++

INCLUDES	+= -I ./includes
###################
### Engine.CORE
CORE		= src/engine/core/object.cpp

### Engines
Engines		= $(CORE)

### Serial -> Json Serialisation
Serial		= src/serialization/serializable.cpp \
		src/serialization/serial.cpp

### FileSystem -> Oop FieSystem
FileSystem	= src/filesystem/file.cpp \
		src/filesystem/directory.cpp
###################
CXXSRC		+= $(Serial) $(FileSystem) $(Engines)
CSRC		+=

FLAGS		=  $(INCLUDES)  -I renderer/libraries/GdlLibrary/includes/
CFLAGS		+= $(FLAGS) -Wall
CXXFLAGS	+= $(FLAGS) -std=c++11
LDFLAGS		+= -lpthread
-include	renderer/.ld_path

CXXOBJ		= $(CXXSRC:.cpp=.o)
COBJ		= $(CSRC:.c=.o)
OBJ		= $(CXXOBJ) $(COBJ)

CXXDEPENDENCIES	= $(CXXSRC:.cpp=.d)
CDEPENDENCIES	= $(CSRC:.c=.d)
DEPENDENCIES	= $(CDEPENDENCIES) $(CXXDEPENDENCIES)

ifneq ($(CXXOBJ),)
LINKER	?= $(CXX)
else
LINKER	?= $(CC)
endif

all: $(OUTPUT)

$(OUTPUT): $(OBJ) $(STATIC_LIBRARY)
ifeq ($(OUTPUT),$(NAME))
	$(LINKER) -o $(OUTPUT) $(OBJ) $(STATIC_LIBRARY) $(LDFLAGS)
else
	@echo "Alternate output:" $(OUTPUT) "build"
	@$(LINKER) -o $(OUTPUT) $(OBJ) $(LDFLAGS)
endif

clean:  clean_dependencies
	$(RM) $(OBJ) $(STATIC_LIBRARY)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPENDENCIES)

clean_dependencies:
	rm -f $(DEPENDENCIES)
	rm -f .build_log

renderer/renderer.a:
	OUTPUT='renderer.a' INCLUDES="-I `pwd`/includes/" make -C renderer

%.d: %.cpp
	@$(CXX) -MM	$*.cpp	 $(CXXFLAGS) 1>> .build_log
	@echo 1>> .build_log
	@echo -n `dirname $*` > $*.d
	@echo -n "/" >> $*.d
	@echo "Building Dependencies file for" $*.cpp
	@$(CXX) -MM	$*.cpp	 $(CXXFLAGS) >>	$*.d

%.d: %.c
	@echo -n `dirname $*` > $*.d
	@echo -n "/" >> $*.d
	@echo "Building Dependencies file for" $*.c
	@$(CC) -MM	$*.c	 $(CFLAGS) >>	$*.d

%.o: %.cpp
	$(CXX) -c	$*.cpp	 $(CXXFLAGS) -o $*.o

%.o: %.c
	$(CC) -c	$*.c	 $(CFLAGS) -o $*.o


.PHONY: all clean fclean re clean_dependencies
