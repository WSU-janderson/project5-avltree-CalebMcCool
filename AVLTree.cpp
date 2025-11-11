#include "AVLTree.h"

#include <string>

//Node Constructor
AVLTree::AVLNode::AVLNode(){
    key = "Null";
    value = 0;
    left = nullptr;
    right = nullptr;
    height = 0;
}

//Insert Node into Tree
bool AVLTree::insert(const std::string& key, size_t value){
    AVLNode* newNode = new AVLNode();

    if (root == nullptr){
        root = newNode;
        root->key = key;
        root->value = value;
        return true;
    } else if (contains(key)){
        return false;
    }

    return false;
}

//Public Contains Method
bool AVLTree::contains(const std::string& key) const {
    return contains(root, key);
}

//Private Contains Method
bool AVLTree::contains(AVLNode* node, const std::string& key) const{
    //Base Case 1
    if (node == nullptr){
        return false;
    }
    //Base Case 2
    else if (node->key == key){
        return true;
    }
    //If key is greater than current
    else if (key < node->key) {
        return contains(node->left, key);
    }
    //If key is less than current
    else if (key > node->key){
        return contains(node->right, key);
    }
    //All Fails
    else {
        return false;
    }
}
//AVL Tree constructor
AVLTree::AVLTree(){
    root = nullptr;
}

//Pre-configured Methods
size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

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
            current = current->right;
        } else {
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

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
