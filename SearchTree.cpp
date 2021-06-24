// @file SearchTree.cpp
// @author Cameron Shore
// @date 06-Jan-20
// This holds definitions for SearchTree class
// Features:
//    Sorted Tree based on Comparable data memeber inserted into Tree.
//    Deep copying of trees via assignment (=) or copy constructor.
//    Insertion and removal of Comparable objects into the Tree.
//    Clearing of the contents of the a Tree without deleting it.
//    Retrieval of a pointer to a Comparable object in the Tree
//    Depth of a Node that contains a Comparable object.
//    Number of decendants a Node has that contains a Comparable object
//    Comparison of Trees, based on their contents
//    Output contents of Tree's Node Comparable object and count
//
// Assumptions:
//    SearchTree's are default constructed with a SearchTree Node pointer to 
//    nullptr.
//    Comparable objects poited to by Node struct contain valid char character
//    and a non-whitespace char (' ')
//    When searching for Comparable objects, Coparable pointers are properly
//    dereferenced.
//    Output of tree is Comparable char chacter and count separated by a space
//    only 1 per line.

#include "SearchTree.h"

// default constructor for SearchTree
// @pre  None
// @post pointer to an empty SearchTree;
// @return none
SearchTree::SearchTree() : root(nullptr){
}// end default Constructor

// destructor
// Completely remove and deallocate memory of a SearchTree
// @pre  pointer that points to memory in the heap
// @post SearchTree for pointer is deallocated
// @return none
SearchTree::~SearchTree(){
   clear(root);
}// end Destructor

// removes and deallocates all of the data from the tree does not delete tree
// @pre  SearchTree that exists already
// @post Empty SearchTree
// @return nothing
void SearchTree::makeEmpty() {
   clear(root);
}// end makeEmpty()

// private method for traversing the SearchTree Deallocates and deletes
// the contents of the SearchTree
// @pre  Pointer to a SearchTree on the heap
// @post SearchTree is deallocated and deleted
// @return  nothing
void SearchTree::clear(SearchTree::Node*& rootptr) {
   if (this->root == nullptr) { // base case leaf node reached
      return;
   }
   else {
      if (rootptr->left != nullptr) {
         clear(rootptr->left);
      }
      if (rootptr->right != nullptr) {
         clear(rootptr->right);
      }
   }
   delete rootptr->item;
   rootptr->item = nullptr;
   rootptr->count = 0;
   rootptr->right = nullptr;
   rootptr->left = nullptr;
   delete rootptr;
   rootptr = nullptr;
} // end clear()

// copy constructor
// Performs deep copy of a SearchTree that is it will completely copy it but
// won't have the same address
// @pre  A SearchTree
// @post a deep copy of the input SearchTree
// @return none
SearchTree::SearchTree(const SearchTree& treeToCopy){
   if (treeToCopy.root == nullptr){ // check if root is empty
      this->root = nullptr;
   }
   copyTree(this->root, treeToCopy.root);
}// end SearchTree copy constructor

// private method for traversing the right SearchTree makes a deep copy of 
// right SearchTree argument
// @pre  Pointer to a SearchTree
// @post Pointer to a deep copy of SearchTree from the left argument
// @return nothing
void SearchTree::copyTree(SearchTree::Node*& copyTo,
   const SearchTree::Node* copyFrom) {
   if (copyFrom == nullptr) { // checking for end of branch
      return;
   }
   else {
      SearchTree::Node* newNode = new SearchTree::Node;
      newNode->item = copyFrom->item->clone(*copyFrom->item);
      newNode->count = copyFrom->count;
      newNode->left = nullptr;
      newNode->right = nullptr;
      copyTo = newNode;
      newNode = nullptr;
   }
   copyTree(copyTo->left, copyFrom->left);
   copyTree(copyTo->right, copyFrom->right);
}// end copyTree method

// inserts a Comparable object into the tree or increments count if already
// in the tree.
// @pre  Comparable pointer object with char data field
// @post Comparable object added to SearchTree or Comparable Object count 
// field incremented
// @return true if Comaparable object actually added to tree otherwise false
// false is also returned if count is just incremented
bool SearchTree::insert(Comparable* insertComp){
   if (root == nullptr) { // check if tree is empty
      SearchTree::Node* newNode = new Node; 
      newNode->item = insertComp;
      newNode->count = 1;
      newNode->left = nullptr;
      newNode->right = nullptr;
      root = newNode;
      return true;
   }
   else if (*insertComp == *root->item){ // item already exists as the root
      root->count++;
      return false;
   }
   else{
      return insert(insertComp, root);
   }
}// end public insert

