#include <vector>
#include <iostream>
#include <string>
#include <map>
// #define MAX_SAFE_INTEGER 9007199254740991.00

#include "wyexpand/header.h"
using namespace wyexpand;

std::string seq_to_string(std::vector<int> seq)
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
    std::vector<int> a{1, 1};
    Expander expander(a);
    std::cout << "Initial Sequence: " << seq_to_string(expander.initialSeq) << std::endl;
    std::vector<int> result(expander.startExpand());
    std::cout << "Result: " << seq_to_string(result) << std::endl;
    std::cout << "Row 1 Parents: " << seq_to_string(expander.parents[{0}]) << std::endl;
    return 0;
}