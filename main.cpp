#include <bits/stdc++.h>
using namespace std;

class RBTNode {
public:
    RBTNode *grandparent;
    RBTNode *parent;
    RBTNode *uncle;
    RBTNode *left;
    RBTNode *right;
    char color;
};

class RBT{
    RBTNode *root;

    void leftRotation(RBTNode){}
    void rightRotation(RBTNode){}
    void insertValue(int num){}
    void deleteValue(int num){}
    RBTNode searchValue(int num){}
};


int main() {
    return 0;
}
