// Author: Giahuy Thai
// CECS 325-02 Prog 1
// Due 09/11/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "deck.h"
using namespace std;

int main() {
    srand(time(0));  // Without this, the random number generator will always produce the same shuffled deck every time. 
                     // This seed is used to ensure that the shuffled deck is random every time.
    
    // Initialize the deck. 52 cards.
    Deck mydeck;

    // Initialize the players.
    string p1, p2;
    
    cout << "Enter the name of the first player: ";
    getline(cin, p1);
    cout << "Enter the name of the second player: ";
    getline(cin, p2);
    
    cout << "\n Original Deck" << endl;
    mydeck.display();
    
    mydeck.shuffle();
    cout << "\n Shuffled Deck" << endl;
    mydeck.display();
    
    // Game statistics
    int p1Wins = 0, p2Wins = 0, ties = 0;
    
    // Play 26 games
    for (int i = 0; i < 26; i++) {
        cout << "\nGame " << (i + 1) << endl;
        cout << "--------" << endl;
        
        Card p1Card = mydeck.deal();
        Card p2Card = mydeck.deal();
        
        cout << "        " << p1 << "=>";
        p1Card.display();
        cout << endl;
        
        cout << "        " << p2 << "=>";
        p2Card.display();
        cout << endl;
        
        // Compare play 1's card with play 2's card. Return 1 if player1 wins, 0 if it's a tie, and -1 if player2 wins.
        int result = p1Card.compare(p2Card);
        
        if (result == 1) {
            cout << p1 << "=> Winner" << endl;
            p1Wins++;
        } else if (result == -1) {
            cout << p2 << "=> Winner" << endl;
            p2Wins++;
        } else {
            cout << "Tie game" << endl;
            ties++;
        }
              
        cin.get();
    }
    
    // Display final statistics
    cout << "\n------Final Stats-------" << endl;
    cout << "       " << p1 << " vs. " << p2 << endl;
    cout << "Wins   " << p1Wins << "          " << p2Wins << endl;
    cout << "Losses " << p2Wins << "          " << p1Wins << endl;
    cout << "Ties   " << ties << "           " << ties << endl;
    
    return 0;
}