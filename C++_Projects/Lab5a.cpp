#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;


float Power(float X, int p)
{
  float xp;
  float temp;

   if (p == 0)
    xp = 1;

   else if (p == 1)
    xp = X;

   else if (p < 0)
    return 1/Power(X, -p);

   else
   {
     if (p % 2 == 0)
     {
       int temp = Power (X, p/2);
       return temp * temp;
     }
     else if (p % 2 == 1)
     {
       temp = Power(X, p/2);
       xp = temp * temp * X;
     }
   }
   return xp;
}

main()
{
  for (int i = 0; i < 10; i++)
    cout << "2" << "^" << i << Power(2.0, -i) << endl;

  return 0;
}
