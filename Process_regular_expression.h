#ifndef PROCESS
#define PROCESS
#include <iostream>
#include <vector>
#include <string>

class Process_regular_expression {
private:
    void print(int id, std::vector<std::vector<bool> >  can_process_substring);
public:
    std::string regexpr;
    Process_regular_expression(const std::string& regular = "1");

    void set_regexpr(std::string regular);

    int find_maximal_suffix(std::string word, std::ostream& out = std::cout);
};

#endif
