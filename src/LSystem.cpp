#include"LSystem.hpp"

LSystem::LSystem(void){
    defineFunctions();
    initializeState();
    parser.parse("src/resource/default.lsystem");
}

LSystem::LSystem(string filename){
    defineFunctions();
    initializeState();
    parser.parse(filename);
}

void LSystem::construct(void){
    string word = axiom;
    string temp;
    unsigned int layer = level;
    while(layer > 0){
        temp = "";
        for(char &c: word){
            if(rule_map.find(c) != rule_map.end()){
                temp += rule_map[c];
            }else{
                temp += c;
            }
        }
        word = temp;
        layer--;
    }
    for(char &c: word){
        if(function_map.find(c) != function_map.end()){
            function_map[c]();
        }
    }
}

void LSystem::draw(){
    drawLines(draw_list);
}

void LSystem::defineFunctions(void){
    parser.define("rule",[&](string input){
        string arg;
        stringstream stream(input);
        while(getline(stream, arg, ',')) {
            rule_map[arg[0]] = arg.substr(2,arg.size()-2);
        }
    });

    parser.define("function",[&](string input){
        string::size_type sz;
        string arg;
        stringstream stream(input);
        while(getline(stream, arg, ',')) {
            string label = funcLabel(arg.substr(2,arg.size()-2),true);
            // cout << label << endl;
            float param = stod(funcParam(arg.substr(2,arg.size()-2),true),&sz);
            // cout << param << endl;
            function_map[arg[0]] = [&,label,param](void){
                if(label == "draw"){
                    float dx = state["x"] + state["length"]*cos(state["theta"]*(M_PI/180))*sin(state["phi"]*(M_PI/180));
                    float dy = state["y"] + state["length"]*sin(state["theta"]*(M_PI/180))*sin(state["phi"]*(M_PI/180));
                    float dz = state["z"] + state["length"]*cos(state["phi"]*(M_PI/180));
                    if(param==1) {
                        hsva c_h(state["hue"],state["saturation"],state["value"],state["alpha"]);
                        rgba c_r(c_h);
                        glLine line = {
                            {c_r.r, c_r.g, c_r.b, c_r.a},
                            {state["x"],state["y"],state["z"]},
                            {dx,dy,dz},
                            state["width"]
                        };
                        draw_list.push_back(line);
                    }
                    state["x"] = dx;
                    state["y"] = dy;
                    state["z"] = dz;
                    x_max = (dx > x_max) ? dx : x_max;
                    x_min = (dx < x_min) ? dx : x_min;
                    y_max = (dy > y_max) ? dy : y_max;
                    y_min = (dy < y_min) ? dy : y_min;

                } else if(label == "store") {
                    if(param==1) {
                        state_stack.push(state);
                    } else if(param==0){
                        state = state_stack.top();
                        state_stack.pop();
                    }
                } else {
                    // cout << label << "->" << param << endl;
                    state[label] += param;
                }
            };
        }
    });

    parser.define("init",[&](string input){
        string::size_type sz;
        string arg;
        stringstream stream(input);
        while(getline(stream, arg, ',')) {
            string label = funcLabel(arg,true);
            float param = stod(funcParam(arg,true),&sz);
            state[label] += param;
        }
    });

    parser.define("axiom",[&](string input){
        axiom = input;
    });

    parser.define("level",[&](string input){
        string::size_type sz;
        level = stod(input, &sz);
    });
}

void LSystem::initializeState(void){
    state["hue"]          = 0;
    state["saturation"]   = 0;
    state["value"]        = 0;
    state["alpha"]        = 0;
    state["theta"]        = 0;
    state["phi"]          = 0;
    state["length"]       = 0;
    state["width"]        = 0;
    state["x"]            = 0;
    state["y"]            = 0;
    state["z"]            = 0;
    x_min                 = 0;
    x_max                 = 0;
    y_min                 = 0;
    y_max                 = 0;
    z_min                 = 0;
    z_max                 = 0;
}

ViewWindow LSystem::generateViewWindow(void){
    ViewWindow vw(x_min,x_max,y_min,y_max);
    return vw;
}

void LSystem::debug(void){
    // cout << x_min << endl;
    // cout << x_max << endl;
    // cout << y_min << endl;
    // cout << y_max << endl;
}