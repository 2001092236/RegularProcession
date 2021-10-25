#include <gtest/gtest.h>
#include "Process_regular_expression.h"
#include "regular_adapter.h"
#include "sequence_regulars.h"

TEST(Regular_adapter, Constructor_from_int) {
    int word_size = 4;
    regular_adapter adapter(word_size);
    ASSERT_TRUE(adapter.word_length == word_size);
    ASSERT_TRUE(adapter.belongs_regular.size() == word_size + 2);
    ASSERT_TRUE(adapter.belongs_regular[0].size() == word_size + 2);
}

TEST(Regular_adapter, Constructor_from_word1) {
    int word_size = 4;
    regular_adapter adapter(word_size);
    ASSERT_TRUE(adapter.word_length == word_size);
    ASSERT_TRUE(adapter.belongs_regular.size() == word_size + 2);
    ASSERT_TRUE(adapter.belongs_regular[0].size() == word_size + 2);
}

TEST(Regular_adapter, Constructor_from_word2) {
    std::string word = "acc";
    char symbol = 'c';
    regular_adapter adapter_A(symbol, word);
    regular_adapter adapter_B(symbol, word);
    adapter_B.belongs_regular = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0},
    };
    ASSERT_TRUE(adapter_A == adapter_B);
}

TEST(Regular_adapter, Constructor_from_word3) {
    std::string word = "acc";
    char symbol = '1';
    regular_adapter adapter_A(symbol, word);
    regular_adapter adapter_B(symbol, word);
    adapter_B.belongs_regular = {
            {0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
    };
    ASSERT_TRUE(adapter_A == adapter_B);
}

TEST(Regular_adapter, Swap) {
    int word_size1 = 4;
    int word_size2 = 5;
    regular_adapter adapter_A(word_size1), adapter_B(word_size2);
    ASSERT_NO_THROW(adapter_A.swap(adapter_B));
    ASSERT_TRUE(adapter_A.word_length == word_size2);
    ASSERT_TRUE(adapter_B.word_length == word_size1);
}

TEST(Regular_adapter, Equal_operator) {
    int word_size1 = 4;
    int word_size2 = 5;
    regular_adapter adapter_A(word_size1), adapter_B(word_size2);
    ASSERT_NO_THROW(adapter_A = adapter_B);
    ASSERT_TRUE(adapter_A.word_length == adapter_B.word_length);
    ASSERT_TRUE(adapter_A.belongs_regular == adapter_B.belongs_regular);
}

TEST(Regular_adapter, Equality_operator_simple) {
    int word_size1 = 4;
    int word_size2 = 5;
    regular_adapter adapter_A(word_size1), adapter_B(word_size2);
    ASSERT_FALSE(adapter_A == adapter_B);
}

TEST(Regular_adapter, Equality_operator_smart) {
    std::string word = "abca";
    int word_size2 = 4;
    regular_adapter adapter_A('c', word), adapter_B(word_size2);
    ASSERT_FALSE(adapter_A == adapter_B);
}

TEST(Regular_adapter, set_belongs_regular) {
    std::string word = "abca";
    int word_size2 = 4;
    regular_adapter adapter_A('c', word), adapter_B(word_size2);
    adapter_A.set_belongs_regular(adapter_B.belongs_regular);
    ASSERT_TRUE(adapter_A == adapter_B);
}

TEST(Regular_adapter, Brackets_operator) {
    int word_size = 4;
    regular_adapter adapter_A(word_size);
    ASSERT_NO_THROW(adapter_A[3]);
    ASSERT_FALSE(adapter_A[3][4]);

    const regular_adapter adapter_B(word_size);
    ASSERT_NO_THROW(adapter_B[4]);
    ASSERT_FALSE(adapter_B[4][2]);
}

TEST(Regular_adapter, Klini) {
    std::string word = "abcaa";
    char symbol = 'a';
    regular_adapter adapter_A(symbol, word);
    ASSERT_NO_THROW(adapter_A.klini());
    regular_adapter adapter_B(symbol, word);
    adapter_B.belongs_regular = {
            {0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 1, 0},
    };
    ASSERT_TRUE(adapter_A == adapter_B);
}

TEST(Regular_adapter, Add) {
    std::string word = "abcaa";
    char symbol = 'a';
    regular_adapter adapter_A(symbol, word);
    std::string word1 = "bcaac";
    char symbol1 = 'a';
    regular_adapter adapter_B(symbol1, word1);
    ASSERT_NO_THROW(adapter_A.add(adapter_B));
    regular_adapter adapter(symbol, word);
    adapter.belongs_regular = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_TRUE(adapter == adapter_A);
}

TEST(Regular_adapter, Mult) {
    std::string word = "abcaa";
    char symbol = 'a';
    regular_adapter adapter_A(symbol, word);
    std::string word1 = "bcaac";
    char symbol1 = 'c';
    regular_adapter adapter_B(symbol1, word1);
    ASSERT_NO_THROW(adapter_A.mult(adapter_B));
    regular_adapter adapter(symbol, word);
    adapter.belongs_regular = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_TRUE(adapter == adapter_A);
}


TEST(Sequence_regulars, Constructor) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    ASSERT_TRUE(seq.word == word);
}

