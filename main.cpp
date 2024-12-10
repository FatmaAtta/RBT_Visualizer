#include <bits/stdc++.h>
using namespace std;

enum Color{
    RED,
    BLACK
};

class RBTNode {
public:
    RBTNode *grandparent;
    RBTNode *parent;
    RBTNode *uncle;
    RBTNode *left;
    RBTNode *right;
    RBTNode *sibling;
    Color color;
    bool isDB = false;
    int value;

    RBTNode(int value, RBTNode* parent){
        this->value = value;
        this->color = Color::RED;
        this->parent = parent;
        if(parent == nullptr){
            this->parent = nullptr;
            this->grandparent = nullptr;
            this->uncle = nullptr;
        }
        else{
            this->parent = parent;
            this->grandparent = parent->parent;
            if(parent->right = this){
                this->uncle = grandparent->left;
                this->sibling = parent->left;
            }
            else{
                this->uncle = grandparent->right;
                this->sibling = parent->right;
            }
        }
    }
};

class RBT{
    RBTNode *root;

    void colorSwitch(RBTNode *node){
        if(node->grandparent->color == Color::RED){
            node->grandparent->color = Color::BLACK;
        }
        else{
            node->grandparent->color = Color::RED;
        }

        if(node->parent->color == Color::RED){
            node->parent->color = Color::BLACK;
        }
        else{
            node->parent->color = Color::RED;
        }

        if(node->uncle->color == Color::RED){
            node->uncle->color = Color::BLACK;
        }
        else{
            node->uncle->color = Color::RED;
        }
    }
    void recolor(RBTNode *node){

    }

    void leftRotation(RBTNode *node){

    }
    void rightRotation(RBTNode *node){

    }
    void leftRightRotation(RBTNode *node){

    }
    void rightLeftRotation(RBTNode *node){

    }
    RBTNode* getDeletePredecessor(RBTNode *node){

    }
    int checkPathType(RBTNode *node){
        if(node->grandparent->left->left == node){
            return 1;
        }
        if(node->grandparent->right->right == node){
            return 2;
        }
        if(node->grandparent->left->right == node){
            return 3;
        }
        if(node->grandparent->right->left == node){
            return 4;
        }
    }
    void insertValue(int num){
        RBTNode *node;
        if(root == nullptr){
            node = new RBTNode(num, nullptr);
            root = node;
            root->color = Color::BLACK;
        }
        else{
            RBTNode *currentNode = root;
            while(true){
                if(num > currentNode->value){
                    if(currentNode->right == nullptr){
                        currentNode->right = node;
                        node = new RBTNode(num, currentNode);
                        break;
                    }
                    currentNode = currentNode -> right;
                }
                else{
                    if(currentNode->left == nullptr){
                        currentNode->left = node;
                        node = new RBTNode(num, currentNode);
                        break;
                    }
                    currentNode = currentNode -> left;
                }
            }
            if(currentNode->color==Color::RED){
                if(node->uncle->color == Color::RED){
                    colorSwitch(node);
                }
                else if(node->uncle->color == Color::BLACK || node->uncle == nullptr){
                    int pathType = checkPathType(node);
                    switch (pathType){
                        case 1: //left left
                            rightRotation(node->grandparent);
                            break;
                        case 2: //right right
                            leftRotation(node->grandparent);
                            break;
                        case 3: //left right
                            leftRightRotation(node);
                            break;
                        case 4: //right left
                            rightLeftRotation(node);
                            break;
                    }
                }
            }
        }
    }
    void deleteValue(int num){
        RBTNode *node = searchValue(num);
        //leaf node
        if(node->left == nullptr && node->right == nullptr){
            if(node->color == Color::RED){
                if(node->parent->left == node){
                    node->parent->left = nullptr;
                    delete(node);
                }
                else if(node->parent->right == node){
                    node->parent->right = nullptr;
                    delete(node);
                }
            }
            else{
                if(node->parent->left == node){
                    node->parent->left->isDB = true;
                }
                else if(node->parent->right == node){
                    node->parent->right->isDB = true;
                }
            }
        } //one child
        else if(node->left == nullptr &&node->right != nullptr || node->left != nullptr &&node->right == nullptr){

        } //two children
        else if(node->left != nullptr && node->right != nullptr){

        }
    }
    RBTNode* searchValue(int num){}

    RBT(){
        root = nullptr;
    }
};


int main() {
    return 0;
}
