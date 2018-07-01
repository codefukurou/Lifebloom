#include<iostream>

struct StructArray{
    float arrayA[3];
    float arrayB[3];
};

using namespace std;

int main(void) {
    
    StructArray s;

    s = {{1,2,3},{5,6,7}};
    

    for(int i = 0; i < 3; i++){
        cout << s.arrayA[i] << " " << s.arrayB[i] << endl;
    }
    
    return 0;
}
