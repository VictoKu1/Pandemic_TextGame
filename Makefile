#!make -f

CXX=clang++-9 
CXXVERSION=c++2a
CXXFLAGS=-std=$(CXXVERSION) -Werror -Wsign-conversion
TIDY_FLAGS=-extra-arg=-std=$(CXXVERSION) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-*
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Board.cpp Player.cpp OperationsExpert.cpp Dispatcher.cpp Scientist.cpp Researcher.cpp Medic.cpp Virologist.cpp GeneSplicer.cpp FieldDoctor.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))


run: demo1 demo2
	./demo1
	./demo2

demo1: Demo1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo1

demo2: Demo2.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo2

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) $(TIDY_FLAGS) --

valgrind: demo1 demo2 test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo1 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo2 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo1 demo2 test






