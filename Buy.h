// @file Buy.h
// @author Cameron Shore
// @date 07-Mar-21
// This file holds declarations for Buy class
// Features:
//       Command Patter to:
//       Capability to increase any object in the stores inventory by 1
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#pragma once
#include "Transaction.h"
#include "ShopManager.h"

// Command pattern method that calls buy() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post Comparable inventory items amount is increased by 1, and the transaction
// is logged into the appropriate customers history vector, or error is sent
// to cout and transaction is not logged.
// @return nothing
class Buy : public Transaction {

   virtual void execute(const ShopManager*, const string) const;
};