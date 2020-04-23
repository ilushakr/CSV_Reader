#include <iostream>
#include <fstream>
#include <vector>
//#include <cctype>
#include <string>
#include <sstream>
#include <map>
#include <map>

using namespace std;

string converter(string str, vector<vector<string>> &table, map<string, int> &rows, map<string, int> &lines)
{
    string row1, row2, line1, line2;
    char op;
    int i = 1;
    while(!isdigit(str[i]))
    {
        row1 += str[i];
        i++;
    }
    while(isdigit(str[i]))
    {
        line1 += str[i];
        i++;
    }
    op = str[i];
    i++;
    while(!isdigit(str[i]))
    {
        row2 += str[i];
        i++;
    }
    while(i != str.length()) {
        line2 += str[i];
        i++;
    }

//    if(!isdigit(table[lines[line1]][rows[row1]][0]))
//    {
//        converter()
//    }
    if(rows.find(row1) == rows.end() || lines.find(line1) == lines.end() || rows.find(row2) == rows.end() || lines.find(line2) == lines.end())
        return "WRONG FORMULA";
    else
        switch ((int) op)
        {
            case (int) '+':
                return to_string(stoi(table[lines[line1]][rows[row1]]) + stoi(table[lines[line2]][rows[row2]]));
            case (int) '-':
                return to_string(stoi(table[lines[line1]][rows[row1]]) - stoi(table[lines[line2]][rows[row2]]));
            case (int) '*':
                return to_string(stoi(table[lines[line1]][rows[row1]]) * stoi(table[lines[line2]][rows[row2]]));
            case (int) '/':
                try {
                    if (table[lines[line2]][rows[row2]] == "0") throw exception();
                    return to_string(stoi(table[lines[line1]][rows[row1]]) / stoi(table[lines[line2]][rows[row2]]));
                }catch(exception&e)
                {
                    return "DEVIDE BY ZERO" ;
                }
            default:
                return "WRONG OPERATION";
        }
}

void printCSV(vector<vector<string>> &table, map<string, int> &rows, map<string, int> &lines)
{
    for(auto x : rows) cout<<","<<x.first;
    cout<<endl;

    for(auto x : lines)
    {
        cout<<x.first;
        for(auto y : table[x.second]) cout<<","<<y;
        cout<<endl;
    }
}

vector<vector<string>> table;
map<string, int> rows{};
map<string, int> lines{};

//int main(int argc, char *argv[])
int main()
{
    ifstream file("1.csv");
    string str;
    getline(file, str);
    stringstream strStream(str);

    string segment;
    vector<string> seglist;
    int what_row = -1;


    while(getline(strStream, segment, ','))
    {
        seglist.push_back(segment);
        rows[segment] = what_row;
        what_row++;
    }
    rows.erase(rows.begin());

    int what_line = 0;
    seglist.clear();
    while(getline(file, str))
    {
        strStream = stringstream(str);
        while(getline(strStream, segment, ','))
        {
            seglist.push_back(segment);
        }
        lines[seglist[0]] = what_line;
        seglist.erase(seglist.begin());
        table.push_back(seglist);
        seglist.clear();
        what_line++;
    }


    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table[i].size(); j++)
        {
            if(!isdigit(table[i][j][0]))
            {
                table[i][j] = converter(table[i][j], table, rows, lines);
            }
        }
    }

    printCSV(table, rows, lines);
    system("Pause");
    return 0;
}