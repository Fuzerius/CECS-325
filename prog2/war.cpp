// Author: Giahuy Thai
// CECS 325-02 Prog 2
// Due 09/24/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Card {
    private:
        char suit;
        char rank;
    
    public:
        Card(char r, char s);  // constructor with rank and suit
        void display();  // display the card
        int compare(Card c);  // compare cards: 1=win, 0=tie, -1=lose
};

Card::Card(char r, char s) {
    rank = r;
    suit = s;
}

// Display the card (e.g., AC, 10S, KD)
void Card::display() {
    if (rank == '1') {
        cout << "10" << suit;  // In my program, 10 is represented as '1' (first char of "10")
    } else {
        cout << rank << suit;
    }
}

// Compare this card with another card
// Returns: 1 if this card wins, 0 for tie, -1 if this card loses
int Card::compare(Card c) {
    // Get value for this card
    int yourValue;
    switch(rank) {
        case 'A': yourValue = 1; break;   // Ace is low in this game
        case '2': yourValue = 2; break;
        case '3': yourValue = 3; break;
        case '4': yourValue = 4; break;
        case '5': yourValue = 5; break;
        case '6': yourValue = 6; break;
        case '7': yourValue = 7; break;
        case '8': yourValue = 8; break;
        case '9': yourValue = 9; break;
        case '1': yourValue = 10; break;  // 10 is represented as '1' (first char of "10")
        case 'J': yourValue = 11; break;
        case 'Q': yourValue = 12; break;
        case 'K': yourValue = 13; break;
        default: yourValue = 0; break;
    }
    
    // Get value for other card
    int otherValue;
    switch(c.rank) {
        case 'A': otherValue = 1; break;   // Ace is low in this game
        case '2': otherValue = 2; break;
        case '3': otherValue = 3; break;
        case '4': otherValue = 4; break;
        case '5': otherValue = 5; break;
        case '6': otherValue = 6; break;
        case '7': otherValue = 7; break;
        case '8': otherValue = 8; break;
        case '9': otherValue = 9; break;
        case '1': otherValue = 10; break;  // 10 is represented as '1' (first char of "10")
        case 'J': otherValue = 11; break;
        case 'Q': otherValue = 12; break;
        case 'K': otherValue = 13; break;
        default: otherValue = 0; break;
    }
    
    // First compare by rank
    if (yourValue > otherValue) return 1;
    else if (yourValue < otherValue) return -1;

    // Ranks are equal, compare by suit: C < S < D < H
    else {
        int yourSuitValue;
        switch(suit) {
            case 'C': yourSuitValue = 1; break;  // Clubs lowest
            case 'S': yourSuitValue = 2; break;  // Spades
            case 'D': yourSuitValue = 3; break;  // Diamonds  
            case 'H': yourSuitValue = 4; break;  // Hearts highest
            default: yourSuitValue = 0; break;
        }
        
        int otherSuitValue;
        switch(c.suit) {
            case 'C': otherSuitValue = 1; break;  // Clubs lowest
            case 'S': otherSuitValue = 2; break;  // Spades
            case 'D': otherSuitValue = 3; break;  // Diamonds
            case 'H': otherSuitValue = 4; break;  // Hearts highest
            default: otherSuitValue = 0; break;
        }
        
        if (yourSuitValue > otherSuitValue) return 1;
        else if (yourSuitValue < otherSuitValue) return -1;
        else return 0;
    }
}

class Deck {
    private:
        vector<Card> cards;
        int currentCard;  // Index for dealing cards
        
    public:
        Deck();           // constructor which creates a deck of 52 cards
        Card deal();      // deal a card
        void display();   // show all the cards in the deck
        void shuffle();   // shuffle the cards in the deck
        bool isEmpty();   // check if the deck is empty
};

bool Deck::isEmpty() {
    // Check if the current card index is greater than or equal to cards.size(). If all cards have been dealt. return true, false otherwise.
    return currentCard >= cards.size();
}

