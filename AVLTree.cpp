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

//Node Constructor with Value Parameter
AVLTree::AVLNode::AVLNode(std::string& key) :
    key(key)
{
    value = 0;
    left = nullptr;
    right = nullptr;
    height = 0;
}
//Insert Node into Tree
bool AVLTree::insert(const std::string& key, size_t value){

    return false;
}

//Public Contains Method
bool AVLTree::contains(const std::string& key) const {

    return containsRecursive(root, key) != nullptr;
}

//Private Contains Method
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
