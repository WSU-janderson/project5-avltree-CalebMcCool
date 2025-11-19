//------------------------------
//AVLTree Implementation
//
//Created By: Caleb McCool
//Date: November 19, 2025
//
//AVLNode:
//  This is an element (or node) of the AVL Tree class. Each
//  node holds a key value pair as well as:
//    - left child pointer
//    - right child pointer
//    - parent pointer
//    - height
//
//AVLTree:
//  This is a tree-like data structure where each node is
//  balanced to meet sorting and height requirements. Methods
//  can be used for easy manipulation of the tree and there is
//  a destructor, copy constructor, os friend, and overloaded
//  operators. The AVLTree has local variables:
//    - treeSize
//    - root pointer


#include "AVLTree.h"

#include <string>
#include <iostream>

//Node Constructor
AVLTree::AVLNode::AVLNode(){
    key = "Null";
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

//Node Constructor with Value Parameter
AVLTree::AVLNode::AVLNode(const std::string& key) :
    key(key),
    value(0),
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    height(0)
{

}
//Insert Node Method
bool AVLTree::insert(const std::string& key, size_t value){
    if (contains(key) == true){
        return false;
    } else {
        root = insertRecursive(root, key, value);
        treeSize++;
        return true;
    }


}

//Insert Node Method Recursive
AVLTree::AVLNode* AVLTree::insertRecursive(AVLNode* node, const std::string& key, size_t value) {
    //If NULL Node
    if (node == nullptr) {
        AVLNode* newNode = new AVLNode(key);
        newNode->value = value;
        return newNode;
    }

    //Traverse the Tree
    if (key < node->key) {
        node->left = insertRecursive(node->left, key, value);
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key, value);
    }

    //Update Height
    int left;
    int right;

        //Setting Heights for Child Nodes
        if (node->left == nullptr) {
            left = -1;
        } else {
            left = node->left->height;
        }

        if (node->right == nullptr) {
            right = -1;
        } else {
            right = node->right->height;
        }

        //Comparing Heights for Child Nodes
        if (left > right) {
            node->height = left + 1;
        } else {
            node->height = right + 1;
        }

    //Balance the Node
    balanceNode(node);

    return node;

}

//Remove Method
bool AVLTree::remove(const std::string& key){
    //Check if key exists
    if (contains(key) == false){
        return false;
    } else {
        root = removeRecursive(root, key);
        treeSize--;
        return true;
    }
}

//Remove Method Recursive
AVLTree::AVLNode* AVLTree::removeRecursive(AVLNode* node, const std::string& key){
    //Key Not Found
    if (node == nullptr) {
        return nullptr;
    }

    //Traverse Tree
    if (key < node->key) {
        node->left = removeRecursive(node->left, key);
    } else if (key > node->key) {
        node->right = removeRecursive(node->right, key);
    } else {
        removeNode(node);
    }

    //After Deletion Nullptr
    if (node == nullptr) {
        return nullptr;
    }

    //Updating Height
    int left;
    int right;

    if (node->left == nullptr) {
        left = -1;
    } else {
        left = node->left->height;
    }

    if (node->right == nullptr) {
        right = -1;
    } else {
        right = node->right->height;
    }

        //Comparing Heights for Child Nodes
        if (left > right) {
            node->height = left + 1;
        } else {
            node->height = right + 1;
        }

    //Balance Node
    balanceNode(node);
    return node;
}

//Contains Method
bool AVLTree::contains(const std::string& key) const {
    return containsRecursive(root, key) != nullptr;
}

//Contains Method Recursive
AVLTree::AVLNode* AVLTree::containsRecursive(AVLNode* node, const std::string& key) const{
    //Base Case 1
    if (node == nullptr){
        return nullptr;
    }
    //Base Case 2
    else if (node->key == key){
        return node;
    }
    //If key is greater than current
    else if (key < node->key) {
        return containsRecursive(node->left, key);
    }
    //If key is less than current
    else{
        return containsRecursive(node->right, key);
    }
}

//Get Method for AVLTree
std::optional<size_t> AVLTree::get (const std::string& key) const{
    AVLNode* result = getRecursive(root, key);

    //If result is null
    if (result == nullptr) {
        return std::nullopt;
    }

    return result->value;
}

