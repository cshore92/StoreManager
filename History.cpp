// @file History.cpp
// @author Cameron Shore
// @date 07-Mar-21
// This file holds definitions for History class
// Features:
//       Command Patter to:
//       Display all cutomers transaction histories
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#include "History.h"

// Command pattern method that calls history() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post all customers (in alphabetical order) history vector is output to cout
// @return nothing
void History::execute(const ShopManager* store, const string input) const{
   store->displayAllCustomers();
}