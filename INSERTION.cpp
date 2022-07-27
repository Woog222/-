#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <list>
#include <stack>
#include <assert.h>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <climits>
#include <cstdio>
#define el '\n'
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;
const int MOD = 1000000007;

typedef int KeyType;
struct Node {
    KeyType key;
    int priority, size;
    Node* left, * right;

    Node(const KeyType& _key) : key(_key), priority(rand()),
        size(1), left(NULL), right(NULL) {}
    ~Node() {
        delete left;
        delete right;
    }

    void setLeft(Node* newLeft) {
        left = newLeft;
        calcSize();
    }
    void setRight(Node* newRight) {
        right = newRight;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};
typedef pair<Node*, Node*> NodePair;

Node* insert(Node* root, Node* node);
Node* erase(Node* root, KeyType key);
int nth(Node* root, int k);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        vi ans(n), input(n);
        for (int i = 0; i < n; ++i) cin >> input[i];

        Node* treap = NULL;
        for (int i = 1; i <= n; ++i) treap = insert(treap, new Node(i));

        for (int i = n - 1; i >= 0; --i) {
            ans[i] = nth(treap, treap->size - input[i]);
            treap = erase(treap, ans[i]);
        }

        for (int i : ans)
            cout << i << " ";
        cout << el;
        delete treap;
    }
}

int nth(Node* root, int k) {
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (leftSize >= k) return nth(root->left, k);
    if (leftSize == k - 1) return root->key;
    else return nth(root->right, k - leftSize - 1);
}


// root서브트리를 key를 기준으로 좌우로 나눔.
NodePair split(Node* root, KeyType key) {
    if (root == NULL) return NodePair(NULL, NULL);

    if (root->key < key) {
        NodePair rightSide = split(root->right, key);
        root->setRight(rightSide.first);
        return NodePair(root, rightSide.second);
    }
    else {
        NodePair leftSide = split(root->left, key);
        root->setLeft(leftSide.second);
        return NodePair(leftSide.first, root);
    }
}

Node* insert(Node* root, Node* node) {
    if (root == NULL) return node;

    // 우선순위 앞설경우, root를 둘로나누고 
    // node 좌우에 붙이고 node가 새로운 루트
    if (root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if (root->key < node->key)
        root->setRight(insert(root->right, node));
    else
        root->setLeft(insert(root->left, node));

    return root;
}

// left와 right를 하나로 합쳐서 루트 리턴
Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->priority < right->priority) {
        right->setLeft(merge(left, right->left));
        return right;
    }
    else {
        left->setRight(merge(left->right, right));
        return left;
    }
}
// 삭제하고 새로운 루트 리턴
Node* erase(Node* root, KeyType key) {
    // 삭제하려는 원소가 없음
    if (root == NULL)
        return root;

    if (root->key == key) {
        Node* ret = merge(root->left, root->right);
        root->setLeft(NULL);
        root->setRight(NULL);
        delete root;
        return ret;
    }

    if (key < root->key)
        root->setLeft(erase(root->left, key));
    else
        root->setRight(erase(root->right, key));
    return root;
}
