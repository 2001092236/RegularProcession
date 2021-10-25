#include "sequence_regulars.h"

bool sequence_regulars::is_letter(char symbol) {
    return (symbol <= 'c' && symbol >= 'a') || (symbol == '1');
}

bool sequence_regulars::is_operation(char symbol) {
    return symbol == '.' || symbol == '*' || symbol == '+';
}

sequence_regulars::Operation sequence_regulars::get_operation(char symbol) {
    if (symbol == '.') {
        return Operation::MULT;
    }
    if (symbol == '+') {
        return Operation::PLUS;
    }
    if (symbol == '*') {
        return Operation::STAR;
    }
    throw error_message_incorrect_symbol;
}

sequence_regulars::sequence_regulars(const std::string& word): word(word) {}

void sequence_regulars::process_symbol(char symbol) {
    if (is_letter(symbol)) {
        sequence_of_regulars.push(regular_adapter(symbol, word));
        return;
    }
    if (!is_operation(symbol)) {
        throw error_message_incorrect_symbol;
    }
    Operation operation = get_operation(symbol);
    regular_adapter last_regular = top();
    pop();
    if (operation == Operation::STAR) {
        sequence_of_regulars.push(last_regular.klini());
        return;
    }
    regular_adapter prelast_regular = top();
    pop();
    if (operation == Operation::PLUS) {
        prelast_regular.add(last_regular);
    } else {
        prelast_regular.mult(last_regular);
    }
    sequence_of_regulars.push(prelast_regular);
}

size_t sequence_regulars::size() const {
    return sequence_of_regulars.size();
}

regular_adapter& sequence_regulars::top() {
    if (size() == 0) {
        throw error_message_incorrect_format_of_operation;
    }
    return sequence_of_regulars.top();
}

void sequence_regulars::pop() {
    sequence_of_regulars.pop();
}

const std::string sequence_regulars::error_message_incorrect_symbol = "Incorrect symbol in regular expression!!!\n";
const std::string sequence_regulars::error_message_incorrect_format_of_operation = "Incorrect formal expression. Wrong operation usage!!!\n";
