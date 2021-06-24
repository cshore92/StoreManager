// @file ShopManager.h
// @author Cameron Shore
// @date 21-Feb-20
// This file holds declarations for ShopManager class
// Features:
//    Automatic handling of a the shop's inventory via 3 files including:
//    Creation of inventory based off initial file.
//    Creation of customer "database" from initial file.
//    Handling transaction between customer and inventory based off input file
//    
//    Transactions include: Buying and Selling an item, Displaying the store's
//    entire inventory. Displaying indivdual customer's transaction history,
//    and displaying all customers transaction history
//    
//    ShopManager will NOT be copyable through assignment or copy constructor
//    this extends into each inventory, and customer data structure.
// 
//    Factory Methods and Command pattern tables for quick object creation and
//    transaction functions
// 
//    Separate SearchTree's for all items in inventory and customers
// 
//    Customer Table for quick access to customer informationa and history
//
// Assumptions:
//    All files will be formatted in a specific manner as mention below:
//    *********************Initialization file:******************************** 
//    *    type of item, number in inventory, year, grade, type/title/player, *
//    * publisher/manufacture (if necessary). Each field is separated by a    *
//    *                comma and a space. One per line                        *
//    *************************************************************************
//
//    *********************Customer file***************************************
//    *  3 digit customer ID, customer name (doesn't matter if Last name is   *
//    *               first or not). One per line                             *  
//    *************************************************************************
//
//    *********************Transaction file************************************
//    *    Transaction denoted by first character on the line (B,S,C,H,D)     *
//    *    depending on which operation is wanted depends on what line        *
//    *    line contents are needed.                                          *
//    *                     (H & D) only need the letter                      *
//    *  C requires customerID to follow it separated by a comma and a space  *
//    *      B & S require parameters mentioned in the initialization file    *
//    *************************************************************************
//    
//    All hash tables will be the same size always (enforced with hashTableSize
//    variable).
//
//    


#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Comparable.h"
#include "Customer.h"
#include "SearchTree.h"
#include "Transaction.h"
#include "Collectible.h"
#include "Coin.h"
#include "Comic.h"
#include "SportsCard.h"
#include "Collectible.h"
#include "Buy.h"
#include "Sell.h"
#include "Display.h"
#include "CustomerDisplay.h"
#include "History.h"
using namespace std;



class ShopManager {
private:

   // controls size of all hash tables in shop manager this is important for
   // destructor call, if you change individual tables with this variable
   // the destructor will need to be changed.
   const int HASH_TABLE_SIZE = 29; 

   // Hash table for dummy collectible derived classes
   vector<Collectible*> factoryTable{ HASH_TABLE_SIZE, nullptr};

   // CommandTable of transaction classes
   vector<Transaction*> transactTable{ HASH_TABLE_SIZE, nullptr };

   // Hash table for customer ID to name look up
   vector<Customer*> customerTable{1000, nullptr}; 

   // hash table pointing to appropriate collectible tree
   vector<SearchTree*> inventory{ HASH_TABLE_SIZE, nullptr};

   // SearchTree for sorting Customers by name
   SearchTree customers;

   // private method for deallocating memory on the heap
   // @pre instantiated shop manager with data on the heap
   // @post allocated memory is deleted from the heap
   // @return nothing
   void clear();

public:

   // Constructor
   // @pre nothing
   // @post ShopManager Object is instantiated, factoryTable is populated with
   // dummy objects to call methods to, customers is populated with blank
   // customer pointers, inventory points to an empty SearchTree, and 
   // transaction hash table is populated with transaction classes.
   // @return nothing
   ShopManager();
   

   // Destructor
   // @pre ShopManager object with allocated data on the heap
   // @post allocated data is deleted
   // @return nothing
   ~ShopManager();

   // fills a blank inventory with pre-set and formatted file containing 
   // specific items, their amounts, and appropriate data fields
   // @pre a file that is in proper format of: type of item, number in 
   // inventory, year, grade, type/title/player, publisher/manufacture (if 
   // necessary). Each field is separated by a comma and a space. One per line
   // @post each SearchTree is populated and sorted with the appropriate item
   // from the file. If invalid item type is in file, nothing will happen and 
   // will skip to the next line. If amount < 0 (0 is okay) item will not be
   // added to the inventory and error will be sent to cout.
   // @return nothing
   void initialize(ifstream&);
   
   // adds customer into customers table, then adds each customer
   // object into a SearchTree sorted by the which ever name is first in the 
   // file
   // @pre a file that is formatted in the proper way of: 3 digit customer ID, 
   // customer name (doesn't matter if Last name is first or not). One per line
   // @post customers table is populated with customer based off their
   // ID and customers are stored sorted in customers SearchTree. Customer
   // number is checked if it is less than 0 or greater than 999 customer wont
   // be added to database and error message will be output to cout
   // @return nothing
   void customerInitial(ifstream&);

   // performs transactions on the inventory and customer classes based on 
   // file contents
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize methods have been successfully ran.
   // file that is formatted in the proper way of one transacation per
   // line with the start of each line representing a specific action
   // @post depending on which transaction is requested, inventory amount
   // could be increased or decreased, customer history displayed, inventory
   // displayed to output, or all transactions displayed to output could 
   // happen. If invalid command in the file nothing wil happen and will skip
   // to the next line.
   // @return nothing
   void transactions(ifstream&);

   // increases objects amount by 1 if it is in inventory
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran. Valid transaction file
   // @post inventory item amount is increased by 1 transaction is stored in
   // customer transaction history, if item is not found in inventory, or if
   // collectible type is invalid error is sent to cout. If customer number 
   // doesn't point to a customer object, error will be sent to cout
   // @return nothing.
   void buyItem(const string, const int, const string) const;

   // decreases objects amount by 1 if it is in inventory
   // @pre instantiated ShopManager obj, ShopManager initialize, and
   // customerInitialize have been successfully ran. Valid transaction file
   // @post inventory item amount is increased by 1 transaction is stored in
   // customer transaction history, if item is not found in inventory, or if
   // collectible type is invalid error is sent to cout. If customer number 
   // doesn't point to a customer object, error will be sent to cout
   // @return nothing.
   void sellItem(const string, const int, const string) const;

   // displays customers transactions stored in the history vector
   // @pre customerTable and customer SearchTree initialized with data
   // ShopManager obj instantiated with it's factory methods, command methods,
   // and inventory vector all with appropriate data
   // @post customer history vector contents are displayed in cout;
   // @return nothing.
   void displayCustomerHistory(const int) const;

   // Displays all customers names followed all their transactions in 
   // aphabetical order to cout. One per line
   // @pre instantiated ShopManager obj, ShopManagers
   // initialize(), customerInitial() methods have been ran
   // @post all customers names and transactions they did are printed to cout in
   // alphabetical order
   // @return nothing
   void displayAllCustomers() const;
   
   // Displays every item in inventory coins, comics, then sportscards
   // @pre instantiated ShopManager obj, ShopManagers
   // initialize(), customerInitial() methods have been ran
   // @post entire inventory is displayed to cout
   // @return nothing.
   void displayInventory() const;
};