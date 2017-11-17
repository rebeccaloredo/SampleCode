#ifndef CasinoHeader
#define CasinoHeader

#include<iostream>
#include<vector>
using namespace std;

class User {

private:

    string name;
    double bank;

public:
    User(string name, double bank);
    void setBank(double bank);
    double getBank();
    string getName();
};

class Money{

private:
    double stakes; // randomly generated in money
    double betAmount; // needs to be set  BEFORE EACH GAME!!!!
    double bank;
    double random(); // you can call this to reset the stakes

public:
    Money(double bank);
    double getBank();
    double getStakes();
    void setBetAmount(double betAmount); // you have to set the bet amount before every game
    void doubleBet(); // that would just up the bet
    void win();
    bool lose(); // returns true if he has no money left!

};

class Card {

private:
    int rank;
    string suit;

public:
    Card(int cardRank, string cardSuit);
    int getRank();
    string getSuit();

};

class deckOfCards {

public:
    deckOfCards();
    void shuffle();
    Card* getCard();
    void printDeck();

private:
    const static int DECK_SIZE = 52;
    vector <Card*> deck;
    int currentCard;

};

class Blackjack {

private:


    string cardOneUser;
    string cardTwoUser;
    string cardThreeUser;
    string cardFourUser;
    string cardFiveUser;
    string cardSixUser;
    string cardSevenUser;
    string cardEightUser;
    string cardNineUser;
    string cardTenUser;
    string cardElevenUser;
    string cardOneDealer;
    string cardTwoDealer;
    string cardThreeDealer;
    string cardFourDealer;
    string cardFiveDealer;
    string cardSixDealer;
    string cardSevenDealer;
    string cardEightDealer;
    string cardNineDealer;
    string cardTenDealer;
    string cardElevenDealer;
    bool addTen;
    bool doubleAce;
    int cnt;
    Card** computerHand;
    Card** userHand;
    int compHandValue;
    int userHandValue;
    double bet;
    User* user;
    void playGame();
    void dealCardUser();
    void dealCardDealer();
    int cardIntUser [11];
    int cardIntDealer[11];
    deckOfCards *d1;
    Money *money;
    int cardArrayIndexUser;
    int cardArrayIndexDealer;
    void youLose();
    void youWin();
    void youLoseMore();
    void dealerPlay();
    string playOption();
    string cardPrint(int rank);
    int dealernNumCards;
    int dealerTotal;
    bool lostAllMoney;

    void tie();

public:

    Blackjack(User *user);

};

class WarCard {
private:
    string rank;
    string suit;

public:
    WarCard(string WarCardRank, string WarCardSuit);
    string getRank();
    string getSuit();
};

class deckOfWarCards {
public:
    deckOfWarCards();
    void shuffle();
    WarCard* getWarCard();
    void printDeck();

private:
    const static int DECK_SIZE = 52;
    vector <WarCard*> deck;
    int currentWarCard;
};

#endif
