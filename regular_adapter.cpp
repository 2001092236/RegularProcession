#include "regular_adapter.h"

void regular_adapter::swap(regular_adapter& other) {
    std::swap(word_length, other.word_length);
    std::swap(belongs_regular, other.belongs_regular);
}

regular_adapter::regular_adapter(int word_length): word_length(word_length),
        belongs_regular(std::vector<std::vector<bool> > (word_length + 2,std::vector<bool> (word_length + 2, false))) {}


regular_adapter::regular_adapter(char symbol, const std::string& word): regular_adapter(word.size()) {
    if (symbol == '1') {
        for (size_t pos = 0; pos <= word_length; ++pos) {
            belongs_regular[pos + 1][pos] = true;
        }
    } else {
        for (size_t pos = 1; pos <= word_length; ++pos) {
            if (word[pos - 1] == symbol) {
                belongs_regular[pos][pos] = true;
            }
        }
    }
}


regular_adapter& regular_adapter::operator=(const regular_adapter& other) {
    regular_adapter copy = other;
    swap(copy);
    return *this;
}

std::vector<bool>& regular_adapter::operator[](size_t index) {
    return belongs_regular[index];
}

const std::vector<bool>& regular_adapter::operator[](size_t index) const {
    return belongs_regular[index];
}

regular_adapter& regular_adapter::klini() {
    regular_adapter ans(word_length);
    for (size_t pos = 0; pos <= word_length; ++pos) {
        ans[pos + 1][pos] = true;
    }
    for (int length = 1; length <= word_length; ++length) {
        for (int left_pos = 1; left_pos + length - 1 <= word_length; ++left_pos) {
            int right_pos = left_pos + length - 1;
            for (int border_pos = left_pos; border_pos <= right_pos; ++border_pos) {
                bool can_process = belongs_regular[left_pos][border_pos];
                if (border_pos < right_pos) {
                    can_process = (can_process && belongs_regular[border_pos + 1][right_pos]);
                }
                if (can_process) {
                    ans[left_pos][right_pos] = true;
                    break;
                }
            }
        }
    }
    *this = ans;
    return *this;
}

regular_adapter& regular_adapter::add(const regular_adapter& other) {
    regular_adapter ans(word_length);
    for (int left_pos = 1; left_pos <= word_length + 1; ++left_pos) {
        for (int right_pos = left_pos - 1; right_pos <= word_length; ++right_pos) {
            bool can = false;
            can |= (belongs_regular[left_pos][right_pos] || other[left_pos][right_pos]);
            ans[left_pos][right_pos] = can;
        }
    }
    *this = ans;
    return *this;
}

regular_adapter& regular_adapter::mult(const regular_adapter& other) {
    regular_adapter ans(word_length);
    for (int left_pos = 1; left_pos <= word_length; ++left_pos) {
        for (int right_pos = left_pos - 1; right_pos <= word_length; ++right_pos) {
            for (int border_pos = left_pos - 1; border_pos <= right_pos; ++border_pos) {
                bool can = belongs_regular[left_pos][border_pos] && other[border_pos + 1][right_pos];
                if (can) {
                    ans[left_pos][right_pos] = true;
                    break;
                }
            }
        }
    }
    *this = ans;
    return *this;
}

bool regular_adapter::operator==(const regular_adapter& other) const {
    if (word_length != other.word_length) {
        return false;
    }
    for (int left_pos = 0; left_pos < belongs_regular.size(); ++left_pos) {
        for (int right_pos = 0; right_pos < belongs_regular[left_pos].size(); ++right_pos) {
            if (belongs_regular[left_pos][right_pos] != other[left_pos][right_pos]) {
                return false;
            }
        }
    }
    return true;
}

void regular_adapter::set_belongs_regular(std::vector<std::vector<bool> > other) {
    belongs_regular = other;
}
