// @file Comic.cpp
// @author Cameron Shore
// @date 06-Mar-21
// This file holds definitions for Comic class
// Features:
//    Capability to create an instance of Comic object
// 
//    Capability to buy - increase amount of Comic obj in inventory by 1
// 
//    Capability to sell - decrease amount of Comic obj in inventory by 1
// 
//    Capability to display - Displays the Comic classes data members to
//    the cout.
// 
//    Capability to input data into the the Comic object
// 
//    Capability to deep copy Comic objects
// 
//    Comparison between Comic objecs 
//
// Assumptions:
//    Files for creating inventory, and transactions will be formatted
//    appropriately and will have only valid contents
//
//    The shop inventory will have 1 SearchTree, and 1 factory method for Comic
//    objects.

#include "Comic.h"

// Destructor
// removes data from the Comics data members
// @pre instatiated Comic object with data in it's members
// @post data is removed from it's members
// @return nothing
Comic::~Comic(){
   publisher = "";
   title = "";
   year = 0;
   grade = "";
   amount = 0;
}

// creates and instance of the Comic object
// @pre Initialized ShopManager
// @post object is initialized 
// @return const pointer to initialized object
Collectible* Comic::create() const{
   Collectible* c = new Comic;
   return c;
}

// outputs Comic object data members to cout
// @pre Initialized ShopManager, and Initialized method had been ran
// @post object's data members are output to cout in specified order
// @return nothing
void Comic::print() const{
   cout << amount << ", " << publisher << ", " << title << ", " << year << ", "
            << grade << endl;
}

// intializes a Comic object with contents from the ifstream
// @pre instantiated Comic object, valid ifstream data
// @post ifstream data is input into the Comic object data members
// @return nothing
void Comic::initialize(ifstream& inputFile){
   string year = "";
   string grade = "";
   string publisher = "";
   string title = "";
   string amount = "";
   getline(inputFile, amount, ',');
   inputFile.get();
   getline(inputFile, year, ',');
   inputFile.get();
   getline(inputFile, grade, ',');
   inputFile.get();
   getline(inputFile, title, ',');
   inputFile.get();
   getline(inputFile, publisher, '\n');
   this->amount = atoi(amount.c_str());
   this->year = atoi(year.c_str());
   this->publisher = publisher;
   this->title = title;
   this->grade = grade;
}

// sets object's data members with string paramater contents
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post objects data members are filled with data from string argument
// @return nothing
void Comic::setParam(const string data){
   string year = "";
   string grade = "";
   string publisher = "";
   string title = "";
   stringstream ss;

   ss << data;
   ss.ignore(3, ' ');
   getline(ss, year, ',');
   ss.get();
   getline(ss, grade, ',');
   ss.get();
   getline(ss, title, ',');
   ss.get();
   getline(ss, publisher, '\n');
   this->year = atoi(year.c_str());
   this->grade = grade;
   this->title = title;
   this->publisher = publisher;
}

// increases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void Comic::add(){
   this->amount++;
}

// decreases amount in inventory by 1
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran
// @post inventory item amount increased by 1
// @return nothing.
void Comic::minus() {
   this->amount--;
}

// returns amount of object currently in inventory
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post object's amount data memeber is returned
// @return int amount of an object in inventory
int Comic::getAmount() const{
   return this->amount;
}

Comparable* Comic::clone(const Comparable& copy){
   const Comic& copyFrom = static_cast<const Comic&>(copy);
   Comic* newComic = new Comic;
   newComic->amount = copyFrom.amount;
   newComic->year = copyFrom.year;
   newComic->grade = copyFrom.grade;
   newComic->title = copyFrom.title;
   newComic->publisher = copyFrom.publisher;
   return newComic;
}

// checks to see if left side object is equal to right side object
// @pre two instantiated Comic objects
// @post return of true or false
// @return true if objects are equal otherwise false
bool Comic::operator==(const Comparable& right) const{
   const Comic& right_comic = static_cast<const Comic&>(right);
   if (this->publisher == right_comic.publisher) {
      if (this->title == right_comic.title) {
         if (this->year == right_comic.year) {
            return this->grade == right_comic.grade;
         }
      }
   }
   return false;
}

// Checks to see if two Comic Objects are not equal
// @pre 2 instantiated Comic objects
// @post return of true or false 
// @return boolen of true if objects are not equal otherwise false
bool Comic::operator!=(const Comparable& right) const{
   const Comic& right_comic = static_cast<const Comic&>(right);
   return !(*this == right_comic);
}

// Checks to see if left side object is less than the right side object
// @pre 2 instantiated Comic objects
// @post return of true or false 
// @return boolen of true if left side is smaller than the right else false
bool Comic::operator<(const Comparable& right) const{
   const Comic& right_comic = static_cast<const Comic&>(right);
   if (this->publisher != right_comic.publisher) {
      return this->publisher < right_comic.publisher;
   }
   if (this->title != right_comic.title) {
      return this->title < right_comic.title;
   }
   if (this->year != right_comic.year) {
      return this->year < right_comic.year;
   }
   if (this->grade != right_comic.grade) {
      return this->grade < right_comic.grade;
   }
   return false; // they are equal
}

// Checks to see if left side object is greater than the right side
// @pre  2 instantiated Comic objects
// @post return of true or false 
// @return boolean of true if left side is greater than the right else false
bool Comic::operator>(const Comparable& right) const{
   const Comic& right_comic = static_cast<const Comic&>(right);
   if (this->publisher != right_comic.publisher) {
      return this->publisher > right_comic.publisher;
   }
   if (this->title != right_comic.title) {
      return this->title > right_comic.title;
   }
   if (this->year != right_comic.year) {
      return this->year > right_comic.year;
   }
   if (this->grade != right_comic.grade) {
      return this->grade > right_comic.grade;
   }
   return false;
}