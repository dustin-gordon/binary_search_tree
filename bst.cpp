/**
 * @author Dustin Gordon 
 */

#include <iostream>
using namespace std;

/** Data object for a BST node */
struct BinNode
{
       int key;
       BinNode *left;
       BinNode *right;
};

class myBST
{
public:
	myBST () { root = NULL; }   // initialize first (root) node
	~myBST ();
	BinNode* findInBST(int k);
	void insertToBST(int k);
	void preOrderTraversal();
	void postOrderTraversal();
	void inOrderTraversal();
	void rotatedPrintTree();

private:
	BinNode* root;
	void free_helper(BinNode* node);
	BinNode* find_helper(BinNode* node, int k);     // optional helper function for findInBST
	BinNode* insert_helper(BinNode* node, int k);   // optional helper function for insertToBST
	void preOrder(BinNode* node);
	void postOrder(BinNode* node);
	void inOrder(BinNode* node);
	void rotatedPrint(BinNode* node, int d);
}; 

/** Deconstructor */
myBST::~myBST()
{
	free_helper(root);
}

/** Private fxn for deleting tree */
void myBST::free_helper(BinNode* node)
{
	if(node != NULL)
	{
		free_helper(node->left);
		free_helper(node->right);
		delete node;
	}
}

/** Recursive Search Implementation */
BinNode* myBST::findInBST(int k)
{
    return find_helper(root, k); // returns NULL if not found.
}

/** Private helper fxn for findInBST() */
BinNode* myBST::find_helper(BinNode* node, int k)
{
    if(node == NULL)        // if not found or tree is empty
        return NULL;

    else if(node->key == k) // if current node matches query
        return node;

    else if(node->key < k)  // if node is smaller, go to right child
        return find_helper(node->right, k);

    else if(node->key > k)  // if node is larger, go to left child
        return find_helper(node->left, k);

    else
        return NULL;
}

// (Unused Non-Recursive Implementation)
// BinNode* myBST::findInBST(int k){ }

/** Recursive Insertion Implementation */
void myBST::insertToBST(int k)
{
    if(findInBST(k) != NULL)
    {
        cout << k << " is an existing key. No new node has been inserted." << endl;
        return;
    }
    else
    {
        root = insert_helper(root, k);
    }
}

/** Private helper fxn for insertToBST() */
BinNode* myBST::insert_helper(BinNode* node, int k)
{
    if(node == NULL)
    {
        BinNode* temp = new BinNode;
        temp->key = k;
        temp->left = NULL;
        temp->right = NULL;
        node = temp; // add node with new value
    }

    else if(k < node->key)
        node->left = insert_helper(node->left, k);

    else if(k > node->key)
        node->right = insert_helper(node->right, k);

    return node;
}

// (Unused Non-Recursive Implementation)
// void myBST::insertToBST(int k){ }

/** Pre-order traversal implementation */
void myBST::preOrderTraversal()
{
	preOrder(root);
	cout << endl;
}

/** Private helper fxn for preOrderTraversal() */
void myBST::preOrder(BinNode* node)
{
    if(node == NULL)
        return;
    cout << node-> key << " ";
    preOrder(node->left);
    preOrder(node->right);
}

/** Post-order traversal Implementation */
void myBST::postOrderTraversal()
{
	postOrder(root);
	cout << endl;
}

/** Private helper fxn for postOrderTraversal() */
void myBST::postOrder(BinNode* node)
{
    if(node == NULL)
        return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node-> key << " ";
}

/** In-order traversal implementation */
void myBST::inOrderTraversal()
{
	inOrder(root);
	cout << endl;
}

/** Private helper fxn for inOrderTraversal() */
void myBST::inOrder(BinNode* node)
{
    if(node != NULL)
    {
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }
}

/** Print the tree (Left-Rotated) */
void myBST::rotatedPrintTree()
{
	rotatedPrint(root, 0);
}
/** Private helper fxn for rotatedPrintTree() */
void myBST::rotatedPrint(BinNode* node, int d)
{
	if(node == NULL)
		return;
	
	if (node->right != NULL)
		rotatedPrint(node->right, d+1);
	
	for(int i = 0; i < d; i++)
		cout << "\t";
	cout << node->key << endl;
	
	if (node->left != NULL)
		rotatedPrint(node->left, d+1);
}

/** Main driver fxn */
int main() 
{ 
    myBST testTree;
	
	int user_input = 0;
	
	while (user_input != -1)
	{
		cout << "Please enter an integer between 0 and 99 as the key, ";
		cout << "or enter -1 to stop and to see the resulting tree: ";
		cin >> user_input;
		if (user_input >= 0 and user_input <= 99)
        {
            cout << "Inserting new node: " << user_input << "..." << endl;
            testTree.insertToBST(user_input);
        }
		else if (user_input != -1)
			cout << "Invalid input value (" << user_input << ") !" << endl;
	}

	cout << "Print the resulting tree (left-rotated):" << endl;
	testTree.rotatedPrintTree();
	
	cout << "preOrderTraversal: ";
	testTree.preOrderTraversal();
	cout << endl;

	cout << "postOrderTraversal: ";
	testTree.postOrderTraversal();
    cout << endl;

	cout << "inOrderTraversal: ";
	testTree.inOrderTraversal();
    cout << endl;
	
	user_input = 0;
	
	while (user_input != -1)
	{
		cout << "Please enter an integer between 0 and 99 as the key to search, ";
		cout << "or enter -1 to stop searching: ";
		cin >> user_input;
		
		if (user_input >= 0 and user_input <= 99)
		{
            cout << "Searching for key: " << user_input << "..." << endl;
			BinNode* temp = testTree.findInBST(user_input);
			if(temp == NULL)
				cout << user_input << " is not in this BST." << endl;
			else
			{
				cout << user_input << " is in this BST." << endl;
				if(temp->left != NULL)
					cout << user_input << " has a left child " << temp->left->key << endl;
				if(temp->right != NULL)
					cout << user_input << " has a right child " << temp->right->key << endl;
			}
			cout << endl;
		}
		else if (user_input != -1)
			cout << "Invalid input value (" << user_input << ") !" << endl;
	}
	
	return 0;
} 