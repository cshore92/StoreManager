// @file main.cpp
// @author Cameron Shore
// @date 20-Feb-20
// 
// main method for program 4
// this method reads in 3 files. One representing
// the starting inventory of the store. One reprensenting a store's customer
// database, and one the transactions that are happening.

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ShopManager.h"
using namespace std;

int main() {
   {
      ifstream infile("hw4inventory.txt");
      ifstream infile2("hw4customers.txt");
      ifstream infile3("hw4commands.txt");

      ShopManager mngr;

      // Initialization of inventory
      if (!infile) {
         cerr << "initialization file could not be opened." << endl;
         return 1;
      }
      cout << "------Initializing------" << endl;
      mngr.initialize(infile);
      cout << "------Done------" << endl;

      // Customer database initialization
      if (!infile2) {
         cerr << "Customer file could not be opened." << endl;
         return 1;
      }
      cout << "------Building Customer Database------" << endl;
      mngr.customerInitial(infile2);
      cout << "------Done------" << endl;

      // Transaction/Command file
      if (!infile3) {
         cerr << "Transaction file could not be opened." << endl;
         return 1;
      }
      cout << "------Transactions Start------" << endl;
      mngr.transactions(infile3);
      cout << "------Transactions End------" << endl;
   }
   _CrtDumpMemoryLeaks(); // mem leak check
   return 0;
 }