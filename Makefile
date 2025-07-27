CXX = g++
CXXFLAGS = -std=c++11 -O3 -DNDEBUG -I$(HOME)/include
LDFLAGS = -L$(HOME)/lib -lsdsl -ldivsufsort -ldivsufsort64

ALL_TARGETS = huffman rle dehuff derle

all: $(ALL_TARGETS)

huffman: huffmantree.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

dehuff: dehuff.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

rle: RLE.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

derle: deRLE.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm -f $(ALL_TARGETS)
