#include"ScriptParser.hpp"
#include"Color.hpp"
#include"Draw.hpp"
#include"ViewWindow.hpp"

class LSystem {
public:
    LSystem(void);
    LSystem(string filename);
    void construct(void);
    void draw(void);
    ViewWindow generateViewWindow(void);
    void debug(void);

private:
    void defineFunctions(void);
    void initializeState(void);

    ScriptParser parser;
    map<char,string> rule_map;
    map<char,function<void(void)>> function_map;
    map<string,float> state;
    stack<map<string,float>> state_stack;
    string axiom;
    vector<glLine> draw_list;
    unsigned int level;
    float x_min, x_max, y_min, y_max, z_min, z_max;
};