TEST(Sequence_regulars, is_letter) {
    ASSERT_TRUE(sequence_regulars::is_letter('a'));
    ASSERT_TRUE(sequence_regulars::is_letter('b'));
    ASSERT_TRUE(sequence_regulars::is_letter('c'));
    ASSERT_TRUE(sequence_regulars::is_letter('1'));
    ASSERT_FALSE(sequence_regulars::is_letter('*'));
    ASSERT_FALSE(sequence_regulars::is_letter('+'));
    ASSERT_FALSE(sequence_regulars::is_letter('.'));
    ASSERT_FALSE(sequence_regulars::is_letter('d'));
}

TEST(Sequence_regulars, is_operation) {
    ASSERT_FALSE(sequence_regulars::is_operation('a'));
    ASSERT_FALSE(sequence_regulars::is_operation('b'));
    ASSERT_FALSE(sequence_regulars::is_operation('c'));
    ASSERT_FALSE(sequence_regulars::is_operation('1'));
    ASSERT_TRUE(sequence_regulars::is_operation('*'));
    ASSERT_TRUE(sequence_regulars::is_operation('+'));
    ASSERT_TRUE(sequence_regulars::is_operation('.'));
}

TEST(Sequence_regulars, get_operation) {
    ASSERT_TRUE(sequence_regulars::get_operation('.') == sequence_regulars::Operation::MULT);
    ASSERT_TRUE(sequence_regulars::get_operation('+') == sequence_regulars::Operation::PLUS);
    ASSERT_TRUE(sequence_regulars::get_operation('*') == sequence_regulars::Operation::STAR);
    ASSERT_ANY_THROW(sequence_regulars::get_operation('@'));
}

TEST(Sequence_regulars, process_symbol_mult) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    ASSERT_ANY_THROW(seq.process_symbol('%'));
    seq.process_symbol('a');
    seq.process_symbol('b');
    seq.process_symbol('.');
    regular_adapter adapter_A = seq.top();
    regular_adapter adapter('c', word);
    adapter.belongs_regular = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_TRUE(adapter_A == adapter);
}

TEST(Sequence_regulars, process_symbol_add) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    ASSERT_ANY_THROW(seq.process_symbol('%'));
    seq.process_symbol('a');
    seq.process_symbol('b');
    seq.process_symbol('+');
    regular_adapter adapter_A = seq.top();
    regular_adapter adapter('c', word);
    adapter.belongs_regular = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_TRUE(adapter_A == adapter);
}

TEST(Sequence_regulars, process_symbol_klini) {
    std::string word = "aaba";
    sequence_regulars seq(word);
    seq.process_symbol('a');
    seq.process_symbol('*');
    regular_adapter adapter_A = seq.top();
    regular_adapter adapter('c', word);
    adapter.belongs_regular = {
            {0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0},
    };
    ASSERT_TRUE(adapter_A == adapter);
}

TEST(Sequence_regulars, process_symbol_incorrect_1) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    seq.process_symbol('a');
    ASSERT_ANY_THROW(seq.process_symbol('+'));
}

TEST(Sequence_regulars, process_symbol_incorrect_2) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    ASSERT_ANY_THROW(seq.process_symbol('+'));
}

TEST(Sequence_regulars, pop) {
    std::string word = "abcab";
    sequence_regulars seq(word);
    seq.process_symbol('a');
    seq.pop();
    ASSERT_TRUE(seq.size() == 0);
}

TEST(Sequence_regulars, size) {
    std::string word = "aaba";
    sequence_regulars seq(word);
    ASSERT_TRUE(seq.size() == 0);
    seq.process_symbol('a');
    seq.process_symbol('b');
    seq.process_symbol('c');
    seq.process_symbol('+');
    ASSERT_TRUE(seq.size() == 2);
}


TEST(Process_regular_expression, Constructor) {
    std::string regular = "ab+c*.";
    Process_regular_expression processor(regular);
    ASSERT_TRUE(processor.regexpr == regular);
}

TEST(Process_regular_expression, set_regexpr) {
    std::string regular = "ab+c*.";
    Process_regular_expression processor;
    processor.set_regexpr(regular);
    ASSERT_TRUE(processor.regexpr == regular);
}

TEST(Process_regular_expression, find_maximal_suffix_incorrect) {
    std::string regular = "abc+";
    Process_regular_expression processor(regular);
    std::string word = "babc";
    ASSERT_ANY_THROW(processor.find_maximal_suffix(word));
}

TEST(Process_regular_expression, find_maximal_suffix_1) {
    std::string regular = "ab+c.aba.*.bac.+.+*";
    std::string word = "babc";
    Process_regular_expression processor(regular);
    std::stringstream buf;
    ASSERT_TRUE(processor.find_maximal_suffix(word, buf) == 2);
}

TEST(Process_regular_expression, find_maximal_suffix_2) {
    std::string regular = "acb..bab.c.*.ab.ba.+.+*a.";
    std::string word = "cbaa";
    Process_regular_expression processor(regular);
    std::stringstream buf;
    ASSERT_TRUE(processor.find_maximal_suffix(word, buf) == 1);
}

TEST(Process_regular_expression, find_maximal_suffix_INF) {
    std::string regular = "ab+c.";
    std::string word = "cbaa";
    Process_regular_expression processor(regular);
    std::stringstream buf;
    ASSERT_TRUE(processor.find_maximal_suffix(word, buf) == -1);
}

TEST(Process_regular_expression, find_maximal_suffix_3) {
    std::string regular = "ab+b*.a*.";
    std::string word = "cbbaa";
    Process_regular_expression processor(regular);
    std::stringstream buf;
    ASSERT_TRUE(processor.find_maximal_suffix(word, buf) == 4);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
