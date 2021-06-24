// @file SportsCard.cpp
// @author Cameron Shore
// @date 06-Mar-21
// This holds definitions for SportsCard class
// Features:
//    Capability to create an instance of SportsCard object
// 
//    Capability to buy - increase amount of SportsCard obj in inventory by 1
// 
//    Capability to sell - decrease amount of SportCard obj in inventory by 1
// 
//    Capability to display - Displays the SportsCard classes data members to
//    the cout.
// 
//    Capability to input data into the the SportsCard object
// 
//    Capability to deep copy SportsCard objects
// 
//    Comparison between SportsCard objecs 
//
// Assumptions:
//    Files for creating inventory, and transactions will be formatted
//    appropriately and will have only valid contents
//
//    The shop inventory will have 1 SearchTree, 1 factory method for 
//    SportsCard objects


#include "SportsCard.h"

// destructor
// removes data from sportscard member variables
// @pre instantiated sportscard object with data in it's members
// @post data is removed from member variables
// @ return nothing.
SportsCard::~SportsCard(){
   player = "";
   manufacuturer = "";
   year = 0;
   grade = "";
   amount = 0;
}

// creates and instance of the SportsCard object
// @pre Initialized ShopManager
// @post object is initialized 
// @return const pointer to initialized object
Collectible* SportsCard::create() const{
   Collectible* s = new SportsCard;
   return s;
}

// outputs SportsCard object data members to cout
// @pre Initialized ShopManager, and Initialized method had been ran
// @post object's data members are output to cout in specified order
// @return nothing
void SportsCard::print() const{
   cout << amount << ", " << player << ", " << year << ", " << manufacuturer 
            << ", " << grade << endl;
}

Comparable* SportsCard::clone(const Comparable& copy){
   const SportsCard& copyFrom = static_cast<const SportsCard&>(copy);
   SportsCard* newCard = new SportsCard;
   newCard->amount = copyFrom.amount;
   newCard->year = copyFrom.year;
   newCard->player = copyFrom.player;
   newCard->grade = copyFrom.grade;
   newCard->manufacuturer = copyFrom.manufacuturer;
   return newCard;
}

// intializes a SportsCard object with contents from the ifstream
// @pre instantiated SportsCard object, valid ifstream data
// @post ifstream data is input into the SportsCard object data members
// @return nothing
void SportsCard::initialize(ifstream& inputFile){
   string year = "";
   string grade = "";
   string player = "";
   string manufacturer = "";
   string amount = "";
   getline(inputFile, amount, ',');
   inputFile.get();
   getline(inputFile, year, ',');
   inputFile.get();
   getline(inputFile, grade, ',');
   inputFile.get();
   getline(inputFile, player, ',');
   inputFile.get();
   getline(inputFile, manufacturer, '\n');
   this->player = player;
   this->year = atoi(year.c_str());
   this->grade = grade;
   this->manufacuturer = manufacturer;
   this->amount = atoi(amount.c_str());
}

// sets object's data members with string paramater contents
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post objects data members are filled with data from string argument
// @return nothing
void SportsCard::setParam(const string data){
   string year = "";
   string grade = "";
   string player = "";
   string manufacturer = "";
   stringstream ss;

   ss << data;
   ss.ignore(3, ' ');
   getline(ss, year, ',');
   ss.get();
   getline(ss, grade, ',');
   ss.get();
   getline(ss, player, ',');
   ss.get();
   getline(ss, manufacturer, '\n');
   this->player = player;
   this->grade = grade;
   this->manufacuturer = manufacturer;
   this->year = atoi(year.c_str());
}

// increases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void SportsCard::add(){
   this->amount++;
}

// decreases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void SportsCard::minus() {
   this->amount--;
}

// returns amount of object currently in inventory
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post object's amount data memeber is returned
// @return int amount of an object in inventory
int SportsCard::getAmount() const{
   return this->amount;
}

// checks to see if left side object is equal to right side object
// @pre two instantiated SportsCard objects
// @post return of true or false
// @return true if objects are equal otherwise false
bool SportsCard::operator==(const Comparable& right) const{
   const SportsCard& right_card = static_cast<const SportsCard&>(right);
   if (this->player == right_card.player) {
      if (this->year == right_card.year) {
         if (this->manufacuturer == right_card.manufacuturer) {
            return this->grade == right_card.grade;
         }
      }
   }
   return false; // they are not equal
}

// Checks to see if two Objects are not equal
// @pre 2 instantiated SportsCard objects
// @post return of true or false 
// @return boolen of true if objects are not equal otherwise false
bool SportsCard::operator!=(const Comparable& right) const{
   const SportsCard& right_card = static_cast<const SportsCard&>(right);
   return !(*this == right_card);
}

// Checks to see if left side object is less than the right side object
// @pre 2 instantiated SportsCard objects
// @post return of true or false 
// @return boolen of true if left side is smaller than the right else false
bool SportsCard::operator<(const Comparable& right) const{
   const SportsCard& right_card = static_cast<const SportsCard&>(right);
   if (this->player != right_card.player) {
      return this->player < right_card.player;
   }
   if (this->year != right_card.year) {
      return this->year < right_card.year;
   }
   if (this->manufacuturer != right_card.manufacuturer) {
      return this->manufacuturer < right_card.manufacuturer;
   }
   if (this->grade != right_card.grade) {
      return this->grade < right_card.grade;
   }
   return false; // they are equal
}

// Checks to see if left side object is greater than the right side
// @pre  2 instantiated SportsCard objects
// @post return of true or false 
// @return boolean of true if left side is greater than the right else false
bool SportsCard::operator>(const Comparable& right) const{
   const SportsCard& right_card = static_cast<const SportsCard&>(right);
   if (this->player != right_card.player) {
      return this->player > right_card.player;
   }
   if (this->year != right_card.year) {
      return this->year > right_card.year;
   }
   if (this->manufacuturer != right_card.manufacuturer) {
      return this->manufacuturer > right_card.manufacuturer;
   }
   if (this->grade != right_card.grade) {
      return this->grade > right_card.grade;
   }
   return false; // they are equal
}