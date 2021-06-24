// @file ShopManger.cpp
// @author Cameron Shore
// @date 06-Mar-21
// This file holds definitions for Shop Manager class
// 
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

#include "ShopManager.h"

// Constructor
// @pre nothing
// @post ShopManager Object is instantiated, factoryTable is populated with
// dummy objects to call methods to, customers is populated with blank
// customer pointers, inventory points to an empty SearchTree, and 
// transaction hash table is populated with transaction classes.
// @return nothing
ShopManager::ShopManager() {
   factoryTable[('M' - 'A')] = new Coin;
   factoryTable[('C' - 'A')] = new Comic;
   factoryTable[('S' - 'A')] = new SportsCard;
   inventory['M' - 'A'] = new SearchTree;
   inventory['C' - 'A'] = new SearchTree;
   inventory['S' - 'A'] = new SearchTree;
   transactTable['B' - 'A'] = new Buy;
   transactTable['S' - 'A'] = new Sell;
   transactTable['D' - 'A'] = new Display;
   transactTable['C' - 'A'] = new CustomerDisplay;
   transactTable['H' - 'A'] = new History;
}

// Destructor
// @pre ShopManager object with allocated data on the heap
// @post allocated data is deleted
// @return nothing
ShopManager::~ShopManager(){
   clear();
}

// private method for deallocating memory on the heap
// @pre instantiated shop manager with data on the heap
// @post allocated memory is deleted from the heap
// @return nothing
void ShopManager::clear() {
   // Note hashTableSize will be the same for all 3 tables
   for (int i = 0; i < HASH_TABLE_SIZE; i++) {
      if (factoryTable[i] != nullptr) {
         delete factoryTable[i];
      }
      if (inventory[i] != nullptr) {
         delete inventory[i];
      }
      if (transactTable[i] != nullptr) {
         delete transactTable[i];
      }
   }
}

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
void ShopManager::initialize(ifstream& inputFile) {
   string type = "";
   string description = "";

   while (inputFile.peek() != EOF) {
      getline(inputFile, type, ','); // acquire type
      inputFile.get(); // consume ' '
      if (factoryTable[type[0] - 'A'] == nullptr) { // check if bucket is empty
         cout << "Invalid transaction" << endl;     // if so rid of line output
         getline(inputFile, description, '\n');     // Invalid Transaction
      }
      else { // Type is good here.
         // Depending on the type a new instance of the type object is created
         Collectible* newItem = factoryTable[type[0] - 'A']->create();
         newItem->initialize(inputFile);  // fills object with data from above
         if (newItem->getAmount() < 0) { // check validity of amount
            cout << "Invalid Inventory Amount" << endl;
            delete newItem;
         }
         else {
            inventory[type[0] - 'A']->insert(newItem); // put it in the correct
         }                                             // searchtree
      }                                             
   }
}

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
void ShopManager::customerInitial(ifstream& fileInput) {
   string number;
   string name;
   while (fileInput.peek() != EOF) {
      getline(fileInput, number, ','); // acquire customer number
      fileInput.get(); // consume ' '
      int iD = atoi(number.c_str());
      if (iD > 999 || iD < 0) { // verify customer number
         cout << "Invalid Customer Number" << endl;
         fileInput.ignore(50, '\n');
      }
      else if (customerTable[iD] != nullptr) { // make sure no duplicate ID's 
         cout << "Duplicate Customer Number" << endl;
         fileInput.ignore(50, '\n');
      }
      else {
         getline(fileInput, name, '\n'); // acquire customer name
         Customer* newCust = new Customer;
         newCust->setName(name);
         newCust->setNumber(iD);
         // Note: the Table and SearchTree point to the same customer Object
         // manipulating one will effect the other.
         customerTable[iD] = newCust; // add to customer table
         customers.insert(newCust); // add to customer SearchTree (sorted)
      }
   }
}

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
void ShopManager::transactions(ifstream& inputFile){
   // this variable holds the whole transaction information and will be passed
   // through functions to be stored in customer's transaction vector which is
   // why it's stored here and kept whole.
   string description = "";

   while (inputFile.peek() != EOF) {
      getline(inputFile, description);
      // Check if transaction type is valid
      if (transactTable[description[0] - 'A'] == nullptr) {
         cout << "Invalid Transaction" << endl;
      }
      else { // Transcation type is good here
         // Calls different methods based on transaction type
         transactTable[description[0] - 'A']->execute(this, description);
      }
   }
}

