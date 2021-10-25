#ifndef REGULAR_ADAPTER
#define REGULAR_ADAPTER
#include <vector>
#include <string>

class regular_adapter {
public:
    void swap(regular_adapter& other);
    int word_length;
    std::vector<std::vector<bool> > belongs_regular;
    explicit regular_adapter(int word_length);

    regular_adapter(char symbol, const std::string& word);

    regular_adapter& operator=(const regular_adapter& other);

    std::vector<bool>& operator[](size_t index);

    const std::vector<bool>& operator[](size_t index) const;

    regular_adapter& klini();

    regular_adapter& add(const regular_adapter& other);

    regular_adapter& mult(const regular_adapter& other);

    bool operator==(const regular_adapter& other) const;

    void set_belongs_regular(std::vector<std::vector<bool> > other);
};

#endif
