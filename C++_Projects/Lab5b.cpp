#include <iostream>
using namespace std;

double fasterExp(int x, int p)
{
    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
    {
        double result = fasterExp(x, p/2);
        return result * result;
    }
}

int crazySum (int n)
{
  if (n == 1)
    return 1;

  else
    {
      int val = fasterExp(n, n);
      return val = crazySum(n - 1);
    }
}

int bacteria(int startAmt, int numWeeks)
{
  float numAmt = (startAmt * 1.4) - 10000;

  if (numWeeks == 0)
    return startAmt;

  if (numAmt < 0)
    return 0;

  else
    {
      return bacteria(numAmt, numWeeks - 1);
    }
}

int mystery(int a, int b)
{
  if (a == 0)
    return b;
  if (b == 0)
    return a;

  return mystery(10*a+b%10, b/10);
}

int main()
{
  int startAmt;
  int numWeeks;

  // cout << crazySum(2) << endl;
  // cout << bacteria(30000, 0);
  cout << mystery(357, 8264);

}
