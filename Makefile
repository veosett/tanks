#
# TODO: Move  to /usr/local/lib so this can work on production servers
#
 
CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := 
OBJECTS := 
CFLAGS := -g # -Wall
LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include: 
  @echo " Linking..."
  @echo "  $^ -o  ";  $^ -o  /%.o: /%.
  @mkdir -p 
  @echo "    -c -o  $<";    -c -o  $<

clean:
  @echo " Cleaning..."; 
  @echo "  -r  ";  -r  

# Tests
tester:
    test/tester.cpp   -o bin/tester

# Spikes
ticket:
    spikes/ticket.cpp   -o bin/ticket

.PHONY: clean
