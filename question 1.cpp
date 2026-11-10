#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node* createNode(int value)
{
    Node *n = new Node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node *root, int value)
{
    if(root == NULL)
        return createNode(value);

    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);

    return root;
}

void preorder(Node *root)
{
    if(root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node *root)
{
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int oneChild(Node *root)
{
    if(root == NULL)
        return 0;

    if((root->left == NULL && root->right != NULL) ||
       (root->left != NULL && root->right == NULL))
        return 1 + oneChild(root->left) + oneChild(root->right);

    return oneChild(root->left) + oneChild(root->right);
}

int twoChildren(Node *root)
{
    if(root == NULL)
        return 0;

    if(root->left != NULL && root->right != NULL)
        return 1 + twoChildren(root->left) + twoChildren(root->right);

    return twoChildren(root->left) + twoChildren(root->right);
}

int height(Node *root)
{
    if(root == NULL)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

int main()
{
    Node *root = NULL;

    int values[] = {45, 25, 65, 15, 35, 55, 75, 30};

    for(int i = 0; i < 8; i++)
        root = insert(root, values[i]);

    cout << "Preorder: ";
    preorder(root);

    cout << endl << "Inorder: ";
    inorder(root);

    cout << endl << "Postorder: ";
    postorder(root);

    cout << endl << "Nodes with one child: " << oneChild(root);
    cout << endl << "Nodes with two children: " << twoChildren(root);
    cout << endl << "Height (edges): " << height(root);

    return 0;
}
