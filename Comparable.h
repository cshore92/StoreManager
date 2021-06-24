// @file Comparable.h
// @author Cameron Shore
// @date 04-Jan-21
// This file holds the declarations for Comparable class
// Features:
// 
//    Allows for comparison of Comparable objects via data member
// 
//    Allows input and output of Comparable data memeber
// 
//    Capability to deep copy Comparable objects
//
// Assumptions:
//    user will insert a valid char using >>
// 
//    char will not be ' ' (whitespace)
// 
//    output (<<) will display char on 1 line and will not do a new line
//    operation
// 
//    Comparable pointer Objects  properly dereferenced when streaming in char.

#pragma once
#include <iostream>
using namespace std;

class Comparable{
private:
   char character = ' ';

public:

   // Destructor
   // removes data from Comparable data member
   // @pre Instantiated comparable object with data in it's member
   // @post removal of data from Comparable data member
   // @return nothing
   virtual ~Comparable();

   // creates a deep copy of the object
   // @pre instantiated comparable object with data in it
   // @post deep copy of passed in comparable object
   // @return pointer to the deep copied object
   virtual Comparable* clone(const Comparable&) = 0;
  
   // Checks to see if two Comparable Objects are equal  
   // @pre  2 Comparable objects wtih == between them
   // @post none 
   // @return boolean of true if objects are equal otherwise false
   virtual bool operator==(const Comparable&) const;

   // Checks to see if two Comparable Objects are not equal
   // @pre  2 Comparable objects with != between them
   // @post none 
   // @return boolen of true if objects are not equal otherwise false
   virtual bool operator!=(const Comparable&) const;

   // Checks to see if left side Comparable is less than the right side
   // @pre 2 Comparable objects with < between them
   // @post none
   // @return boolen of true if left side is smaller than the right else false
   virtual bool operator<(const Comparable&) const;

   // Checks to see if left side Comparable is greater than the right side
   // @pre  2 Comparable objcets with > between them
   // @post none
   // @return boolean of true if left side is greater than the right else false
   virtual bool operator>(const Comparable&) const;

   // prints out contents of comparable obj
   // @pre instantiated comparable obj
   // @post contents of comprabale obj are sent to cout
   // @return nothing
   virtual void print() const;

   // Prints contents of Comparable object to an output stream
   // @pre  Comparable object with char data in it
   // @post output stream with contents of Comparable object
   // @return  ostream
   friend ostream& operator<< (ostream&, const Comparable&);

   // Streams char character into Comparabale object
   // @pre  Comparable object, istream with char
   // @post Comparable object, with char data from istream
   // @return istream
   friend istream& operator>> (istream&, Comparable&);
   
};