//Get Method for AVLTree Recursive
AVLTree::AVLNode* AVLTree::getRecursive(AVLNode* node, const std::string& key) const {
    if (node == nullptr) {
        return nullptr;
    }

    else if (node->key == key){
        return node;
    }

    //If Smaller
    else if (key < node->key) {
        return getRecursive(node->left, key);
    }

    //If Larger
    else {
        return getRecursive(node->right, key);
    }
}


size_t& AVLTree::operator[] (const std::string& key){
    AVLNode* node = containsRecursive(root, key);

    if (node != nullptr) {
        return node->value;
    }

    insert(key, 0);
    return containsRecursive(root, key)->value;
}

size_t AVLTree::size() const{
    return treeSize;
}

vector<size_t> AVLTree::findRange(const std::string& lowKey, const std:: string& highKey) const{
    std::vector<size_t> result;
    findRangeRecursive(root, lowKey, highKey, result);
    return result;
}

void AVLTree::findRangeRecursive(AVLNode* node, const std::string& lowKey, const std::string& highKey, std::vector<size_t>&result) const{
    //If node is null
    if (node == nullptr) {
        return;
    }

    if (node->key > lowKey) {
        findRangeRecursive(node->left, lowKey, highKey, result);
    }

    if (node->key >= lowKey && node->key <= highKey) {
        result.push_back(node->value);
    }

    if (node->key < highKey) {
        findRangeRecursive(node->right, lowKey, highKey, result);
    }

}

std::vector<std::string> AVLTree::keys() const {

    std::vector<std::string> result;
    keysRecursive(root, result);
    return result;
}

void AVLTree::keysRecursive(AVLNode* node, std::vector<std::string>& result) const {
    if (node == nullptr) {
        return;
    }

    keysRecursive(node->left, result);
    result.push_back(node->key);
    keysRecursive(node->right ,result);

}

//AVL Tree constructor
AVLTree::AVLTree(){
    root = nullptr;
}

//Get Height Method (AVL Tree)
size_t AVLTree::getHeight() const{
    //If the root is null, the height is -1
    if (root == nullptr) {
        return -1;
    }

    return root->height;
}

//Copy Constructor Method
AVLTree::AVLTree(const AVLTree& other) {
    treeSize = other.treeSize;
    root = copyRecursive(other.root);
}

//Copy Constructor Method Recursive
AVLTree::AVLNode* AVLTree::copyRecursive(AVLNode* other) {
    if (other == nullptr) {
        return nullptr;
    }

    //Create new node for copy, and update values
    AVLNode* newNode = new AVLNode(other->key);
    newNode->parent = nullptr;
    newNode->height = other->height;
    newNode->value = other->value;

    newNode->left = copyRecursive(other->left);
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }

    newNode->right = copyRecursive(other->right);
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }

    return newNode;
}

//Operator = Overload
void AVLTree::operator=(const AVLTree& other) {
    //Regarding Self-assignment
    if (this == &other) {
        return;
    }

    deleteRecursive(root);

    root = copyRecursive(other.root);
    treeSize = other.treeSize;
}

//Destructor Method
AVLTree::~AVLTree() {
    deleteRecursive(root);
    root = nullptr;
    treeSize = 0;
}

//Destructor Method Recursive
void AVLTree::deleteRecursive(AVLNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node;
}

//OStream Methods
std::ostream& operator<<(ostream& os, const AVLTree& avlTree){
    avlTree.printRecursive(os, avlTree.root, 0);
    return os;
}

//OStream Method Recursive
void AVLTree::printRecursive(std::ostream& os, AVLTree::AVLNode* node, int depth) const{
    //If Null
    if (node == nullptr) {
        return;
    }

    //Print Right Subtree
    printRecursive(os, node->right, depth + 1);

    for (int i=0; i<depth; i++){
        os << "    ";
    }

    os << "{" << node->key << ": " << node->value << "}" << std::endl;

    //Print Left Subtree
    printRecursive(os, node->left, depth + 1);
}

//Pre-configured Methods
size_t AVLTree::AVLNode::numChildren() const {
    if (left == nullptr && right == nullptr){
        return 0;
    } else if (left == nullptr || right == nullptr) {
        return 1;
    } else {
        return 2;
    }
}

//isLeaf Method (Checks if the node is a leaf)
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr){
        return true;
    } else {
        return false;
    }
}

