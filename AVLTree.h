/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>

using namespace std;

class AVLTree {

    //Declaring Data Types for Variables
    public:
        using KeyType = std::string;
        using ValueType = size_t;

    //Declaring AVL Node Class
    protected:
        class AVLNode {
        public:
            KeyType key;
            ValueType value;
            size_t height;


            AVLNode* left;
            AVLNode* right;
            AVLNode* parent;

            //Node Constructor
            AVLNode();
            AVLNode(const std::string& key);
            //Implemented
            size_t numChildren() const;
            //Implemented
            bool isLeaf() const;
            //Implemented
            size_t getHeight() const;


        };

    //Declaring Public Methods
    public:
        //AVLTree Variables
        size_t treeSize;

        //AVLTree Methods
        AVLTree();
        bool insert(const std::string& key, size_t value);
        bool remove(const std::string& key);
        bool contains(const std::string& key) const;
        std::optional<size_t> get (const std::string& key) const;
        size_t& operator[] (const std::string& key);
        vector<std::string> findRange(const std::string& lowKey, const std:: string& highKey) const;
        //std::vector<std::string> keys() const;
        size_t size() const;
        size_t getHeight() const;
        //AVLTree(const AVLTree& other);
        //void operator=(const AVLTree& other);
        //~AVLTree();
        friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);
        void printRecursive(std::ostream& os, AVLTree::AVLNode* node, int depth) const;

    //Declaring Private Methods
    private:
        AVLNode* root;
        AVLNode* insertRecursive(AVLNode* node, const std::string& key, size_t value);
        AVLNode* removeRecursive(AVLNode* node, const std::string& key);
        AVLNode* containsRecursive(AVLNode* node, const std::string& key) const;
        void findRangeRecursive(AVLNode* node, const std::string& lowKey, const std::string& highKey, std::vector<std::string>&result) const;
        size_t getHeightRecursive(AVLNode* node) const;

        /* Helper methods for remove */
        // this overloaded remove will do the recursion to remove the node
        bool remove(AVLNode*& current, KeyType key);
        // removeNode contains the logic for actually removing a node based on the numebr of children
        bool removeNode(AVLNode*& current);
        //Implemented
        void balanceNode(AVLNode*& node);
        int getBalance(AVLNode* node);

        //Rotate Functions
        AVLNode* rotateRight(AVLNode* node);
        AVLNode* rotateLeft(AVLNode* node);

};

#endif //AVLTREE_H
