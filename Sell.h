// @file Sell.h
// @author Cameron Shore
// @date 07-Mar-21
// This file holds declarations for Sell class
// Features:
//       Command Pattern to:
//       Capability to decrease any object in the stores inventory by 1
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//
#pragma once

#include "ShopManager.h"
#include "Transaction.h"

// Command pattern method that calls sell() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post Comparable inventory items amount is decreased by 1, and the transaction
// is logged into the appropriate customers history vector
// @return nothing
class Sell : public Transaction {

   virtual void execute(const ShopManager*, const string) const;
};