#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

class suffix_bor {

    struct bor_node {
        int index;
        std::map<char, bor_node*> children;

        explicit bor_node(int index) : index(index) {}
        bor_node() : index(0) {}

        void add_node(int ut, char symbol) {
            children[symbol] = new bor_node(ut);
        }
    };

    bor_node head;

public:
    explicit suffix_bor(const std::string &word) {
        int number = 1;
        for (int i = 0; i < word.length(); ++i) {
            std::string suffix = word.substr(i, word.length() - i);
            int index = 0;
            bor_node *current = &head;

            while (index < suffix.length()) {
                if (current->children.count(suffix[index]) == 0) {
                    current->add_node(number, suffix[index]);
                    number++;
                }
                current = current->children[suffix[index]];
                index++;
            }
        }
    }

    std::vector<std::pair<std::pair<int, int>, char>> to_vector() {
        std::queue<bor_node*> q;
        q.push(&head);

        std::vector<std::pair<std::pair<int, int>, char>> result;
        while (!q.empty()) {
            bor_node *current = q.front();
            q.pop();

            if (current->children.empty()) continue;
            for (const auto &child : current->children) {
                result.push_back({{current->index, child.second->index}, child.first});
                q.push(child.second);
            }
        }
        std::sort(result.begin(), result.end(), [](std::pair<std::pair<int, int>, char> a, std::pair<std::pair<int, int>, char> b) { return a.first.second < b.first.second; });
        std::sort(result.begin(), result.end(), [](std::pair<std::pair<int, int>, char> a, std::pair<std::pair<int, int>, char> b) { return a.first.first < b.first.first; });
        return result;
    }
};

int main() {
    std::string word;
    std::cin >> word;
    suffix_bor bor = suffix_bor(word);

    auto ans = bor.to_vector();
    int vertex = 0;
    for (const auto &item : ans) {
        if (item.first.first > vertex) {
            vertex = item.first.first;
        }
        if (item.first.second > vertex) {
            vertex = item.first.second;
        }
    }
    std::cout << vertex + 1 << " " << ans.size() << std::endl;
    for (const auto &item : ans) {
        std::cout << item.first.first + 1 << " " << item.first.second + 1 << " " << item.second << std::endl;
    }
    return 0;
}