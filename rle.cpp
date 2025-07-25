#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <chrono>

typedef unsigned uint;
using namespace std;

struct rlePair
{
    uint beginPos;
    u_int32_t sequentialChars;
};


void writeToDiskText(const std::string& text, const string& outPath) {
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "[Error] Not possible to open file for writing.\n";
        return;
    }

    out.write(text.c_str(), text.size());
    out.close();
}

int main(int argc, char* argv[])
{

    if (argc < 2) {
        cerr << "Usage: ./rle <input_file> <output_file>\n";
        return 1;
    }
    string baseName = argv[1];

    string input((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    auto start = chrono::high_resolution_clock::now();
    std::cout << "[Console] Starting.\n";
    int size = input.size();
    input += "$";
    vector<rlePair> run;
    string end;
    end.reserve(size);
    std::cout << "[Console] Building the RLE...\n";
    for(int i = 0; i < size; i++)
    {
        if(input[i] != input[i + 1])
        {
            end.push_back(input[i]);
        }
        else
        {
            end.push_back(input[i]);
            int counter = 0;
            int pairI = end.size() - 1;
            while(input[i] == input[i + 1])
            {
                i++;
                counter++;
            }
            rlePair pair;
            pair.beginPos = pairI;
            pair.sequentialChars = counter + 1;
            run.push_back(pair);
        }
    }

    string finalString;
    unsigned sequentialCharsChecker = 0;
    for(int i = 0; i < end.size(); i++)
    {
        finalString.push_back(end[i]);

        if(sequentialCharsChecker < run.size() && run[sequentialCharsChecker].beginPos == i)
        {
            //finalString.push_back(':');
            finalString += to_string(run[sequentialCharsChecker].sequentialChars);
            //finalString.push_back(':');
            sequentialCharsChecker++;
        }

    }
    std::cout << "[Console] Succesfully built the RLE.\n";
    std::cout << "[Console] Writing to disk...\n";
    writeToDiskText(finalString, baseName);
    std::cout << "[Console] Done.\n";
    auto ending = chrono::high_resolution_clock::now();
cout << "\n[RLE: Time elapsed: "
     << chrono::duration_cast<chrono::milliseconds>(ending - start).count()
     << " ms]\n\n";




}