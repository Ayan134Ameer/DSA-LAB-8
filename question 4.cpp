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

void inorder(Node *root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

Node* minimum(Node *root)
{
    while(root->left != NULL)
        root = root->left;

    return root;
}

Node* maximum(Node *root)
{
    while(root->right != NULL)
        root = root->right;

    return root;
}

void showGreater(Node *root, double threshold)
{
    if(root == NULL)
        return;

    showGreater(root->left, threshold);

    if(root->data > threshold)
        cout << root->data << " ";

    showGreater(root->right, threshold);
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
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

void printLongestPath(Node *root)
{
    if(root == NULL)
        return;

    cout << root->data << " ";

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight > rightHeight)
        printLongestPath(root->left);
    else if(rightHeight > 0)
        printLongestPath(root->right);
}

bool isSkewed(Node *root)
{
    if(root == NULL)
        return true;

    if(root->left != NULL && root->right != NULL)
        return false;

    return isSkewed(root->left) && isSkewed(root->right);
}

Node* deleteNode(Node *root, int value)
{
    if(root == NULL)
        return NULL;

    if(value < root->data)
        root->left = deleteNode(root->left, value);
    else if(value > root->data)
        root->right = deleteNode(root->right, value);
    else
    {
        if(root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

Node* deleteOriginalOneChild(Node *root, int &deleted)
{
    if(root == NULL)
        return NULL;

    bool hadOneChild = (root->left == NULL && root->right != NULL) ||
                       (root->left != NULL && root->right == NULL);

    root->left = deleteOriginalOneChild(root->left, deleted);
    root->right = deleteOriginalOneChild(root->right, deleted);

    if(hadOneChild)
    {
        int value = root->data;
        root = deleteNode(root, value);
        deleted++;
    }

    return root;
}

int kthSmallest(Node *root, int k, int &count)
{
    if(root == NULL)
        return -1;

    int value = kthSmallest(root->left, k, count);

    if(value != -1)
        return value;

    count++;

    if(count == k)
        return root->data;

    return kthSmallest(root->right, k, count);
}

int main()
{
    Node *root = NULL;

    int values[] = {45, 25, 65, 15, 35, 55, 75, 10, 30, 40, 60, 80, 32, 33};

    for(int i = 0; i < 14; i++)
        root = insert(root, values[i]);

    cout << "Original Inorder: ";
    inorder(root);

    int minValue = minimum(root)->data;
    int maxValue = maximum(root)->data;
    double threshold = (minValue + maxValue) / 2.0;

    cout << endl << "Minimum: " << minValue;
    cout << endl << "Maximum: " << maxValue;
    cout << endl << "Threshold: " << threshold;

    cout << endl << "Marks greater than threshold: ";
    showGreater(root, threshold);

    cout << endl << "Nodes with two children: " << twoChildren(root);

    cout << endl << "Longest root-to-leaf path: ";
    printLongestPath(root);

    cout << endl << "Tree height: " << height(root);

    if(isSkewed(root))
        cout << endl << "Tree is skewed";
    else
        cout << endl << "Tree is not skewed";

    int deleted = 0;
    root = deleteOriginalOneChild(root, deleted);

    cout << endl << "Deleted nodes: " << deleted;

    cout << endl << "Final Inorder: ";
    inorder(root);

    int k;
    cout << endl << "Enter k: ";
    cin >> k;

    int count = 0;
    int result = kthSmallest(root, k, count);

    if(result == -1)
        cout << "Invalid k";
    else
        cout << "Kth smallest mark: " << result;

    return 0;
}