// Removes one occurrence of a Comparable from a SearchTree, if it is the 
// last occurrence the node will be removed otherwise it will be decremented
// @pre  defined SearchTree & Comparable argument you wish to remove from 
// the tree
// @post if Comparable is found in the tree it is decremented or removed 
// depending on number of count parameter
// @return true if node is removed or if count is decremented, false if 
// Comparable is not found in the SearchTree
bool SearchTree::remove(const Comparable& removeComp){
   if (root == nullptr){ // check if root is empty
      return false;
   }
   else{
      return remove(removeComp, root);
   }
}// end public remove

// finds Comparable in tree and returns it if found
// @pre Comparable Object you wish to retrieve from the Tree
// @post nothing
// @return Comparable* of the desired comparable object or 
// nullptr if not found
Comparable* SearchTree::retrieve(const Comparable& compKey) const{
   if (this->root == nullptr){
      return nullptr;
   }
   else{
      return retrieve(compKey, this->root);
   }
}// end public retrieve 

// returns the depth of the Node in which the Comparable you are searching
// for is
// @pre Comparable you want to find
// @post nothing
// @return int of the depth the node holding the Comparable is, if the
// Comparable is not found then -1 is returned, Root of SearchTree is
// 0 depth.
int SearchTree::depth(const Comparable& compKey) const{
   if (this->root == nullptr) { // check if tree is empty
      return -1;
   }
   else if (*this->root->item == compKey){ // check if root holds comparable
      return 0;
   }
   else{
      return depth(this->root, compKey);
   }
}// end public depth

// returns the number of descendents nodes of the node containing the
// Comparable object
// @pre Comparable Object
// @post nothing
// @return int number of decendent nodes from node containg the comparable
// if comparable is not in SearchTree -1 is returned, if the Node is a leaf
// 0 is returned as it has no decendents
int SearchTree::descendants(const Comparable& compKey) const{
   if (this->root == nullptr) { // check if tree is empty
      return -1;
   }
   else if (*this->root->item == compKey){ // check if root holds comparable
      return numDecendants(this->root);
   }
   else{
      return findComparable(this->root, compKey);
   }
}// end public descendants

// Determines if two trees are equal includes contents and counts
// @pre 2 SearchTrees separated by ==
// @post nothing
// @return bool of true if they are equal or false if they are not
bool SearchTree::operator==(const SearchTree& right) const{
   if (this->root == nullptr && right.root == nullptr){ // both trees empty
      return true;
   }
   else if ((this->root != nullptr && right.root == nullptr) || // one tree is
            (this->root == nullptr && right.root != nullptr)){ // empty one is
      return false;                                            // not
   }
   else{
      return compareTree(this->root, right.root);
   }
}// end public operator==

// Determins if two SearchTrees are not equal 
// @pre 2 SearchTrees separated by !=
// @post nothing
// @return bool of true if they are not equal otherwise false
bool SearchTree::operator!=(const SearchTree& right) const{
   return !(*this == right);
}// end operator!=

// Assigns left argument SearchTree the contents of the right SearchTree
// if left tree is already equal to the right tree, left tree is not cleared
// @pre 2 SearchTree's separated by =
// @post left SearchTree has the same contents as the right SearchTree
// @return SearchTree by reference.
SearchTree& SearchTree::operator=(const SearchTree& right){
   if (*this == right){ // check if they are the same
      return *this;
   }
   this->makeEmpty();
   copyTree(this->root, right.root);
   return *this;
}// end operator=

// Outputs contents of SearchTree to console as a frequency table
// @pre SearchTree whose contents you want to display
// @post Contents of SearchTree in console or output stream as item and count
// with a space between them, 1 Comparable and count per line
// @return ostream
ostream& operator<<(ostream& output, const SearchTree& outputTree){
   if (outputTree.root == nullptr){
      return output;
   }
   else{
      outputHelper(output, outputTree.root);
   }
   return output;
}// end operator<<

// Private recursive method for sending contents of SearchTree to the output
// @pre SearchTree that is not empty
// @post contents of SearchTree are output to the ostream as Comparable data
// and count with a space between then new line 
// @return nothing
void outputHelper(ostream& output, const SearchTree::Node* rootptr) {
   if (rootptr->left != nullptr) {
      outputHelper(output, rootptr->left);
   }
   output << *rootptr->item;
   if (rootptr->right != nullptr) {
      outputHelper(output, rootptr->right);
   }
} // end outputHelper()


