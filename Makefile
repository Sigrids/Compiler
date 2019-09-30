CXX = g++
BASICOPTS = -std=c++11
CXXFLAGS = $(BASICOPTS)

# Define the target directories.
TARGETDIR_exe=.

all: $(TARGETDIR_exe)/comp

## Target: testSem
OBJS =  \
	input.o \
	parser.o \
	scanner.o \
	token.o \
	tokenEnum.o \
	tree.o \
	staticSemantics.o \
	code.o \
	scope.o \
	local.o

# Link or archive
$(TARGETDIR_exe)/comp:  $(OBJS) 
	$(LINK.cc) -o $@ $(OBJS) 

# Compile source files into .o files
input.o: input.cpp
	$(COMPILE.cc) -o $@ input.cpp

parser.o: parser.cpp
	$(COMPILE.cc) -o $@ parser.cpp

scanner.o: scanner.cpp
	$(COMPILE.cc)  -o $@ scanner.cpp

token.o: token.cpp
	$(COMPILE.cc) -o $@ token.cpp

tokenEnum.o: tokenEnum.cpp
	$(COMPILE.cc) -o $@ tokenEnum.cpp

tree.o: tree.cpp
	$(COMPILE.cc)  -o $@ tree.cpp

staticSemantics.o: staticSemantics.cpp
	$(COMPILE.cc) -o $@ staticSemantics.cpp

code.o: code.cpp
	$(COMPILE.cc) -o $@ code.cpp

scope.o: scope.cpp
	$(COMPILE.cc) -o $@ scope.cpp

local.o: local.cpp
	$(COMPILE.cc) -o $@ local.cpp



# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux

