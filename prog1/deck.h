#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <iostream>
#include <string>
using namespace std;

class Deck {
    private:
        Card cards[52];
        int currentCard;  // Index for dealing cards
        
    public:
        Deck();           // constructor which creates a deck of 52 cards
        Card deal();      // deal a card
        void display();   // show all the cards in the deck
        void shuffle();   // shuffle the cards in the deck
};

#endif
