CXX = g++
CXXFLAGS = -Wall \
	-std=c++14
INCPATH = -I include/ \
	-I include/lda/

OBJS = $(addprefix build/, vocab.o document.o model.o utils.o sampler.o trainer.o)

main: src/main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o main.exe $^

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c -o $@ $^