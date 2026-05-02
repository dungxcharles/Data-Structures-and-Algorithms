#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* makeNode(int val) {
    Node* p = malloc(sizeof(Node));
    p->val = val;
    p->left = NULL;
    p->right = NULL;
    return p;
}

Node* root = NULL;

/* ============================================================
 * isExist(val, p, flag)
 *
 * PURPOSE: Find the PARENT of the node containing `val`.
 *
 * HOW IT WORKS:
 *   Instead of returning the node itself, we return its parent.
 *   This is because removal needs to update the parent's pointer
 *   (parent->left or parent->right) to detach the node.
 *
 *   At each step we check if the LEFT or RIGHT child matches val:
 *     - If left child matches  → set flag = -1, return current node (the parent)
 *     - If right child matches → set flag =  1, return current node (the parent)
 *     - Otherwise recurse in the correct BST direction
 *
 *   flag tells the caller which side the found node is on:
 *     flag = -1 → found node is parent->left
 *     flag =  1 → found node is parent->right
 *
 * IMPORTANT: removeNode() handles root separately before calling
 *   this, so we never need to match p itself — only its children.
 *   The final `return NULL` handles the edge case where p->val == val
 *   (unreachable in normal use, but avoids undefined behavior).
 * ============================================================ */
Node* isExist(int val, Node* p, int* flag) {
    if (!p) return NULL;

    if (p->left && p->left->val == val) {
        *flag = -1;
        return p;
    }
    if (p->right && p->right->val == val) {
        *flag = 1;
        return p;
    }

    if (p->val > val)      return isExist(val, p->left, flag);
    else if (p->val < val) return isExist(val, p->right, flag);

    return NULL; // p->val == val but not caught as child: unreachable in practice
}

int isLeaf(Node* p) {
    return p && p->left == NULL && p->right == NULL;
}

/* ============================================================
 * bigSmallest(r, parent)
 *
 * PURPOSE: Find the IN-ORDER SUCCESSOR of node `r`.
 *
 * The in-order successor is the smallest value that is still
 * LARGER than r->val. In a BST this is always the LEFTMOST
 * node of r's RIGHT subtree.
 *
 * WHY DO WE NEED THIS?
 *   When removing a node that has TWO children, we can't just
 *   delete it — we need a replacement that preserves BST order.
 *   The in-order successor is the perfect replacement because:
 *     - It's larger than everything in the left subtree
 *     - It's smaller than everything in the right subtree
 *
 * HOW IT WORKS:
 *   1. Go to r->right (start of right subtree)
 *   2. Walk as far LEFT as possible — that's the smallest value
 *   3. Before returning the successor, DETACH it from its current
 *      position and wire its right child (if any) in its place.
 *      This is critical: the successor may have a right child
 *      that must not be lost.
 *
 * Two sub-cases:
 *   Case A: r->right has no left child
 *     → r->right itself is the successor
 *     → Set parent->right = successor->right (detach cleanly)
 *
 *   Case B: Walk left until r->left->left == NULL
 *     → r->left is the successor (leftmost node)
 *     → Set parent->left = successor->right (preserve successor's right child)
 *
 * OUTPUT:
 *   Returns the successor node (detached, ready to be placed).
 *   Sets *parent to the node that WAS the successor's parent,
 *   so the caller can update that parent's pointer.
 *   Returns NULL if r has no right subtree (no successor exists).
 * ============================================================ */
Node* bigSmallest(Node* r, Node** parent) {
    if (!r) return NULL;

    Node* tmp = r;   // save original node (the one being deleted)
    r = r->right;    // move to right subtree

    if (!r) return NULL; // no right subtree → no in-order successor

    // Case A: right child has no left child → it IS the successor
    if (r->left == NULL) {
        *parent = tmp;
        (*parent)->right = r->right; // detach: wire r's right child up
        r->right = NULL;             // clean up successor before returning
        return r;
    }

    // Case B: walk left to find leftmost node
    while (r->left) {
        if (r->left->left == NULL) {
            // r->left is the leftmost (successor)
            *parent = r;
            Node* res = r->left;
            // KEY: res may have a right child — wire it up so it's not lost
            (*parent)->left = res->right; // could be NULL, that's fine
            res->right = NULL;            // clean up successor before returning
            return res;
        }
        r = r->left;
    }

    return NULL; // unreachable
}

