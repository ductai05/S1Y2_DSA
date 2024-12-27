#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    int height;
    Node(int data) : val(data), left(nullptr), right(nullptr), height(1) {}
};

int height(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

int getBalance(Node *root)
{
    if (root == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

Node *rightRotate(Node *A)
{
    Node *B = A->left;
    Node *C = B->right;

    B->right = A;
    A->left = C;

    A->height = 1 + max(height(A->left), height(A->right));
    B->height = 1 + max(height(B->left), height(B->right));

    return B;
}

Node *leftRotate(Node *A)
{
    Node *B = A->right;
    Node *C = B->left;

    B->left = A;
    A->right = C;

    A->height = 1 + max(height(A->left), height(A->right));
    B->height = 1 + max(height(B->left), height(B->right));

    return B;
}

Node *insertNode(Node *root, int data)
{
    // insert like BST
    if (root == nullptr)
        return new Node(data);
    if (root->val == data)
        return root;
    if (data > root->val)
        root->right = insertNode(root->right, data);
    else if (data < root->val)
        root->left = insertNode(root->left, data);

    int balance = getBalance(root);

    root->height = 1 + max(height(root->left), height(root->right));

    // turn AVL
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) < 0)
    {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) >= 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node *minValueNode(Node *root)
{
    Node *cur = root;
    while (cur->left != nullptr)
    {
        cur = cur->left;
    }
    return cur;
}

Node *deleteNode(Node *root, int data)
{
    if (root == nullptr)
        return root;
    if (data > root->val)
        root->right = deleteNode(root->right, data);
    else if (data < root->val)
        root->left = deleteNode(root->left, data);
    else
    { // data = root->val
        if (root->left == nullptr || root->right == nullptr)
        { // 1 or 0 child
            Node *temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            { // 0 child
                temp = root;
                root = nullptr;
            }
            else
            { // 1 child
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            Node *minV = minValueNode(root->right);
            root->val = minV->val;
            root->right = deleteNode(root->right, minV->val);
        }
    }

    if (root == nullptr)
        return root;

    int balance = getBalance(root);
    root->height = 1 + max(height(root->left), height(root->right));

    // turn AVL
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) < 0)
    {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) >= 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void levelOrder(Node *root, vector<Node *> &lvOrder)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();

        lvOrder.push_back(cur);
        cout << cur->val << " ";
        if (cur->left != nullptr)
            q.push(cur->left);
        if (cur->right != nullptr)
            q.push(cur->right);
    }
}

void LNR(Node *root)
{
    if (root != nullptr)
    {
        LNR(root->left);
        cout << root->val << " ";
        LNR(root->right);
    }
}

int maxNode(Node *root)
{
    Node *cur = root;
    while (cur->right != nullptr)
    {
        cur = cur->right;
    }
    return cur->val;
}

int main()
{
    // read input
    freopen("e1.txt", "r", stdin);
    Node *root = nullptr;

    int n;
    cin >> n;

    int *keys = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> keys[i];
    }

    int k;
    cin >> k;
    // insertNode
    for (int i = 0; i < n; i++)
    {
        root = insertNode(root, keys[i]);
    }

    // Test duyet
    vector<Node *> lvOrder;
    // cout << "levelOrder : ";
    levelOrder(root, lvOrder);
    cout << "\n";

    int maxN = maxNode(root);
    if (maxN == k)
    {
        cout << "No solution";
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (lvOrder[i]->val == k)
        {
            if (lvOrder[i]->height == lvOrder[i + 1]->height)
            {
                cout << lvOrder[i + 1]->val;
            }
            else
            {
                cout << "No solution";
            }
            break;
        }
    }

    return 0;
}