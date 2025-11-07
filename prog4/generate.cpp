// Author: Giahuy Thai
// CECS 325-02 Prog 4
// Due 11/04/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <fstream>

using namespace std;

//Generate random numbers between low and high
void generate_random_numbers(int n, int low, int high, ofstream& outputFile) {
    if (n == 0) {
        return;
    }


    for (int i = 0; i < n; i++) {
    int random_number = low + (rand() % (high - low + 1));
    outputFile << random_number << endl;

    }
}

int main(int argc, char* argv[]) {

    //Check if the arguments are correct
    if (argc != 4) {
        cout << "Incorrect arguments. Expected: " << argv[0] << " <n> <low> <high>" << endl;
        return 1;
    }

    //Random seed
    srand(time(0));
    
    //Open the output file
    ofstream outputFile("numbers.dat");
    if (!outputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    
    //Generate random numbers. atoi is used to convert the string to an integer
   generate_random_numbers(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), outputFile);
   outputFile.close();
   
    return 0;
}
