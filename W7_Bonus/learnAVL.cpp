#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	int height;
};

// Exercise 1: AVL Tree

// 1. Create a new Node from a given value
Node* newNode(int data){
	Node* node = new Node;
	node->key = data;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	return node;
}

int height(Node* node){
	if (node == nullptr) return 0;
	return node->height;
}

int getBalance(Node* node){
	if (node == nullptr) return 0;
	return height(node->left) - height(node->right);
}

Node* rightRotate(Node* A){ // (B->C)<-A  =>  B->(C<-A)  
	Node* B = A->left;
	Node* C = B->right;

	B->right = A;
	A->left = C;
	
	A->height = 1 + max(height(A->left), height(A->right));
	B->height = 1 + max(height(B->left), height(B->right));
	return B;
}

Node* leftRotate(Node* A){ // A->(C<-B)  =>  (A->C)<-B
	Node* B = A->right;
	Node* C = B->left;

	B->left = A;
	A->right = C;

	A->height = 1 + max(height(A->left), height(A->right));
	B->height = 1 + max(height(B->left), height(B->right));
	return B;
}

// 2. Insert a new value into a AVL Tree (do not add existing keys)
Node* insertNode(Node* root, int data){
	// a. insertNode like BST
	if (root == nullptr) return newNode(data);
	if (data < root->key) root->left = insertNode(root->left, data); 
	else if (data > root->key) root->right = insertNode(root->right, data);
	else return root; // (do not add existing keys)

	// b. update Height
	root->height = 1 + max(height(root->left), height(root->right));

	// c. get Balance factor
	int balance = getBalance(root);

	// Left Left case:
	if (balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	// Left Right case:
	if (balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right case:
	if (balance < -1 && getBalance(root->right) <= 0){
		return leftRotate(root);
	}
	// Right Left case:
	if (balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root; // unchange root
}

// 3. Search a Node with a given value from a AVL Tree. Return NULL if not found.
Node* searchNode(Node* root, int data){
	if (root == nullptr) return nullptr;
	if (root->key == data) return root;
	if (data < root->key) return searchNode(root->left, data);
	else return searchNode(root->right, data);
}

Node* minValueNode(Node* node){
	Node* current = node;
	while (current->left != nullptr){
		current = current->left;
	}
	return current;
}

// 4. Delete a Node with a given value from a AVL Tree
Node* deleteNode(Node* root, int data){
	// a. deleteNode BST
	if (root == nullptr) return root;

	if (data < root->key) root->left = deleteNode(root->left, data);
	else if (data > root->key) root->right = deleteNode(root->right, data);
	else {
		// no child or one child
		if ((root->left == nullptr) || (root->right == nullptr)){
			Node* temp = root->left ? root->left : root->right;

			if (temp == nullptr){ // no child case
				temp = root;
				root = nullptr;
			} else { // one child case
				*root = *temp; // child -> root
			}
			delete temp;
		} else { // two child
			// get inorder successor
			Node* temp = minValueNode(root->right);
			root->key = temp->key; // swap value (root <-> inorder successor)
			root->right = deleteNode(root->right, temp->key); // delete inorder successor
		}
	}

	if (root == nullptr) return root;

	// b. update height;
	root->height = 1 + max(height(root->left), height(root->right));

	// c. get Balance factor
	int balance = getBalance(root);

	// Left Left case:
	if (balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	// Left Right case:
	if (balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right case:
	if (balance < -1 && getBalance(root->right) <= 0){
		return leftRotate(root);
	}
	// Right Left case:
	if (balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// 5. Traversal in Pre-order, In-order, Post-order and Level-order.

void NLR(Node* root){
	if (root != nullptr){
		cout << root->key << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

void LNR(Node* root){
	if (root != nullptr){
		LNR(root->left);
		cout << root->key << " ";
		LNR(root->right);
	}
}

void LRN(Node* root){
	if (root != nullptr){
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

void levelOrder(Node* root){
	if (root == nullptr) return;
	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* cur = q.front();
		q.pop();

		cout << cur->key << " ";
		if (cur->left != nullptr) q.push(cur->left);
		if (cur->right != nullptr) q.push(cur->right);
	}
}

// Exercise 2

// 1. Check if the given AVL Tree is a full tree.
bool isFull(Node* root){ // zero or two child
	if (root == nullptr) return true;
	if ((root->left == nullptr) ^ (root->right == nullptr)) return false; // only one child is wrong
		
	return isFull(root->left) && isFull(root->right);
}

// 2. Check if the given AVL Tree is a complete tree
bool isComplete(Node* root){ // all level of tree are filled, except lowest leaves (filled from as left as possible)
	if (root == nullptr) return true; // root is nullptr
	if (root->left == nullptr && root->right == nullptr) return true; // root is a leaf

	if (root->right == nullptr) { // right child is nullptr, left child must be a leaf
		return (root->left->left == nullptr && root->left->right == nullptr);
	}

	if (root->left == nullptr) return false; // right child is not nullptr, left child must be a node

	// both child
	return isComplete(root->left) && isComplete(root->right) && (height(root->left) >= height(root->right));
}

// 3. Check if the given AVL Tree is a perfect tree.
bool isPerfect(Node* root){
	if (root == nullptr) return true;

	if ((root->left == nullptr) && (root->right == nullptr)) return true; // base case - leaf node
	if (!isFull(root)) return false;
	
	return isPerfect(root->left) && isPerfect(root->right) && (height(root->left) == height(root->right)); 
}

// 4. Find all nodes with 2 child nodes, and the left child is a divisor of the right child. 
// Print them to the console in ascending order.
void printSpecialNodes(Node* root){
	if (root == nullptr) return;

	// In-Order
	printSpecialNodes(root->left);

	if (root->left != nullptr && root->right != nullptr){
		if (root->right->key % root->left->key == 0){
			cout << root->key << " ";
		}
	}

	printSpecialNodes(root->right);
}

int main() {
    Node* root = nullptr;

    // Test insertNode
    int keys[] = {10, 20, 30, 40, 50, 25, 5, 15, 35, 45, 22, 27, 4, 6};
    for (int key : keys) {
        root = insertNode(root, key);
    }

    // Test duyet
    cout << "Pre-order (NLR): "; NLR(root); cout << "\n";
    cout << "In-order (LNR): "; LNR(root); cout << "\n";
    cout << "Post-order (LRN): "; LRN(root); cout << "\n";
    cout << "Level-order: "; levelOrder(root); cout << "\n";

    // Test searchNode
    int searchKey = 25;
    Node* foundNode = searchNode(root, searchKey);
    if (foundNode) cout << "Da tim thay node co key: " << searchKey << "\n";
    else cout << "Node co key: " << searchKey << " khong tim thay" << "\n";

    searchKey = 99;
    foundNode = searchNode(root, searchKey);
    if (foundNode) cout << "Da tim thay node co key: " << searchKey << "\n";
    else cout << "Node co key: " << searchKey << " khong tim thay" << "\n";

    // Test isFull, isComplete, isPerfect
    cout << "Full tree? " << (isFull(root) ? "Yes" : "No") << "\n";
    cout << "Complete tree? " << (isComplete(root) ? "Yes" : "No") << "\n";
    cout << "Perfect tree? " << (isPerfect(root) ? "Yes" : "No") << "\n";

    // Test printSpecialNodes
    cout << "Special nodes (2 child nodes, left child is a divisor of the right child): ";
    printSpecialNodes(root); cout << "\n";

    // Test deleteNode
    int deleteKeys[] = {25, 5, 6};
    for (int deleteKey : deleteKeys) {
        root = deleteNode(root, deleteKey);
	    cout << "LNR sau khi xoa " << deleteKey << ": ";
	    LNR(root); cout << "\n";
    }

    return 0;
}