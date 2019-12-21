// Naive_Multiplication.cpp : O(n^2)

#include <iostream>
#include <vector>

using namespace std;

void normalize(vector<int> &num);
vector<int> multiply(const vector<int> &a, const vector<int> &b);

int main()
{
   vector<int> lhs{ 3, 2, 1 }; reverse(lhs.begin(), lhs.end());
   vector<int> rhs{ 6, 5, 4 }; reverse(rhs.begin(), rhs.end());

   for (vector<int>::iterator i = lhs.begin(); i < lhs.end(); ++i)
      cout << *i;
   cout << endl;

   for (vector<int>::iterator i = rhs.begin(); i < rhs.end(); ++i)
      cout << *i;
   cout << endl;

   vector<int> ret = multiply(lhs, rhs);
   reverse(ret.begin(), ret.end());
   for (vector<int>::iterator i = ret.begin(); i < ret.end(); ++i)
      cout << *i;
   cout << endl;
}

// num[] 자릿수 올림을 처리한다.
void normalize(vector<int> &num) {
   num.push_back(0);
   // 자릿수 올림을 처리한다
   for (size_t i = 0; i + 1 < num.size(); ++i) {
      if (num[i] < 0) {
         int borrow = (abs(num[i]) + 9) / 10;
         num[i + 1] -= borrow;
         num[i] += borrow * 10;
      }
      else {
         num[i + 1] += num[i] / 10;
         num[i] %= 10;
      }
   }
   while (num.size() > 1 && num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
   vector<int> c(a.size() + b.size() + 1, 0);
   for (size_t i = 0; i < a.size(); ++i)
      for (size_t j = 0; j < b.size(); ++j)
         c[i + j] += a[i] * b[j];

   normalize(c);
   return c;
}