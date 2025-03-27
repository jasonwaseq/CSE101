// Jason Waseq
// jwaseq
// pa5
// Shuffle.cpp

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

void shuffle(List& D) {
    List tempDeck;
    int halfDeck = D.length() / 2;
    D.moveFront();
    for (int i = 0; i < halfDeck; i++) {
        int card = D.moveNext();
        tempDeck.insertBefore(card);
        D.eraseBefore();
    }
    tempDeck.moveFront();
    while (D.position() < D.length()) {
        D.moveNext();
        if (tempDeck.position() < tempDeck.length()) {
            D.insertAfter(tempDeck.moveNext());
            D.moveNext();
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return EXIT_FAILURE;
    }
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    int deckSize = stoi(argv[1]);
    List initialDeck;
    for (int i = 1; i <= deckSize; i++) {
        initialDeck.insertBefore(i - 1);
        List currentDeck(initialDeck);
        int shuffleCount = 0;
        do { shuffle(currentDeck), shuffleCount++;}
        while (!currentDeck.equals(initialDeck));
	  cout << i << "\t\t\t" << shuffleCount << endl;
    }
    return EXIT_SUCCESS;
}

