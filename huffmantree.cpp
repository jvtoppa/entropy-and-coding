#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>

#define BYTE_SIZE 256

using namespace std;
typedef unsigned u_int;

typedef struct bucketed
{
    char label;
    int frequency;
}bucketed;

typedef struct node
{
    node* next;
    node* left;
    node* right;
    bucketed field;

}node;

typedef struct ll
{
    node* head;
    u_int size;

}ll;

typedef struct inputVectorProcessed
{
    bucketed* vector;
    u_int size;

}IVP;


node* createNode(bucketed fld)
{
    node* newNode = new node;
    newNode->right = nullptr;
    newNode->next = nullptr;
    newNode->left = nullptr;
    newNode->field.frequency = fld.frequency;
    newNode->field.label = fld.label;

    return newNode;
}


node* addNode(bucketed fld) {
    
    node* N = createNode(fld);
    if (!N) return nullptr;

    return N;
}

ll* createLL()
{
    bucketed headValues;
    headValues.frequency = 0;
    headValues.label = 0;
    node* head = createNode(headValues);
    ll* linkedList = new ll;
    linkedList->head = head;
    linkedList->size = 0;

    return linkedList;
}

void freeLL(ll* list)
{
    if (list == nullptr) return;

    node* current = list->head;
    while (current != nullptr)
    {
        node* next = current->next;
        delete current;
        current = next;
    }

    delete list;
}

ll* buildList(IVP* inputAfterProcessing)
{
    ll* linkedList = createLL();
    linkedList->size = inputAfterProcessing->size;
    node* head = linkedList->head;
    for (int i = 0; i < linkedList->size; i++)
    {
        node* newNode = createNode(inputAfterProcessing->vector[i]);
        head->next = newNode;
        head = newNode;
    }

    return linkedList;
}

int compare(const void *a, const void *b)
{
    int first = ((struct bucketed *)a)->frequency;
    int second = ((struct bucketed *)b)->frequency;
    return (first - second);
}

IVP* inputPreProcess(string input, bucketed* processedInput)
{
    int inputSize = input.size();
    int allASCII[BYTE_SIZE] = {0};


    for(int bucketIterator = 0; bucketIterator < inputSize; bucketIterator++)
    {
        allASCII[input[bucketIterator]]++;
    }

    unsigned counter = 0;
    for(int i = 0; i < inputSize; i++)
    {
        if(allASCII[input[i]] > 0)
        {
            processedInput[counter].label = input[i];
            processedInput[counter].frequency = allASCII[input[i]];
            allASCII[input[i]] = 0;
            counter++;
        }
    }
    

//    cout << "Array Counter: \n";
    
    qsort(processedInput, counter, sizeof(bucketed), compare);
  
  /*
  for (int i = 0; i < counter; i++)
  {
    cout << processedInput[i].label << ": " << processedInput[i].frequency << "\n";
}

*/
    IVP* inputVectorProcessed = new IVP;
    inputVectorProcessed->vector = processedInput;
    inputVectorProcessed->size = counter;


    return inputVectorProcessed;
}

node* huffmanTree(ll* list)
{
    bucketed emptyNode;
    emptyNode.frequency = 0;
    emptyNode.label = 0;

    while (list->head->next && list->head->next->next)
    {
        node* first = list->head->next;
        node* second = first->next;
        node* listN = createNode(emptyNode);
        listN->left = first;
        listN->right = second;
        listN->field.frequency = first->field.frequency + second->field.frequency;

        list->head->next = second->next;

        node* prev = list->head;
        node* curr = list->head->next;

        while (curr && curr->field.frequency <= listN->field.frequency)
        {
            prev = curr;
            curr = curr->next;
        }

        listN->next = curr;
        prev->next = listN;

    }
    return list->head->next;
}

void freeTree(node* root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void mapping(node* root, string prefix, string* ASCIImap)
{
    if (!root) return;

    if (root->field.label != 0)
    {
        ASCIImap[root->field.label] = prefix;
    }
    mapping(root->left, prefix + "0", ASCIImap);
    mapping(root->right, prefix + "1", ASCIImap);

}

void writeToDisk(string bitString)
{

u_int32_t bits = bitString.size();

ofstream out("encoding.bin", ios::binary);
unsigned char buffer = 0;
int bitCount = 0;
out.write(reinterpret_cast<const char*>(&bits), sizeof(bits));
for (char bit : bitString) 
{
    buffer <<= 1;
    if (bit == '1') buffer |= 1;
    bitCount++;

    if (bitCount == 8) {
        out.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}

if (bitCount > 0)
{
    buffer <<= (8 - bitCount);
    out.put(buffer);
}

out.close();
}



int encodeHuffman(string input, node* tree)
{

    string ASCIImap[BYTE_SIZE] = {};
    cout << "[Console] Mapping the ASCII encoding from the Huffman tree.\n";
    mapping(tree, "", ASCIImap);
    cout << "[Console] Encoding the string.\n";
    
    string endString;
    endString.reserve(input.size() * 8);
    
    for (int i = 0; i < input.size(); i++) {

        endString += ASCIImap[(unsigned char)input[i]];


    }
    cout << "[Console] Encoding complete.\n";
    cout << "[Console] Writing to disk.\n";
    writeToDisk(endString);

    return 1;
}



int main(void)
{
string input;
auto start = chrono::high_resolution_clock::now();
cout << "Input:";

cout << "\n";
cin >> input;

cout << "[Console] Initializing...\n";

int inputSize = input.size();
bucketed processedInput[inputSize];
for(int i = 0; i < inputSize; i++)
{
    processedInput[i].label = 0;
    processedInput[i].frequency = 0;
    
}
cout << "[Console] Preprocessing the input.\n";
IVP* procInput = inputPreProcess(input, processedInput);
cout << "[Console] Building the list.\n";
ll* list = buildList(procInput);

node* tree = huffmanTree(list);

if(encodeHuffman(input, tree))
{
    cout << "[Console] Succesfully generated Huffman coding of the input string.\n";
}
else
{
    cout << "[Console] Failed to generate Huffman coding of the input string.";
}
auto end = chrono::high_resolution_clock::now();
cout << "\n[Time elapsed: "
     << chrono::duration_cast<chrono::milliseconds>(end - start).count()
     << " ms]\n\n";

freeTree(tree);
delete list->head;
delete list;
delete procInput;

}