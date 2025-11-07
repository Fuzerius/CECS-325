// Author: Giahuy Thai
// CECS 325-02 Prog 5
// Due 11/18/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

//#define INTEGER short		// “INTEGER” will be replaced with “short” in the program
#define INTEGER int		// “INTEGER” will be replaced with “int” in the program
//#define INTEGER long long		// “INTEGER” will be replaced with “long long” in the program

#include <iostream>
#include <time.h>
#include <iomanip>
#include <map>
#include <cctype> // for isdigit
using namespace std;

INTEGER goldRabbits(INTEGER);
static map<INTEGER, INTEGER> rabbitmap; 

int main(int argc, char *argv[])
{
    for(int j = 1; j < argc; j++)
    {
        int a = atoi(argv[j]);

        // If the argument is -1, print the contents of the map and continue
        if (a == -1){
            cout << "fibo(-1):\t" << endl;  // Print fibo(-1) with empty result
            cout << "Fibo Map contents:" << endl;
            for (const auto& pair : rabbitmap) {
                cout << pair.first << ":" << pair.second << endl;
            }
            cout << "end of Fibo map" << endl;
            cout << endl;  

            continue;
        }

        // If the argument is not a number, print an error message and continue
        bool allDigits = true;
        for (int k = 0; argv[j][k] != '\0'; k++) {
            if (!isdigit(argv[j][k])) {
                allDigits = false;
                break;
            }
        }
        // If the argument is not a number, print an error message
        if (!allDigits) {
            cout << argv[j] << " is not an integer" << endl;
            continue;
        }

        // a is number
        //Calculate the fibonacci number
        int start = time(0);
        try{
            // number of seconds since Jan 1, 1970
            cout << "fibo(" << a << "):\t" << goldRabbits(a) << endl;
        } 
        catch(string s) {
            cout << s << endl;
        }
        catch(INTEGER n){ // Catch the negative error and print the index that caused the negative error                
            cout<< "months cannot be negative"<< endl;
            continue;
        }
        
    }
}

// this is the goldRabbits function
INTEGER goldRabbits(INTEGER n) 
{
	if (n==0 || n==1){
        rabbitmap[n] = 1;
		return 1;
    }
    else if (n<0){
        throw n;
    }
    else if (rabbitmap.find(n) != rabbitmap.end()) // If the index is already in the map, return the value
        return rabbitmap[n];
    else {

        INTEGER a = goldRabbits(n-1);
        INTEGER b = goldRabbits(n-2);
        INTEGER result = a + b;
        if (result < 0) {
            // Overflow detected!
            throw string("overflow error at fib(" + to_string(n) + "):" + to_string(result));
        }
        else{
            rabbitmap[n] = a + b;      // Safe to add
            return rabbitmap[n];
        }
    }
}
