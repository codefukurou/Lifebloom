#include"ScriptParser.hpp"

ScriptParser::ScriptParser(void){
}

void ScriptParser::define(string name, function<void(string)> func){
    fmap.insert(map<string,function<void(string)>>::value_type(name, func));
}

void ScriptParser::parse(string filename){
    // Read script file
    ifstream file(filename);
    string script((std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>()));
    // Remove white space
    script.erase(remove_if(script.begin(), script.end(), 
        [](char ch) {return isspace<char>(ch,locale::classic());}), script.end());
    // Process functions
    string func;
    stringstream stream(script);
    while(getline(stream, func, ';')){
        auto fp = fmap.find(funcLabel(func,false));
        if(fp != fmap.end()){
            fp->second(funcParam(func,false));
        }
    }
}

string funcLabel(string input, bool meta){
    regex rfn_rgx{"^[^\\(]+"}; // regular function name
    regex mfn_rgx{"^[^\\{]+"}; // meta function name
    smatch match;
    if(regex_search(input, match, meta ? mfn_rgx : rfn_rgx)){
        return match[0];
    }else{
        return "";

    }
}

string funcParam(string input, bool meta){
    regex rfa_rgx{"\\(([^\\)]*)\\)"}; // regular function arguments
    regex mfa_rgx{"\\{([^\\}]*)\\}"}; // meta function arguments
    smatch match;
    if(regex_search(input, match, meta ? mfa_rgx : rfa_rgx)){
        return match[1];
    } else {
        return "";
    }
}
