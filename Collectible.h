// @file Collectible.h
// @author Cameron Shore
// @date 21-Feb-20
// This file holds declarations for Collectible class
// Features:
//    Pure Virtual Class for all items being stored in the store inventory 
//
//    Capability to create an instance of Collectible object
// 
//    Capability to buy - increase amount of Collectible obj in inventory by 1
// 
//    Capability to sell - decrease amount of Collectible obj in inventory by 1
// 
//    Capability to display - Displays the Collectible classes data members to
//    the cout.
// 
//    Capability to input data into the the Collectible object
// 
//    Capability to deep copy Collectible objects
// 
//    Comparison between Collectible objecs 
//
// Assumptions:
//    Files for creating inventory, and transactions will be formatted
//    appropriately and will have only valid contents
// 
//    All derived classes will have methods declared in this class
//
//    The shop inventory will have a SearchTree, and factory method for each 
//    type of Collectible.

#pragma once
#include <sstream>
#include "Comparable.h"
#include <string>
#include <fstream>
using namespace std;

class Collectible : public Comparable {
public:

   // sets object's data members with string paramater contents
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran, and a valid commands file
   // @post objects data members are filled with data from string argument
   // @return nothing
   virtual void setParam(const string) = 0;

   // increases amount in inventory by 1
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran
   // @post inventory item amount increased by 1
   // @return nothing.
   virtual void add() = 0;

   // decreases amount in inventory by 1
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran
   // @post inventory item amount increased by 1
   // @return nothing.
   virtual void minus() = 0;

   // returns amount of object currently in inventory
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran, and a valid commands file
   // @post object's amount data memeber is returned
   // @return int amount of an object in inventory
   virtual int getAmount() const = 0;

   // creates and instance of the object
   // @pre Initialized ShopManager
   // @post object is initialized 
   // @return const pointer to initialized object
   virtual Collectible* create() const = 0;

   // creates a deep copy of the object
   // @pre instantiated collectible object with data in it
   // @post deep copy of passed in Collectible object
   // @return pointer to the deep copied object
   virtual Comparable* clone(const Comparable&) = 0;

   // intializes a collectible object with contents from the ifstream
   // @pre instantiated collectible object, ifstream data
   // @post ifstream data is input into the colletible object data members
   // @return nothing
   virtual void initialize(ifstream&) = 0;

   // checks to see if left side object is equal to right side object
   // @pre two instantiated collectible objects
   // @post return of true or false
   // @return true if objects are equal otherwise false
   virtual bool operator==(const Comparable&) const = 0;

   // Checks to see if two Objects are not equal
   // @pre 2 instantiated collectible objects
   // @post return of true or false 
   // @return boolen of true if objects are not equal otherwise false
   virtual bool operator!=(const Comparable&) const = 0;

   // Checks to see if left side object is less than the right side object
   // @pre 2 instantiated collectible objects
   // @post return of true or false 
   // @return boolen of true if left side is smaller than the right else false
   virtual bool operator<(const Comparable&) const = 0;

   // Checks to see if left side object is greater than the right side
   // @pre  2 instantiated collectible objects
   // @post return of true or false 
   // @return boolean of true if left side is greater than the right else false
   virtual bool operator>(const Comparable&) const = 0;

   // prints contents of Collectible objects data members to cout
   // @pre Initialized ShopManager, and Initialized method had been ran
   // @post object's data members are output to cout in specified order
   // @return nothing
   virtual void print() const = 0;

};