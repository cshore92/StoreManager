// @file SearchTree.h
// @author Cameron Shore
// @date 06-Jan-20
// This holds the declarations for the SearchTree class
// Features:
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


#pragma once
#include "Comparable.h"
using namespace std;

class SearchTree {
protected:

   // Stucture for holding pointer to Comparable object, integer for a count
   // variable and pointers to other Nodes 
   struct Node {
      Comparable* item;
      int count;
      Node* left;
      Node* right;
   };

private:

   // pointer that holds the start of the SearchTree
   SearchTree::Node* root;

   // private method for traversing the SearchTree Deallocates and deletes
   // the contents of the SearchTree
   // @pre  Pointer to a SearchTree on the heap
   // @post SearchTree is deallocated and deleted
   // @return  nothing
   void clear(SearchTree::Node*&);

   // private method for traversing the right SearchTree makes a deep copy of 
   // right SearchTree argument
   // @pre  Pointer to a SearchTree
   // @post Pointer to a deep copy of SearchTree from the left argument
   // @return nothing
   void copyTree(SearchTree::Node*&, const SearchTree::Node*);

   // private method for traversing the right SearchTree argument to either add
   // a Node or increment an already existing node
   // @pre  pointer to a Comparable that you want to add to a SearchTree and
   // the SearchTree Node root of the SearchTree you wish to add the node to.
   // @post either the Node is added to the Tree, or count parameter of an
   // existing node is incremented
   // @return bool if a the Node is added true is returned, if the count is 
   // incrmented then false is return
   bool insert(Comparable*, SearchTree::Node*&);

   // private method for traversing the SearchTree recursively to try and find
   // the Comparable "key" in the SearchTree
   // @pre Comparable Obj as the "key", and SearchTree root that you are
   // searching in.
   // @post either removal of a node if found or nothing if Comparable is not 
   // found
   // @return true if Comparable is found in the SearchTree, otherwise false
   bool remove(const Comparable&, SearchTree::Node*&);

   // private method for handling removal of a node with only 1 child
   // @pre SearchTree Node pointer to the Node to be removed
   // @post Child will be "adopted" by grandparent Node, and parent node will
   // be removed and deallocated
   // @return SearchTree Node pointer to the adopted child
   SearchTree::Node* removeOneChild(SearchTree::Node*&);

   // private method for handling the remove of a node with 2 children
   // @pre SearchTre Node pointer to the Node to be removed with 2 chidren
   // @post Removal of parent node and adoption of child node to grandparent
   // @return SearchTree Node pointer to adopted child
   SearchTree::Node* removeTwoChild(SearchTree::Node*&);

   // private method for finding the minimum comparable in the right subtree
   // also deletes the node holding the smallest comparable
   // @pre SearchTree Node pointer
   // @post deletes the node holding the smallest comparable obj
   // @return pointer to smallest comparable object
   Comparable* getMinComparable(SearchTree::Node*&);

   // private method for finding the minimum comparable in the right subtree
   // but for getting the count of the min node
   // @pre SearchTree Node pointer
   // @post nothing
   // @return int of the count of the Node with smallest comparable obj
   int getMinComparableCount(SearchTree::Node*&);

   // Private method for searching tree for comparable pointer to return
   // @pre desired comparable you want to get, pointer to the root of the tree
   // @post nothing
   // @return Pointer to Comparable object you wanted to retrieve
   Comparable* retrieve(const Comparable&, SearchTree::Node*) const;

   // private method for finding at what depth the comparable object is at
   // @pre SearchTree Node pointer, and comparable object
   // @post nothing
   // @returns int of depth that the comparable is at. -1 if comparable is not
   // in the tree
   int depth(SearchTree::Node*, const Comparable&) const;

   // Finds the location of SearhTree Node pointer that has the Comparble
   // calls numDecendants method to return int number of decendants
   // @pre SearchTree Node pointer and Comparable
   // @post nothing
   // @return int number of decendants from SearchTree Node pointer that holds
   // the comparable object through the use of numDecendant method
   int findComparable(SearchTree::Node*, const Comparable&) const;

