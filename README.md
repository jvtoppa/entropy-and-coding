# entropy-and-coding
Entropy-based coding algorithms. Based on Gonzalo Navarro's "Compact Data Structures - A Practical Approach".

For now, only Huffman coding is implemented. Compile it with the following commands:

git clone https://github.com/jvtoppa/entropy-and-coding.git
cd entropy-and-coding
g++ -std=c++11 -O3 -DNDEBUG -pg -I ~/include -L ~/lib huffmantree.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64

You also need to install Gog et al.'s sdsl-lite<https://github.com/simongog/sdsl-lite>. 


