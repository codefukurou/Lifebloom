#include<fstream>
#include<functional>
#include<iostream>
#include<map>
#include<sstream>
#include<string>
#include<regex>
#include<algorithm>

using namespace std;

class ScriptParser {
public:
    ScriptParser(void);
    void define(string name, function<void(string)> func);
    void parse(string filename);

private:
    map<string,function<void(string)>> fmap;
};

string funcLabel(string, bool);
string funcParam(string, bool);
