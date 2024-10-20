#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned long long int a, b, arrayLength, numberOfEvenNumbers, numberOfOddNumbers, result = 0;

    cin >> a >> b;

    arrayLength = b - a + 1;

    if (arrayLength % 2 == 0)
    {
        numberOfEvenNumbers = arrayLength / 2;
        numberOfOddNumbers = arrayLength / 2;
    }
    else if (a % 2 == 0)
    {
        numberOfEvenNumbers = arrayLength / 2 + 1;
        numberOfOddNumbers = arrayLength / 2;
    }
    else
    {
        numberOfEvenNumbers = arrayLength / 2;
        numberOfOddNumbers = arrayLength / 2 + 1;
    }

    result += (numberOfEvenNumbers % 2 == 0) ? numberOfEvenNumbers : numberOfEvenNumbers - 1;
    result += (numberOfOddNumbers % 2 == 0) ? numberOfOddNumbers : numberOfOddNumbers - 1; 

    cout << result << endl;
}