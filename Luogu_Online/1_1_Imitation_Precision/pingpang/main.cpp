//
//  main.cpp
//  Pingpang
//
//  Created by 史家箫 on 2022/3/8.
//

#include <iostream>
#include <cstring>

using namespace std;

int main() {
    const char win = 'W';
    const char lose = 'L';
    const char end = 'E';
    string data;
    // cout << "Please input(E as ending mark):";
    getline(cin, data, end);
    int index = 0;
    int w = 0, l = 0;
    
    // 11 points.
    while (data[index] != '\0') {
        if (data[index] == win)
            w++;
        else if (data[index] == lose)
            l++;
        index++;
        if ( (w == 11 || l == 11) && (w - l >=2 || w-l <=-2) ) {
            cout << w << ':' << l << endl;
            w = 0;
            l = 0;
        }
        else if ( (w > 11 || l > 11) && (w - l ==2 || w-l ==-2) ) {
            cout << w << ':' << l << endl;
            w = 0;
            l = 0;
        }
    }
    
    cout << w << ':' << l << endl << endl;
    index = 0;
    w = 0;
    l = 0;
    // 21 points.
    while (data[index] != '\0') {
        if (data[index] == win)
            w++;
        else if (data[index] == lose)
            l++;
        index++;
        if ( (w == 21 || l == 21) && (w - l >=2 || w-l <=-2) ) {
            cout << w << ':' << l << endl;
            w = 0;
            l = 0;
        }
        else if ( (w > 21 || l > 21) && (w - l ==2 || w-l ==-2) ) {
            cout << w << ':' << l << endl;
            w = 0;
            l = 0;
        }
    }
    cout << w << ':' << l <<endl;
    
    return 0;
}
