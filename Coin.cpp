// @file Coin.cpp
// @author Cameron Shore
// @date 06-Mar-21
// this holds defintions for Coin class
// Features:
//    Capability to create an instance of Coin object
// 
//    Capability to buy - increase amount of Coin obj in inventory by 1
// 
//    Capability to sell - decrease amount of Coin obj in inventory by 1
// 
//    Capability to display - Displays the Coin classes data members to
//    the cout.
// 
//    Capability to input data into the the Coin object
// 
//    Capability to deep copy Coin objects
// 
//    Comparison between Coin objecs 
//
// Assumptions:
//    Files for creating inventory, and transactions will be formatted
//    appropriately and will have only valid contents
//
//    The shop inventory will have 1 SearchTree, and 1 factory method for Coin
//    objects.

#include "Coin.h"
using namespace std;


// destructor
// removes data from data members
// @pre instantiated Coin object with data in its members
// @post data removed from it's memebers
// @return nothing
Coin::~Coin() {
   amount = 0;
   grade = 0;
   year = 0;
   type = "";
}

// creates and instance of the Coin object
// @pre Initialized ShopManager
// @post object is initialized 
// @return const pointer to initialized object
Collectible* Coin::create() const{
   Collectible* c = new Coin;
   return c;
}

// outputs Coin object data members to cout
// @pre Initialized ShopManager, and Initialized method had been ran
// @post object's data members are output to cout in specified order
// @return nothing
void Coin::print() const{
   cout << amount << ", " << type << ", " << year << ", " << grade << endl;
}

Comparable* Coin::clone(const Comparable& copy){
   const Coin& copyFrom = static_cast<const Coin&>(copy);
   Coin* newCoin = new Coin;
   newCoin->amount = copyFrom.amount;
   newCoin->year = copyFrom.year;
   newCoin->grade = copyFrom.grade;
   newCoin->type = copyFrom.type;
   return newCoin;
}

// intializes a Coin object with contents from the ifstream
// @pre instantiated Coin object, valid ifstream data
// @post ifstream data is input into the Coin object data members
// @return nothing
void Coin::initialize(ifstream& input){
   string year = "";
   string grade = "";
   string amount = "";
   string description = "";
   getline(input, amount, ',');
   input.get();
   getline(input, year, ',');
   input.get();
   getline(input, grade, ',');
   input.get();
   getline(input, description, '\n');
   this->amount = atoi(amount.c_str());
   this->year = atoi(year.c_str());
   this->type = description;
   this->grade = atoi(grade.c_str());
}

// sets object's data members with string paramater contents
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post objects data members are filled with data from string argument
// @return nothing
void Coin::setParam(const string data){
   string year = "";
   string grade = "";
   string description = "";
   stringstream ss;

   ss << data;
   ss.ignore(3, ' ');
   getline(ss, year, ',');
   ss.get();
   getline(ss, grade, ',');
   ss.get();
   getline(ss, description, '\n');
   this->year = atoi(year.c_str());
   this->grade = atoi(grade.c_str());
   this->type = description;
}

// increases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void Coin::add(){
   this->amount++;
}

// decreases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void Coin::minus() {
   this->amount--;
}

// returns amount of object currently in inventory
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post object's amount data memeber is returned
// @return int amount of an object in inventory
int Coin::getAmount() const {
   return this->amount;
}

// checks to see if left side object is equal to right side object
// @pre two instantiated Coin objects
// @post return of true or false
// @return true if objects are equal otherwise false
bool Coin::operator==(const Comparable& right) const{
   const Coin& right_coin = static_cast<const Coin&>(right);
   if (this->type == right_coin.type) {
      if (this->year == right_coin.year) {
         return this->grade == right_coin.grade;
      }
   }
   return false; // they are not equal
}

// Checks to see if two Objects are not equal
// @pre 2 instantiated Coin objects
// @post return of true or false 
// @return boolen of true if objects are not equal otherwise false
bool Coin::operator!=(const Comparable& right) const{
   const Coin& right_coin = static_cast<const Coin&>(right);
   return !(*this == right_coin);
}

// Checks to see if left side object is less than the right side object
// @pre 2 instantiated Coin objects
// @post return of true or false 
// @return boolen of true if left side is smaller than the right else false
bool Coin::operator<(const Comparable& right) const{
   const Coin& right_coin = static_cast<const Coin&>(right);
   if (this->type != right_coin.type) {
      return this->type < right_coin.type;
   }
   if (this->year != right_coin.year) {
      return this->year < right_coin.year;
   }
   if (this->grade != right_coin.grade) {
      return this->grade < right_coin.grade;
   }
   return false; // they are equal
}

// Checks to see if left side object is greater than the right side
// @pre  2 instantiated Coin objects
// @post return of true or false 
// @return boolean of true if left side is greater than the right else false
bool Coin::operator>(const Comparable& right) const{
   const Coin& right_coin = static_cast<const Coin&>(right);
   if (this->type != right_coin.type) {
      return this->type > right_coin.type;
   }
   if (this->year != right_coin.year) {
      return this->year > right_coin.year;
   }
   if (this->grade != right_coin.grade) {
      return this->grade > right_coin.grade;
   }
   return false; // they are equal
}