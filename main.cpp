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
    bool isNull = false;
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
        //for recursive call incase theres no grandparent,,
        if(node== nullptr){
            return;
        }
        node->uncle->color = Color::BLACK;
        node->parent->color = Color::BLACK;
        node->grandparent->color = Color::RED;
        if(node->grandparent == root){
            node->grandparent->color = Color::BLACK;
        }
        colorSwitch(node->grandparent);
    }
    void recolor(RBTNode *node, int pathType){
        switch (pathType){
            case 1: //left left
                node->parent->color = Color::BLACK;
                node->grandparent->color = Color::RED;
                break;
            case 2: //right right
                node->parent->color = Color::BLACK;
                node->grandparent->color = Color::RED;
                break;
            case 3: //left right
                node->color= Color::BLACK;
                node->grandparent->color = Color::RED;
                break;
            case 4: //right left
                node->color = Color::BLACK;
                node->grandparent->color = Color::RED;
                break;
        }
    }
    void leftRotation(RBTNode *node){
        if(node->parent->right == node){
            node->parent->right = node->right;
            node->right = node->right->left;
            node->parent->right->left=node;
        }
        else if(node->parent->left == node){
            node->parent->left = node->right;
            node->right = node->right->left;
            node->parent->left->left=node;
        }
        else if(node == root){
            root = node->right;
            node->right = root->left;

        }
    }
    void rightRotation(RBTNode *node){ //the node that will rotate,, not the new node itself
        if(node->parent->right == node){
            node->parent->right = node->left;
            node->left = node->left->right;
            node->parent->right->right=node;
        }
        else if(node->parent->left == node){
            node->parent->left = node->left;
            node->left = node->left->right;
            node->parent->left->right=node;
        }
        else if(node == root){
            root = node->left;
            node->left = root->right;
        }
    }
    void leftRightRotation(RBTNode *node){ //the new node
        leftRotation(node->parent);
        rightRotation(node->parent); //supposed to be the gp but it is now its parent after the first rotation
    }
    void rightLeftRotation(RBTNode *node){
        rightRotation(node->parent);
        leftRotation(node->parent);
    }
    int getAndDeletePredecessor(RBTNode *node){
        RBTNode *currentNode = node->left;
        while(currentNode->right != nullptr){
            currentNode=currentNode->right;
        }
        int value = currentNode->value;
        //deletet the node
        if(currentNode->color==Color::RED){
            delete(currentNode);
        }
        else{
            currentNode->isDB = true;
            resolveDB(currentNode);
        }
        return value;
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
                    recolor(node, pathType);
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
                    node->isDB = true;
                    node->isNull = true;
                    resolveDB(node);
                    node->parent->left = nullptr;
                    delete(node);
                }
                else if(node->parent->right == node){
                    node->isDB = true;
                    node->isNull = true;
                    resolveDB(node);
                    node->parent->right = nullptr;
                    delete(node);
                }
            }
        } //one child
        else if(node->left == nullptr &&node->right != nullptr || node->left != nullptr &&node->right == nullptr){
            RBTNode* replacedNode;
            if(node->parent->left == node){
                if(node->left != nullptr){
                    node->parent->left = node->left;
                    replacedNode = node->left;
                }
                else{
                    node->parent->left = node->right;
                    replacedNode = node->right;
                }
            }
            else if(node->parent->right == node){
                if(node->left != nullptr){
                    node->parent->right = node->left;
                    replacedNode = node->left;
                }
                else{
                    node->parent->right = node->right;
                    replacedNode = node->right;
                }
            }
            else if(node == root){
                if(root->left != nullptr){
                    root = root->left;
                    root->color = Color::BLACK;
                }
                else{
                    root = root->right;
                    root->color = Color::BLACK;
                }
            }
            if(node->color == Color::BLACK){
                if(replacedNode->color==Color::BLACK){
                    replacedNode->isDB=true;
                    resolveDB(replacedNode);
                }
                else{
                    replacedNode->color=Color::BLACK;
                }
            }
            delete(node);
        } //two children
        else if(node->left != nullptr && node->right != nullptr){
            int val = getAndDeletePredecessor(node);
            node->value = val;
        }
    }
    RBTNode* findNearSibling(RBTNode *node){
        if(node->parent->left == node){
            return node->parent->right->left;
        }
        else if(node->parent->right == node){
            return node->parent->left->right;
        }
    }
    RBTNode* findFarSibling(RBTNode *node){
        if(node->parent->left == node){
            return node->parent->right->right;
        }
        else if(node->parent->right == node){
            return node->parent->left->left;
        }
    }

    RBTNode* searchValue(int num){
        RBTNode *currentNode = root;
        while(currentNode->left != nullptr || currentNode->right != nullptr){
            if(num == currentNode->value){
                return currentNode;
            }
            else if(num > currentNode->value){
                currentNode = currentNode->right;
            }
            else{
                currentNode = currentNode->left;
            }
        }
        return nullptr;
    }
    void findSibling(RBTNode *node){
        if(node->parent->left == node){
            node->sibling = node->parent->right;
        }
        else if(node->parent->right == node){
            node->sibling = node->parent->left;
        }
    }
    int checkDBType(RBTNode *node){
        findSibling(node);
        RBTNode* near = findNearSibling(node);
        RBTNode* far = findFarSibling(node);
        if(node == root){
            return 2;
        }//sibling and its children are all black
        if(node->sibling->color == Color::BLACK && (node->sibling->left->color == Color::BLACK || node->sibling->left ==
                                                                                                          nullptr) && (node->sibling->right->color == Color::BLACK || node->sibling->right ==
                                                                                                                                                                     nullptr)){
            return 3;
        }
        if(node->sibling->color == Color::RED){
            return 4;
        }
        if(node->sibling->color == Color::BLACK && far->color == Color::BLACK && near->color == Color::RED){
            return 5;
        }
        if(node->sibling->color == Color::BLACK && far->color == Color::RED){
            return 6;
        }
    }
    void resolveDB(RBTNode *node){
        int DBType = checkDBType(node);
        switch (DBType){
            case 2:
                node->isDB = false;
                node->color = Color::BLACK;
                break;
            case 3:

                break;
            case 4:
                break;
            case 5:

            case 6:
                break;
        }

    }
    RBT(){
        root = nullptr;
    }
};


int main() {
    return 0;
}
