// @file CustomerDisplay.h
// @author Cameron Shore
// @date 07-Mar-21
// This file holds declarations for CustomerDisplay class
// Features:
//       Command Pattern to:
//       Display 1 customer and their transaction history
//
// Assumptions:
// 
//       Transaction/Command file is formatted properly with valid data
//

#pragma once

#include "Transaction.h"
#include "ShopManager.h"
using namespace std;
// Command pattern method that calls history() function for comparable obj
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran, and a valid commands file
// @post specified customer comparable object's history vector is displayed to
// cout
// @return nothing
class CustomerDisplay : public Transaction {

   virtual void execute(const ShopManager*, const string) const;
};