#include <iostream>
using namespace std;

int fast_exp_calls = 0;
int faster_exp_calls = 0;

int power(int x, int p)
{
  int result = 1;
  for(int i=0; i < p; i++)
    result *= x;
  return result;
}

int recPower(int x, int p)
{
  if(p == 0)
    return 1;
  else if (p == 1)
    return x;
  else
    return x * recPower(x, p-1);
}

double fastExp(int x, int p)
{
    fast_exp_calls++;

    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
        return fastExp(x, p/2) * fastExp(x, p/2);

    else
        return x * fastExp(x, p/2)  * fastExp(x, p/2);
}

double fasterExp(int x, int p)
{
    faster_exp_calls++;

    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
    {
        double result = fasterExp(x, p/2);
        return result * result;
    }

    else
    {
        double result = fasterExp(x, p/2);
        return x * result * result;
    }
}

int main()
{
  int x = 5;
  int p = 200;

  cout << x << "^" << p << " = " << fastExp(x, p) << "\n";
  cout << x << "^" << p << " = " << fasterExp(x, p) << "\n";

  cout << "Fast Exp calls: " << fast_exp_calls << "\n"; //O(n) function
  cout << "Faster Exp calls: " << faster_exp_calls << "\n"; //Log function

  return 0;
}
