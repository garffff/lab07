#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void saveToFile(const string& filename, const vector<string>& data)
{
    ofstream out;
    out.open(filename);
    for(string i : data) out << i << endl;
    out.close();
}

void loadFromFile(const string& filename, vector<string>& outData)
{
    ifstream in;
    string b;
    in.open(filename);
    if(!in)
    {
        cout << "Impossible to read file" << endl;
        exit(0);
    }
    while(getline(in, b)) outData.push_back(b);
}

int main()
{
    ofstream a;
    vector<string> vec = {"odin", "thor", "loki"}, vec1;
    string str1, str2, str3;
    a.open("test1");
    a.close();
    saveToFile("test1", vec);
    loadFromFile("test1", vec1);
    for(string i : vec1) cout << i << endl;
    return 0;
}
