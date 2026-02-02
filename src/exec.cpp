#include <vector>
#include <iostream>
#include <string>
#include <map>
// #define MAX_SAFE_INTEGER 9007199254740991.00

#include "wyexpand/header.h"
using namespace wyexpand;

std::string seq_to_string(vecint seq)
{
    std::string result = "";
    for (auto it = seq.begin(); it != seq.end(); ++it)
    {
        result += std::to_string(*it);
        if (it != seq.end() - 1)
        {
            result += ",";
        }
    }
    return result;
}

int main()
{
    vecint a{1, 2};
    Expander expander(a);
    std::cout << "Initial Sequence: " << seq_to_string(expander.initialSeq) << std::endl;
    vecint result(expander.startExpand());
    std::cout << "Result: " << seq_to_string(result) << std::endl;
    vecint level({0});
    while (true)
    {
        auto seq = expander.rows[level];
        auto parents = expander.parents[level];
        if (seq.empty())
            break;

        std::cout << "Row " + seq_to_string(level) + " S" << seq_to_string(seq) << "\t\t";
        std::cout << "P" << seq_to_string(parents) << std::endl;
        level = succ(level);
    }
    return 0;
}