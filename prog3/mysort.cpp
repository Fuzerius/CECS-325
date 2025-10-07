// Author: Giahuy Thai
// CECS 325-02 Prog 3
// Due 10/09/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Bubble sort, very slow
vector<int> bubble(vector<int> v)
{
    for (int pass = 0; pass < v.size() - 1; pass++) {
        for (int i = 0; i < v.size() - 1 - pass; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
            }
        }
    }
    return v;
}


int main(int argc, char* argv[]) {
    //Check if the arguments are correct
    if (argc != 3) {
        cout << "Incorrect arguments. Expected: " << argv[0] << " <inputFile> <outputFile>" << endl;
        return 1;
    }

    //Open the input and output files
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    vector<int> numbers;
    int number;

    //Read the numbers from the input file. Put them in a vector named numbers
    while (inputFile >> number) {
        numbers.push_back(number);
    }

    //bubble sort the vector
    numbers = bubble(numbers);   
    
    //Write the sorted numbers to the output file
    for (int num : numbers) {
        outputFile << num << endl;
    }

    return 0;
}
