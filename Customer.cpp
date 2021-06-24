// @file Customer.cpp
// @author Cameron Shore
// @date 06-Mar-21
// This file hold definitions for Customer class
// Features:
//    Unique ID for each customer object.
// 
//    Vector for holding transaction history of the customer.
// 
//    Capability to print transaction history to cout.
// 
//    Capability to compare customer objects
// 
//    Capability to deep copy customer objects
// 
//    Capability to input data and output data into and out of customer object
//
// Assumptions:
//    ID will not be over 3 Digits.
// 
//    Customer names will consists of strings only.
// 
//    Customer files and Transaction files will be formatted appropriately and
//    only contain valid data.
// 
//    No customers will have the same exact name or number.

#include "Customer.h"

// Destructor
// removes data from data memebers
// @pre instantiated customer object with data stored in it's memebers
// @post data is removed from its members
// @return nothing
Customer::~Customer() {
   name = "";
   number = 0;
   history.clear();
}

// outputs contents of history vector to cout
// @pre customer obj must be instantiated
// @post contents of history vector are output to cout
// @return nothing
void Customer::Display() const {
   cout << name << endl;
   for (unsigned int i = 0; i < history.size(); i++) {
      cout << history[i] << endl;
   }
   cout << endl;
}

// sets the name of the customer object
// @pre instantiated customer object, string parameter argument
// @post customer's name data member is set to passed in string parameter
// @return nothing
void Customer::setName(const string nameSet){
   this->name = nameSet;
}

// sets the customer ID
// @pre instantiated customer object, int parameter argument
// @post customer's number data member is set to passed in int argument
// @return nothing
void Customer::setNumber(const int numberSet){
   this->number = numberSet;
}

// adds transaction to the customers history vector
// @pre instantiated customer object, string parameter argument
// @post passed in string transaction is pushed onto the back of the history
// vector
// @return nothing
void Customer::addTransaction(const string transaction){
   history.push_back(transaction);
}

// creates a deep copy of the object
// @pre instantiated customer object with data in it
// @post deep copy of passed in customer object
// @return pointer to the deep copied object
Comparable* Customer::clone(const Comparable& copy){
   const Customer& copyFrom = static_cast<const Customer&>(copy);
   Customer* newCust = new Customer;
   newCust->name = copyFrom.name;
   newCust->number = copyFrom.number;
   for (int i = 0; i < copyFrom.history.size(); i++) {
      newCust->history[i] = copyFrom.history[i];
   }
   return newCust;
}

// checks to see if left side object is equal to right side object
// @pre two instantiated Customer objects
// @post return of true or false
// @return true if objects are equal otherwise false
bool Customer::operator==(const Comparable& right) const {
   const Customer& right_cust = static_cast<const Customer&>(right);
   if (this->name == right_cust.name) {
      return this->number == right_cust.number;
   }
   return false;
}

// Checks to see if two Customer Objects are not equal
// @pre 2 instantiated Customer objects
// @post return of true or false 
// @return boolen of true if objects are not equal otherwise false
bool Customer::operator!=(const Comparable& right) const {
   const Customer& right_cust = static_cast<const Customer&>(right);
   return !(*this == right_cust);
}

// Checks to see if left side object is less than the right side object
// @pre 2 instantiated Customer objects
// @post return of true or false 
// @return boolen of true if left side is smaller than the right else false
bool Customer::operator<(const Comparable& right) const {
   const Customer& right_cust = static_cast<const Customer&>(right);
   return this->name < right_cust.name;
}

// Checks to see if left side object is greater than the right side
// @pre  2 instantiated Customer objects
// @post return of true or false 
// @return boolean of true if left side is greater than the right else false
bool Customer::operator>(const Comparable& right) const {
   const Customer& right_cust = static_cast<const Customer&>(right);
   return this->name > right_cust.name;
}

// Prints contents of object to an output stream
// @pre an instance of a Customer object
// @post output stream with contents of Customer object
// @return  ostream
void Customer::print() const{
   this->Display();
}
   