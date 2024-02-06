// EB
// Implementing Binary Search Tree in C++

/**
  BLG335E - Analysis of Algorithms I - Project 3
  Author: Yusuf Yıldız
  Student ID: 150210006
  Date: 30.12.2023 
*/

#include <iostream>

/**
 * @brief Node struct to hold attributes of each node inside a namespace for the Binary Search Tree.
 */
namespace BST {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };
}

/**
 * @brief A class representing a Binary Search Tree.
 */
class BinarySearchTree {
private:
  BST::Node *root; // Pointer to the root node of the tree

  /**
   * @brief Helper function to recursively delete nodes starting from the given node.
   * @param node The current node being deleted.
   */
  void destroyTree(BST::Node* node) {
    if (node != nullptr) {
      destroyTree(node->left);  // Recursively delete left subtree
      destroyTree(node->right); // Recursively delete right subtree
      delete node;              // Delete the current node
      node = nullptr;           // Set the current node to null to avoid dangling pointer
    }
  }

  /**
   * @brief Helper function to traverse the tree in preorder and store the data in the given array.
   * @param node The current node being traversed.
   * @param orderedData The array to store the data in.
   * @param index The index of the array to store the data in.
   */
  void preorderHelper(BST::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node != nullptr) {
      orderedData[index++] = std::make_pair(node->name, node->data);
      preorderHelper(node->left, orderedData, index);
      preorderHelper(node->right, orderedData, index);
    }
  }

  /**
   * @brief Helper function to traverse the tree in inorder and store the data in the given array.
   * @param node The current node being traversed.
   * @param orderedData The array to store the data in.
   * @param index The index of the array to store the data in.
   */
  void inorderHelper(BST::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node != nullptr) {
      inorderHelper(node->left, orderedData, index);
      orderedData[index++] = std::make_pair(node->name, node->data);
      inorderHelper(node->right, orderedData, index);
    }
  }

  /**
   * @brief Helper function to traverse the tree in postorder and store the data in the given array.
   * @param node The current node being traversed.
   * @param orderedData The array to store the data in.
   * @param index The index of the array to store the data in.
   */
  void postorderHelper(BST::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node != nullptr) {
      postorderHelper(node->left, orderedData, index);
      postorderHelper(node->right, orderedData, index);
      orderedData[index++] = std::make_pair(node->name, node->data);
    }
  }

  /**
   * @brief Helper function to get the height of the tree.
   * @param node The current node being traversed.
   * @return The total count of nodes in tree. To get the height, subtract 1 from the result. 
   */
  int getHeightHelper(BST::Node *node) {
    if (node == nullptr) {  // Base case: reached a null node
      return 0;
    }

    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);

    return 1 + std::max(leftHeight, rightHeight); // Add 1 for the current node
  }

  /**
   * @brief Helper function to find the minimum value in the tree rooted with given node.
   * @param node The initial root of the subtree.
   * @return The node with the minimum value in the tree rooted with given node.
   */
  BST::Node *findMin(BST::Node *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  /**
   * @brief Helper function to find the maximum value in the tree rooted with given node.
   * @param node The initial root of the subtree.
   * @return The node with the maximum value in the tree rooted with given node.
   */
  BST::Node *findMax(BST::Node *node) {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

  /**
   * @brief Helper function to count the total number of nodes in the tree.
   * @param node The initial root of the subtree, when called with root it simply count all nodes.
   * @return The total count of nodes in tree.
   */
  int countNodes(BST::Node *node) {
    if (node == nullptr) {
      return 0; // Base case: reached a null node
    }
    return 1 + countNodes(node->left) + countNodes(node->right); // Add 1 for the current node
  }

  /**
   * @brief Helper function to replace the subtree rooted at node u with the subtree rooted at node v.
   * @param u The node to be replaced.
   * @param v The node to replace the node u.
   */
  void transplant(BST::Node* u, BST::Node* v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }

    if (v != nullptr) {
      v->parent = u->parent;
    }
  }

public:
  /**
   * @brief Constructor to initialize the root node to null.
   */
  BinarySearchTree() {
    root = nullptr;
  }

  /**
   * @brief Destructor to free the memory allocated for nodes in the Binary Search Tree.
   */
  ~BinarySearchTree() {
    // Call a helper function to recursively delete nodes starting from the root
    destroyTree(root);
  }

  /**
   * @brief Function to traverse the tree in preorder and store the data in the given array.
   * @param orderedData The array to store the data in.
   * @param startIndex The starting index of the array to store the data in, if given as 0 it simply starts the array in 0th index.
   */
  void preorder(std::pair<std::string, int> orderedData[], int startIndex) {
    int index = startIndex;
    preorderHelper(root, orderedData, index);
  }
  
  /**
   * @brief Function to traverse the tree in inorder and store the data in the given array.
   * @param orderedData The array to store the data in.
   * @param startIndex The starting index of the array to store the data in, if given as 0 it simply starts the array in 0th index.
   */
  void inorder(std::pair<std::string, int> orderedData[], int startIndex) {
    int index = startIndex;
    inorderHelper(root, orderedData, index);
  }
  
  /**
   * @brief Function to traverse the tree in postorder and store the data in the given array.
   * @param orderedData The array to store the data in.
   * @param startIndex The starting index of the array to store the data in, if given as 0 it simply starts the array in 0th index.
   */
  void postorder(std::pair<std::string, int> orderedData[], int startIndex) {
    int index = startIndex;
    postorderHelper(root, orderedData, index);
  }

  /**
   * @brief Function to search the tree iteratively for a given value.
   * @param value The value to search for.
   * @return The node with the given value, if found. Otherwise, returns null.
   */
  BST::Node* searchTree(int value) {
    BST::Node* current = root;
    while (current != nullptr && current->data != value) {
      if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return current;
  }

  /**
  * @brief Find the successor of a node in a Binary Search Tree (BST).
  *
  * If the given node has a right subtree, the successor is the minimum value in the right subtree.
  * If the node does not have a right subtree, find the lowest ancestor whose left child is an ancestor.
  *
  * @param node The node for which to find the successor.
  * @return A pointer to the successor node, or nullptr if the node is not found.
  */
  BST::Node *successor(BST::Node *node) {
    if (node == nullptr) {
      return nullptr; // Node with the given value not found
    }

    // If the node has a right subtree
    if (node->right != nullptr) {
      return findMin(node->right);
    }

    // If the node does not have a right subtree
    BST::Node *ancestor = node->parent;

    while (ancestor != nullptr && node == ancestor->right) {
      node = ancestor;
      ancestor = ancestor->parent;
    }

    return ancestor;
  }

  /**
  * @brief Find the predecessor of a node in a Binary Search Tree (BST).
  *
  * If the given node has a left subtree, the predecessor is the maximum value in the left subtree.
  * If the node does not have a left subtree, go up the tree until finding the first ancestor
  * that is a right child, and that ancestor is the predecessor.
  *
  * @param node The node for which to find the predecessor.
  * @return A pointer to the predecessor node, or nullptr if the node is not found.
  */
  BST::Node *predecessor(BST::Node *node) {
      if (node == nullptr) {
          return nullptr; // Node with the given value not found
      }

      // If the node has a left subtree
      if (node->left != nullptr) {
          return findMax(node->left);
      }

      // If the node does not have a left subtree
      BST::Node *predecessor = nullptr;

      while (node->parent != nullptr) {
          if (node->data > node->parent->data) {
              predecessor = node->parent;
              break;
          }
          node = node->parent;
      }

      return predecessor;
  }

  /**
  * @brief Inserts a new node with the given name and value into the Binary Search Tree (BST).
  *
  * Inserts a new node with the specified name and value into the BST. The new node is placed in the
  * appropriate position based on the comparison of values. If the value is less than the current
  * node's value, it is placed in the left subtree; otherwise, it is placed in the right subtree.
  *
  * @param name The name associated with the new node.
  * @param value The value to be inserted into the BST.
  */
  void insert(const std::string& name, int value) {
    BST::Node* newNode = new BST::Node;
    newNode->data = value;
    newNode->name = name;
    newNode->left = nullptr;
    newNode->right = nullptr;

    BST::Node* parent = nullptr;
    BST::Node* current = root;

    // Traverse the tree to find the appropriate position for the new node
    while (current != nullptr) { 
      parent = current;
      if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    newNode->parent = parent;

    // Update the parent's left or right pointer based on the comparison
    if (parent == nullptr) {
      root = newNode; // Tree is empty
    } else if (value < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  }

  /**
  * @brief Deletes a node with the given value from the Binary Search Tree (BST).
  *
  * Deletes the node with the specified value from the BST. The deletion operation takes into account
  * three cases based on the number of children the node to be deleted has:
  * - Case 1: Node has 0 children (leaf node)
  * - Case 2: Node has 1 child
  * - Case 3: Node has 2 children
  *
  * @param value The value of the node to be deleted.
  */
  void deleteNode(int value) {
    BST::Node* nodeToDelete = searchTree(value); // First find the node to be deleted

    if (nodeToDelete == nullptr) {
      return; // Node with the given value not found
    }

    if (nodeToDelete->left == nullptr) {                  // cases when current node has 0 child, it simply satisfy the first if then replaced with nullptr(nodeToDelete->right)
      transplant(nodeToDelete, nodeToDelete->right); // cases when current node has 1 child, transplant the child to the current node
    } else if (nodeToDelete->right == nullptr) {    
      transplant(nodeToDelete, nodeToDelete->left);
    } else {
      BST::Node* successor_node = successor(nodeToDelete); // cases when current node has 2 children, find the successor node and replace the current node with the successor node

      if (successor_node->parent != nodeToDelete) {
        transplant(successor_node, successor_node->right);
        successor_node->right = nodeToDelete->right;
        successor_node->right->parent = successor_node;
      }

      transplant(nodeToDelete, successor_node);
      successor_node->left = nodeToDelete->left;
      successor_node->left->parent = successor_node;
    }

    delete nodeToDelete; // Delete the node
  }

  /**
   * @brief Function to get the height of the tree.
   * @return The height of the tree.
   */
  int getHeight() {
    return getHeightHelper(root) - 1; // (Count of nodes from top  to bottom) - 1 = height
  }

  /**
  * @brief Gets the node with the maximum value in the Binary Search Tree (BST).
  * @return The node with the maximum value, or nullptr if the tree is empty.
  */
  BST::Node *getMaximum() {
    if (root == nullptr) {
      return nullptr; // Tree is empty
    }
    return findMax(root);
  }

  /**
  * @brief Gets the node with the minimum value in the Binary Search Tree (BST).
  * @return The node with the minimum value, or nullptr if the tree is empty.
  */
  BST::Node *getMinimum() {
    if (root == nullptr) {
      return nullptr; // Tree is empty
    }
    return findMin(root);
  }
  
  /**
  * @brief Gets the total number of nodes in the Binary Search Tree (BST).
  * @return The total number of nodes in the BST, or 0 if the tree is empty.
  */
  int getTotalNodes() {
    return countNodes(root);
  }
  
}; // End of class BinarySearchTree