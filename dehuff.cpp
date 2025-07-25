#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sdsl/bit_vectors.hpp>


using namespace std;

typedef struct node
{
    node* left;
    node* right;
    char label;

}node;

node* createNode(char label)
{
    node* newNode = new node;
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->label = label;

    return newNode;
}

//Thanks leetcode ;) 
node* deserializeTree(const sdsl::bit_vector& treeBits, const vector<uint8_t>& leafSymbols, size_t& bitPos, size_t& symbolPos)
{
if (bitPos >= treeBits.size()) {
    return nullptr;
}

if (treeBits[bitPos++] == 1) {

    char label = leafSymbols[symbolPos++];
    return createNode(label);
}

char emptyLabel = 0;
node* root = createNode(emptyLabel);
root->left = deserializeTree(treeBits, leafSymbols, bitPos, symbolPos);
root->right = deserializeTree(treeBits, leafSymbols, bitPos, symbolPos);

return root;

}

//This one is not mine...
sdsl::bit_vector decodeBitfile(string path)
{
    ifstream enc(path, ios::binary);
    uint32_t bitCount = 0;
    enc.read(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));

    vector<char> buffer((istreambuf_iterator<char>(enc)), {});
    sdsl::bit_vector bitString(bitCount);

    size_t bitIndex = 0;
    for (size_t i = 0; i < buffer.size(); ++i) {
        unsigned char byte = static_cast<unsigned char>(buffer[i]);
        for (int b = 7; b >= 0; --b) {
            if (bitIndex >= bitCount) break;
            bitString[bitIndex++] = (byte >> b) & 1;
        }
    }
    return bitString;
}

//For debug purposes. Simply a preorder traversal.
void printTree(node* root, string prefix = "")
{
    if (!root) return;

    if (root->label != 0)
    {
        cout << root->label << ": "<<  prefix << "\n";
    }
    printTree(root->left, prefix + "0");
    printTree(root->right, prefix + "1");

}

int writeToDiskText(const string& text, const string& outPath) {
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "[Error] Not possible to open file for writing.\n";
        return 0;
    }

    out.write(text.c_str(), text.size());
    out.close();

    return 1;
}


char searchSymbolInTree(const sdsl::bit_vector& bits, node* root, size_t* i)
{
    while(root->left || root->right)
    {
        root = bits[(*i)++] ? root->right : root->left;
    }
    return root->label;
}

string decodeHuffman(const sdsl::bit_vector& bits, node* root)
{
    string finalString;
    for(size_t i = 0; i < bits.size();)
    {
        char symbol = searchSymbolInTree(bits, root, &i);
        finalString.push_back(symbol);
    }
    return finalString;
}

int main(int argc, char* argv[])
{
if (argc < 3) {
    cerr << "Usage: ./dehuff <tree_data_file> <encoded_file> [output_file]\n";
    return 1;
}

string treeFile = argv[1];
string encodedFile = argv[2];
string outputFile = (argc >= 4) ? argv[3] : "decompressed.txt";

auto start = chrono::high_resolution_clock::now();
std::ifstream in(treeFile, std::ios::binary);
sdsl::bit_vector treeBits;

cout << "[Console] Loading tree data..." << "\n";

sdsl::load(treeBits, in);

uint32_t leafCount;
in.read(reinterpret_cast<char*>(&leafCount), sizeof(leafCount));

std::vector<uint8_t> leafSymbols(leafCount);
in.read(reinterpret_cast<char*>(leafSymbols.data()), leafCount);

size_t bitPos = 0;
size_t symbolPos = 0;
node* tree = deserializeTree(treeBits, leafSymbols, bitPos, symbolPos);

cout << "[Console] Deserializing tree..." << "\n";
//cout << "[DEBUG] PrintTree:" << "\n";

//printTree(tree);
cout << "[Console] Decoding bitfile..." << "\n";
sdsl::bit_vector bitString = decodeBitfile(encodedFile);
cout << "[Console] Successfully decoded bitfile." << "\n";
cout << "[Console] Dehuffmaning..." << "\n";
string decoded = decodeHuffman(bitString, tree);
//cout << decoded << "\n";
cout << "[Console] Successfully decompressed the file." << "\n";
cout << "[Console] Writing to disk..." << "\n";
if(!writeToDiskText(decoded, outputFile))
{
    cout << "[Console] Successfully written to disk." << "\n";
    return 1;
}
cout << "[Console] Done." << "\n";

auto end = chrono::high_resolution_clock::now();
cout << "\n[Huffman: Time elapsed: "
     << chrono::duration_cast<chrono::milliseconds>(end - start).count()
     << " ms]\n\n";
//decodeHuffman(stream, tree)

}