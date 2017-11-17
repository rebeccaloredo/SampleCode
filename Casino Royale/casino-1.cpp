//CRITICAL PROBLEM: WE NEED TO SET USER'S BANK VALUE TO THE NEW MONEY OBJECT VALUE AFTER EACH BET.
//IF YOU SEE THIS, THEN THE ISSUE IS NOT FIXED.
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

//USER DEFINITION(S) GO HERE============================================================================================================================

  /*
   The user class is a class that creates an object that is an
  instance of a user. This user object is used throughout the program in one instance.
   The user is defined by a string name and a double amount of money. 
   These values are accessed through various accessor methods called from their respective locations
   */

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

User::User(string name, double bank){
    this->name = name;
    this->bank = bank;
}

void User::setBank(double bank){
    this->bank = bank;
}

double User::getBank(){
    return this->bank;
}

string User::getName(){
    return this->name;
}

//MONEY DEFINITION(S) GO HERE==========================================================================================================

/*The money class is the class that handles all the money values of the game
   the money object is defined by a double stakes. Stakes is randomly generated
   each time to decide what the stakes are for the night at the casino.
   The bank stores in the user's monetary value. There are different methods to access
    the bet value and also the stakes for the night and bank.
    There are separate functions for wins case and loss case.
 (*/

class Money{
    
private:
    double stakes;
    double betAmount;
    double bank;
    double random();
    
public:
    Money(double bank);
    double getBank();
    double getStakes();
    void setBetAmount(double betAmount);
    void doubleBet();
    void win();
    bool lose();
    
};

Money::Money(double bank){
    double stakes = random();
    this->stakes = stakes;
    this->bank = bank;
}

double Money::getStakes(){
    return this->stakes;
}
double Money::getBank(){
    return this->bank;
}

void Money::doubleBet(){
    this->betAmount = this->betAmount * 2;
}

void Money::setBetAmount(double betAmount){
    this->betAmount = betAmount;
}

bool Money::lose(){
    double lose = this->betAmount * this->stakes;
    this->bank = this->bank - lose;
    if (this->bank <= 0){
        cout << "This game's losses $" << lose << endl;
        cout << "You have no money left, Bank: $0" << endl;
        return true;
    }
    else {
        cout << "This game's losses $" << lose << endl;
        cout << "You now have $" << this->bank << endl;
        return false;
    }
    
    
    
}

void Money::win(){
    double win = this->betAmount * this->stakes;
    this->bank = this->bank + win;
    cout << "This game's winnings $" << win << endl;
    cout << "You now have $" << this->bank << endl;
}

double Money:: random(){
    srand(time(0));
    int random = (int)rand()%(20 + 1) + 10;
    double dbRandom = (double) random;
    dbRandom = dbRandom / 10;
    return dbRandom;
}

//CARD DEFINITION(S) GO HERE================================================================================================================

/*
  This is a specific card class that is used by black jack.
  Here we handle the creation of each card of the deck. The card 
  object is defined by an integer rank and a string suit.
  The cards are stored into a deck object that is used specifically
  by the black jack class
  */


class Card {
    
private:
    int rank;
    string suit;
    
public:
    Card(int cardRank, string cardSuit);
    int getRank();
    string getSuit();
    
};

Card::Card(int cardRank, string cardSuit){
    this->rank = cardRank;
    this->suit = cardSuit;
}

int Card::getRank(){
    return this->rank;
}

string Card::getSuit(){
    return this->suit;
}

//DECK DEFINITION(S) GO HERE=====================================================================================================================

/*
  This is a specific deck class that is used by black jack. It has methods that accept card objects and push them into 
   a vector of card objects. The deck object is defined by its vector of card objects. The deck object also has a shuffle method
   which shuffles the cards in it, a getCard method that allows you to access each card object. A printDeck method prints out each card of the deck
   using the cards accessor methods.
 */

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

