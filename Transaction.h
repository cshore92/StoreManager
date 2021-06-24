// @file Transaction.h
// @author Cameron Shore
// @date 06-Mar-21
// This file holds declarations for transaction class
// Features:
//    Pure virtual class for excuting any number of commands based off derived
//    classes using a command table.
// 
// Assumptions:
//    Command file will be formatted correctly with valid data:
// 
//    *********************Transaction file************************************
//    *    Transaction denoted by first character on the line (B,S,C,H,D)     *
//    *    depending on which operation is wanted depends on what line        *
//    *    line contents are needed.                                          *
//    *                     (H & D) only need the letter                      *
//    *  C requires customerID to follow it separated by a comma and a space  *
//    *      B & S require parameters mentioned in the initialization file    *
//    *************************************************************************

#pragma once
#include <string>
#include <sstream>


using namespace std;
class ShopManager;
class Transaction {
public:
   // perform a transaction based on Collectible object, and transaction file
   // stream
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran, and a valid commands file
   // @post depending on which transaction is called a certain transaction
   // is performed see transaction derived classes for more information
   // @return nothing
   virtual void execute(const ShopManager*, const string) const = 0;
};