// private method for traversing the right SearchTree argument to either add
// a Node or increment an already existing node
// @pre  pointer to a Comparable that you want to add to a SearchTree and
// the SearchTree Node root of the SearchTree you wish to add the node to.
// @post either the Node is added to the Tree, or count parameter of an
// existing node is incremented
// @return bool if a the Node is added true is returned, if the count is 
// incrmented then false is return
bool SearchTree::insert(Comparable* insertComp, SearchTree::Node*& rootptr){
   if (rootptr == nullptr){ // base case leaf node reached so item was not in 
      SearchTree::Node* newNode = new Node; // tree and will be added
      newNode->item = insertComp;
      newNode->count = 1;
      newNode->left = nullptr;
      newNode->right = nullptr;
      rootptr = newNode;
      newNode = nullptr;
      return true;
   }
   else if (*insertComp == *rootptr->item){ // item existed in tree already
      rootptr->count++;
      return false;
   }
   else {
      if (*insertComp < *rootptr->item){
        return insert(insertComp, rootptr->left);
      }
      else{
         return insert(insertComp, rootptr->right);
      }
   }
}// end private insert method

// private method for traversing the SearchTree recursively to try and find
// the Comparable "key" in the SearchTree
// @pre Comparable Obj as the "key", and SearchTree root that you are
// searching in.
// @post either removal of a node if found or nothing if Comparable is not 
// found
// @return true if Comparable is found in the SearchTree, otherwise false
bool SearchTree::remove(const Comparable& compKey, SearchTree::Node*& rootptr){
   if (rootptr == nullptr){ // base case comparable not in tree
      return false;
   }
   else if (compKey == *rootptr->item){ // check if Comparable found
      if (rootptr->count == 1){
         if (rootptr->right == nullptr && rootptr->left == nullptr){ 
            delete rootptr->item; // Node to be removed is a leaf
            rootptr->count--; 
            rootptr->item = nullptr;
            delete rootptr;
            rootptr = nullptr;
            return true;
         }
         else if ((rootptr->left == nullptr && rootptr->right != nullptr) ||
            (rootptr->left != nullptr && rootptr->right == nullptr)){
            rootptr = removeOneChild(rootptr); // Node to be removed has 1 child
            return true;
         }
         else{ // node to be removed has 2 children
            rootptr = removeTwoChild(rootptr);
            return true;
         }
      }
      else{ // Comparable count > 1
         rootptr->count--;
         return true;
      }
   }
   else{
      if (compKey < *rootptr->item){
         return remove(compKey, rootptr->left);
      }
      else{
         return remove(compKey, rootptr->right);
      }
   }
}// end remove private fucntion

// private method for handling removal of a node with only 1 child
// @pre SearchTree Node pointer to the Node to be removed
// @post Child will be "adopted" by grandparent Node, and parent node will
// be removed and deallocated
// @return SearchTree Node pointer to the adopted child 
SearchTree::Node* SearchTree::removeOneChild(SearchTree::Node*& nodePtr){
   if (nodePtr->left == nullptr){ // Node to adopt is on the right
      SearchTree::Node* toDelete = nodePtr;
      nodePtr = nodePtr->right;
      delete toDelete->item;
      toDelete->count = 0;
      toDelete->item = nullptr;
      toDelete->right = nullptr;
      delete toDelete;
      toDelete = nullptr;
      return nodePtr;
   }
   else{ // Node to adopt is on the left
      SearchTree::Node* toDelete = nodePtr;
      nodePtr = nodePtr->left;
      delete toDelete->item;
      toDelete->count = 0;
      toDelete->item = nullptr;
      toDelete->left = nullptr;
      delete toDelete;
      toDelete = nullptr;
      return nodePtr;
   }
}// end removeOneChild()

// private method for handling the remove of a node with 2 children
// @pre SearchTre Node pointer to the Node to be removed with 2 chidren
// @post Removal of parent node and adoption of child node to grandparent
// @return SearchTree Node pointer to adopted child
SearchTree::Node* SearchTree::removeTwoChild(SearchTree::Node*& nodePtr){
   delete nodePtr->item;
   nodePtr->count = getMinComparableCount(nodePtr->right); // setting count
   nodePtr->item = getMinComparable(nodePtr->right); // setting item
   return nodePtr;
}// end removeTwoChild()

