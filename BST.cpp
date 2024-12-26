#include <iostream>
#include <queue>
using namespace std;

struct Node{
	int key;
	Node* left;
	Node* right;
};

// Exercise 1

Node* newNode(int data){
	Node* temp = new Node;
	temp->key = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

Node* insert(Node* root, int data){
	if (root == NULL) root = newNode(data);
	else {
		if (data < root->key) root->left = insert(root->left, data);
		else root->right = insert(root->right, data);
	}
	return root;
}

Node* search(Node* root, int data){
	if (root == NULL) return NULL;
	if (root->key == data) return root;
	else if (root->key > data) return search(root->left, data);
	else return search(root->right, data);
}

Node* getSuccessor(Node* curr)
{
    curr = curr->left;
    while (curr != NULL && curr->right != NULL)
        curr = curr->right;
    return curr;
}

Node* deleteNode(Node* root, int data){
	if (root == NULL) return root;
	if (root->key > data) root->left = deleteNode(root->left, data);
	else if (root-> key < data) root->right = deleteNode(root->right, data);
	else { // root->key == data
		// 0 children or only right child
		if (root->left == NULL){
			Node* temp = root->right;
			delete root;
			return temp;
		}
		// only left child
		if (root->right == NULL){
			Node* temp = root->left;
			delete root;
			return temp;
		}
		// both children
		Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->left = deleteNode(root->left, succ->key);
	}
	return root;
}

void NLR(Node* root){
	if (root != NULL){
		cout << root->key << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

void LNR(Node* root){
	if (root != NULL){
		LNR(root->left);
		cout << root->key << " ";
		LNR(root->right);
	}
}

void LRN(Node* root){
	if (root != NULL){
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

void LevelOrder(Node* root){
	if (root == NULL) return;
	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* curr = q.front();
		q.pop();

		cout << curr->key << " ";
		if (curr->left != NULL) q.push(curr->left);
		if (curr->right != NULL) q.push(curr->right);
	}
}

// Exercise 2

int height(Node* root){
	if (root == NULL) return -1;
	return (1 + max(height(root->left), height(root->right)));
}

int countNode(Node* root){
	if (root == NULL) return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}

int sumNode(Node* root){
	if (root == NULL) return 0;
	return root->key + sumNode(root->left) + sumNode(root->right);
}

int countLeaf(Node* root){
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return countLeaf(root->left) + countLeaf(root->right);
}

Node* searchLess(Node* root, int data){
	if (root == NULL) return NULL;
	if (root->key <= data) return root;
	else if (root->key > data) return search(root->left, data);
	// else return search(root->right, data);
	else return NULL; // dont need this much
}

Node* searchGreater(Node* root, int data){
	if (root == NULL) return NULL;
	if (root->key >= data) return root;
	else if (root->key < data) return search(root->right, data);
	// else return search(root->left, data);
	else return NULL; // dont need this much
}

int countLess(Node* root, int x){
	if (root == NULL) return 0;
	// return int(root->key < x) + countLess(root->left, x) + countLess(root->right, x);
	Node* start = searchLess(root, x);
	return countNode(start->left) + 1 - int(start->key == x);
}

int countGreater(Node* root, int x){
	if (root == NULL) return 0;
	// return int(root->key > x) + countGreater(root->left, x) + countGreater(root->right, x);
	Node* start = searchGreater(root, x);
	return countNode(start->right) + 1 - int(start->key == x);
}

int main(){
	// Exercise 1

	int n, temp; cin >> n;
	Node* t = NULL;
	for (int i = 0; i < n; i++){
		cin >> temp; 
		t = insert(t, temp);
	}

	cout << "NLR (Pre-order): "; NLR(t); cout << "\n";
	cout << "LNR (In-order): "; LNR(t); cout << "\n";
	cout << "LRN (Post-order): "; LRN(t); cout << "\n";

	t = deleteNode(t, 8);
	cout << "LevelOrder: "; LevelOrder(t); cout << "\n";

	// Exercise 2
	cout << "Height: " << height(t) << "\n";
	cout << "Number of nodes: " << countNode(t) << "\n";
	cout << "Sum of nodes: " << sumNode(t) << "\n";
	cout << "Number of leaves: " << countLeaf(t) << "\n";
	cout << "Number of nodes smaller than 7: " << countLess(t, 7) << "\n";
	cout << "Number of nodes bigger than 7: " << countGreater(t, 7) << "\n";
}