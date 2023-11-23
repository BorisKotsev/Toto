#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <map>

using namespace std;

struct int2
{
    int first, second;
};

struct int6
{
    int first, second, third, fourth, fifth, sixth;
};

int maxCirculation = 0;
int maxNumbers = 0;
int numbers = 0;
int myNum;

vector<int6> totoNumbers;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool operator<(const int2& lhs, const int2& rhs)
{
    if (lhs.first != rhs.first)
    {
        return lhs.first < rhs.first;
    }

    return lhs.second < rhs.second;
}

void loadData(string configFile)
{
    fstream stream;

    stream.open("files\\" + configFile + ".txt");


    int size = 0;

    while(!stream.eof())
    {
        int6 _num;

        if(numbers == 6)
        {
            stream >> _num.first >> _num.second >> _num.third >> _num.fourth >> _num.fifth >> _num.sixth;
        }
        else if(numbers == 5)
        {
            stream >> _num.first >> _num.second >> _num.third >> _num.fourth >> _num.fifth;
        }

        totoNumbers.push_back(_num);

        size ++;
    }

    stream.close();

    maxCirculation = size;
}

void print()
{
    for (int i = 0; i < maxNumbers; i++)
    {
        int currCirculation = i + 1;

        if (currCirculation < 10)
        {
            cout << currCirculation << ' ' << ' ';
        }
        else
        {
            cout << currCirculation << ' ';
        }

        for (int j = 1; j <= maxCirculation; j++)
        {
            bool found = false;

            for (int k = 0; k < maxNumbers; k++)
            {
                int6 currint6 = totoNumbers[j - 1];

                if (currCirculation == currint6.first ||
                    currCirculation == currint6.second ||
                    currCirculation == currint6.third ||
                    currCirculation == currint6.fourth ||
                    currCirculation == currint6.fifth ||
                    currCirculation == currint6.sixth)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                SetConsoleTextAttribute(hConsole, 240); ///64 79
                cout << 'X';
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                cout << '.';
            }
        }

        if (currCirculation < 10)
        {
            cout << ' ' << currCirculation << ' ';
        }
        else
        {
            cout << ' ' << currCirculation;
        }
        cout << endl;
    }

    cout << endl;
}

void checkStats(int myNumber)
{
    int occurrences[maxNumbers] = {0};

    for(int i = 0; i < maxCirculation; i ++)
    {
        if(myNumber == totoNumbers[i].first || myNumber == totoNumbers[i].second ||
           myNumber == totoNumbers[i].third || myNumber == totoNumbers[i].fourth ||
           myNumber == totoNumbers[i].fifth || myNumber == totoNumbers[i].sixth)
        {
            for(int j = 1; j <= maxNumbers; j ++)
            {
                if(j != myNumber && (j == totoNumbers[i].first || j == totoNumbers[i].second ||
                                     j == totoNumbers[i].third || j == totoNumbers[i].fourth ||
                                     j == totoNumbers[i].fifth || j == totoNumbers[i].sixth))
                {
                    occurrences[j - 1] ++;
                }
            }
        }
    }

    for(int i = 0; i < maxNumbers; i ++)
    {
        cout  << i + 1 << " : " << occurrences[i] << "      ";

        if(i % 5 == 4)
        {
            cout << endl;
        }
    }

    cout << endl;
}

void printCurrCirculation(vector<int6>& thisCirculation)
{
    cout << endl;

    for (int i = 0; i < thisCirculation.size(); i++)
    {
        cout << "Circulation " << i + 1 << ":" << endl;

        cout << "First number: " << thisCirculation[i].first << endl;
        cout << "Second number: " << thisCirculation[i].second << endl;
        cout << "Third number: " << thisCirculation[i].third << endl;
        cout << "Fourth number: " << thisCirculation[i].fourth << endl;
        cout << "Fifth number: " << thisCirculation[i].fifth << endl;
        cout << "Sixth number: " << thisCirculation[i].sixth << endl << endl;
    }
}

void fillCurrCirculation(int myNumber, vector<int6>& thisCirculation)
{
    for(int i = 0; i < maxCirculation; i ++)
    {
        if(myNumber == totoNumbers[i].first || myNumber == totoNumbers[i].second ||
           myNumber == totoNumbers[i].third || myNumber == totoNumbers[i].fourth ||
           myNumber == totoNumbers[i].fifth || myNumber == totoNumbers[i].sixth)
        {
            thisCirculation.push_back(totoNumbers[i]);
        }
    }
}

