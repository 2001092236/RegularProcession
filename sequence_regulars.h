#ifndef SEQUENCE_REGULARS
#define SEQUENCE_REGULARS
#include <string>
#include <stack>
#include "regular_adapter.h"

class sequence_regulars {
public:
    enum Operation {
        MULT,
        PLUS,
        STAR
    };

    std::string word;
    std::stack<regular_adapter> sequence_of_regulars;
    static bool is_letter(char symbol);

    static bool is_operation(char symbol);

    static Operation get_operation(char symbol);

    static const std::string error_message_incorrect_symbol;
    static const std::string error_message_incorrect_format_of_operation;
    sequence_regulars(const std::string& word);

    void process_symbol(char symbol);

    size_t size() const;

    regular_adapter& top();

    void pop();
};

#endif
