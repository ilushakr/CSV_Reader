#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <regex>

using namespace std;

vector<vector<string>> table;
map<string, int> rows{};
map<string, int> lines{};

int iterations = 0;

void converter(string str, int positionLine, int positionRow)
{
    iterations++;
    if (iterations >= rows.size() * lines.size() || str == "loop")
    {
        table[positionLine][positionRow] = "loop";
        return;
//        cout<<"err";
//        exit(3);
    }

    if(!regex_match(str.begin(), str.end(), regex("=[a-zA-Z]+\\d+[+\\-*\\/][a-zA-Z]+\\d+")))
    {
        table[positionLine][positionRow] = "WRONG FORMULA";
        return;
    }
    string row1, row2, line1, line2;
    string op;
    smatch m;
    regex_search (str,m,regex("[a-zA-Z]+"));
    row1 = m[0];
    str = m.suffix().str();

    regex_search (str,m,regex("\\d+"));
    line1 = m[0];
    str = m.suffix().str();

    regex_search (str,m,regex("[\\+\\-\\*\\/]"));
    op = m[0];
    str = m.suffix().str();

    regex_search (str,m,regex("[a-zA-Z]+"));
    row2 = m[0];
    str = m.suffix().str();

    regex_search (str,m,regex("\\d+"));
    line2 = m[0];
    str = m.suffix().str();

    if (rows.find(row1) == rows.end() || lines.find(line1) == lines.end() || rows.find(row2) == rows.end() ||
        lines.find(line2) == lines.end())
        table[positionLine][positionRow] = "WRONG FORMULA";
    else {
        if (!isdigit(table[lines[line1]][rows[row1]][0])) {
            converter(table[lines[line1]][rows[row1]], lines[line1], rows[row1]);
            if(table[lines[line1]][rows[row1]] == "loop")
            {
                table[positionLine][positionRow] = "loop";
                return;;
            }
        } else if (!isdigit(table[lines[line2]][rows[row2]][0])) {
            converter(table[lines[line2]][rows[row2]], lines[line2], rows[row2]);
            if(table[lines[line2]][rows[row2]] == "loop")
            {
                table[positionLine][positionRow] = "loop";
                return;;
            }
        }

        switch ((int) op[0]) {
            case (int) '+':
                table[positionLine][positionRow] = to_string(
                        stoi(table[lines[line1]][rows[row1]]) + stoi(table[lines[line2]][rows[row2]]));
                break;
            case (int) '-':
                table[positionLine][positionRow] = to_string(
                        stoi(table[lines[line1]][rows[row1]]) - stoi(table[lines[line2]][rows[row2]]));
                break;
            case (int) '*':
                table[positionLine][positionRow] = to_string(
                        stoi(table[lines[line1]][rows[row1]]) * stoi(table[lines[line2]][rows[row2]]));
                break;
            case (int) '/':
                try {
                    if (table[lines[line2]][rows[row2]] == "0") throw exception();
                    table[positionLine][positionRow] = to_string(
                            stoi(table[lines[line1]][rows[row1]]) / stoi(table[lines[line2]][rows[row2]]));
                } catch (exception &e) {
                    table[positionLine][positionRow] = "DEVIDE BY ZERO";
                }
                break;
            default:
                table[positionLine][positionRow] = "WRONG OPERATION";
                break;
        }
    }

}

void printCSV()
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



//int main(int argc, char *argv[])
int main()
{
    ifstream file("recursion.csv");
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
                converter(table[i][j], i, j);
                iterations = 0;
            }
        }
    }

    printCSV();
    system("Pause");
    return 0;
}