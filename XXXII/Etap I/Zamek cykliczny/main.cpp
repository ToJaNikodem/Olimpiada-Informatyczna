#include <iostream>
#include <string>

using namespace std;

int calculateAddOneButtonPresses(const string &n)
{
    unsigned int buttonPresses = 0;

    for (size_t i = 0; i < n.length(); ++i)
    {
        if (n[i] != '0' && n[i] != '9')
        {
            int ch = n[i] - '0';
            buttonPresses += 9 - ch;
        }
    }

    return buttonPresses + 1;
}

int calculateSection(unsigned int sectionLength, unsigned int nineCountInSection, unsigned int zeroCountInSection, unsigned int nineCountInUninterruptedSeriesOfNinesInSection, bool isFirstSection)
{
    if (nineCountInSection == sectionLength)
    {
        return 0;
    }
    else if (zeroCountInSection == 0)
    {
        if (isFirstSection && nineCountInUninterruptedSeriesOfNinesInSection > 0)
        {
            return sectionLength - nineCountInUninterruptedSeriesOfNinesInSection;
        }
        else
        {
            return sectionLength - 1;
        }
    }
    else
    {
        return sectionLength - zeroCountInSection;
    }
}

bool allButLastCharAreNines(const string &n)
{
    if (n.size() <= 1)
    {
        return false;
    }

    for (size_t i = 0; i < n.size() - 1; ++i)
    {
        if (n[i] != '9')
        {
            return false;
        }
    }

    return true;
}

int calculateRotateButtonPresses(const string &n)
{
    if (n.back() != '0' && allButLastCharAreNines(n))
    {
        return 1;
    }

    unsigned int buttonPresses = 0;
    unsigned int nineCountInSection = 0;
    unsigned int zeroCountInSection = 0;
    unsigned int sectionLength = 0;
    unsigned int nineCountInUninterruptedSeriesOfNinesInSection = 1;

    bool isFirstSection = true;
    bool lastWasNine = true;

    for (size_t i = n.length(); i-- > 0;)
    {
        ++sectionLength;
        if (n[i] == '0')
        {
            ++zeroCountInSection;
            if (sectionLength == zeroCountInSection)
            {
                continue;
            }
            buttonPresses += calculateSection(sectionLength - 1, nineCountInSection, zeroCountInSection - 1, nineCountInUninterruptedSeriesOfNinesInSection, isFirstSection);

            nineCountInSection = 0;
            zeroCountInSection = 1;
            sectionLength = 1;
            isFirstSection = false;
            lastWasNine = false;
            nineCountInUninterruptedSeriesOfNinesInSection = 0;
            continue;
        }
        else if (n[i] == '9')
        {
            ++nineCountInSection;
            if (lastWasNine && sectionLength > 1)
            {
                ++nineCountInUninterruptedSeriesOfNinesInSection;
            }
        }
        else
        {
            if (sectionLength > 1)
            {
                lastWasNine = false;
            }
        }
    }
    buttonPresses += calculateSection(sectionLength, nineCountInSection, zeroCountInSection, nineCountInUninterruptedSeriesOfNinesInSection, isFirstSection);

    return buttonPresses + 1;
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);

    string n;
    cin >> n;
    if (n == "1")
    {
        cout << 0;

        return 0;
    }
    if (n.length() > 1 && n.find_first_not_of('0', 1) == string::npos && n[0] == '1')
    {
        cout << 1;

        return 0;
    }
    if (n.find_first_not_of('9') == string::npos)
    {
        cout << 2;

        return 0;
    }
    unsigned int buttonPresses = 0;

    buttonPresses += calculateAddOneButtonPresses(n);
    buttonPresses += calculateRotateButtonPresses(n);

    cout << buttonPresses;
}