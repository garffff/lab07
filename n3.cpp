#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;

enum Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student
{
    string Name;
    int Year;
    map<string, Score> RecordBook;
};

using Groups = map<string, vector<Student>>;

void saveToFile(const string& filename, const Groups& groups)
{
    ofstream out;
    out.open(filename);
    for(auto [grname, lst] : groups)
    {
        out << "$" << endl << grname << endl;
        for(int i = 0; i < lst.size(); ++i)
        {
            out << "*" << endl << lst[i].Name << endl;
            out << lst[i].Year << endl;
            for(auto [sub, sc] : lst[i].RecordBook)
            {
                out << sub << endl;
                out << sc << endl;
            }
        }
    }
    out.close();
}

void loadFromFile(const string& filename, Groups& outGroups)
{
    ifstream in;
    vector<Student> lst;
    string b, grname, stname, a;
    map<string, Score> records;
    int i = 0, j = 0, year;
    in.open(filename);
    while(getline(in, b))
    {
        if(b == "$")
        {
            if(i != 0)
            {
                lst.push_back({stname, year, records});
                records.clear();
                outGroups.insert({grname, lst});
                lst.clear();
            }
            getline(in, grname);
            ++i;
            j = 0;
        }
        else if (b == "*")
        {
            if(j!= 0)
            {
                lst.push_back({stname, year, records});
                records.clear();
            }
            getline(in, stname);
            getline(in, a);
            year = stoi(a);
            ++j;
            cout << j << endl;
        }
        else
        {
            getline(in, a);
            Score val = static_cast<Score>(stoi(a));
            records.insert({b, val});
        }
    }
    lst.push_back({stname, year, records});
    outGroups.insert({grname, lst});
    in.close();
}

int main()
{
    Groups groups = {
        {"Group1", {{"Student1", 2020, {{"Math", Good}, {"Physics", Excellent}}}, {"Student2", 2021, {{"Math", Satisfactorily}, {"Physics", Good}}}}},
        {"Group2", {{"Student3", 2022, {{"Math", Excellent}, {"Physics", Good}}}, {"Student4", 2023, {{"Math", Satisfactorily}, {"Physics", Unsatisfactorily}}}}}};

    saveToFile("groups.txt", groups);
    Groups loadedGroups;
    loadFromFile("groups.txt", loadedGroups);
    for(auto [grname, lst] : loadedGroups)
    {
        cout << "Group: " << grname << endl;
        for(auto i : lst)
        {
            cout << i.Name << endl << i.Year << endl;
            for(auto [subj, sc] : i.RecordBook) cout << subj << " " << sc << endl;
        }
    }
    return 0;
}
