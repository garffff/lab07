#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Book
{
    string Author;
    string Title;
    int Year;
};

void saveToFile(const string& filename, const vector<Book>& data)
{
    ofstream out;
    out.open(filename);
    for(int i = 0; i < data.size(); ++i)
    {
        out << data[i].Author << endl;
        out << data[i].Title << endl;
        out << data[i].Year << endl;
    }
    out.close();
}

void loadFromFile(const string& filename, vector<Book>& outData)
{
    ifstream in;
    string b;
    Book k;
    int i = 0;
    in.open(filename);
    if(!in)
    {
        cout << "Impossible to read file" << endl;
        exit(0);
    }
    while(getline(in, b))
    {
        if(i % 3 == 0) k.Author = b;
        else if(i % 3 == 1) k.Title = b;
        else
        {
            k.Year = stoi(b);
            outData.push_back(k);
        }
        ++i;
    }
    in.close();
}

int main()
{
    vector<Book> vec = {{"George Orwell", "1984", 1949}, {"Aldous Huxley", "Brave New World", 1932}}, vec1;
    saveToFile("text1", vec);
    loadFromFile("text1", vec1);
    for(int i = 0; i < vec1.size(); ++i)
    {
        cout << vec1[i].Author << " ";
        cout << vec1[i].Title << " ";
        cout << vec1[i].Year << endl;
    }
    return 0;
}
