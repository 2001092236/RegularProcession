#include "Process_regular_expression.h"
#include "regular_adapter.h"
#include "sequence_regulars.h"

Process_regular_expression::Process_regular_expression(const std::string& regular): regexpr(regular) {}

void Process_regular_expression::set_regexpr(std::string regular) {
    regexpr = regular;
}

int Process_regular_expression::find_maximal_suffix(std::string word, std::ostream& out) {
    int word_len = word.size();
    sequence_regulars sequence_of_regulars(word);
    for (char symbol: regexpr) {
        sequence_of_regulars.process_symbol(symbol);
    }
    if (sequence_of_regulars.size() != 1) {
        throw sequence_regulars::error_message_incorrect_format_of_operation;
    }
    regular_adapter final_regular = sequence_of_regulars.top();
    int maximal_suffix_length = -1;
    for (int pos = word_len + 1; pos >= 1; --pos) {
        if (final_regular[pos][word_len])
            maximal_suffix_length = word_len - pos + 1;
    }
    if (maximal_suffix_length != -1) {
        out << maximal_suffix_length << "\n";
    } else {
        out << "INF\n";
    }
    return maximal_suffix_length;
}
