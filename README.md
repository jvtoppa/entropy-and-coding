Entropy-Huffman + RLE Compression Tool
==============================
This project is based on Gonzalo Navarro's amazing "Compact Data Structures: A Practical Approach. 

We aim to implement simple Huffman Coding and Run-Length Encoding (RLE)
algorithms for data compression and decompression by providing command-line
tools for encoding, decoding, and combining both algorithms into a compression pipeline.



Note: Requires g++ and the [sdsl-lite](https://github.com/simongog/sdsl-lite).

Build
-----

```bash
git clone https://github.com/jvtoppa/huffman-rle-compressor.git
cd huffman-rle-compressor
make
```

Usage
-----

Run all commands using the Python CLI interface:

Huffman Compression:

    python3 cli.py huffman --input path/to/file.txt --output path/to/file (NOTE: DO NOT ADD THE EXTENSION OF THE FILE!)

RLE Compression:

    python3 cli.py rle --input path/to/file.txt --output path/to/file

Pipeline Compression (RLE -> Huffman):

    python3 cli.py pipeline --input path/to/file.txt --output path/to/file

Huffman Decompression:

    python3 cli.py dehuffman --tree path/to/tree_data.bin --encoded path/to/encoding.bin --output output.txt

If --output is not provided, the default output file is `decompressed.txt`.


License
-------

Copyright 2025 João Vitor H. Toppa

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