// private method for finding the minimum comparable in the right subtree
// also deletes the node holding the smallest comparable
// @pre SearchTree Node pointer
// @post deletes the node holding the smallest comparable obj
// @return pointer to smallest comparable object
Comparable* SearchTree::getMinComparable( SearchTree::Node*& nodePtr){
   if (nodePtr->left == nullptr){ // left most node reached
      Comparable* character = nodePtr->item;
      SearchTree::Node* toDelete = nodePtr;
      nodePtr = nodePtr->right;
      delete toDelete;  // delete Node here for convience
      return character;
   }
   else{
      return getMinComparable(nodePtr->left);
   }
}// end getMinComparable

// private method for finding the minimum comparable in the right subtree
// but for getting the count of the min node
// @pre SearchTree Node pointer
// @post nothing
// @return int of the count of the Node with smallest comparable obj
int SearchTree::getMinComparableCount(SearchTree::Node*& nodePtr) {
   if (nodePtr->left == nullptr) { // left most Node reached
      return nodePtr->count;
   }
   else {
      return getMinComparableCount(nodePtr->left);
   }
}// end getMinComparableCount

// Private method for searching tree for comparable pointer to return
// @pre desired comparable you want to get, pointer to the root of the tree
// @post nothing
// @return Pointer to Comparable object you wanted to retrieve
Comparable* SearchTree::retrieve(const Comparable& compKey, SearchTree::Node* rootPtr) const{
   if (rootPtr == nullptr){ // Comparable not in tree
      return nullptr;
   }
   else if (compKey == *rootPtr->item){
      return rootPtr->item;
   }
   else{
      if (compKey < *rootPtr->item){
         return retrieve(compKey, rootPtr->left);
      }
      else{
         return retrieve(compKey, rootPtr->right);
      }
   }
}// end private retrieve

// private method for finding at what depth the comparable object is at
// @pre SearchTree Node pointer, and comparable object
// @post nothing
// @returns int of depth that the comparable is at. -1 if comparable is not
// in the tree
int SearchTree::depth(SearchTree::Node* rootPtr, const Comparable& compKey) const{
   if (rootPtr == nullptr){ // comparable not in branch
      return -1;
   }
   if (*rootPtr->item == compKey){
      return 0;
   }
   int tryBranch = depth(rootPtr->left, compKey); // check left branch
   if (tryBranch == -1){
      tryBranch = depth(rootPtr->right, compKey); // check right branch 
   }
   if (tryBranch == -1){
      return -1;  // Comparable not in Tree at this point
   }
   else{
      return 1 + tryBranch; 
   }
}// end private depth

// Finds the location of SearhTree Node pointer that has the Comparble
// calls numDecendants method to return int number of decendants
// @pre SearchTree Node pointer and Comparable
// @post nothing
// @return int number of decendants from SearchTree Node pointer that holds
// the comparable object through the use of numDecendant method
int SearchTree::findComparable(SearchTree::Node* rootPtr, const Comparable& compKey) const{
   if (rootPtr == nullptr){ // Comparable not in the tree
      return -1;
   }
   else if (*rootPtr->item == compKey){
      return numDecendants(rootPtr);
   }
   else{
      if (compKey < *rootPtr->item) {
         return findComparable(rootPtr->left, compKey);
      }
      else{
         return findComparable(rootPtr->right, compKey);
      }
   }
}// end findComparable

// Determines number of Decendants from a Node
// @pre SearchTree Node pointer
// @post nothing
// @return int number of descendants from SearchTree Node
int SearchTree::numDecendants(SearchTree::Node* rootPtr) const{
   if (rootPtr == nullptr){ // end of branch
      return -1;
   }
   int leftBranch = 1 + numDecendants(rootPtr->left);
   int rightBranch = 1 + numDecendants(rootPtr->right);
   return leftBranch + rightBranch;
}// end numDecendants

// Private recursive method for comparing all the contents of two trees
// @pre two Search Tree roots you want to compare
// @post nothing
// @return true if all contents (items and counts) are the same
bool SearchTree::compareTree(const SearchTree::Node* left, const SearchTree::Node* right) const {
   if (left == nullptr && right == nullptr){ // making sure leaf nodes are the same
      return true;
   }
   else if ((left == nullptr && right != nullptr) ||
      (left != nullptr && right == nullptr)){ // checking if depths differ
      return false;
   }
   else{
      if ((*left->item == *right->item) && (left->count == right->count) &&
         (compareTree(left->left, right->left)) &&
         (compareTree(left->right, right->right))){
         return true;
      }
      else{
         return false;
      }
   }
}// end compareTree




   