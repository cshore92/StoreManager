// @file Customer.h
// @author Cameron Shore
// @date 21-Feb-20
// This file holds declarations for Customer class
// Features:
//    Unique ID for each customer object.
// 
//    Vector for holding transaction history of the customer.
// 
//    Capability to print transaction history to cout.
// 
//    Capability to compare customer objects
// 
//    Capability to deep copy Customer objects
// 
//    Capability to input data and output data into and out of customer object
// 
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

#pragma once
#include <vector>
#include <string>
#include "Comparable.h"
using namespace std;

class Customer : public Comparable {
private:
   string name = "";
   int number = 0;
   vector<string> history;

public:

   // Destructor
   // removes data from data memebers
   // @pre instantiated customer object with data stored in it's memebers
   // @post data is removed from its members
   // @return nothing
   ~Customer();

   // sets the name of the customer object
   // @pre instantiated customer object, string parameter argument
   // @post customer's name data member is set to passed in string parameter
   // @return nothing
   void setName(const string);

   // sets the customer ID
   // @pre instantiated customer object, int parameter argument
   // @post customer's number data member is set to passed in int argument
   // @return nothing
   void setNumber(const int);

   // adds transaction to the customers history vector
   // @pre instantiated customer object, string parameter argument
   // @post passed in string transaction is pushed onto the back of the history
   // vector
   // @return nothing
   void addTransaction(const string);

   // outputs contents of history vector to cout
   // @pre customer obj must be instantiated
   // @post contents of history vector are output to cout
   // @return nothing
   void Display() const;

   // creates a deep copy of the object
   // @pre instantiated customer object with data in it
   // @post deep copy of passed in customer object
   // @return pointer to the deep copied object
   virtual Comparable* clone(const Comparable&);

   // checks to see if left side object is equal to right side object
   // @pre two instantiated Customer objects
   // @post return of true or false
   // @return true if objects are equal otherwise false
   virtual bool operator==(const Comparable&) const;

   // Checks to see if two Customer Objects are not equal
   // @pre 2 instantiated Customer objects
   // @post return of true or false 
   // @return boolen of true if objects are not equal otherwise false
   virtual bool operator!=(const Comparable&) const;

   // Checks to see if left side object is less than the right side object
   // @pre 2 instantiated Customer objects
   // @post return of true or false 
   // @return boolen of true if left side is smaller than the right else false
   virtual bool operator<(const Comparable&) const;

   // Checks to see if left side object is greater than the right side
   // @pre  2 instantiated Customer objects
   // @post return of true or false 
   // @return boolean of true if left side is greater than the right else false
   virtual bool operator>(const Comparable&) const;

   // Prints contents of object to an output stream
   // @pre an instance of a Customer object
   // @post output stream with contents of Customer object
   // @return  ostream
   virtual void print() const;
};


