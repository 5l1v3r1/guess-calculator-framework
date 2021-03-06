# Makefile for guess calculator framework tools
# 
# Use of this source code is governed by the GPLv2 license that can be found
#   in the LICENSE file.
#
# Version 0.1
# Author: Saranga Komanduri
#
CC = g++
CFLAGS =-O3 -Wall -g -std=c++11
# Enable the following options (and add \ to the above line) for more warnings
# -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
# -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
# -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
# -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef

CLASSFILES=bit_array.* gcfmacros.* grammar_tools.* lookup_data.* lookup_tools.* mixed_radix_number.* \
           nonterminal_collection.* \
           nonterminal.* pcfg.* pattern_manager.* seen_terminal_group.* structure.* \
           terminal_group.* unseen_terminal_group.*

CLASS_CPP_FILES = grammar_tools.cpp lookup_tools.cpp mixed_radix_number.cpp \
           nonterminal_collection.cpp nonterminal.cpp pcfg.cpp pattern_manager.cpp seen_terminal_group.cpp \
           structure.cpp unseen_terminal_group.cpp big_count.cpp
CLASS_OBJ_FILES = $(CLASS_CPP_FILES:.cpp=.o)

default: main

main: GeneratePatterns sortedcountaggregator LookupGuessNumbers GenerateStrings

# Binaries must be compiled with the GMP library
GeneratePatterns: GeneratePatterns.o
	$(CC) $(CFLAGS) $(CLASS_OBJ_FILES) GeneratePatterns.o -o GeneratePatterns -lgmpxx -lgmp

GeneratePatterns.o: GeneratePatterns.cpp .classes
	$(CC) $(CFLAGS) -c GeneratePatterns.cpp

GenerateStrings: GenerateStrings.o
	$(CC) $(CFLAGS) $(CLASS_OBJ_FILES) GenerateStrings.o -o GenerateStrings -lgmpxx -lgmp

GenerateStrings.o: GenerateStrings.cpp .classes
	$(CC) $(CFLAGS) -c GenerateStrings.cpp

LookupGuessNumbers: LookupGuessNumbers.o
	$(CC) $(CFLAGS) $(CLASS_OBJ_FILES) LookupGuessNumbers.o -o LookupGuessNumbers -lgmpxx -lgmp

LookupGuessNumbers.o: LookupGuessNumbers.cpp .classes
	$(CC) $(CFLAGS) -c LookupGuessNumbers.cpp


.classes: $(CLASSFILES)
	$(CC) $(CFLAGS) -c $(CLASS_CPP_FILES)
	touch .classes

sortedcountaggregator: sortedcountaggregator.o
	$(CC) $(CFLAGS) sortedcountaggregator.o -o sortedcountaggregator -lgmpxx -lgmp

sortedcountaggregator.o: sortedcountaggregator.cpp
	$(CC) $(CFLAGS) -c sortedcountaggregator.cpp

clean:
	rm -f GeneratePatterns
	rm -f sortedcountaggregator
	rm -f LookupGuessNumbers
	rm -f GenerateStrings
	rm -f .classes
	rm -f *.o
