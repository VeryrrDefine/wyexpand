#ifndef WYEXPAND_H
#define WYEXPAND_H

#include <cstdint>
#include <vector>
#include <map>
typedef std::vector<int> vecint;
namespace wyexpand
{
  vecint calcInitialParent(const vecint &seq);
  vecint calcParent(const vecint &seq, const vecint &parents);
  vecint succ(const vecint ord);
  class Expander
  {
  public:
    Expander(vecint seq);

    std::map<vecint, vecint> rows;
    std::map<vecint, vecint> parents;
    vecint initialSeq;
    vecint startExpand();
  };
}
#endif
