#include <iostream>
using namespace std;

int ackermann (int m, int n)
{
    if (m == 0)
        return n + 1;

    else if (m > 0 && n == 0)
        return ackermann(m - 1, 1);

    else if (m > 0 && n > 0)
        return ackermann(m - 1, ackermann(m, n - 1));
}

int main()
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            cout << "ackermann(" << i << ", " << j << ") = " << ackermann(i, j) << endl;

    return 0;
}
