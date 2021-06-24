// @file Display.cpp
// @author Cameron Shore
// @date 07-Mar-21
// This file holds definitions for Display class
// Features:
//       Command Pattern to:
//       Display the entire store's inventory in pre-determined format
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#include "Display.h"

// Command pattern method that calls display() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post entire inventory is displayed to cout by Coins, then comics, and lastly
// sportscards
// @return nothing
void Display::execute(const ShopManager* store, const string input) const{
   store->displayInventory();
}