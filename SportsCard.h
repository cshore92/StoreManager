// @file SportsCard.h
// @author Cameron Shore
// @date 21-Feb-20
// This file holds declarations for SportsCard class
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

#pragma once
#include "Collectible.h"
using namespace std;

class SportsCard : public Collectible {

private:
   string player = "";
   string manufacuturer = "";
   int year = 0;
   string grade = "";
   int amount = 0;

public:

   // destructor
   // removes data from sportscard member variables
   // @pre instantiated sportscard object with data in it's members
   // @post data is removed from member variables
   // @ return nothing.
   ~SportsCard();

   // sets object's data members with string paramater contents
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran, and a valid commands file
   // @post objects data members are filled with data from string argument
   // @return nothing
   virtual void setParam(const string);
   
   // increases amount in inventory by 1
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran
   // @post inventory item amount increased by 1
   // @return nothing.
   virtual void add();

   // decreases amount in inventory by 1
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran
   // @post inventory item amount increased by 1
   // @return nothing.
   virtual void minus();

   // returns amount of object currently in inventory
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran, and a valid commands file
   // @post object's amount data memeber is returned
   // @return int amount of an object in inventory
   virtual int getAmount() const;

   // outputs SportsCard object data members to cout
   // @pre Initialized ShopManager, and Initialized method had been ran
   // @post object's data members are output to cout in specified order
   // @return nothing
   virtual void print() const;

   // creates and instance of the SportsCard object
   // @pre Initialized ShopManager
   // @post object is initialized 
   // @return const pointer to initialized object
   virtual Collectible* create() const;

   // creates a deep copy of the object
   // @pre instantiated SportsCard object with data in it
   // @post deep copy of passed in SportsCard object
   // @return pointer to the deep copied object
   virtual Comparable* clone(const Comparable&);

   // intializes a SportsCard object with contents from the ifstream
   // @pre instantiated SportsCard object, valid ifstream data
   // @post ifstream data is input into the SportsCard object data members
   // @return nothing
   virtual void initialize(ifstream&);

   // checks to see if left side object is equal to right side object
   // @pre two instantiated SportsCard objects
   // @post return of true or false
   // @return true if objects are equal otherwise false
   virtual bool operator==(const Comparable&) const;

   // Checks to see if two Objects are not equal
   // @pre 2 instantiated SportsCard objects
   // @post return of true or false 
   // @return boolen of true if objects are not equal otherwise false
   virtual bool operator!=(const Comparable&) const;

   // Checks to see if left side object is less than the right side object
   // @pre 2 instantiated SportsCard objects
   // @post return of true or false 
   // @return boolen of true if left side is smaller than the right else false
   virtual bool operator<(const Comparable&) const;

   // Checks to see if left side object is greater than the right side
   // @pre  2 instantiated SportsCard objects
   // @post return of true or false 
   // @return boolean of true if left side is greater than the right else false
   virtual bool operator>(const Comparable&) const;

};