void fillNextCirculation(int myNumber, vector<int6>& thisCirculation)
{

    for(int i = 0; i < maxCirculation; i ++)
    {
        if(myNumber == totoNumbers[i].first || myNumber == totoNumbers[i].second ||
           myNumber == totoNumbers[i].third || myNumber == totoNumbers[i].fourth ||
           myNumber == totoNumbers[i].fifth || myNumber == totoNumbers[i].sixth)
        {
            thisCirculation.push_back(totoNumbers[i + 1]);
        }
    }

    int occurrences[maxNumbers] = {0};

    for(int i = 0; i < thisCirculation.size(); i ++)
    {
        occurrences[thisCirculation[i].first - 1] ++;
        occurrences[thisCirculation[i].second - 1] ++;
        occurrences[thisCirculation[i].third - 1] ++;
        occurrences[thisCirculation[i].fourth - 1] ++;
        occurrences[thisCirculation[i].fifth - 1] ++;
        occurrences[thisCirculation[i].sixth - 1] ++;
    }

    for(int i = 0; i < maxNumbers; i ++)
    {
        cout  << i + 1 << " : " << occurrences[i] << "      ";

        if(i % 5 == 4)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void checkForDouble(int myNumber)
{
    vector<int6> thisCirculation;

    fillCurrCirculation(myNumber, thisCirculation);
    /// printCurrCirculation(thisCirculation);

    cout << endl;

    vector<int2> doubles;

    for(int i = 0; i < thisCirculation.size(); i ++)
    {
        if (thisCirculation[i].first - thisCirculation[i].second == -1)
        {
            int2 tmp = {thisCirculation[i].first, thisCirculation[i].second};
            doubles.push_back(tmp);
        }

        if (thisCirculation[i].second - thisCirculation[i].third == -1)
        {
            int2 tmp = {thisCirculation[i].second, thisCirculation[i].third};
            doubles.push_back(tmp);
        }

        if (thisCirculation[i].third - thisCirculation[i].fourth == -1)
        {
            int2 tmp = {thisCirculation[i].third, thisCirculation[i].fourth};
            doubles.push_back(tmp);
        }

        if (thisCirculation[i].fourth - thisCirculation[i].fifth == -1)
        {
            int2 tmp = {thisCirculation[i].fourth, thisCirculation[i].fifth};
            doubles.push_back(tmp);
        }

        if (thisCirculation[i].fifth - thisCirculation[i].sixth == -1)
        {
            int2 tmp = {thisCirculation[i].fifth, thisCirculation[i].sixth};
            doubles.push_back(tmp);
        }
    }

    map<int2, int> countMap;

    for (const int2& val : doubles)
    {
        countMap[val]++;
    }

    for (const auto& pair : countMap)
    {
        const int2& val = pair.first;
        int count = pair.second;

        cout << val.first << " & " << val.second << " -> " << count << endl;
    }

    cout << endl;
}

void checkNextCirculation(int myNumber)
{
    cout << "After " << myNumber << endl;

    vector<int6> thisCirculation;

    fillNextCirculation(myNumber, thisCirculation);

    cout << endl;
}

void checkNextCirculation()
{
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].first);
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].second);
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].third);
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].fourth);
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].fifth);
    checkNextCirculation(totoNumbers[totoNumbers.size() - 1].sixth);
}

void printInFile(int myNum, string configFile)
{
    ofstream outputFile("files\\output.txt");
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());

    loadData(configFile);
    print();

    cout << "The stats for " << myNum << " are:" << endl;
    checkStats(myNum);
    checkForDouble(myNum);

    checkNextCirculation();

    cout.rdbuf(coutBuffer);
    outputFile.close();
}

void printInConsole(string configFile)
{
    loadData(configFile);
    print();

    cout << "Your number is: ";
    cin >> myNum;

    checkStats(myNum);
    checkForDouble(myNum);

    checkNextCirculation();
}

int main()
{
    string configFile;

    cout << "What file you want to open? (toto49 / toto42 / toto35) ";
    cin >> configFile;

    if(configFile == "toto49")
    {
        maxNumbers = 49;
        numbers = 6;
    }
    else if(configFile == "toto42")
    {
        maxNumbers = 42;
        numbers = 6;
    }
    else if(configFile == "toto35")
    {
        maxNumbers = 35;
        numbers = 5;
    }
    else
    {
        configFile = "toto42";
        maxNumbers = 42;
        numbers = 6;
    }

    printInConsole(configFile);
    printInFile(myNum, configFile);

    while(true);

    return 0;
}