deckOfCards::deckOfCards() {
    int ranks[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    currentCard = 0;
    int divide;
    for(int count = 0; count < DECK_SIZE; count++) {
        divide = count / 13;
        Card *temp = 0;
        temp = new Card(ranks[count % 13], suits[divide]);
        deck.push_back(temp);
    }
    
}

void deckOfCards::shuffle() {
    Card *temp = 0;
    for(int first = 0; first < DECK_SIZE; first++) {
        int second = (rand() + time(0)) % DECK_SIZE;
        temp = this->deck[first];
        deck[first] = deck[second];
        deck[second] = temp;
    }
}

Card* deckOfCards::getCard(){
    Card *temp = deck[deck.size()-1];
    deck.pop_back();
    return temp;
    
}

void deckOfCards::printDeck() {
    
    for(int count = 0; count < DECK_SIZE; count++) {
        cout << deck[count]->getSuit() << ", " << deck[count]->getRank() <<endl;
        
    }
    
}

//BLACKJACK DEFINITION(S) GO HERE=======================================================================================================================

/*
  The Blackjack class handles all of the black jack logic. It pulls out the cards from the deck, handles input from
   the user, and handles all bets. It also creates card Ascii art so the user can see a visual of each card that is played
*/


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


void Blackjack::playGame(){
    bool stickStop = false;
    string hidden = "┌────┐"
    "\n│░░░░│"
    "\n│░░░░│"
    "\n│░░░░│"
    "\n└────┘";
    
    d1->shuffle();
    int cardTotalUser;
    int cardTotalDealer;
    string hitOrStick;
    double bet;
    
    cout << " ____  _            _     _            _\n"
    "| __ )| | __ _  ___| | __(_) __ _  ___| |__\n"
    "|  _ \\| |/ _` |/ __| |/ /| |/ _` |/ __| |/ /\n"
    "| |_) | | (_| | (__|   < | | (_| | (__|   <\n"
    "|____/|_|\\__,_|\\___|_|\\_\\/ |\\__,_|\\___|_|\\_\\\n"
    "                        |__/\n";
    cout << endl;
    cout << endl;
    cout << "Welcome to BlackJack!" <<  endl;
    cout << endl;
    cout << "We are so excited that you could join us this evening!" << endl;
    cout << "Here’s how Blackjack (or 21 works):";
    cout << endl;
    cout << "1. Each player is dealt two cards, first you as the player as well as the house (the dealer)" << endl;
    cout << endl;
    cout << "2. You will be able to see both of your cards and only one of the house’s cards" << endl;
    cout << endl;
    cout << "3. The object of the game is to get your hand total to get as close as possible to 21 without" << endl;
    cout << "going over, also known as “Busting.” If your hand adds up to 21, you automatically win " << endl;
    cout << "and will receive a payout based on the stakes for that given night for the game of " << endl;
    cout << "Blackjack. " << endl;
    cout << endl;
    cout << "4. Upon looking at your hand, you may decide if you would like to “Hit” or “Stick” by typing" << endl;
    cout << "those works exactly when prompted (the input is case-sensitive)." << endl;
    cout << endl;
    cout << "5. If you decide to “Hit,” you will receive another card to your hand. At this time, if your hand" << endl;
    cout << "total equals 21, you win. However, if your hand total is greater than 21, you “bust”, the " << endl;
    cout << "game is over, and the house wins." << endl;
    cout << endl;
    cout << "6. If your hand does not equal 21 at this time, you have the option to “Hit” again, which " << endl;
    cout << "means you will receive another card, or to “Stick,” in which case your hand will not " << endl;
    cout << "increase in value." << endl;
    cout << endl;
    cout << "7. If you decide to “Stick”, you will not receive a new card to your hand, and the play turns" << endl;
    cout << "over to the dealer who may “Hit” and/or “Stick” as well." << endl;
    cout << endl;
    cout << "8. Once the dealer’s hand has been confirmed, then all cards are turned over, and the" << endl;
    cout << "player with the higher overall hand total wins that round. " << endl;
    cout << endl;
    cout << "The stakes tonight are set at: " << money->getStakes() << endl;
    cout << "Your current bank has $" << money->getBank() << endl;
    cout << "How much are you betting tonight?" << endl;
    cout << endl;
    // MUST INCLUDE A CHARACTER CHECK
    while(true){

    cin >> bet;
    if (cin.good()) {
        money->setBetAmount(bet);
        break;
    } else {
        cout << "Invalid Input. Please input a number value." << endl;
        cin.clear();
        cin.ignore(100000, '\n') ;
    }
}
    while (bet > money->getBank() || bet < 0.01){
        cout << "You are betting more money than you have, try again." << endl;
        cout << "How much are you betting tonight?" << endl;
    }
    

    
    cout << "Your first two cards were dealt." << endl;
    
    bool gotAce = false;
    
    bool addedTen = false;
    
    dealCardUser();
    dealCardUser();
    dealCardDealer();
    dealCardDealer();
    cardOneUser = cardPrint(cardIntUser[0]);
    cardTwoUser = cardPrint(cardIntUser[1]);
    cardOneDealer = cardPrint(cardIntDealer[0]);
    cardTwoDealer = cardPrint(cardIntDealer[1]);
    
    bool subtractTen = false;
    
    cout << "User Card 1: " <<  "\n" << cardOneUser << endl;
    cout << "User Card 2: " << "\n" <<  cardTwoUser << endl;
    cout << "Dealer Card 1: " << "\n" << cardOneDealer << endl;
    cout << "Dealer Card 2: " << "\n" << hidden  << endl;
    dealernNumCards = 2;
    if ((cardIntUser[0]==1)||(cardIntUser[1]==1)){
        gotAce = true;
    }
    if (gotAce){
        bool b = true;
        gotAce = true;
        while(b){
            /*This piece checks that if an Ace has been pulled
            whether the user wants to count that ace as  a 1 or 11*/
            cout << "Do you want to count the Ace as 1 or 11?" << endl;
            int choice = 0;
            cin >> choice;
            switch(choice)
            {
                case 1: addTen = false;
                    b = false;
                    break;
                case 11: addTen = true;
                    b = false;
                    break;
                default:
                    cout<<"\nPlease enter a one or an eleven\n";
                    cin.clear();//clears stream state
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //ignores anything remaining in stream
            }
        }
    }
    if (addTen){
        cardTotalUser = cardIntUser[0] + cardIntUser[1] + 10;
        cardTotalDealer = cardIntDealer[0] + cardIntDealer[1];
        addedTen = true;
    } else{
        cardTotalUser = cardIntUser[0] + cardIntUser[1];
        cardTotalDealer = cardIntDealer[0] + cardIntDealer[1];
    }
    
    
    
    
    if (cardTotalUser>21) {
        youLose();
    }
    if (cardTotalUser == 21) {
        youWin();
    }
    
    if (cardTotalDealer>21) {
        youWin();
    }
    if (cardTotalDealer == 21) {
        youLose();
    }
    
    bool dealerHit = false;
    bool stick = false;
    bool wentToZero = false;
    
    for (int i = 0; i < 8; i++){
        
        string hitOrStick;
        int dealerHitInt = rand()%2;
        if (dealerHitInt == 1) {
            dealerHit = true;
        }
        if (dealerHitInt == 0){
            dealerHit = false;
        }
        
        if(stickStop == false){
            do {
                cout << "Do you want to 'Hit' or 'Stick'?" << endl;
                cin >> hitOrStick;
                cout << endl;
                
                if (hitOrStick == "Hit") {
                    dealCardUser();
                    break;
                }
                if (hitOrStick == "Stick") {
                    dealerPlay();
                    stick = true;
                    stickStop = true;
                    break;
                }
                else {
                    cout << "Please enter a valid input, case matters." << endl;
                    cout << "Do you want to 'Hit' or 'Stick'?" << endl;
                    cin >> hitOrStick;
                    cout << endl;
                }
                
            } while ((hitOrStick != "Hit") && (hitOrStick != "Stick") && (!stickStop));
        }
        
        if ((stickStop) && (!dealerHit) ){
            break;
        }
        
        if ((stickStop) && (dealerHit) &&(!wentToZero)){
            i=0;
            wentToZero= true;
        }
        
        /*This piece of code shows the first two sets of 
         two cards dealt to both the dealer and the player.*/
        cout << "Blackjack" << endl;
        cout << "*********" << endl;
        cout << endl;
        cout << "User Card 1: " <<  "\n" << cardOneUser<< endl;
        cout << "User Card 2: " << "\n" << cardTwoUser << endl;
        cout << "Dealer Card 1: " << "\n" << cardOneDealer << endl;
        cout << "Dealer Card 2:" << "\n" << hidden << endl;
        
        /* This piece handles how cards are dealt.
        This also handles whether or not certain dealer cards 
        are shown or hidden.*/
        if ((i == 0) && (hitOrStick=="Stick") && dealerHit) {
            cardThreeDealer = cardPrint(cardIntDealer[2]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            dealernNumCards = 3;
            cardTotalDealer += cardIntDealer[2];
        }
        if ((i == 0) && (hitOrStick=="Hit")) {
            cardThreeUser = cardPrint(cardIntUser[2]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cardTotalUser += cardIntUser[2];
        }
        if ((i == 1) && (hitOrStick=="Stick") && dealerHit) {
            cardFourDealer = cardPrint(cardIntDealer[3]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            dealernNumCards = 4;
            cardTotalDealer += cardIntDealer[3];
        }
        if ((i == 1) && (hitOrStick=="Hit")) {
            cardFourUser = cardPrint(cardIntUser[3]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: " << "\n" <<  cardFourUser << endl;
            cardTotalUser += cardIntUser[3];
        }
        if ((i == 2) && (hitOrStick=="Stick" && dealerHit)) {
            cardFiveDealer = cardPrint(cardIntDealer[4]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            dealernNumCards = 5;
            cardTotalDealer += cardIntDealer[4];
        }
        if ((i == 2) && (hitOrStick=="Hit")) {
            cardFiveUser = cardPrint(cardIntUser[4]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cardTotalUser += cardIntUser[4];
        }
        if ((i == 3) && (hitOrStick=="Stick") && dealerHit) {
            cardSixDealer = cardPrint(cardIntDealer[5]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            dealernNumCards = 6;
            cardTotalDealer += cardIntDealer[5];
        }
        if ((i == 3) && (hitOrStick=="Hit")) {
            cardSixUser = cardPrint(cardIntUser[5]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cardTotalUser += cardIntUser[5];
        }
        if ((i == 4) && (hitOrStick=="Stick") && dealerHit) {
            cardSevenDealer = cardPrint(cardIntDealer[6]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            cout << "Dealer Card 7: \n" <<  hidden << endl;
            dealernNumCards = 7;
            cardTotalDealer += cardIntDealer[6];
        }
        if ((i == 4) && (hitOrStick=="Hit")) {
            cardSevenUser = cardPrint(cardIntUser[6]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cout << "User Card 7: \n" << cardSevenUser << endl;
            
            cardTotalUser += cardIntUser[6];
        }
        if ((i == 5) && (hitOrStick=="Stick") && dealerHit) {
            cardEightDealer = cardPrint(cardIntDealer[7]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            cout << "Dealer Card 7: \n" <<  hidden << endl;
            cout << "Dealer Card 8: \n" <<  hidden << endl;
            dealernNumCards = 8;
            cardTotalDealer += cardIntDealer[7];
        }
        if ((i == 5) && (hitOrStick=="Hit")) {
            cardEightUser = cardPrint(cardIntUser[7]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cout << "User Card 7: \n" << cardSevenUser << endl;
            cout << "User Card 8: \n" << cardEightUser<< endl;
            cardTotalUser += cardIntUser[7];
        }
        if ((i == 6) && (hitOrStick=="Stick") && dealerHit) {
            cardNineDealer = cardPrint(cardIntDealer[8]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            cout << "Dealer Card 7: \n" <<  hidden << endl;
            cout << "Dealer Card 8: \n" <<  hidden << endl;
            cout << "Dealer Card 9: \n" <<  hidden << endl;
            dealernNumCards = 9;
            cardTotalDealer += cardIntDealer[8];
        }
        if ((i == 6) && (hitOrStick=="Hit")) {
            cardNineUser = cardPrint(cardIntUser[8]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cout << "User Card 7: \n" << cardSevenUser << endl;
            cout << "User Card 8: \n" << cardEightUser<< endl;
            cout << "User Card 9: \n" << cardNineUser << endl;
            cardTotalUser += cardIntUser[8];
        }
        if ((i == 7) && (hitOrStick=="Stick") && dealerHit) {
            cardTenDealer = cardPrint(cardIntDealer[9]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            cout << "Dealer Card 7: \n" <<  hidden << endl;
            cout << "Dealer Card 8: \n" <<  hidden << endl;
            cout << "Dealer Card 9: \n" <<  hidden << endl;
            cout << "Dealer Card 10: \n" <<  hidden << endl;
            dealernNumCards = 10;
            cardTotalDealer += cardIntDealer[9];
        }
        if ((i == 7) && (hitOrStick=="Hit")) {
            cardTenUser = cardPrint(cardIntUser[9]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cout << "User Card 7: \n" << cardSevenUser << endl;
            cout << "User Card 8: \n" << cardEightUser<< endl;
            cout << "User Card 9: \n" << cardNineUser << endl;
            cout << "User Card 10: \n" << cardTenUser << endl;
            cardTotalUser += cardIntUser[9];
        }
        if ((i == 8) && (hitOrStick=="Stick") && dealerHit) {
            cardElevenDealer = cardPrint(cardIntDealer[10]);
            cout << "Dealer Card 3: \n" << hidden << endl;
            cout << "Dealer Card 4: \n" << hidden <<endl;
            cout << "Dealer Card 5: \n" <<  hidden << endl;
            cout << "Dealer Card 6: \n" <<  hidden << endl;
            cout << "Dealer Card 7: \n" <<  hidden << endl;
            cout << "Dealer Card 8: \n" <<  hidden << endl;
            cout << "Dealer Card 9: \n" <<  hidden << endl;
            cout << "Dealer Card 10: \n" <<  hidden << endl;
            cout << "Dealer Card 11: \n" <<  hidden << endl;
            dealernNumCards = 11;
            cardTotalDealer += cardIntDealer[10];
        }
        if ((i == 8) && (hitOrStick=="Hit")) {
            cardElevenUser = cardPrint(cardIntUser[10]);
            cout << "User Card 3: " <<  "\n" << cardThreeUser << endl;
            cout << "User Card 4: "<< "\n" <<  cardFourUser << endl;
            cout << "User Card 5: \n" << cardFiveUser << endl;
            cout << "User Card 6: \n" << cardSixUser << endl;
            cout << "User Card 7: \n" << cardSevenUser << endl;
            cout << "User Card 8: \n" << cardEightUser<< endl;
            cout << "User Card 9: \n" << cardNineUser << endl;
            cout << "User Card 10: \n" << cardTenUser << endl;
            cout << "User Card 11: \n" << cardElevenUser << endl;
            cardTotalUser += cardIntUser[10];
            
        }
        
        /*This piece of code continues to check whether
         future cards are an ace or not and then goes
         through the logic of whether or not the user
         wants that ace to function as a 1 or 11*/
        if (cardIntUser[i+2]==1){
            gotAce = true;
        }
        if ((gotAce)&&(!stickStop)){
            
            cout << "Do you want to count the Ace as 1 or 11?" << endl;
            
            while(true){
                int input = 0;
                
                cin >> input;
                if (input == 1){
                    if (addedTen){
                        subtractTen = true;
                    }
                    addTen = false;
                    break;
                }
                else if (input == 11){
                    if (subtractTen){
                        subtractTen = false;
                    } else if (addedTen){
                        addTen = false;
                    }else{
                        addTen = true;
                    }
                    break;
                } else {
                    cout<<"\nPlease enter a one or an eleven\n";
                    cin.clear();//clears stream state
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                
            }
        }
        
        if ((addTen)&&(addedTen==false)){
            cardTotalUser += 10;
        } else if  (subtractTen){
            cardTotalUser -= 10;
        }
        
        cout << endl;
        
        if (cardTotalUser>21) {
            youLose();
            break;
        }
        if (cardTotalUser == 21) {
            youWin();
            break;
        }
        
        if (cardTotalDealer>21) {
            youWin();
            break;
        }
        if (cardTotalDealer == 21) {
            youLose();
            break;
        }
        
        
    }
    if ((dealerHit == false)&&(stick)){
        if (cardTotalUser > cardTotalDealer) {
            youWin();
        }
        if (cardTotalUser == cardTotalDealer) {
            tie();
        }
        if (cardTotalUser < cardTotalDealer) {
            youLoseMore();
        }
        else if ((dealerHit == true)&&(stick)){
            if (cardTotalUser>21) {
                youLose();
            }
            if (cardTotalUser == 21) {
                youWin();
            }
            
            if (cardTotalDealer>21) {
                youWin();
            }
            if (cardTotalDealer == 21) {
                youLoseMore();
            }
            
        }
    }
}

/*This method handles the situation when a user and the
 computer dealer both have the same value hand*/
void Blackjack::tie(){
    
    cout << "Blackjack" << endl;
    cout << "*********" << endl;
    cout << endl;
    cout << "That was a push (tie)!" << endl;
    int total = 0;
    for (int i = 0 ; i < cardArrayIndexUser; i++){
        if (i == 0){
            cout << "User Card " << i+1 << ": \n" << cardOneUser << endl;
        } else if (i == 1){
            cout << "User Card " << i+1 << ": \n" << cardTwoUser << endl;
        }  else if (i == 2){
            cout << "User Card " << i+1 << ": \n" << cardThreeUser << endl;
        } else if (i == 3){
            cout << "User Card " << i+1 << ": \n" << cardFourUser << endl;
        } else if (i == 4){
            cout << "User Card " << i+1 << ": \n" << cardFiveUser << endl;
        } else if (i == 5){
            cout << "User Card " << i+1 << ": \n" << cardSixUser << endl;
        } else if (i == 6){
            cout << "User Card " << i+1 << ": \n" << cardSevenUser << endl;
        } else if (i == 7){
            cout << "User Card " << i+1 << ": \n" << cardEightUser << endl;
        } else if (i == 8){
            cout << "User Card " << i+1 << ": \n" << cardNineUser << endl;
        } else if (i == 9){
            cout << "User Card " << i+1 << ": \n" << cardTenUser << endl;
        } else if (i == 10){
            cout << "User Card " << i+1 << ": \n" << cardElevenUser << endl;
        }
        total += cardIntUser[i];
    }
    if (addTen){
        total += 10;
    }
    cout << "User hand total: " << total << endl;
    total = 0;
    for (int i = 0 ; i < dealernNumCards; i++){
        if (i == 0){
            cout << "Dealer Card " << i+1 << ": \n" << cardOneDealer << endl;
        } else if (i == 1){
            cout << "Dealer Card " << i+1 << ": \n" << cardTwoDealer<< endl;
        }  else if (i == 2){
            cout << "Dealer Card " << i+1 << ": \n" << cardThreeDealer << endl;
        } else if (i == 3){
            cout << "Dealer Card " << i+1 << ": \n" << cardFourDealer << endl;
        } else if (i == 4){
            cout << "Dealer Card " << i+1 << ": \n" << cardFiveDealer << endl;
        } else if (i == 5){
            cout << "Dealer Card " << i+1 << ": \n" << cardSixDealer << endl;
        } else if (i == 6){
            cout << "Dealer Card " << i+1 << ": \n" << cardSevenDealer << endl;
        } else if (i == 7){
            cout << "Dealer Card " << i+1 << ": \n" << cardEightDealer << endl;
        } else if (i == 8){
            cout << "Dealer Card " << i+1 << ": \n" << cardNineDealer << endl;
        } else if (i == 9){
            cout << "Dealer Card " << i+1 << ": \n" << cardTenDealer << endl;
        } else if (i == 10){
            cout << "Dealer Card " << i+1 << ": \n" << cardElevenDealer << endl;
        }
        total += cardIntDealer[i];
    }
    cout << "Dealer hand total: " << total << endl;
}

/*This method handles the printing of each card
 to be used throughout the Blackjack class.*/
string Blackjack::cardPrint(int rank){
    string temp;
    string add;
    int whichRank = rand() % 4;
    if (rank == 1){
        add = "A";
    } else if (rank == 2){
        add = "2";
    }else if (rank == 3){
        add = "3";
    }else if (rank == 4){
        add = "4";
    }else if (rank == 5){
        add = "5";
    }else if (rank == 6){
        add = "6";
    }else if (rank == 7){
        add = "7";
    }else if (rank == 8){
        add = "8";
    }else if (rank == 9){
        add = "9";
    }else if (rank == 10){
        if (whichRank == 0){
            add = "J";
        }
        if (whichRank == 1){
            add = "Q";
        }
        if (whichRank == 2){
            add = "K";
        }
        if (whichRank == 3){
            add = "10";
        }
    }
    
    
    int rando = rand()%4;
    if (add != "10"){
        if (rando == 0){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2660│"
            "\n│....│"
            "\n│\u2660.." + add +
            "│"
            "\n└────┘";
        } else if (rando == 1){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2665│"
            "\n│....│"
            "\n│\u2665.." + add +
            "│"
            "\n└────┘";
        }
        else if (rando == 2){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2666│"
            "\n│....│"
            "\n│\u2666.." + add +
            "│"
            "\n└────┘";
            
        } else if (rando == 3){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2663│"
            "\n│....│"
            "\n│\u2663.." + add +
            "│"
            "\n└────┘";
        }
    }
    else if (add == "10"){
        if (rando == 0){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2660│"
            "\n│....│"
            "\n│\u2660." + add +
            "│"
            "\n└────┘";
        } else if (rando == 1){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2665│"
            "\n│....│"
            "\n│\u2665." + add +
            "│"
            "\n└────┘";
        }
        else if (rando == 2){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2666│"
            "\n│....│"
            "\n│\u2666." + add +
            "│"
            "\n└────┘";
            
        } else if (rando == 3){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2663│"
            "\n│....│"
            "\n│\u2663." + add +
            "│"
            "\n└────┘";
        }
        
    }
    
    return temp;
}


/*This method handles the actual dealing of cards
 to the user for use throughout the Blackjack
 class as more cards are added to the user's hand through
 hitting or the initial deal of the game.*/

void Blackjack::dealCardUser(){
    int CardValueUser = 0;
    srand(time(NULL));
    Card *temp = d1->getCard();
    CardValueUser =  temp->getRank();
    if (CardValueUser == 1){
        cnt++;
    }
    if ((cnt > 1)&&(CardValueUser==1)) CardValueUser = 2;
    cardIntUser[cardArrayIndexUser] = CardValueUser;
    cardArrayIndexUser++;
    
}

/*This method handles the actual dealing of cards
 to the dealer for use throughout the Blackjack
 class as more cards are added to the dealer's hand through
 hitting or the initial deal of the game.*/

void Blackjack::dealCardDealer(){
    int CardValueDealer = 0;
    srand(time(NULL));
    Card *temp = d1->getCard();
    CardValueDealer =  temp->getRank();
    if(CardValueDealer == 1) CardValueDealer = 2;
    cardIntDealer[cardArrayIndexDealer] = CardValueDealer;
    cardArrayIndexDealer++;
}

/*This method handles when the player loses
 to the dealer in a game of Blackjack, communicating 
 with the money class to update how much
 money the user has lost. To reach this
 method, the user has to lose by busting. Losing 
 by having less points than the dealer is handled in
 loseMore()*/

void Blackjack::youLose() {
    cout << "Blackjack" << endl;
    cout << "*********" << endl;
    cout << endl;
    cout << "Sorry, you have bust!" << endl;
    int total = 0;
    for (int i = 0 ; i < cardArrayIndexUser; i++){
        if (i == 0){
            cout << "User Card " << i+1 << ": \n" << cardOneUser << endl;
        } else if (i == 1){
            cout << "User Card " << i+1 << ": \n" << cardTwoUser << endl;
        }  else if (i == 2){
            cout << "User Card " << i+1 << ": \n" << cardThreeUser << endl;
        } else if (i == 3){
            cout << "User Card " << i+1 << ": \n" << cardFourUser << endl;
        } else if (i == 4){
            cout << "User Card " << i+1 << ": \n" << cardFiveUser << endl;
        } else if (i == 5){
            cout << "User Card " << i+1 << ": \n" << cardSixUser << endl;
        } else if (i == 6){
            cout << "User Card " << i+1 << ": \n" << cardSevenUser << endl;
        } else if (i == 7){
            cout << "User Card " << i+1 << ": \n" << cardEightUser << endl;
        } else if (i == 8){
            cout << "User Card " << i+1 << ": \n" << cardNineUser << endl;
        } else if (i == 9){
            cout << "User Card " << i+1 << ": \n" << cardTenUser << endl;
        } else if (i == 10){
            cout << "User Card " << i+1 << ": \n" << cardElevenUser << endl;
        }
        total += cardIntUser[i];
    }
    if (addTen){
        total += 10;
    }
    cout << "User hand total: " << total << endl;
    total = 0;
    for (int i = 0 ; i < dealernNumCards; i++){
        if (i == 0){
            cout << "Dealer Card " << i+1 << ": \n" << cardOneDealer << endl;
        } else if (i == 1){
            cout << "Dealer Card " << i+1 << ": \n" << cardTwoDealer<< endl;
        }  else if (i == 2){
            cout << "Dealer Card " << i+1 << ": \n" << cardThreeDealer << endl;
        } else if (i == 3){
            cout << "Dealer Card " << i+1 << ": \n" << cardFourDealer << endl;
        } else if (i == 4){
            cout << "Dealer Card " << i+1 << ": \n" << cardFiveDealer << endl;
        } else if (i == 5){
            cout << "Dealer Card " << i+1 << ": \n" << cardSixDealer << endl;
        } else if (i == 6){
            cout << "Dealer Card " << i+1 << ": \n" << cardSevenDealer << endl;
        } else if (i == 7){
            cout << "Dealer Card " << i+1 << ": \n" << cardEightDealer << endl;
        } else if (i == 8){
            cout << "Dealer Card " << i+1 << ": \n" << cardNineDealer << endl;
        } else if (i == 9){
            cout << "Dealer Card " << i+1 << ": \n" << cardTenDealer << endl;
        } else if (i == 10){
            cout << "Dealer Card " << i+1 << ": \n" << cardElevenDealer << endl;
        }
        total += cardIntDealer[i];
    }
    cout << "Dealer hand total: " << total << endl;
    if(money->lose()){
        cout<< "You lost all your money\n";
        lostAllMoney = true;
    }
    double temp = money->getBank();
    user->setBank(temp);
}

/*This method handles the special case of a loss
 when the user didn't bust but the dealer has
 a high value of cards in their hand that 
 also does not bust. */

void Blackjack::youLoseMore() {
    cout << "Blackjack" << endl;
    cout << "*********" << endl;
    cout << endl;
    cout << "Sorry, you lose!" << endl;
    int total = 0;
    for (int i = 0 ; i < cardArrayIndexUser; i++){
        if (i == 0){
            cout << "User Card " << i+1 << ": \n" << cardOneUser << endl;
        } else if (i == 1){
            cout << "User Card " << i+1 << ": \n" << cardTwoUser << endl;
        }  else if (i == 2){
            cout << "User Card " << i+1 << ": \n" << cardThreeUser << endl;
        } else if (i == 3){
            cout << "User Card " << i+1 << ": \n" << cardFourUser << endl;
        } else if (i == 4){
            cout << "User Card " << i+1 << ": \n" << cardFiveUser << endl;
        } else if (i == 5){
            cout << "User Card " << i+1 << ": \n" << cardSixUser << endl;
        } else if (i == 6){
            cout << "User Card " << i+1 << ": \n" << cardSevenUser << endl;
        } else if (i == 7){
            cout << "User Card " << i+1 << ": \n" << cardEightUser << endl;
        } else if (i == 8){
            cout << "User Card " << i+1 << ": \n" << cardNineUser << endl;
        } else if (i == 9){
            cout << "User Card " << i+1 << ": \n" << cardTenUser << endl;
        } else if (i == 10){
            cout << "User Card " << i+1 << ": \n" << cardElevenUser << endl;
        }
        total += cardIntUser[i];
    }
    if (addTen){
        total += 10;
    }
    cout << "User hand total: " << total << endl;
    total = 0;
    for (int i = 0 ; i < dealernNumCards; i++){
        if (i == 0){
            cout << "Dealer Card " << i+1 << ": \n" << cardOneDealer << endl;
        } else if (i == 1){
            cout << "Dealer Card " << i+1 << ": \n" << cardTwoDealer<< endl;
        }  else if (i == 2){
            cout << "Dealer Card " << i+1 << ": \n" << cardThreeDealer << endl;
        } else if (i == 3){
            cout << "Dealer Card " << i+1 << ": \n" << cardFourDealer << endl;
        } else if (i == 4){
            cout << "Dealer Card " << i+1 << ": \n" << cardFiveDealer << endl;
        } else if (i == 5){
            cout << "Dealer Card " << i+1 << ": \n" << cardSixDealer << endl;
        } else if (i == 6){
            cout << "Dealer Card " << i+1 << ": \n" << cardSevenDealer << endl;
        } else if (i == 7){
            cout << "Dealer Card " << i+1 << ": \n" << cardEightDealer << endl;
        } else if (i == 8){
            cout << "Dealer Card " << i+1 << ": \n" << cardNineDealer << endl;
        } else if (i == 9){
            cout << "Dealer Card " << i+1 << ": \n" << cardTenDealer << endl;
        } else if (i == 10){
            cout << "Dealer Card " << i+1 << ": \n" << cardElevenDealer << endl;
        }
        total += cardIntDealer[i];
    }
    cout << "Dealer hand total: " << total << endl;
    if(money->lose()){
        cout<< "You lost all your money";
        lostAllMoney = true;
        
    }
    double temp = money->getBank();
    user->setBank(temp);
}

/*This method handles the case when the user both hasn't 
 busted and either the dealer/computer busted or
 has a lesser value of cards in their hand than
 the user does. This allows the user to win, and
 this method communicates with the money class to 
 update the user's money.*/

void Blackjack::youWin() {
    cout << "Blackjack" << endl;
    cout << "*********" << endl;
    cout << endl;
    cout << "Congratulations, you have won!" << endl;
    int total = 0;
    for (int i = 0 ; i < cardArrayIndexUser; i++){
        if (i == 0){
            cout << "User Card " << i+1 << ": \n" << cardOneUser << endl;
        } else if (i == 1){
            cout << "User Card " << i+1 << ": \n" << cardTwoUser << endl;
        }  else if (i == 2){
            cout << "User Card " << i+1 << ": \n" << cardThreeUser << endl;
        } else if (i == 3){
            cout << "User Card " << i+1 << ": \n" << cardFourUser << endl;
        } else if (i == 4){
            cout << "User Card " << i+1 << ": \n" << cardFiveUser << endl;
        } else if (i == 5){
            cout << "User Card " << i+1 << ": \n" << cardSixUser << endl;
        } else if (i == 6){
            cout << "User Card " << i+1 << ": \n" << cardSevenUser << endl;
        } else if (i == 7){
            cout << "User Card " << i+1 << ": \n" << cardEightUser << endl;
        } else if (i == 8){
            cout << "User Card " << i+1 << ": \n" << cardNineUser << endl;
        } else if (i == 9){
            cout << "User Card " << i+1 << ": \n" << cardTenUser << endl;
        } else if (i == 10){
            cout << "User Card " << i+1 << ": \n" << cardElevenUser << endl;
        }
        total += cardIntUser[i];
        
    }
    if (addTen){
        total += 10;
    }
    cout << "User hand total: " << total << endl;
    total = 0;
    for (int i = 0 ; i < dealernNumCards; i++){
        if (i == 0){
            cout << "Dealer Card " << i+1 << ": \n" << cardOneDealer << endl;
        } else if (i == 1){
            cout << "Dealer Card " << i+1 << ": \n" << cardTwoDealer<< endl;
        }  else if (i == 2){
            cout << "Dealer Card " << i+1 << ": \n" << cardThreeDealer << endl;
        } else if (i == 3){
            cout << "Dealer Card " << i+1 << ": \n" << cardFourDealer << endl;
        } else if (i == 4){
            cout << "Dealer Card " << i+1 << ": \n" << cardFiveDealer << endl;
        } else if (i == 5){
            cout << "Dealer Card " << i+1 << ": \n" << cardSixDealer << endl;
        } else if (i == 6){
            cout << "Dealer Card " << i+1 << ": \n" << cardSevenDealer << endl;
        } else if (i == 7){
            cout << "Dealer Card " << i+1 << ": \n" << cardEightDealer << endl;
        } else if (i == 8){
            cout << "Dealer Card " << i+1 << ": \n" << cardNineDealer << endl;
        } else if (i == 9){
            cout << "Dealer Card " << i+1 << ": \n" << cardTenDealer << endl;
        } else if (i == 10){
            cout << "Dealer Card " << i+1 << ": \n" << cardElevenDealer << endl;
        }
        total += cardIntDealer[i];
    }
    cout << "Dealer hand total: " << total << endl;
    money->win();
    double temp = money->getBank();
    user->setBank(temp);
    
}


/*This method initiates the dealer's turn after the
 user has decided to stick.*/

void Blackjack::dealerPlay(){
    dealCardDealer();
}

/*This is the Blackjack constructor. This is what 
 the interface will call and the function that
 will call playGame() to start and complete the
 game of Blackjack.*/

Blackjack::Blackjack(User *user){
    
    this-> user = user;
    doubleAce = false;
    lostAllMoney = false;
    addTen = false;
    cardArrayIndexUser = 0;
    cardArrayIndexDealer = 0;
    computerHand = new Card* [11];
    userHand = new Card* [11];
    compHandValue = 0;
    userHandValue= 0;
    bet = 0;
    d1 = new deckOfCards();
    money = new Money(user->getBank());
    dealernNumCards = 0;
    
    
    
    
    
    /*This is the piece of code that actually begins the game.
     Just below it, loseMoney keeps track of whether or not 
     the user has used up all their money in the process of
     playing the game. If this happens, the user is then kicked
     out of the casino uncerimoniously, and the computer takes
     ownership of the player's house. (Well, maybe not that last bit,
     but the user is indeed kicked out and the program ends)*/

    while(true){
        playGame();
        if(lostAllMoney){
            cout << "Your night at the casino is over, see you next time! :)" << endl;
            exit(0);
        } else{
            break;
        }
    }
}


//WAR DEFINITION(S) GO HERE=============================================================================================================================

/*Instead of being a class like Blackjack,
 the game of War is handled as a series of 
 separate methods keepint track of the actual
 game and with a WarCard class that
 keeps track of the actual cards in War
 since the values of cards in War vary from
 those in Blackjack.*/

/*This is the WarCard class that
 keeps track of the information
 for the cards used in War.*/

class WarCard {
private:
    string rank;
    string suit;
    
public:
    WarCard(string WarCardRank, string WarCardSuit);
    string getRank();
    string getSuit();
};


/*This is the WarCard class that creates each individual card
 to be used in the War game.*/

WarCard::WarCard(string WarCardRank, string WarCardSuit)
{
    this->rank = WarCardRank;
    this->suit = WarCardSuit;
}

string WarCard::getRank()
{
    // accessor method for the rank of the WarCard
    return this->rank;
}

string WarCard::getSuit()
{
    // accessor method for the suit of the WarCard
    return this->suit;
}

/*
 ==========================
 creates deckOfWarCards object
 specifically for the war class
 ==========================
 */

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

deckOfWarCards::deckOfWarCards()
{
    /*
     Constructor for deckOfWarCards class.
     Constructs a deck vector while pulling string values from both arrays.
     */
    string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    currentWarCard = 0;
    int divide;
    for(int count = 0; count < DECK_SIZE; count++) {
        divide = count / 13;
        WarCard *temp = 0;
        temp = new WarCard(ranks[count % 13], suits[divide]);
        deck.push_back(temp);
    }
}

void deckOfWarCards::shuffle()
{
    /*This method shuffles the deck */
    WarCard *temp = 0;
    for(int first = 0; first < DECK_SIZE; first++) {
        int second = abs((rand() + time(0)) % DECK_SIZE);
        temp = this->deck[first];
        deck[first] = deck[second];
        deck[second] = temp;
    }
}

WarCard* deckOfWarCards::getWarCard()
{
    /*Accessor method for each individual WarCard in the deck */
    WarCard *temp = deck[deck.size()-1];
    deck.pop_back();
    return temp;
    
}

void deckOfWarCards::printDeck()
{
    /*This method prints each WarCard in the deck using the WarCard's accessor methods*/
    for(int count = 0; count < DECK_SIZE; count++) {
        cout << deck[count]->getSuit() << ", " << deck[count]->getRank() <<endl;
        
    }
    
}

//Ascii art for WarCards
//The WarCard prints depending on the rank
string WarCardPrint(int rank, string suit){
    string temp;
    string add;
    if (rank == 14){
        add = "A";
    }else if (rank == 2){
        add = "2";
    }else if (rank == 3){
        add = "3";
    }else if (rank == 4){
        add = "4";
    }else if (rank == 5){
        add = "5";
    }else if (rank == 6){
        add = "6";
    }else if (rank == 7){
        add = "7";
    }else if (rank == 8){
        add = "8";
    }else if (rank == 9){
        add = "9";
    }else if (rank == 10){
        add = "10";
    }else if (rank == 11){
        add = "J";
    }else if(rank == 12){
        add = "Q";
    }else if(rank == 13){
        add = "K";
    }
    
    
    if (add != "10"){
        if (suit == "Spades"){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2660│"
            "\n│....│"
            "\n│\u2660.." + add +
            "│"
            "\n└────┘";
        } else if (suit == "Hearts"){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2665│"
            "\n│....│"
            "\n│\u2665.." + add +
            "│"
            "\n└────┘";
        }
        else if (suit == "Diamonds"){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2666│"
            "\n│....│"
            "\n│\u2666.." + add +
            "│"
            "\n└────┘";
            
        } else if (suit == "Clubs"){
            temp = "┌────┐"
            "\n│" + add +
            "..\u2663│"
            "\n│....│"
            "\n│\u2663.." + add +
            "│"
            "\n└────┘";
        }
    }
    else if (add == "10"){
        if (suit == "Spades"){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2660│"
            "\n│....│"
            "\n│\u2660." + add +
            "│"
            "\n└────┘";
        } else if (suit == "Hearts"){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2665│"
            "\n│....│"
            "\n│\u2665." + add +
            "│"
            "\n└────┘";
        }
        else if (suit == "Diamonds"){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2666│"
            "\n│....│"
            "\n│\u2666." + add +
            "│"
            "\n└────┘";
            
        } else if (suit == "Clubs"){
            temp = "┌────┐"
            "\n│" + add +
            ".\u2663│"
            "\n│....│"
            "\n│\u2663." + add +
            "│"
            "\n└────┘";
        }
        
    }
    return temp;
}

int stringToInt(string s)
{
    /*This method returns integer values for the rank of each WarCard*/
    if(s == "2")
    {
        return 2;
    }
    if(s == "3")
    {
        return 3;
    }
    if(s == "4")
    {
        return 4;
    }
    if(s == "5")
    {
        return 5;
    }
    if(s == "6")
    {
        return 6;
    }
    if(s == "7")
    {
        return 7;
    }
    if(s == "8")
    {
        return 8;
    }
    if(s == "9")
    {
        return 9;
    }
    if(s == "10")
    {
        return 10;
    }
    if(s == "Jack")
    {
        return 11;
    }
    if(s == "Queen")
    {
        return 12;
    }
    if(s == "King")
    {
        return 13;
    }
    if(s == "Ace")
    {
        return 14;
    }
    
    return 0;
}

/* Menu method continuously asks user for input
 and prints out the main menu for War */
void warRules() {
    cout << endl;
    cout << "\n----------------------------------------------------"<< endl;
    cout << setw(47)<< "First, let us go over the rules of War:" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << endl;
    cout << "1. The deck of 52 is split in half among you and your opponent."<< endl;
    cout << endl;
    cout << "2. The first two cards on the top of each hand are compared";
    cout << "\nbased on rank. Ace in this game is highest in value."<< endl;
    cout << endl;
    cout << "3. The comparison continues until the cards that are drawn are equal.";
    cout << "\nThen you declare War and 4 cards are placed down. The last card from";
    cout << "\neach of the 4 is compared again and if they are equal the process";
    cout << "\nrepeats until they are different." << endl;
    cout << endl;
    cout << "4. The winner gets all the cards from their own hand and from the"
    << "\nhand of the opponent." << endl;
    //cout << "Tonight the stakes are set at " money->getStakes() << endl;
    cout << endl;
}

void menu(vector<WarCard*> &vector)
{
    
    // boolean variable that is used as the condition for the
    // while loop that prints out the menu
    bool b= true;
    int choice;
    // variable to store integer value of user's choice
    while(b)
    {
        cout << "\n-------------------------------------"<< endl;
        cout << setw(20) <<"Menu: ";
        cout << "\n-------------------------------------" << endl;
        cout <<"\nContinue - 1\n"; //break out of menu
        cout <<"Shuffle Deck - 2\n";//shuffle's user's deck
        cout <<"Concede Game - 3\n";//exits game
        cout <<"\nChoice: " << endl;
        cin >> choice;
        switch(choice)
        {
            case 1: b = false;
                break;
            case 2: random_shuffle(vector.begin(), vector.end());
                // some versions of war shuffle the deck
                // this case shuffles the contents of the WarCard* vector
                b = false;
                break;
            case 3:
                vector.resize(0);
                // this option is essentially "quit"
                // the deck of WarCards is resized to 0
                b=false;
                break;
            default:
                // default case tells user to input 1, 2, or 3 in case the user
                // gives bad input
                cout<<"\nPlease enter: 1, 2, or 3\n";
                cin.clear();//clears stream state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //ignores anything remaining in stream
        }
    }
}

/*
 ==========================================================================
 War method handles actual war gameplay. There are several vectors
 that store the user's hand, the opponent's hand, and an intermediate vector
 that holds the WarCards stored when War is declared. The deck is instantiated,
 shuffled, and split into the user's hand and the opponent's hand
 ===========================================================================
 */

bool War()
{
    cout << endl;
    cout<<"\nLet's begin by drawing two cards..." << endl;
    cout<<endl;
    deckOfWarCards *d = new deckOfWarCards();
    // shuffle the WarCards multiple times
    // just to be sure it's fair
    d->shuffle();
    d->shuffle();
    d->shuffle();
    vector<WarCard*> userDeck;//User's Deck
    vector<WarCard*> npcDeck;//NPC's deck
    vector<WarCard*> warDeck;//The neutral deck that goes to the winner
    // creates temporary WarCards from each hand
    WarCard *tempUser;
    WarCard *tempNpc;
    WarCard *tempWar;
    // integer variables to store value of rank from
    // both the user's WarCard and the cpu's WarCard
    int userRank;
    int npcRank;
    
    //Empty deck object to player decks
    for(int i = 0; i < 26; i++)
    {
        userDeck.push_back(d->getWarCard());
        npcDeck.push_back(d->getWarCard());
    }
    
    //EXAMPLE CODE REFERENCE: userDeck.insert(userDeck.begin(), npcDeck[npcDeck.size()-1]);
    //npcDeck.pop_back();
    /* The following loop continues to run as long as the user's and CPU's hands are
     not empty */
    while(userDeck.size() != 0 and npcDeck.size() != 0)
    {
        //We pull two WarCards from each vector
        // store the WarCard in the respective temp WarCard variable
        tempUser = userDeck[userDeck.size()-1];
        tempNpc = npcDeck[npcDeck.size()-1];
        // remove the WarCard from the end of both of the hands
        userDeck.pop_back();
        npcDeck.pop_back();
        
        //We convert the rank to an int, then compare the two. Uses custom helper function stringToInt()
        userRank = stringToInt(tempUser->getRank());
        npcRank = stringToInt(tempNpc-> getRank());
        
        //Display WarCards to console
        cout<<WarCardPrint(npcRank, tempNpc->getSuit()) << endl;
        cout<<endl;
        cout<<"\nYour opponent's Card is - " << tempNpc->getRank()
        << " of "<<tempNpc->getSuit()<<"\n";
        cout<<endl;
        cout<<WarCardPrint(userRank, tempUser->getSuit()) << endl;
        cout<<endl;
        cout<<"Your Card is - "<<tempUser->getRank()
        << " of " << tempUser->getSuit()<<"\n";
        
        if(userRank > npcRank) //If you win
        {
            cout<<"\nYou Won!\n";
            // add the WarCards to the beginning of the user's hand if the user wins
            userDeck.insert(userDeck.begin(), tempUser);
            userDeck.insert(userDeck.begin(), tempNpc);
            while(warDeck.size() > 0) //If there are WarCards in the war vector, you win them
            {
                tempWar = warDeck[warDeck.size()-1];
                warDeck.pop_back();
                userDeck.insert(userDeck.begin(), tempWar);
            }
        }
        else if(userRank < npcRank)//if you lose
        {
            cout<<"\nYou Lose!\n";
            // add the WarCards to the beginning of the CPU's hand if the CPU wins
            npcDeck.insert(npcDeck.begin(), tempUser);
            npcDeck.insert(npcDeck.begin(), tempNpc);
            while(warDeck.size() > 0) //if there are WarCards in the war vector, you win them
            {
                tempWar = warDeck[warDeck.size()-1];
                warDeck.pop_back();
                npcDeck.insert(npcDeck.begin(), tempWar);
            }
        }
        else //Declare War!
        {
            //If the WarCards are the same, War is declared
            cout<<"\n\"I DECLARE WAR\"\n";
            //Throw the two lead WarCards onto the war stack
            warDeck.push_back(tempUser);
            warDeck.push_back(tempNpc);
            //Check how many WarCards there are in the stacks
            if(userDeck.size() >= 4 and npcDeck.size() >= 4)//if both players have WarCards for war
            {
                for(int i = 0; i < 3; i++)
                {
                    tempUser = userDeck[userDeck.size()-1];
                    tempNpc = npcDeck[npcDeck.size()-1];
                    userDeck.pop_back();
                    npcDeck.pop_back();
                    warDeck.push_back(tempUser);
                    warDeck.push_back(tempNpc);
                }
            }
            else if(userDeck.size() < 4)
                //If you don't have the WarCards for war, you lose!
            {
                userDeck.resize(0);
                cout<<"You Lose the game!";
                cout<<endl;
                return true;
            }
            else
            {
                npcDeck.pop_back();
                cout<<"You Win the game!";
                cout<<endl;
                return false;
            }
        }
        cout<<"\n\nYour remaining Cards - "<<userDeck.size()<<"\nYour opponents remaining Cards - "<<npcDeck.size()<<"\n\n";
        if(warDeck.size() > 0)
        {
            cout<<"The number of Cards up for grabs is - " << warDeck.size()<<"\n\n";
        }
        menu(userDeck);
    }
    cout<<"\nYou Concede, better luck next time!\n";
    return false;
}

double confirmBet(User *user)
{
    /*
     * Helper function which gets and verifies a money value from the user.
     * Requests a double value. If the value can be stored within double d and
     * if that value is between 0 and 500,000, returns d.
     */
    double d;
    while(true)
    {
        if(cin>>d)
        {
            if(d <= user->getBank() and d > 0)
            {
                return d;
            }
        }
        cout<<"\nError, please enter a bet that you can afford";
        cout<<"\n\n";
        cout<<"Starting Money (Between 1 and 500,000) - ";
        std::cin.clear();//clears stream state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //ignores anything remaining in stream
    }
}

void warBet(User *user)
{
    /*
     * The warBet function holds the bet, which first must be confirmed in the confirm bet function.
     * User is passed into the warBet function in order for the confirmBet method to determine if our bet exceeds user's money
     * The War returns a bool, which is used to reward a won bet or inform the user if he loses.
     */
    
    
    Money *moneyWar = new Money(user->getBank());
    double bet;
    cout <<  "__        __\n"
    "\\ \\      / /_ _ _ __\n"
    " \\ \\ /\\ / / _` | '__|\n"
    "  \\ V  V / (_| | |\n"
    "   \\_/\\_/ \\__,_|_|\n" << endl;
    
    
    cout << endl;
    cout << endl;
    
    cout << "The stakes tonight are set at: " << moneyWar->getStakes() << endl;
    cout << "Your current bank has $" << moneyWar->getBank() << endl;
    cout << "How much are you betting tonight?" << endl;
    
    /*This piece of code checks to ensure the
     input is a vaild number instead of a
     character that would cause problems
     for the code and make the game
     impossible to play.*/
    
    while(true){
        cin >> bet;
        if (cin.good()) {
            moneyWar->setBetAmount(bet);
            break;
        } else {
            cout << "Invalid Input. Please input a number value." << endl;
            cin.clear();
            cin.ignore(100000, '\n') ;
        }
    }
    while (bet > moneyWar->getBank() || bet < 0.01){
        cout << "You are betting more money than you have, try again." << endl;
        cout << "How much are you betting tonight?" << endl;
        cin >> bet;
    }
    
    moneyWar->setBetAmount(bet);
    
    
    
    warRules();
    
    cout<<"Please place your bet: \n";
    
    //bet = confirmBet(user);
    //user->setBank(user->getBank() - bet);
    if(War() == false)
    {
        moneyWar->win();
        user->setBank(moneyWar->getBank());
        cout << endl;
        cout<<"*** Congratulations!!! YOU WON!!! ***" << endl;
    }
    else{
        cout << endl;
        moneyWar->lose();
        user->setBank(moneyWar->getBank());
        cout << endl;
        cout<<"*** YOU LOST!!! ***" << endl;
        
    }
}






//MAIN MEMBER FUNCTION(S) GO HERE
//Money must be between 1 and 500,000. Must fit into a double.

double getMoney()
{
    /*
     * Helper function which gets and verifies a money value from the user.
     * Requests a double value. If the value can be stored within double d and
     * if that value is between 0 and 500,000, returns d.
     */
    double d;
    while(true)
    {
        if(cin>>d)
        {
            if(d > 0 and d <= 500000)
            {
                return d;
            }
        }
        cout<<"\nError, please enter a double between 1 and 500,000 (without commas) - ";
        cout<<"\n\n";
        cout<<"Starting Money (Between 1 and 500000) - ";
        std::cin.clear();//clears stream state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores anything remaining in stream
    }
}

string getUserName()
{
    /*
     * Helper function which gets and verifies the username for our program.
     * First checks if the enterred input can fit into a string, then confirms it's a size we can support.
     * If true, then we return the string and set userName's value equal to it, else we repeatedly request correct input.
     */
    string s;
    while(true)
    {
        if(cin>>s)
        {
            if(s.size() < 11 and s.size() > 0)
            {
                return s;
            }
        }
        cout<<"\nError, please enter a string between 1 and 11 characters - ";
        cout<<"\n\n";
        cout<<"Username - ";
        std::cin.clear();//clears stream state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores anything remaining in stream
    }
}

/*
 * Helper methods to add to main:
 * User Verification Methods.
 * Sound output for some sort of in-game music and sound effects. (Consider this a stretch goal)
 * Additional error protection.
 */


int main(void)
{
    string userName;
    int userInput;
    double inputMoney;
    bool run = true;
    //bool moneyVerified = false;
    
    cout<<
    "██████╗ █████╗ ███████╗██╗███╗   ██╗ ██████╗     ██████╗  ██████╗ ██╗   ██╗ █████╗ ██╗     ███████╗\n"
    "██╔════╝██╔══██╗██╔════╝██║████╗  ██║██╔═══██╗    ██╔══██╗██╔═══██╗╚██╗ ██╔╝██╔══██╗██║     ██╔════╝\n"
    "██║     ███████║███████╗██║██╔██╗ ██║██║   ██║    ██████╔╝██║   ██║ ╚████╔╝ ███████║██║     █████╗\n"
    "██║     ██╔══██║╚════██║██║██║╚██╗██║██║   ██║    ██╔══██╗██║   ██║  ╚██╔╝  ██╔══██║██║     ██╔══╝\n"
    "╚██████╗██║  ██║███████║██║██║ ╚████║╚██████╔╝    ██║  ██║╚██████╔╝   ██║   ██║  ██║███████╗███████╗\n"
    "╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝ \n";
    cout << endl;
    cout << endl;
    cout << "Welcome to Casino Royale" << endl;
    cout << "Get ready for the night of your life" << endl;
    cout << "Play it safe or lose it all" << endl;
    cout << "First rule, of Casino Royale is, we don't talk about Casino Royale" << endl;
    cout << "Second rule, what happens in Casino Royale stays in Casino Royale" << endl;
    cout << "Third rule, there is no third rule." << endl;
    cout << endl;
    cout << endl;
    cout<<"Please enter username and starting money\n\n";
    cout<<"Username - ";
    userName = getUserName();
    cout<<"\n\n";
    cout<<"Starting Money (Between 1 and 500000) - ";
    inputMoney = getMoney();
    //Instantiate User Object
    User *user = new User(userName,inputMoney);
    //Instantiate Money Object
    //Money *money = new Money(inputMoney);
    cout<<"\n";
    
    
    while(run)
    {
        
        //DISPLAY MENU
        cout<<user->getName()<<"                       Casino Placeholder Menu                     $"<<user->getBank()<<"\n\n"; //TODO: CURRENTLY NOT CALLING USERNAME OBJECT OR MONEY OBJECT
        cout<<"(1) Play Blackjack\n";
        cout<<"(2) Play War\n";
        cout<<"(3) Exit\n\n";
        cout<<"User Choice - ";
        cin>>userInput;
        cout<<"\n";
        
        
        if (userInput == 1) {
            //This causes a warning because it is not used again
            //But it's necessary to play blackjack
            Blackjack *b1 = new Blackjack(user);
        }
        
        if (userInput == 2) {
            //INSTANTIATE WAR
            warBet(user);
        }
        
        if (userInput == 3) {
            //INSTANTIATE BK
            cout << "Its been great having you here with us at Casino Royale, goodbye!" << endl;
            cout << "You left here today with $" << user->getBank() << endl;
            exit(0);
        }
        
        //TODO: AT THE END OF LOOP -- CHECK TO SEE IF MONEY IS 0, IF TRUE, END LOOP
        cin.clear();//clears stream state
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores anything remaining in stream
    }
    
    return 0;
}
