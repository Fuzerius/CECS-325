#include "deck.h"

// Constructor that creates a deck of 52 cards
Deck::Deck() {
    char suits[] = {'C', 'S', 'D', 'H'};
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K'};
    // 1 for 10
    
    int cardIndex = 0;
    
    // Create all 52 cards
    // Outer loop for the suits.
    for (int suit = 0; suit < 4; suit++) {
        // Inner loop for the ranks.
        for (int rank = 0; rank < 13; rank++) {
            // Create a card and add it to the deck.
            cards[cardIndex] = Card(ranks[rank], suits[suit]);
            cardIndex++;
        }
    }
    
    currentCard = 0;  // A counter to keep track of the current card being dealt. 
                      // Initialize the current card to 0 to start dealing from the first card.
}

// Deal a card from the deck
Card Deck::deal() {
    // Start at index 0 and increment the current card index by 1 until the deck is empty.
    if (currentCard < 52) {
        return cards[currentCard++];
    } else {
        // Return a default card if deck is empty (shouldn't happen in this game)
        return Card();
    }
}

// Display all cards in the deck
void Deck::display() {
    for (int i = 0; i < 52; i++) {
        cards[i].display();
        if (i < 51) cout << ",";  // Add comma between cards
        if ((i + 1) % 13 == 0) cout << endl;  // New line after each suit
    }
}

// Shuffle function. A loop that swaps each card with a random card in the deck.
void Deck::shuffle() {
    for (int i = 0; i < 52; i++) {
        int randomIndex = rand() % 52; // Generate a random index between 0 and 51 for the swap.
        
        // Swap cards[i] with cards[randomIndex]
        Card temp = cards[i];
        cards[i] = cards[randomIndex];
        cards[randomIndex] = temp;
    }
}
