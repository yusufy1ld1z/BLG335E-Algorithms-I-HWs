// EB
// Implementing Red-Black Tree in C++

/**
  BLG335E - Analysis of Algorithms I - Project 3
  Author: Yusuf Yıldız
  Student ID: 150210006
  Date: 30.12.2023 
*/

#include <iostream>

/**
 * @brief Node struct to hold attributes of each node inside a namespace for the Red-Black Tree.
 */
namespace RBT {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    int color;  // Color attribute additional to BST
  };
}

/**
 * @brief Color enum for the Red-Black Tree, BLACK -> 0, RED -> 1.
 */
enum Color {BLACK, RED};

/**
 * @brief A class representing a Red-Black Tree.
 */
class RedBlackTree {
private:
  RBT::Node *root; // Root of the tree

  /**
   * @brief Helper function to recursively delete nodes starting from the given node.
   * @param node The current node being deleted.
   */
  void destroyTree(RBT::Node* node) {
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
  void preorderHelper(RBT::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node) {
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
  void inorderHelper(RBT::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node) {
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
  void postorderHelper(RBT::Node *node, std::pair<std::string, int> orderedData[], int &index) {
    if (node) {
      postorderHelper(node->left, orderedData, index);
      postorderHelper(node->right, orderedData, index);
      orderedData[index++] = std::make_pair(node->name, node->data);
    }
  }

  /**
  * @brief Performs a left rotation on the nodes of the RBT to the left, preserving the Red-Black Tree properties.
  * @param x The node around which the left rotation is performed.
  */
  void leftRotate(RBT::Node* x) {
    RBT::Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
      y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  /**
  * @brief Performs a right rotation on the nodes of the RBT to the right, preserving the Red-Black Tree properties.
  * @param x The node around which the left rotation is performed.
  */
  void rightRotate(RBT::Node* y) {
    RBT::Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
      x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
      root = x;
    else if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;

    x->right = y;
    y->parent = x;
  }

  /**
   * @brief Helper function to get the height of the tree.
   * @param node The current node being traversed.
   * @return The total count of nodes in tree. To get the height, subtract 1 from the result. 
   */
  int getHeightHelper(RBT::Node *node) {
    if (node == nullptr) { // Base case: reached a null node
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
  RBT::Node *findMin(RBT::Node *node) {
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
  RBT::Node *findMax(RBT::Node *node) {
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
  int countNodes(RBT::Node *node) {
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
  void transplant(RBT::Node* u, RBT::Node* v) {
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

  /**
  * @brief Performs fixup operations on the Red-Black Tree (RBT) after node insertion.
  *
  * This function ensures that the Red-Black Tree properties are maintained after inserting a new node.
  * It applies a series of cases (1 to 6) to rebalance and recolor the tree appropriately.
  *
  * @param z The newly inserted node that may violate the Red-Black Tree properties.
  */
  void insertFixup(RBT::Node* z) {
    while (z->parent && z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        RBT::Node* y = z->parent->parent->right;
        if (y && y->color == RED) {
          z->parent->color = BLACK;          // Case 1
          y->color = BLACK;                  // Case 1
          z->parent->parent->color = RED;    // Case 1
          z = z->parent->parent;             // Case 1
        } else {
          if (z == z->parent->right) {
            z = z->parent;                   // Case 2
            leftRotate(z);                // Case 2
          }
          z->parent->color = BLACK;           // Case 3
          z->parent->parent->color = RED;     // Case 3
          rightRotate(z->parent->parent);  // Case 3
        }
      } else {
        RBT::Node* y = z->parent->parent->left;
        if (y && y->color == RED) {
          z->parent->color = BLACK;          // Case 4
          y->color = BLACK;                  // Case 4
          z->parent->parent->color = RED;    // Case 4
          z = z->parent->parent;             // Case 4
        } else {
          if (z == z->parent->left) {
            z = z->parent;                   // Case 5
            rightRotate(z);               // Case 5
          }
          z->parent->color = BLACK;          // Case 6
          z->parent->parent->color = RED;    // Case 6
          leftRotate(z->parent->parent);  // Case 6
        }
      }
    }
    root->color = BLACK; // Ensure the root is black // Case 0
  }

  /**
  * @brief Performs fixup operations on the Red-Black Tree (RBT) after node deletion.
  *
  * This function ensures that the Red-Black Tree properties are maintained after deleting a node.
  * It applies a series of cases (1 to 4) to rebalance and recolor the tree appropriately.
  *
  * @param x The node that might violate the Red-Black Tree properties after deletion.
  */
  void deleteFixup(RBT::Node* x) {

    if (x == nullptr || x->parent == nullptr) {
      return; // undefined error
    }
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        RBT::Node* w = x->parent->right;
        if (w && w->color == RED) {
          w->color = BLACK;               // Case 1
          x->parent->color = RED;         // Case 1
          leftRotate(x->parent);        // Case 1
          w = x->parent->right;           // Case 1
        }
        if (w->left && w->left->color == BLACK && w->right && w->right->color == BLACK) {
          w->color = RED;                 // Case 2
          x = x->parent;                  // Case 2
        } else {
          if (w->right && w->right->color == BLACK) {
            w->left->color = BLACK;       // Case 3
            w->color = RED;               // Case 3
            rightRotate(w);             // Case 3
            w = x->parent->right;         // Case 3
          }
          w->color = x->parent->color;     // Case 4
          x->parent->color = BLACK;        // Case 4
          w->right->color = BLACK;         // Case 4
          leftRotate(x->parent);         // Case 4
          x = root;                        // Case 4
        }
      } else { // Symmetric cases for right subtree
        RBT::Node* w = x->parent->left;
        if (w && w->color == RED) {
          w->color = BLACK;                 // Case 1
          x->parent->color = RED;           // Case 1
          rightRotate(x->parent);         // Case 1
          w = x->parent->left;              // Case 1
        }
        if (w->right && w->right->color == BLACK && w->left && w->left->color == BLACK) {
          w->color = RED;                   // Case 2
          x = x->parent;                    // Case 2
        } else {
          if (w->left && w->left->color == BLACK) {
            w->right->color = BLACK;       // Case 3
            w->color = RED;                // Case 3
            leftRotate(w);               // Case 3
            w = x->parent->left;           // Case 3
          }
          w->color = x->parent->color;      // Case 4
          x->parent->color = BLACK;         // Case 4
          w->left->color = BLACK;           // Case 4
          rightRotate(x->parent);         // Case 4
          x = root;                         // Case 4
        }
      }
    }
    if (x != nullptr) {
        x->color = BLACK; // Ensure the root is black
    } else {
        return; //Undefined error
    }
  }
public:
  /**
   * @brief Constructor to initialize the root node to null.
   */
  RedBlackTree() {
    root = nullptr;
  }

  /**
   * @brief Destructor to free the memory allocated for nodes in the Red-Black Tree.
   */
  ~RedBlackTree() {
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
  RBT::Node* searchTree(int value) {
    RBT::Node* current = root;
    while (current != nullptr && value != current->data) {
      if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return current;
  }

  /**
  * @brief Find the successor of a node in a Red-Black Tree (RBT).
  *
  * If the given node has a right subtree, the successor is the minimum value in the right subtree.
  * If the node does not have a right subtree, find the lowest ancestor whose left child is an ancestor.
  *
  * @param node The node for which to find the successor.
  * @return A pointer to the successor node, or nullptr if the node is not found.
  */
  RBT::Node* successor(RBT::Node* node) {
      if (node == nullptr) {
          return nullptr; // Node with the given value not found
      }

      // If the node has a right subtree
      if (node->right != nullptr) {
          return findMin(node->right);
      }

      // If the node does not have a right subtree
      RBT::Node* ancestor = node->parent;

      while (ancestor != nullptr && node == ancestor->right) {
          node = ancestor;
          ancestor = ancestor->parent;
      }

      return ancestor;
  }

  /**
  * @brief Find the predecessor of a node in a Red-Black Tree (RBT).
  *
  * If the given node has a left subtree, the predecessor is the maximum value in the left subtree.
  * If the node does not have a left subtree, go up the tree until finding the first ancestor
  * that is a right child, and that ancestor is the predecessor.
  *
  * @param node The node for which to find the predecessor.
  * @return A pointer to the predecessor node, or nullptr if the node is not found.
  */
  RBT::Node* predecessor(RBT::Node* node) {
      if (node == nullptr) {
          return nullptr; // Node with the given value not found
      }

      // If the node has a left subtree
      if (node->left != nullptr) {
          return findMax(node->left);
      }

      // If the node does not have a left subtree
      RBT::Node* predecessor = nullptr;

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
  * @brief Inserts a node into the Red-Black Tree (RBT) and performs fixup operations.
  *
  * This function inserts a new node with the given name and data into the Red-Black Tree.
  * It then applies fixup operations to maintain the Red-Black Tree properties, including balancing
  * and recoloring as needed.
  *
  * @param name The name of the node to be inserted.
  * @param data The data value associated with the node to be inserted.
  */
  void insert(std::string name, int data) {
    RBT::Node* z = new RBT::Node;
    z->name = name;
    z->data = data;
    z->left = nullptr;
    z->right = nullptr;
    z->color = RED; // New node is always red

    RBT::Node* y = nullptr;
    RBT::Node* x = root;

    // Traverse the tree to find the appropriate position for the new node
    while (x != nullptr) {
      y = x;
      if (z->data < x->data)
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;

    // Update the parent's left or right pointer based on the comparison
    if (y == nullptr)
      root = z;
    else if (z->data < y->data)
      y->left = z;
    else
      y->right = z;

    insertFixup(z); // Fixup the Red-Black Tree after insertion
  }

  /**
  * @brief Deletes a node with the given data from the Red-Black Tree (RBT).
  *
  * This function deletes the node with the specified data from the Red-Black Tree. The deletion operation
  * considers three cases based on the number of children the node to be deleted has:
  * - Case 1: Node has 0 children (leaf node)
  * - Case 2: Node has 1 child
  * - Case 3: Node has 2 children
  *
  * After deletion, the function ensures the Red-Black Tree properties are maintained and performs
  * fixup operations as necessary.
  *
  * @param data The data value of the node to be deleted.
  */
  void deleteNode(int data) {
    RBT::Node* nodeToDelete = searchTree(data); // Find the node to delete

    if (nodeToDelete == nullptr) {
      return; // Node with the given value not found
    }
    RBT::Node* x = nullptr;
    RBT::Node* y = nodeToDelete;
    int yOriginalColor = y->color;

    if (nodeToDelete->left == nullptr) { // cases when current node has 0 child, it simply satisfy the first if then replaced with nullptr(nodeToDelete->right)
      x = nodeToDelete->right;           // cases when current node has 1 child, transplant the child to the current node

      transplant(nodeToDelete, nodeToDelete->right);
    } else if (nodeToDelete->right == nullptr) {
      x = nodeToDelete->left;

      transplant(nodeToDelete, nodeToDelete->left);
    } else {  // cases when current node has 2 children
        if (nodeToDelete != nullptr && nodeToDelete->right != nullptr) {
            y = findMin(nodeToDelete->right); // Find the successor node (minimum value in the right subtree)
            yOriginalColor = y->color;
            x = y->right; // Get the right child of the successor node

            if (y->parent == nodeToDelete) {  // Case where the successor node is the right child of the node to be deleted
                if (x != nullptr) {
                    x->parent = y;
                }
            } else {                          // Case where the successor node is deeper in the right subtree
                transplant(y, y->right);
                if (nodeToDelete->right != nullptr) {
                    y->right = nodeToDelete->right;
                    y->right->parent = y;
                }
            }
            transplant(nodeToDelete, y);     // Replace the node to be deleted with its successor
            if (nodeToDelete->left != nullptr) {  // Update left child of the successor with the left child of the node to be deleted
                y->left = nodeToDelete->left;
                y->left->parent = y;
            }
            y->color = nodeToDelete->color;       // Maintain the color of the successor node
        }
    }

    delete nodeToDelete; // Delete the node to be deleted

    if (yOriginalColor == BLACK) {
      deleteFixup(x);
    }
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
  RBT::Node *getMaximum() {
    if (root == nullptr) {
      return nullptr; // Tree is empty
    }
    return findMax(root);
  }

  /**
  * @brief Gets the node with the minimum value in the Binary Search Tree (BST).
  * @return The node with the minimum value, or nullptr if the tree is empty.
  */
  RBT::Node *getMinimum() {
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

}; // End of RedBlackTree class