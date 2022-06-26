#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <list>
#include <stack>
#include <assert.h>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

typedef int KeyType;
struct Node {
    KeyType key;
    
    int priority, size; // size는 본인이 루트인 서브트리 크기

    Node *left, *right;

    Node (const KeyType& _key) : key(_key), priority(rand()), 
        size(1), left(NULL), right(NULL) {}

    void setLeft(Node* newLeft) {
        left = newLeft; calSize();
    }

    void setRight(Node* newRight) {
        right = newRight; calSize();
    }

    void calSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }

};


typedef pair<Node*, Node*> NodePair;
int N;

Node* erase(Node* root, KeyType key);
Node* insert(Node* root, Node* node);
Node* find_nth(Node* root, int nth);
int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    srand((unsigned int)time(NULL));


    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> N;
        vi moved(N + 1);
        for (int i = 1; i <= N; ++i)
            cin >> moved[i];


        // MAKE TREAP
        Node* treap = NULL;
        for (int i = 1; i <= N; ++i) 
            treap = insert(treap, new Node(i));
        

        vi ans(N+1);
        for (int i = N; i >= 1; --i) {
            int nth = treap->size - moved[i];

            ans[i] = find_nth(treap, nth)->key;
            treap = erase(treap, ans[i]);
        }

        for (int i = 1; i <= N; ++i)
            cout << ans[i] << " ";
        cout << '\n';

        
    }

 
}

Node* find_nth(Node* root, int nth)
{
    int lsize = (root->left) ? root->left->size : 0;

    if (lsize >= nth)
        return find_nth(root->left, nth);
    else if (nth == lsize + 1)
        return root;
    // lsize +1 < nth
    else
        return find_nth(root->right, nth - lsize - 1);

}

// key가 새로운 루트가 될 것.
NodePair split(Node* root, KeyType key)
{
    // no need perhaps?
    if (root == NULL) return NodePair(NULL, NULL);

    if (root->key < key) {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    else {
        NodePair ls = split(root->left, key);
        root->setLeft(ls.second);
        return NodePair(ls.first, root);
    }

    
}

// new Root return
Node* insert(Node* root, Node* node)
{
    if (root == NULL) return node;

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

// a의모든게 b보다 작다는 게 보장되어있음
Node* merge(Node* a, Node* b)
{
    //both NULL case also handled correctly
    if (a == NULL) return b;
    if (b == NULL) return a;

    // b is root
    if (a->priority < b->priority)
    {
        b->setLeft(merge(a, b->left));
        return b;
    }
    // a is root
    else
    {
        a->setRight(merge(a->right, b));
        return a;
    }
}

Node* erase(Node* root, KeyType key)
{
    // WHEN SUCH KEY DOESNT EXIST
    if (root == NULL)
        return NULL;


    if (root->key == key) {
        Node* nroot = merge(root->left, root->right);
        delete root;
        return nroot;
    }


    //left
    if (root->key > key) {
        root->setLeft(erase(root->left, key));
    }
    //right
    else {
        root->setRight(erase(root->right, key));
    }

    return root;
}
