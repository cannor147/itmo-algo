#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

const int MAX_SIZE = 100000;

class suffix_tree {

    class node {
    private:
        std::string *word;
        node *parent, *suffix_link;
        std::map<char, node*> children;

        int edge_start;
        int edge_end;
        int parent_depth;

    public:
        explicit node(std::string *word) {
            this->word = word;
            this->parent = nullptr;
            this->suffix_link = nullptr;
            this->children = std::map<char, node*>();

            this->edge_start = 0;
            this->edge_end = 0;
            this->parent_depth = 0;
        }

        bool is_leaf() {
            return children.empty();
        }
        bool has_parent() {
            return parent != nullptr;
        }
        bool has_child(char symbol) {
            return children.count(symbol) > 0;
        }
        bool has_suffix_link() {
            return suffix_link != nullptr;
        }

        int get_start() const {
            return edge_start;
        }
        int get_end() const {
            return edge_end;
        }
        int get_parent_depth() const {
            return parent_depth;
        }
        int get_depth() {
            return parent_depth + edge_end - edge_start;
        }
        node* const get_parent() {
            return parent;
        }
        node* const get_child(char symbol) {
            return children[symbol];
        }
        const std::map<char, node*>& get_children() {
            return children;
        }
        node* const get_suffix_link() {
            return suffix_link;
        }

        void set_suffix_link(node* link) {
            suffix_link = link;
        }

        void create_link(node *child, int start, int end) {
            children[(*word)[start]] = child;
            child->parent = this;

            child->edge_start = start;
            child->edge_end = end;
            child->parent_depth = this->get_depth();
        }
    };

private:
    std::string word;
    std::vector<node> child_nodes;
    node *root, *current_suffix;

    node *_current;
    int _index, _count;
    bool _split;

    node *create_node() {
        child_nodes.emplace_back(&word);
        return &child_nodes.back();
    }
    void add_suffix_link(node *current) {
        if (current_suffix != nullptr) {
            current_suffix->set_suffix_link(current);
            current_suffix = nullptr;
        }
    }
    bool check_node(node *current, const std::string &substring, int index) {
        for (int i = current->get_start(); i < current->get_end(); i++) {
            if (word[i] == substring[index]) {
                index++;
                if (index == substring.length()) return true;
            } else {
                break;
            }
        }
        if (current->has_child(substring[index])) {
            return check_node(current->get_child(substring[index]), substring, index);
        }
        return false;
    }
    void build(int limit) {
        for (; _index < limit - 1; ++_index) {
            char symbol = word[_index + 1];
            for (int j = _count; j <= _index + 1; ++j, ++_count) {
                if (_split) {
                    if (_current->has_parent() && !_current->has_suffix_link()) {
                        _current = _current->get_parent();
                    }
                    _current = !_current->has_suffix_link() ? root : _current->get_suffix_link();
                    if (_index - j + 1 > 0) {
                        for (int k = _current->get_depth() + j; _index - j + 1 <= _current->get_parent_depth() || _index - j + 1 >
                                                                                                                  _current->get_depth(); k += _current->get_end() - _current->get_start()) {
                            _current = _current->get_child(word[k]);
                        }
                    }
                }

                _split = true;
                int pos = _current->get_start() - _current->get_parent_depth() + _index - j + 1;
                if (_current->get_depth() == _index - j + 1) {
                    add_suffix_link(_current);
                    if (_current->has_child(symbol)) {
                        _current = _current->get_child(symbol);
                        _split = false;
                        break;
                    } else {
                        _current->create_link(create_node(), _index + 1, word.length());
                    }
                } else if (word[pos] == symbol) {
                    add_suffix_link(_current);
                    if (!_current->is_leaf() || _current->get_depth() != _current->get_end() - j) {
                        _split = false;
                        break;
                    }
                } else {
                    node *splitting_node = create_node();
                    _current->get_parent()->create_link(splitting_node, _current->get_start(), pos);

                    splitting_node->create_link(_current, pos, _current->get_end());
                    splitting_node->create_link(create_node(), _index + 1, word.length());
                    add_suffix_link(splitting_node);

                    if (splitting_node->get_depth() <= 1) {
                        splitting_node->set_suffix_link(root);
                    } else {
                        current_suffix = splitting_node;
                    }
                    _current = splitting_node;
                }
            }
        }
    }

public:
    explicit suffix_tree(const std::string word, int stop = -1) {
        this->word = word;
        this->child_nodes.reserve(3 * MAX_SIZE);
        this->root = create_node();
        this->current_suffix = nullptr;

        _current = create_node();
        root->create_link(_current, 0, word.length());

        _index = 0;
        _count = 1;
        _split = true;
        int limit = (stop == -1) ? word.length() : stop;
        build(limit);
    }

    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> to_vector() {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> result;
        std::map<node*, int> mapping;

        std::queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node *current = q.front();
            q.pop();

            if (mapping.count(current) == 0) {
                mapping[current] = mapping.size();
            }
            if (current->is_leaf()) {
                continue;
            }
            for (const auto &child : current->get_children()) {
                if (mapping.count(child.second) == 0) {
                    mapping[child.second] = mapping.size();
                }
                result.push_back({{mapping[current], mapping[child.second]}, {child.second->get_start(), child.second->get_end()}});
                q.push(child.second);
            }
        }
        return result;
    }
    void continue_build(int limit) {
        build(limit);
    }
    bool contains(const std::string &substring) {
        return check_node(root, substring, 0);
    }
};

int main() {
    std::string command, word;

    std::string text = "_";
    std::vector<std::pair<bool, std::string>> queries;
    while (std::cin >> command) {
        if (command == "exit") break;
        std::cin >> word;
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        queries.push_back({command == "A", word});
        text += word;
    }

    int count = 1;
    suffix_tree t = suffix_tree(text, count);
    for (const auto &query : queries) {
        if (query.first) {
            count += query.second.length();
            t.continue_build(count);
        } else {
            std::string ans = t.contains(query.second) ? "YES" : "NO";
            std::cout << ans << std::endl;
        }
    }
}