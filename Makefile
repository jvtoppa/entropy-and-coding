CXX = g++
CXXFLAGS = -std=c++11 -O3 -DNDEBUG -I$(HOME)/include
LDFLAGS = -L$(HOME)/lib -lsdsl -ldivsufsort -ldivsufsort64

ALL_TARGETS = huffman rle dehuff

all: $(ALL_TARGETS)

huffman: huffmantree.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

dehuff: dehuff.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

rle: rle.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
clean:
	rm -f $(ALL_TARGETS)

