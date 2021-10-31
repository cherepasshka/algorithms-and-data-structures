#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Node {
    std::shared_ptr<Node> left, right;
    int y, sub_size;
    long long sum, val;
    Node(int x, int _y = rand()) {
        val = x, y = _y;
        sub_size = 1;
        left = right = nullptr;
        sum = val * val;
    }
};
int get_size(std::shared_ptr<Node> n) {
    if (n == nullptr) {
        return 0;
    }
    return n->sub_size;
}
long long get_value(std::shared_ptr<Node> n) {
    if (n == nullptr) {
        return 0;
    }
    return n->val;
}
long long get_sum(std::shared_ptr<Node> n) {
    if (n == nullptr) {
        return 0;
    }
    return n->sum;
}
std::shared_ptr<Node> validate(std::shared_ptr<Node> root) {
    if (root == nullptr) {
        return root;
    }
    root->sub_size = 1 + get_size(root->left) + get_size(root->right);
    root->sum = get_sum(root->left) + get_sum(root->right) + root->val * root->val;
    return root;
}
pair<std::shared_ptr<Node>, std::shared_ptr<Node>> split(std::shared_ptr<Node> root, int x) {
    pair<std::shared_ptr<Node>, std::shared_ptr<Node>> res = { nullptr, nullptr };
    if (root == nullptr) {
        return res;
    }
    if (get_size(root->left) < x) {
        res = split(root->right, x - get_size(root->left) - 1);
        root->right = validate(res.first);
        res.first = validate(root);
    } else {
        res = split(root->left, x);
        root->left = validate(res.second);
        res.second = validate(root);
    }
    return res;
}
std::shared_ptr<Node> merge(std::shared_ptr<Node> l, std::shared_ptr<Node> r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->y > r->y) {
        l->right = merge(l->right, r);
        return validate(l);
    }
    r->left = merge(l, r->left);
    return validate(r);
}
std::shared_ptr<Node> push_back(std::shared_ptr<Node> root, int val) {
    return merge(root, std::make_shared<Node>(val));
}