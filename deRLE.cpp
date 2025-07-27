#include <iostream>
#include <string.h>
#include <fstream>
#include <chrono>

using namespace std;

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



int main(int argc, char* argv[])
{
if (argc < 2) {
    cerr << "Usage: ./deRLE <encoded_file> [output_file]\n";
    return 1;
}

string encodedFile = argv[1];
string outputFile = (argc >= 3) ? argv[2] : "decompressed_rle.txt";
ifstream in(encodedFile, ios::binary);
string input;
input.assign((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
auto start = chrono::high_resolution_clock::now();


//Algorithm
string endString;
int j = 0;
string amount = "0";

for(int i = 0; i < input.size(); i++)
{
    
    while(input[i] > '/' && input[i] < ':')
    {
        amount.push_back(input[i]);
        i++;
    }
    int amountInt = stoi(amount) - 1;
    while(amountInt > 0)
    {
        endString.push_back(input[j]);
        amountInt--;
    }
    j = i;

    amount = "0"; 
    endString.push_back(input[j]);
}
//End of algorithm.
writeToDiskText(endString, outputFile);

auto end = chrono::high_resolution_clock::now();
cout << "\n[deRLE: Time elapsed: "
     << chrono::duration_cast<chrono::milliseconds>(end - start).count()
     << " ms]\n\n";
}