//getHeight Method (checks the height of a node)
size_t AVLTree::AVLNode::getHeight() const {
    int leftHeight;
    int rightHeight;

    if (left == nullptr) {
        leftHeight = -1;
    } else {
        leftHeight = left->height;
    }

    if (right == nullptr) {
        rightHeight = -1;
    } else {
        rightHeight = right->height;
    }

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

//Remove Node Method (Removes a node from the tree)
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current->right->parent = current->parent;
            current = current->right;
        } else {
            current->left->parent = current->parent;
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

//Remove Node Function
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

//Balance Node Function
void AVLTree::balanceNode(AVLNode *&node) {
    //Initalizing balance factors
    int balanceParent = getBalance(node);
    int balanceChild;

    //If right Heavy from Parent
    if (balanceParent < -1){
        if (node->right == nullptr) {
            return;
        }
        balanceChild = getBalance(node->right);

        if (balanceChild > 0){
            //Right-Left Case
            node->right = rotateRight(node->right);
        }

        //Right-Right Case
        node = rotateLeft(node);

    //If Left Heavy from Parent
    } if (balanceParent > 1) {
        if (node->left == nullptr) {
            return;
        }
        balanceChild = getBalance(node->left);

        if (balanceChild < 0) {
            //Left-Right Case
            node->left = rotateLeft(node->left);
        }

        //Left-Left Case
        node = rotateRight(node);
    }

}

//Getter for Balance
int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }

    //Copied Height Calculation from Insert
    int left;
    int right;

    //Setting Heights for Child Nodes
    if (node->left == nullptr) {
        left = -1;
    } else {
        left = node->left->height;
    }

    if (node->right == nullptr) {
        right = -1;
    } else {
        right = node->right->height;
    }

    return left - right;
}

//Rotation Functions
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* node){
    if (node == nullptr || node->left == nullptr){
        return node;
    }
    AVLNode* current = node->left;
    AVLNode* sub = current->right;

    current->right = node;
    node->left = sub;

    if (sub != nullptr) {
        sub->parent = node;
    }

    if (current->parent != nullptr) {
        if (current->parent->left == node) {
            current->parent->left = current;
        } else if (current->parent->right == node) {
            current->parent->right = current;
        }
    }

    //current->parent = node->parent;
    //node->parent = current;

    //Updating Height of Node
        int left;
        int right;

        if (node->left == nullptr) {
            left = -1;
        } else {
            left = node->left->height;
        }
        if (node->right == nullptr) {
            right = -1;
        } else {
            right = node->right->height;
        }

        if (left > right) {
            node->height = left + 1;
        } else {
            node->height = right + 1;
        }

    //Updating Height of Current
        if (current->left == nullptr) {
            left = -1;
        } else {
            left = current->left->height;
        }
        if (current->right == nullptr) {
            right = -1;
        } else {
            right = current->right->height;
        }

        if (left > right) {
            current->height = left + 1;
        } else {
            current->height = right + 1;
        }

    return current;
}

//rotateLeft Method (Performs rotate left on a node)
AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode* node){
    if (node == nullptr || node->right == nullptr){
        return node;
    }
    AVLNode* current = node->right;
    AVLNode* sub = current->left;

    current->left = node;
    node->right = sub;

    if (sub != nullptr) {
        sub->parent = node;
    }

    if (current->parent != nullptr) {
        if (current->parent->left == node) {
            current->parent->left = current;
        } else if (current->parent->right == node) {
            current->parent->right = current;
        }
    }
    //current->parent = node->parent;
    //node->parent = current;

    //Updating Height of Node
    int left;
    int right;

    if (node->left == nullptr) {
        left = -1;
    } else {
        left = node->left->height;
    }
    if (node->right == nullptr) {
        right = -1;
    } else {
        right = node->right->height;
    }
    //Fill Out node->height=
    if (left > right) {
        node->height = left + 1;
    } else {
        node->height = right + 1;
    }

    //Updating Height of Current
    if (current->left == nullptr) {
        left = -1;
    } else {
        left = current->left->height;
    }
    if (current->right == nullptr) {
        right = -1;
    } else {
        right = current->right->height;
    }
    //fill out current->height=
    if (left > right) {
        current->height = left + 1;
    } else {
        current->height = right + 1;
    }

    return current;
}

