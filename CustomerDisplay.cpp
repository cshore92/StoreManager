// @file CustomerDisplay.cpp
// @author Cameron Shore
// @date 07-Mar-21
// This file holds definitions for CustomerDisplay class
// Features:
//       Command Pattern to:
//       Display 1 customer and their transaction history
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#include "CustomerDisplay.h"

// Command pattern method that calls history() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post specified customer comparable object's history vector is displayed to
// cout
// @return nothing
void CustomerDisplay::execute(const ShopManager* store, const string input) const{
   string number = "";
   int custID = 0;
   stringstream ss;
   ss << input;
   ss.ignore(3, ' ');
   getline(ss, number, '\n');
   custID = atoi(number.c_str());
   store->displayCustomerHistory(custID);
}