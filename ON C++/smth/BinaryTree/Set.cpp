#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        this->left = this->right = NULL;
    }
};

class BinaryTree{
private:
    Node* root;
public:
    BinaryTree(){
        this->root = NULL;
    }

    Node* insertion(Node* root, int value){
        if (root == NULL){
            return new Node(value);
        }
        if (value < root->data){
            root->left = insertion(root->left, value);
        }
        else if(value > root->data){
            root->right = insertion(root->right, value);
        }
        
        return root;
    }
    void insert(int value){
        root = insertion(root, value);
    }

    Node* findParent(Node* root, int value){
        if (root == NULL || (root->left != NULL && root->left->data == value) || (root->right != NULL && root->right->data == value)){
            return root;
        }
        if (value < root->data){
            return findParent(root->left, value);
        }
        else{
            return findParent(root->right, value);
        }
    }
};

int main(){

}