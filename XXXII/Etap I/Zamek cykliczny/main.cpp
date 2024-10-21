#include <iostream>
#include <string>

using namespace std;

string rotate(const string &n)
{
    if (n.size() == 1)
    {
        return n;
    }

    string rotated = n.substr(1) + n[0];
    rotated.erase(0, rotated.find_first_not_of('0'));

    return rotated;
}

string addOne(const string &n)
{
    string result = n;

    int carry = 1;

    for (int i = result.size() - 1; i >= 0; --i)
    {
        if (carry == 0)
        {
            break;
        }

        int digit = result[i] - '0';

        digit += carry;

        if (digit == 10)
        {
            result[i] = '0';
            carry = 1;
        }
        else
        {
            result[i] = digit + '0';
            carry = 0;
        }
    }

    if (carry > 0)
    {
        result.insert(result.begin(), '1');
    }

    return result;
}

bool isPowerOfTen(const string &n)
{
    if (n.length() < 2)
    {
        return false;
    }

    if (n.find_first_not_of('0', 1) == string::npos)
    {
        return true;
    }

    return false;
}

bool isAllNines(const string &n)
{
    if (n.find_first_not_of('9') == string::npos)
    {
        return true;
    }

    return false;
}

bool isRightPartAllNines(const string &n)
{
    size_t zeroPos = n.rfind('0');

    if (zeroPos == string::npos)
    {
        zeroPos = -1;
    }

    string rightPart = n.substr(zeroPos + 1);

    if (rightPart.find_first_not_of('9') == string::npos)
    {
        return true;
    }

    return false;
}

bool isLastDigitZero(const string &n)
{
    if (n.back() == '0')
    {
        return true;
    }

    return false;
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);

    string n;
    cin >> n;

    unsigned int buttonPresses = 0;

    while (true)
    {
        if (n == "1")
        {
            cout << buttonPresses;

            return 0;
        }
        else if (isPowerOfTen(n))
        {
            n = rotate(n);
            buttonPresses++;
        }
        else if (isAllNines(n))
        {
            n = addOne(n);
            buttonPresses++;
        }
        else if (isLastDigitZero(n))
        {
            n = rotate(n);
            buttonPresses++;
        }
        else if (isRightPartAllNines(n))
        {
            n = rotate(n);
            buttonPresses++;
        }
        else
        {
            n = addOne(n);
            buttonPresses++;
        }
    }
}