Deck::Deck() {
    vector<char> suits = {'C', 'S', 'D', 'H'};
    vector<char> ranks = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K'};
    // 1 for 10
    
    // Create all 52 cards
    // Outer loop for the suits.
    for (int suit = 0; suit < 4; suit++) {
        // Inner loop for the ranks.
        for (int rank = 0; rank < 13; rank++) {
            // Create a card and add it to the deck.
            cards.push_back(Card(ranks[rank], suits[suit]));
        }
    }
    
    currentCard = 0;  // A counter to keep track of the current card being dealt. 
                      // Initialize the current card to 0 to start dealing from the first card.
}

// Deal a card from the deck
Card Deck::deal() {
    // Check if the deck is empty. If it is, throw an error.
    if (currentCard >= cards.size()) {
        throw "Error- Deck is empty!";
    }
    return cards[currentCard++];
}

// Display all cards in the deck
void Deck::display() {
    for (int i = 0; i < cards.size(); i++) {
        cards[i].display();
        if (i < cards.size() - 1) cout << ",";  // Add comma between cards
        if ((i + 1) % 13 == 0) cout << endl;  // New line after each suit
    }
}

// Shuffle function. A loop that swaps each card with a random card in the deck.
void Deck::shuffle() {
    for (int i = 0; i < cards.size(); i++) {
        int randomIndex = rand() % cards.size(); // Generate a random index for the swap.
        
        // Swap cards[i] with cards[randomIndex]
        Card temp = cards[i];
        cards[i] = cards[randomIndex];
        cards[randomIndex] = temp;
    }
}

struct Player {
    string name;
    int wins = 0;
    int losses = 0;
    int ties = 0;
};


int main() {
    srand(time(0));  // Without this, the random number generator will always produce the same shuffled deck every time. 
                     // This seed is used to ensure that the shuffled deck is random every time.
    
    // Initialize the deck. 52 cards.
    Deck mydeck;

    // Initialize the players.
    Player p1, p2;
    int numGames;

    cout << "Enter the name of the first player: ";
    getline(cin, p1.name);
    cout << "Enter the name of the second player: ";
    getline(cin, p2.name);
    cout << "How many games will they play?: ";
    cin >> numGames;
    cin.ignore();

    cout << "\n Original Deck" << endl;
    mydeck.display();
    
    mydeck.shuffle();

    cout << "\n Shuffled Deck" << endl;
    mydeck.display();

    for (int i = 0; i < numGames; i++) {
        cout << "\nGame " << (i + 1) << endl;
        cout << "--------" << endl;
        
        try {
            Card p1Card = mydeck.deal();
            Card p2Card = mydeck.deal();
            
            cout << "        " << p1.name << "=>";
            p1Card.display();
            cout << endl;
            
            cout << "        " << p2.name << "=>";
            p2Card.display();
            cout << endl;
            
            // Compare play 1's card with play 2's card. Return 1 if player1 wins, 0 if it's a tie, and -1 if player2 wins.
            int result = p1Card.compare(p2Card);
            
            if (result == 1) {
                cout << p1.name << "=> Winner" << endl;
                p1.wins++;
                p2.losses++;
            } else if (result == -1) {
                cout << p2.name << "=> Winner" << endl;
                p2.wins++;
                p1.losses++;
            } else {
                cout << "Tie game" << endl;
                p1.ties++;
                p2.ties++;
            }
        } catch (const char* e) {
            cout << e << endl;
            break;  // Exit the game loop when deck is empty
        }
    }
    cout << "\n------Final Stats-------" << endl;
    cout << "       " << p1.name << " vs. " << p2.name << endl;
    cout << "Wins   " << p1.wins << "          " << p2.wins << endl;
    cout << "Losses " << p1.losses << "          " << p2.losses << endl;
    cout << "Ties   " << p1.ties << "           " << p2.ties << endl;
    
    return 0;

}

