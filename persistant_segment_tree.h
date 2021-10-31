#include <algorithm>
#include <vector>
#include <memory>

struct Node {
    std::shared_ptr<Node> left, right;
    int sum;
    Node(int x = 0) {
        sum = x;
        left = right = nullptr;
    }
    Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) {
        left = l;
        right = r;
        sum = l->sum + r->sum;
    }
};

std::shared_ptr<Node> build(int l, int r, const std::vector<int>& a) {
    if (l == r - 1) {
        return std::make_shared<Node>(a[l]);
    }
    int m = (l + r) / 2;
    return std::make_shared<Node>(build(l, m, a), build(m, r, a));
}
int sum(std::shared_ptr<Node> root, int l, int r, int ql, int qr) {
    if (root == nullptr) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return root->sum;
    }
    int mid = (l + r) / 2;
    return sum(root->left, l, mid, ql, qr) + sum(root->right, mid, r, ql, qr);
}
std::shared_ptr<Node> update(std::shared_ptr<Node> root, int l, int r, int i, int x) {
    if (l == r - 1) {
        return std::make_shared<Node>(x);
    }
    int mid = (l + r) / 2;
    if (i < mid) {
        return std::make_shared<Node>(update(root->left, l, mid, i, x), root->right);
    } else {
        return std::make_shared<Node>(root->left, update(root->right, mid, r, i, x));
    }
}
int get_sum(std::shared_ptr<Node> root) {
    return (root == nullptr ? 0 : root->sum);
}
int get(std::shared_ptr<Node> root, int l, int r, int k, bool& found) {
    if (l == r - 1) {
        if (k == get_sum(root)) {
            found = true;
        }
        return r;
    }
    int mid = (l + r) / 2;
    if (k <= get_sum(root->left)) {
        return get(root->left, l, mid, k, found);
    } else {
        return get(root->right, mid, r, k - get_sum(root->left), found);
    }
}