   // Determines number of Decendants from a Node
   // @pre SearchTree Node pointer
   // @post nothing
   // @return int number of descendants from SearchTree Node
   int numDecendants(SearchTree::Node*) const;

   // Private recursive method for comparing all the contents of two trees
   // @pre two Search Tree roots you want to compare
   // @post nothing
   // @return true if all contents (items and counts) are the same
   bool compareTree(const SearchTree::Node*, const SearchTree::Node*) const;

   // Private recursive method for sending contents of SearchTree to the output
   // @pre SearchTree that is not empty
   // @post contents of SearchTree are 
   friend void outputHelper(ostream&, const SearchTree::Node*);   

public:

   // default constructor for SearchTree
   // @pre  None
   // @post pointer to an empty SearchTree;
   // @return none
   SearchTree();

   // destructor
   // Completely remove and deallocate memory of a SearchTree
   // @pre  pointer that points to memory in the heap
   // @post SearchTree for pointer is deallocated
   // @return none
   ~SearchTree();

   // copy constructor
   // Performs deep copy of a SearchTree that is it will completely copy it but
   // won't have the same address
   // @pre  A SearchTree
   // @post a deep copy of the input SearchTree
   // @return none
   SearchTree(const SearchTree&);

   // inserts a Comparable object into the tree or increments count if already
   // in the tree.
   // @pre  Comparable pointer object with char data field
   // @post Comparable object added to SearchTree or Comparable Object count 
   // field incremented
   // @return true if Comaparable object actually added to tree otherwise false
   // false is also returned if count is just incremented
   bool insert(Comparable*);

   // Removes one occurrence of a Comparable from a SearchTree, if it is the 
   // last occurrence the node will be removed otherwise it will be decremented
   // @pre  defined SearchTree & Comparable argument you wish to remove from 
   // the tree
   // @post if Comparable is found in the tree it is decremented or removed 
   // depending on number of count parameter
   // @return true if node is removed or if count is decremented, false if 
   // Comparable is not found in the SearchTree
   bool remove(const Comparable&);

   // removes and deallocates all of the data from the tree does not delete 
   // tree
   // @pre  SearchTree that exists already
   // @post Empty SearchTree
   // @return nothing
   void makeEmpty();

   // finds Comparable in tree and returns it if found
   // @pre Comparable Object you wish to retrieve from the Tree
   // @post nothing
   // @return Comparable* of the desired comparable object or 
   // nullptr if not found
   Comparable* retrieve(const Comparable&) const;

   // returns the depth of the Node in which the Comparable you are searching
   // for is
   // @pre Comparable you want to find
   // @post nothing
   // @return int of the depth the node holding the Comparable is, if the
   // Comparable is not found then -1 is returned, Root of SearchTree is
   // 0 depth.
   int depth(const Comparable&) const;

   // returns the number of descendents nodes of the node containing the
   // Comparable object
   // @pre Comparable Object
   // @post nothing
   // @return int number of decendent nodes from node containg the comparable
   // if comparable is not in SearchTree -1 is returned, if the Node is a leaf
   // 0 is returned as it has no decendents
   int descendants(const Comparable&) const;

   // Determines if two trees are equal includes contents and counts
   // @pre 2 SearchTrees separated by ==
   // @post nothing
   // @return bool of true if they are equal or false if they are not
   bool operator==(const SearchTree&) const;

   // Determins if two SearchTrees are not equal 
   // @pre 2 SearchTrees separated by !=
   // @post nothing
   // @return bool of true if they are not equal otherwise false
   bool operator!=(const SearchTree&) const;

   // Assigns left argument SearchTree the contents of the right SearchTree
   // if left tree is already equal to the right tree, left tree is not cleared
   // @pre 2 SearchTree's separated by =
   // @post left SearchTree has the same contents as the right SearchTree
   // @return SearchTree by reference.
   SearchTree& operator=(const SearchTree&);

   // Outputs contents of SearchTree to console as a frequency table
   // @pre SearchTree whose contents you want to display
   // @post Contents of SearchTree in console or output stream as item and count
   // with a space between them, 1 Comparable and count per line
   // @return ostream
   friend ostream& operator<<(ostream&, const SearchTree&);
};