// increases objects amount by 1 if it is in inventory
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran. Valid transaction file
// @post inventory item amount is increased by 1 transaction is stored in
// customer transaction history, if item is not found in inventory, or if
// collectible type is invalid error is sent to cout. If customer number 
// doesn't point to a customer object, error will be sent to cout
// @return nothing.
void ShopManager::buyItem(const string type, const int custID,
                           const string transaction) const{
   if (factoryTable[type[0] - 'A'] == nullptr) { // check type validity
      cout << "Invalid Transaction" << endl;
   }
   // check customer number validity and if the customer exists
   else if (custID > 999 || custID < 0 ||customerTable[custID] == nullptr) { 
      cout << "Invalid Customer Number" << endl;
   }
   else { // type and customer good here
      // depending on type an instance of type object is created
      Collectible* newItem = factoryTable[type[0] - 'A']->create();
      newItem->setParam(type); // fills object with data from file

      // Attempt to find matching object in current inventory 
      Comparable* invItem = inventory[type[0] - 'A']->retrieve(*newItem);
      if (invItem == nullptr) {
         cout << "Invalid Transaction" << endl;
         delete newItem;
      }
      else { // item was found here, transaction is good
         Collectible* collectible = static_cast< Collectible*>(invItem);
         collectible->add();
         customerTable[custID]->addTransaction(transaction);
         delete newItem;
      }
   }
}

// decreases objects amount by 1 if it is in inventory
// @pre instantiated ShopManager obj, ShopManager initialize, and
// customerInitialize have been successfully ran. Valid transaction file
// @post inventory item amount is increased by 1 transaction is stored in
// customer transaction history, if item is not found in inventory, or if
// collectible type is invalid error is sent to cout. If customer number 
// doesn't point to a customer object, error will be sent to cout
// @return nothing.
void ShopManager::sellItem(const string type, const int custID,
                           const string transaction) const {
   if (factoryTable[type[0] - 'A'] == nullptr) { // check type validity
      cout << "Invalid Transaction" << endl;
   }
   // check customer number validity and if the customer exists
   else if (custID > 999 || custID < 0 || customerTable[custID] == nullptr) { 
      cout << "Invalid Customer Number" << endl;
   }
   else { // type and customer good here
      // depending on type an instance of type object is created
      Collectible* newItem = factoryTable[type[0] - 'A']->create();
      newItem->setParam(type); // fills object with data from file

      // Attempt to find matching object in current inventory
      Comparable* invItem = inventory[type[0] - 'A']->retrieve(*newItem);
      if (invItem == nullptr) {
         cout << "Invalid Transaction" << endl;
         delete newItem;
      }
      else { // item was found here
         Collectible* collectible = static_cast<Collectible*>(invItem);
         // check to make sure inventory is not 0 (less than included incase
         // error occurs where and inventory item was initialized as negative)
         if (collectible->getAmount() <= 0) {
            cout << "Invalid Transaction" << endl;
            delete newItem;
         }
         else { // transaction is good here
            collectible->minus();
            customerTable[custID]->addTransaction(transaction);
            delete newItem;
         }
      }
   }
}

// displays customers transactions stored in the history vector
// @pre instantiated ShopManager obj, ShopManagers
// initialize(), customerInitial() methods have been ran successfully
// @post customer history vector contents are displayed in cout;
// @return nothing.
void ShopManager::displayAllCustomers() const{
   cout << customers << endl;
}

// Displays all customers names followed all their transactions in 
// aphabetical order to cout. One per line
// @pre instantiated ShopManager obj, ShopManagers
// initialize(), customerInitial() methods have been ran successfully
// @post all customers names and transactions they did are printed to cout in
// alphabetical order
// @return nothing
void ShopManager::displayCustomerHistory(const int custID) const{
   // check customer number validity and if the customer exists
   if (custID > 999 || custID < 0 || customerTable[custID] == nullptr) {
      cout << "Invalid Customer Number" << endl;
   }
   else {
      customerTable[custID]->Display();
   }
}

// Displays every item in inventory coins, comics, then sportscards
// @pre instantiated ShopManager obj, ShopManagers
// initialize(), customerInitial() methods have been ran successfully
// @post entire inventory is displayed to cout
// @return nothing.
void ShopManager::displayInventory() const{
   // Hard coded output order per customer requirement
   cout << "------Inventory------" << "\n" << endl;
   cout << "Coins:" << endl;
   cout << *inventory['M' - 'A'] << endl; // Coin SearchTree
   cout << "Comics:" << endl;
   cout << *inventory['C' - 'A'] << endl; // Comic SearchTree
   cout << "Sportscards:" << endl;
   cout << *inventory['S' - 'A'] << endl; // SportsCard SearchTree
   cout << "------End Inventory------" << "\n" << endl;
}