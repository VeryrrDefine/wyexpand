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
  bool isAllMinusOne1(const vecint &vec)
  {
    return std::all_of(vec.begin(), vec.end(),
                       [](int x)
                       { return x == -1; });
  }
  vecint succ(const vecint ord)
  {
    vecint ord1 = ord;
    if (ord1.empty())
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
  vecint addExp(const vecint &ord, int exponent, bool minus1)
  {
    if (minus1 && exponent == 0)
      throw std::logic_error("Exponent cannot be 0 on Minus1");
    if (exponent == 0)
      return succ(ord);
    vecint ord1 = ord;
    if (ord1.size() < exponent)
    {
      ord1 = std::vector(exponent, 0);
      ord1.push_back(1);
    }
    else
    {
      for (int i = 0; i < exponent; i++)
      {
        ord1.at(i) = 0;
      }
      ord1[exponent]++;
    }
    if (minus1)
      ord1[0]--;
    return ord1;
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
        if (seq[j] < seq[i] && seq[j] != 0 && parentSet.count(j))
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
    if (enterseq.size() < 2)
      throw std::logic_error("Sequence too short");
    if (enterseq.at(0) != 1)
      throw std::logic_error("Illegal sequence");

    this->initialSeq = enterseq;
  }
  vecint Expander::startExpand()
  {
    vecint currentSeq(this->initialSeq);
    vecint rawParents(calcInitialParent(currentSeq));
    if (rawParents.back() == -1)
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
      for (int i = 0; i < seq.size(); ++i)
      {
        std::cout << i << std::endl;
        if (parents.at(i) != -1)
          nextSeq.push_back(seq.at(i) - seq.at(parents.at(i)));
        else
          nextSeq.push_back(0);
      }
      level = succ(level);
      this->rows[level] = nextSeq;

      vecint nextparents = calcParent(nextSeq, parents);

      this->parents[level] = nextparents;
      if (isAllMinusOne1(nextparents))
      {
        std::clog << "All Minus One, check for ω+ rows " << std::endl;
        break;
      }
      // TODO: ω行处理
    }
    return currentSeq;
  }

  vecint Expander::calcCrossRow(int *exponent)
  {
    /**
Row 0     S1,3,2,5          P-1,[0],[0],2
Row 1     S0,2,1,3          P-1,-1,-1,[2]
Row 2     S0,0,0,2          P-1,-1,-1,-1

Row -1,1  S1,2,1,2          P-1,0, 0, 2
Row 0,1   S0,1,0,1          P-1,-1,-1,-1
     */

    /**
Row 0     S1,4,2,5          P-1,[0],[0],2
Row 1     S0,3,1,3          P-1,-1,-1,[2]
Row 2     S0,0,0,2          P-1,-1, {-1},-1

Row -1,1   1,3,1,2          P-1,{0}, 0,{2}
Row 0,1    0,2,0,1          P-1,-1,-1,-1

Row -1,0,1 1,2,1,1          P-1,0 , -1, 2
Row 0,0,1  0,1,0,0          P-1,-1, -1, -1
     */
    /**
Row 0         S1,3,10           P-1,[0],1
Row 1         S0,2,7            P-1,-1,[1]
Row 2         S0,0,5            P-1,-1,-1

Row -1,1      S1,2,5            P-1,{0}, 1
Row 0,1       S0,1,3            P-1,-1,{1}
Row 1,1       S0,0,2            P-1,-1,-1
这里有一个0*n 1的数组，可以shift

Row -1,2      S?,1,2            P?,0,1
     */
    vecint lastlevel = {0};
    vecint level = {1};
  }

}