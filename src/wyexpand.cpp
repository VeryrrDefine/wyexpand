#include <algorithm>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <stack>
#include <unordered_set>
#include <iostream>
#define MAX_SAFE_INTEGER 9007199254740991.00
#include "wyexpand/header.h"

typedef std::vector<int> vecint;
namespace wyexpand
{
  vecint succ(const vecint ord)
  {
    vecint ord1 = ord;
    if (ord1.size() == 0)
    {
      ord1.push_back(1);
    }
    else
    {
      ord1[0]++;
    }

    return ord1;
  }
  /**
   * 查找初始序列的父项
   * @param seq 初始序列
   */
  vecint calcInitialParent(const vecint &seq)
  {
    vecint parents(seq.size(), -1);
    std::stack<int> st; // 存储索引的单调栈

    for (int i = 0; i < seq.size(); i++)
    {
      while (!st.empty() && seq[st.top()] >= seq[i])
      {
        st.pop();
      }
      parents[i] = st.empty() ? -1 : st.top();
      st.push(i);
    }
    return parents;
  }
  /**
   * 查找序列的父项
   * @param seq 序列
   * @param seq 上一行序列的父项
   */
  vecint calcParent(const vecint &seq, const vecint &parents)
  {
    vecint seqParents(seq.size(), -1);
    std::unordered_set<int> parentSet(parents.begin(), parents.end());

    for (int i = 0; i < seq.size(); i++)
    {
      for (int j = i - 1; j >= 0; j--)
      {
        if (seq[j] < seq[i] && parentSet.count(j))
        {
          seqParents[i] = j;
          break;
        }
      }
    }
    return seqParents;
  }
  Expander::Expander(vecint enterseq)
  {
    this->initialSeq = enterseq;
  }
  vecint Expander::startExpand()
  {
    vecint currentSeq(this->initialSeq);
    vecint rawParents(calcInitialParent(currentSeq));
    if (this->parents[{0}].back() == -1)
    {
      std::clog << "Last Term is 1" << std::endl;

      currentSeq.pop_back();

      return currentSeq;
    }
    this->rows[{0}] = currentSeq;
    this->parents[{0}] = rawParents;

    vecint level{0};
    int maxIteration = 1e5;
    while (maxIteration--)
    {
      vecint seq = this->rows[level];
      vecint parents = this->parents[level];
      int lastValue = seq.back();
      int lastParent = parents.back();
      int lastParentValue = seq.at(lastParent);

      vecint nextSeq;
      for (auto i = seq.begin(); i != seq.end(); i++)
      {
        if (parents.at(*i) != -1)
          nextSeq.push_back(seq.at(*i) - seq.at(parents.at(*i)));
        else
          nextSeq.push_back(0);
      }
      level = succ(level);
      this->rows[level] = nextSeq;

      vecint nextparents = calcParent(nextSeq, parents);

      this->parents[level] = nextparents;
      // TODO: ω行处理
    }
    return currentSeq;
  }
}