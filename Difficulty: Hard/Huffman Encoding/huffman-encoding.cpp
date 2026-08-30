class Solution {
public:

class Node {
public:
    Node* left;
    Node* right;
    char c;
    int freq;
    int idx;

    Node(char character, int frequency, int index) {
        c = character;
        freq = frequency;
        idx = index;
        left = NULL;
        right = NULL;
    }
};

class comp {
public:
    bool operator()(Node* a, Node* b) {

        // Smaller frequency should come first
        if (a->freq != b->freq) {
            return a->freq > b->freq;
        }

        // If frequencies are equal, subtree containing
        // earlier character should come first
        return a->idx > b->idx;
    }
};


void preorder(Node* root, string code, vector<string>& ans) {

    if (root == NULL)
        return;

    // Leaf node
    if (root->left == NULL && root->right == NULL) {
        ans.push_back(code);
        return;
    }

    preorder(root->left, code + "0", ans);
    preorder(root->right, code + "1", ans);
}


vector<string> huffmanCodes(string &s, vector<int> f) {

    int n = s.size();

    // Important edge case
    if (n == 1) {
        return {"0"};
    }

    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create leaf nodes
    for (int i = 0; i < n; i++) {
        pq.push(new Node(s[i], f[i], i));
    }


    // Build Huffman Tree
    while (pq.size() > 1) {

        Node* first = pq.top();
        pq.pop();

        Node* second = pq.top();
        pq.pop();


        Node* root = new Node(
            '#',
            first->freq + second->freq,
            min(first->idx, second->idx)
        );

        root->left = first;
        root->right = second;

        pq.push(root);
    }


    Node* root = pq.top();

    vector<string> ans;

    preorder(root, "", ans);

    return ans;
}

};