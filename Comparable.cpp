// @file Comparable.cpp
// @author Cameron Shore
// @date 06-Jan-20
// This holds definitions for Comparable class
// Features:
//    Allows for comparison of Comparable objects via data member
// 
//    Allows input and output of Comparable data memeber
// 
//    Capability to deep copy coparable objects
//
// Assumptions:
//    user will insert a valid char using >>
// 
//    char will not be ' ' (whitespace)
// 
//    output (<<) will display char on 1 line and will not do a new line 
//    operation
// 
//    Comparable pointer Objects properly dereferenced when streaming in char.

#include "Comparable.h"

// Destructor
// removes data from Comparable data member
// @pre Instantiated comparable object with data in it's member
// @post removal of data from Comparable data member
// @return nothing
Comparable::~Comparable(){
   character = ' ';
}

// Checks to see if two Comparable Objects are equal  
// @pre  2 Comparable objects wtih == between them
// @post none 
// @return boolean of true if objects are equal otherwise false
bool Comparable::operator==(const Comparable& right) const{
   return this->character == right.character;
}

// Checks to see if two Comparable Objects are not equal
// @pre  2 Comparable objects with != between them
// @post none 
// @return boolen of true if objects are not equal otherwise false
bool Comparable::operator!=(const Comparable& right) const{
   return this->character != right.character;
}

// Checks to see if left side Comparable is less than the right side
// @pre 2 Comparable objects with < between them
// @post none
// @return boolen of true if left side is smaller than the right else false
bool Comparable::operator<(const Comparable& right) const{
   return this->character < right.character;
}

// Checks to see if left side Comparable is greater than the right side
// @pre  2 Comparable objcets with > between them
// @post none
// @return boolean of true if left side is greater than the right else false
bool Comparable::operator>(const Comparable& right) const{
   return this->character > right.character;
}


// Prints contents of Comparable object to an output stream
// @pre  Comparable object with char data in it
// @post output stream with contents of Comparable object
// @return  ostream
 ostream& operator<<(ostream& output, const Comparable& comparObj){
    comparObj.print();
    return output;
}

 // prints out contents of comparable obj
// @pre instantiated comparable obj
// @post contents of comprabale obj are sent to cout
// @return nothing
 void Comparable::print() const{
    cout << this->character << endl;
 }


// Streams char character into Comparabale object
// @pre  Comparable object, istream with char
// @post Comparable object, with char data from istream
// @return istream
istream& operator>>(istream& input, Comparable& charInput){
   input >> charInput.character;
   return input;
}

