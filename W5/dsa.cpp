#include<iostream>
using namespace std;

struct node{
    int data;
    node* left;
    node* right;
};

node* insert(node* t, int x){
    if (t == NULL){
        node* temp = new node;
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    } else {
        if (x < t->data) t->left = insert(t->left, x);
        else t->right = insert(t->right, x);
    }
    return t;
}

void preOrder(node* t){
    if (t != NULL){
        cout << t->data << " ";
        preOrder(t->left);
        preOrder(t->right);
    } 
}

void inOrder(node* t){
    if (t != NULL){
        inOrder(t->left);
        cout << t->data << " ";
        inOrder(t->right);
    }
}

void postOrder(node* t){
    if (t != NULL){
        postOrder(t->left);
        postOrder(t->right);
        cout << t->data << " ";
    } 
}

bool isLeafNode(node* t){
    return (t->left == NULL && t->right == NULL);
}

int countLeafNode(node* t){
    if (t == NULL) return 0;
    if (isLeafNode(t)) return 1;
    return countLeafNode(t->left) + countLeafNode(t->right);
}

// only root: bac 0; them 1 la -> bac 1; -> ....
int treeLevel(node* t){
    if (t == NULL) return -1;
    return 1 + max(treeLevel(t->left), treeLevel(t->right));
}

// 2 cay con co do cao khong chenh nhau qua 1
bool checkAVL(node* t){ 
    if (t == NULL) return true;
    if (abs(treeLevel(t->left) - treeLevel(t->right)) > 1) return false;
    return checkAVL(t->left) && checkAVL(t->right);
}

// XOAY CAY AVL
node *turnRight(node *t){
    node *b = t->left;
    node *d = b->right;
    b->right = t;
    t->left = d;
    return b;
}

node *turnLeft(node *t){
    node *b = t->right;
    node *c = b->left;
    b->left = t;
    t->right = c;
    return b;
}

node *updateTreeAvl(node *t){
    if (abs(treeLevel(t->left) - treeLevel(t->right)) > 1){
        if (treeLevel(t->left) > treeLevel(t->right)){
            node *p = t->left;
            if (treeLevel(p->left) >= treeLevel(p->right)){
                t = turnRight(t);
            } else {
                t->left = turnLeft(t->left);
                t = turnRight(t);
            }
        } else {
            node *p = t->right;
            if (treeLevel(p->right) >= treeLevel(p->left)){
                t = turnLeft(t);
            } else {
                t->right = turnRight(t->right);
                t = turnLeft(t);
            }
        }
    }
    if (t->left != NULL) t->left = updateTreeAvl(t->left);
    if (t->right != NULL) t->right = updateTreeAvl(t->right);
    return t;
}

int main(){
    int n; cin >> n;
    int x;
    node* t = NULL;
    for (int i = 0; i < n; i++){
        cin >> x;
        t = insert(t, x);
    }

    // Xoay cay -> tao AVL: while(!checkAvl(t)) t = updateTreeAvl(t);

    cout << "pre: "; preOrder(t); cout << "\n";
    cout << "in: "; inOrder(t); cout << "\n";
    cout << "post: "; postOrder(t); cout << "\n";

    cout << "numOfLeafNode: " << countLeafNode(t) << "\n";
    cout << "treeLevel: " << treeLevel(t) << "\n";
    cout << "isAVL: " << (checkAVL(t) ? "YES" : "NO");
    return 0;
}