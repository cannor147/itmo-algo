#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

class suffix_array {

    std::string word;
    std::vector<int> values;

private:
    bool cond(int x0, int y0, int x1, int y1, int x2, int y2) {
        return x0 != y0 ? x0 < y0 : (x1 != y1 ? x1 < y1 : x2 < y2);
    }
    void csort(std::vector<int> &s, std::vector<int> &a, std::vector<int> &b, int offset, int length, int alphabet_size) {
        std::vector<int> count(alphabet_size + 1, 0);

        for (int i = 0; i < length; ++i) {
            count[s[a[i] + offset]]++;
        }
        for (int d = 0, sum = 0; d <= alphabet_size; ++d) {
            sum += count[d];
            count[d] = sum - count[d];
        }
        for (int i = 0; i < length; ++i) {
            b[count[s[a[i] + offset]]] = a[i];
            count[s[a[i] + offset]]++;
        }
    }
    void karkkainen_sanders(std::vector<int> &s, std::vector<int> &suf_array, int length, int alphabet_size) {
        int length_a = (length + 2) / 3;
        int length_b = length / 3;
        int length_c = (length + 2) / 3;
        int length_ab = length_a + length_b;

        int k = 0;
        std::vector<int> indeces_ab(length_ab, 0);
        for (int j = 0; j < length_ab; ++j) {
            k++;
            if (k % 3 == 0) {
                k++;
            }
            indeces_ab[j] = k;
        }
        std::vector<int> tmp_ab(length_ab, 0);
        csort(s, indeces_ab, tmp_ab, 2, length_ab, alphabet_size);
        csort(s, tmp_ab, indeces_ab, 1, length_ab, alphabet_size);
        csort(s, indeces_ab, tmp_ab, 0, length_ab, alphabet_size);
        for (int i = 0; i < length_ab; ++i) {
            indeces_ab[i] = tmp_ab[i];
        }

        std::vector<int> codes(length_ab, 0);
        std::vector<int> previous{-1, -1, -1};
        int code_number = 0;
        for (int i = 0; i < length_ab; ++i) {
            if (cond(previous[0], s[indeces_ab[i]], previous[1], s[indeces_ab[i] + 1], previous[2], s[indeces_ab[i] + 2])) {
                code_number++;
            }
            codes[i] = code_number;

            previous[0] = s[indeces_ab[i]];
            previous[1] = s[indeces_ab[i] + 1];
            previous[2] = s[indeces_ab[i] + 2];
        }
        std::vector<int> suf_array_ab(length_ab + 2, 0);
        suf_array_ab[length_ab] = suf_array_ab[length_ab + 1] = -1;
        if (code_number < length_ab) {
            std::vector<int> s_ab(length_ab + 3, 0);
            for (int i = 0; i < length_ab; ++i) {
                s_ab[indeces_ab[i] / 3 + (indeces_ab[i] % 3 == 1 ? 0 : length_a)] = codes[i];
            }
            karkkainen_sanders(s_ab, suf_array_ab, length_ab, code_number);
            for (int i = 0; i < length_ab; ++i) {
                indeces_ab[i] = (suf_array_ab[i] < length_a ? 1 + 3 * suf_array_ab[i] : 2 + 3 * (suf_array_ab[i] - length_a));
            }
        }
        for (int i = 0; i < length_ab; ++i) {
            suf_array_ab[indeces_ab[i] - (indeces_ab[i] + 2) / 3] = i;
        }

        std::vector<int> indeces_c(length_c, 0);
        for (int i = 0, j = 0; j < length_c; ++i) {
            if (indeces_ab[i] % 3 == 1){
                indeces_c[j++] = indeces_ab[i] - 1;
            }
        }
        std::vector<int> tmp_c(length_c, 0);
        csort(s, indeces_c, tmp_c, 0, length_c, alphabet_size);
        for (int i = 0; i < length_c; ++i) {
            indeces_c[i] = tmp_c[i];
        }

        std::vector<int> ab{-1, -1, -1};
        std::vector<int> c{-1, -1, -1};
        for (int i = 0, index_ab = (length % 3 == 1) ? 1 : 0, index_c = 0; i < length; ++i) {
            bool f;
            if (index_ab < length_ab && index_c < length_c) {
                if (indeces_ab[index_ab] % 3 == 1) {
                    ab[0] = s[indeces_ab[index_ab]];
                    ab[1] = suf_array_ab[indeces_ab[index_ab] - indeces_ab[index_ab] / 3];
                    c[0] = s[indeces_c[index_c]];
                    c[1] = suf_array_ab[indeces_c[index_c] - indeces_c[index_c] / 3];
                } else {
                    ab[0] = s[indeces_ab[index_ab]];
                    ab[1] = s[indeces_ab[index_ab] + 1];
                    ab[2] = suf_array_ab[indeces_ab[index_ab] + 1 - (indeces_ab[index_ab] + 1) / 3];
                    c[0] = s[indeces_c[index_c]];
                    c[1] = s[indeces_c[index_c] + 1];
                    c[2] = suf_array_ab[indeces_c[index_c] + 1 - (indeces_c[index_c] + 1) / 3];
                }
                f = cond(c[0], ab[0], c[1], ab[1], c[2], ab[2]);
            } else{
                f = index_c < length_c;
            }
            suf_array[i] = f ? indeces_c[index_c++] : indeces_ab[index_ab++];
        }
    }
    std::vector<int> kasai() {
        std::vector<int> lcp(values.size(), 0), pos(values.size(), 0);
        for (int i = 0; i < values.size(); ++i) {
            pos[values[i]] = i;
        }

        int k = 0;
        for (int i = 0; i < values.size(); ++i) {
            if (k > 0) {
                k--;
            }
            if (pos[i] == values.size() - 1) {
                lcp[values.size() - 1] = -1;
                k = 0;
            } else {
                int j = values[pos[i] + 1];
                while (word[i + k] == word[j + k] && i + k < values.size() && j + k < values.size()) {
                    k++;
                }
                lcp[pos[i]] = k;
            }
        }

        lcp.pop_back();
        return lcp;
    }

public:
    explicit suffix_array(std::string word) {
        std::set<char> symbols;
        for (int i = 0; i < word.length(); ++i) {
            if (symbols.count(word[i]) == 0) {
                symbols.insert(word[i]);
            }
        }

        int k = 0;
        std::unordered_map<char, int> convert_map;
        for (const auto &symbol : symbols) {
            k++;
            convert_map[symbol] = k;
        }

        std::vector<int> result;
        for (int i = 0; i < word.length(); ++i) {
            result.push_back(convert_map[word[i]]);
        }

        result.push_back(0);
        result.push_back(0);
        result.push_back(0);
        if (word.length() % 2 == 1) {
            result.push_back(0);
        }

        this->word = word;
        this->values = std::vector<int>(word.length(), 0);
        karkkainen_sanders(result, this->values, word.length(), k);
    }

    const std::vector<int> &get_suffix_array() const {
        return values;
    }
    std::vector<int> get_lcp_for_suffices() {
        return kasai();
    }
};

int main() {
    std::string word;
    std::cin >> word;
    word += "$";

    suffix_array suf_array = suffix_array(word);
    auto ans = suf_array.get_suffix_array();
    for (int i = 1; i < ans.size(); ++i) {
        std::cout << ans[i] + 1 << " ";
    }
    std::cout << std::endl;
    auto lcp = suf_array.get_lcp_for_suffices();
    for (int i = 1; i < lcp.size(); ++i) {
        std::cout << lcp[i] << " ";
    }

}