/* ============================================================
 * removeNode(val)
 *
 * PURPOSE: Remove the node with value `val` from the BST.
 *
 * CASES handled:
 *
 * 1. Tree is empty → do nothing.
 *
 * 2. Removing ROOT:
 *    a) Root has no right child → root = root->left
 *    b) Root's right child has no left child → right child becomes
 *       new root, inherits old root's left subtree
 *    c) General case → find in-order successor of root using the
 *       same leftmost-walk logic, detach it, make it the new root
 *
 * 3. Removing a NON-ROOT node:
 *    a) Use isExist() to find the PARENT of the target node.
 *       flag tells us if target is parent->left or parent->right.
 *    b) If target is a LEAF → just null out the parent's pointer.
 *    c) If target has NO RIGHT SUBTREE → replace with its left child.
 *    d) General case → find in-order successor via bigSmallest(),
 *       detach it, put it in place of the deleted node,
 *       giving it the deleted node's left and right children.
 * ============================================================ */
void removeNode(int val) {
    if (!root) return;

    // ── Case 2: removing root ──────────────────────────────────
    if (root->val == val) {
        // 2a: no right subtree → left child becomes root
        Node* p = root->right;
        if (!p) {
            p = root;
            root = root->left;
            free(p);
            return;
        }
        // 2b: right child has no left child → right child becomes root
        if (p->left == NULL) {
            p->left = root->left;
            root->left = NULL;
            root->right = NULL;
            free(root);
            root = p;
            return;
        }
        // 2c: find leftmost of right subtree, make it the new root
        while (p) {
            if (p->left && p->left->left == NULL) {
                Node* q = p->left;
                // detach q, preserving q's right child
                p->left = q->right; // could be NULL, fine
                q->left = root->left;
                q->right = root->right;
                free(root);
                root = q;
                return;
            }
            p = p->left;
        }
    }

    // ── Case 3: removing a non-root node ──────────────────────
    else {
        int flag = 0;
        // parentOfFoundNode: the parent of the node we want to delete
        // flag: -1 if target is parent->left, +1 if parent->right
        Node* parentOfFoundNode = isExist(val, root, &flag);
        if (!parentOfFoundNode || !flag) return; // val not found

        // Get the actual node to delete
        Node* foundNode = (flag == 1) ? parentOfFoundNode->right
                                      : parentOfFoundNode->left;

        // 3b: target is a leaf → simply detach
        if (isLeaf(foundNode)) {
            if (flag == 1) parentOfFoundNode->right = NULL;
            else           parentOfFoundNode->left  = NULL;
            free(foundNode);
            return;
        }

        // 3c & 3d: find in-order successor
        Node* parentOfSuccessor = NULL;
        Node* successor = bigSmallest(foundNode, &parentOfSuccessor);

        if (successor == NULL) {
            // 3c: no right subtree → replace with left child
            // (both flag cases use foundNode->left — it's the only child)
            if (flag == -1) parentOfFoundNode->left  = foundNode->left;
            else            parentOfFoundNode->right = foundNode->left;
            free(foundNode);
            return;
        } else {
            // 3d: place successor where foundNode was
            // successor is already detached by bigSmallest()
            successor->left  = foundNode->left;
            successor->right = foundNode->right;
            free(foundNode);
            if (flag == 1) parentOfFoundNode->right = successor;
            else           parentOfFoundNode->left  = successor;
        }
    }
}

/* ============================================================
 * insert(val)
 *
 * Standard iterative BST insert.
 * Walk down the tree following BST order until we find an
 * empty slot, then attach a new node there.
 * Duplicates are ignored (return immediately if val found).
 * ============================================================ */
void insert(int val) {
    if (!root) { root = makeNode(val); return; }
    Node* p = root;
    while (1) {
        if (p->val == val) return; // duplicate, ignore
        if (p->val > val) {
            if (p->left)  p = p->left;
            else { p->left  = makeNode(val); return; }
        } else {
            if (p->right) p = p->right;
            else { p->right = makeNode(val); return; }
        }
    }
}

void preOrder(Node* r) {
    if (!r) return;
    printf("%d ", r->val);
    preOrder(r->left);
    preOrder(r->right);
}

void postOrder(Node* r) {
    if (!r) return;
    postOrder(r->left);
    postOrder(r->right);
    printf("%d ", r->val);
}

void solution() {
    char cmd[20];
    int v;
    while (1) {
        scanf("%s", cmd);
        if (cmd[0] == '#') break;
        if      (!strcmp(cmd, "postorder")) { postOrder(root); printf("\n"); }
        else if (!strcmp(cmd, "preorder"))  { preOrder(root);  printf("\n"); }
        else if (!strcmp(cmd, "insert"))    { scanf("%d", &v); insert(v); }
        else if (!strcmp(cmd, "remove"))    { scanf("%d", &v); removeNode(v); }
    }
}

int main() {
    solution();
    return 0;
}