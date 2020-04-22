#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>


using namespace std;

string converter(string str, vector<vector<string>> &table)
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
    while(i != str.length())
    {
        line2 += str[i];
        i++;
    }


    int posr1 = 0;
    int posl1 = 0;
    while(table[0][posr1] != row1)
    {
        posr1++;
        if(posr1 == table[0].size())
            break;
    }
    while(table[posl1][0] != line1)
    {
        posl1++;
        if(posl1 == table.size())
            break;
    }

    int posr2 = 1;
    int posl2 = 1;
    while(table[0][posr2] != row2)
    {
        posr2++;
        if(posr2 == table[0].size())
            break;
    }
    while(table[posl2][0] != line2)
    {
        posl2++;
        if(posl2 == table.size())
            break;
    }

    if(posl1 >= table.size() || posr1 >= table[0].size() || posl2 >= table.size() || posr2 >= table[0].size())
        return "WRONG FORMULA";
    else
        switch ((int) op)
        {
            case (int) '+':
                return to_string(stoi(table[posl1][posr1]) + stoi(table[posl2][posr2]));
            case (int) '-':
                return to_string(stoi(table[posl1][posr1]) - stoi(table[posl2][posr2]));
            case (int) '*':
                return to_string(stoi(table[posl1][posr1]) * stoi(table[posl2][posr2]));
            case (int) '/':
                try {
                    if (table[posl2][posr2] == "0") throw exception();
                    return to_string(stoi(table[posl1][posr1]) / stoi(table[posl2][posr2]));
                }
                catch(exception&e) {
                    return "DEVIDE BY ZERO" ;
                }

            default:
                return "WRONG OPERATION";
        }

}
int main(int argc, char *argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);

    vector<vector<string>> table;
    table.emplace_back();

    int x = 0;
    char ch = '\n';
    string str = "";
    for (char write2line; inFile.get(write2line);) {

        if (write2line == ch) {
            table[x].push_back(str);
            str = "";
            table.emplace_back();
            x++;
        } else if (write2line == ',') {
            table[x].push_back(str);
            str = "";
        } else {
            str += write2line;
        }
    }
    table.pop_back();


    for(int i = 1; i < table.size(); i++)
    {
        for(int j = 1; j < table[i].size(); j++)
        {
            if(!isdigit(table[i][j][0]))
            {
                table[i][j] = converter(table[i][j], table);
            }
        }
    }

    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table[i].size() - 1; j++)
        {
            cout<<table[i][j]<<",";
        }
        cout<<table[i][table[i].size() - 1]<<endl;
    }

    system("Pause");
    return 0;
}