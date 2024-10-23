#include <iostream>
#include <string>
#include <cmath>

using namespace std;

unsigned int calculateUsingRotateMethod(unsigned int sectionLength, unsigned int nineCountInSection, unsigned int zeroCountInSection, unsigned int rotateMethodAddOneButtonPresses)
{
    unsigned int rotateButtonPresses = 0;

    if (nineCountInSection == sectionLength)
    {
        rotateButtonPresses = 0;
    }
    else if (zeroCountInSection == 0)
    {
        rotateButtonPresses = sectionLength - 1;
    }
    else
    {
        rotateButtonPresses = sectionLength - zeroCountInSection;
    }

    cout << "rotate method, addOne - " << rotateMethodAddOneButtonPresses << endl;
    cout << "rotate method, rotate - " << rotateButtonPresses << endl;

    return rotateMethodAddOneButtonPresses + rotateButtonPresses;
}

unsigned int calculateUsingAddingFirstMethod(bool lastSection, unsigned int addingFirstMethodAddOneButtonPresses)
{
    unsigned int rotateButtonPresses = (lastSection) ? 0 : 1;

    cout << "adding first method, addOne - " << addingFirstMethodAddOneButtonPresses << endl;
    cout << "adding first method, rotate - " << rotateButtonPresses << endl;

    return rotateButtonPresses + addingFirstMethodAddOneButtonPresses + 9;
}

unsigned int calculateSection(bool firstSection, bool lastSection, unsigned int sectionLength, unsigned int nineCountInSection, unsigned int zeroCountInSection, unsigned int rotateMethodAddOneButtonPresses, bool addingFirstMethodViable, unsigned int addingFirstMethodAddOneButtonPresses)
{
    unsigned int sectionButtonPresses;

    if (firstSection && addingFirstMethodViable)
    {
        unsigned int addingFirstMethod = calculateUsingAddingFirstMethod(lastSection, addingFirstMethodAddOneButtonPresses);
        unsigned int rotateMethod = calculateUsingRotateMethod(sectionLength, nineCountInSection, zeroCountInSection, rotateMethodAddOneButtonPresses);

        sectionButtonPresses = (addingFirstMethod < rotateMethod) ? addingFirstMethod : rotateMethod;
    }
    else
    {
        sectionButtonPresses = calculateUsingRotateMethod(sectionLength, nineCountInSection, zeroCountInSection, rotateMethodAddOneButtonPresses);
    }
    return sectionButtonPresses;
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

    bool firstSection = true;

    unsigned int buttonPresses = 0;
    unsigned int sectionLength = 0;
    unsigned int nineCountInSection = 0;
    unsigned int zeroCountInSection = 0;

    unsigned int rotateMethodAddOneButtonPresses = 0;
    unsigned int addingFirstMethodAddOneButtonPresses = 0;

    bool addingFirstMethodViable = true;

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

            buttonPresses += calculateSection(firstSection, false, sectionLength, nineCountInSection, zeroCountInSection, rotateMethodAddOneButtonPresses, addingFirstMethodViable, addingFirstMethodAddOneButtonPresses);
            sectionLength = 0;
            nineCountInSection = 0;
            zeroCountInSection = 0;
            rotateMethodAddOneButtonPresses = 0;
            firstSection = false;

            continue;
        }
        if (n[i] == '9')
        {
            ++nineCountInSection;

            continue;
        }
        rotateMethodAddOneButtonPresses += 9 - (n[i] - '0');

        if (firstSection && addingFirstMethodViable)
        {
            addingFirstMethodAddOneButtonPresses += 10 - ((n[i] - '0') * pow(10, sectionLength - 1));
            if (addingFirstMethodAddOneButtonPresses > 1000000)
            {
                addingFirstMethodViable = false;
            }
        }
    }

    buttonPresses += calculateSection(firstSection, false, sectionLength, nineCountInSection, zeroCountInSection, rotateMethodAddOneButtonPresses, addingFirstMethodViable, addingFirstMethodAddOneButtonPresses);
    buttonPresses += 2;

    cout << buttonPresses;
}