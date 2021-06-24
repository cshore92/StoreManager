// @file Buy.cpp
// @author Cameron Shore
// @date 07-Mar-21
// This file holds definitions for Buy class
// Features:
//       Command Pattern to:
//       Capability to increase any object in the stores inventory by 1
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#include "Buy.h"

// Command pattern method that calls buy() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post Comparable inventory items amount is increased by 1, and the transaction
// is logged into the appropriate customers history vector, or error is sent
// to cout and transaction is not logged.
// @return nothing
void Buy::execute(const ShopManager* store, const string input) const{
   string number = "";
   string type = "";
   int custID = 0;

   // input is kept as a whole string so the transaction can be stored in 
   // customer transaction history, ss allows for easier parsing of the string
   stringstream ss;
   ss << input;
   ss.ignore(3, ' ');
   getline(ss, number, ',');
   ss.get(); // remove ' '
   getline(ss, type, '\n');
   custID = atoi(number.c_str());
   store->buyItem(type, custID, input);
}