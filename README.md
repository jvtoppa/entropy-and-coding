# Coding/Compression algorithms

Entropy-based coding algorithms. Based on Gonzalo Navarro's *Compact Data Structures - A Practical Approach*.

Currently, only Huffman coding is implemented.
You need to install [sdsl-lite](https://github.com/simongog/sdsl-lite) by Gog et al.
## Build

```bash
git clone https://github.com/jvtoppa/entropy-and-coding.git
cd entropy-and-coding
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib huffmantree.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64


