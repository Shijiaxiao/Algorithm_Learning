//
//  main.cpp
//  1 ~ 9: ( )( )( ) + ( )( )( ) = ( )( )( )
//
//  Created by 史家箫 on 2022/3/9.
//



#include <iostream>
#define N 200

using namespace std;

void DFS1(int step, int & n, int * & box, int * & mark);
void DFS2(int step, int & n, int * & box, int * & mark);

int numbers1 = 0;
int numbers2 = 0;
int repeat[N][2] {0};
int nRepeat = 0;

int main() {
    int n = 9;
    int start = 1;
    int * box = new int[n];
    int * mark = new int[n];
    for (int i = 1; i <= n; i++)
        mark[i] = 0;
    DFS1(start, n, box, mark);
    for (int i = 1; i <= n; i++)
        mark[i] = 0;
    DFS2(start, n, box, mark);
    cout << "Total possibilities (before cut to half): " << numbers1 << endl;
    cout << "Total possibilities (after cut to half): " << numbers2 << endl;
    return 0;
}

void DFS1(int step, int & n, int * & box, int * & mark) {
    // finished one sorting.
    if (step == n + 1) {
        if(box[1] * 100 + box[2] * 10 + box[3] + box[4] * 100 + box[5] * 10 + box[6] == box[7] * 100 + box[8] * 10 + box[9] ) {
            for (int i = 1; i <= 3; i++)
                cout << box[i];
            cout << " + ";
            for (int i = 4; i <= 6; i++)
                cout << box[i];
            cout << " = ";
            for (int i = 7; i <= 9; i++)
                cout << box[i];
            cout << endl;
            numbers1++;
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (mark[i] == 0) {
            box[step] = i;
            mark[i] = 1;
            DFS1(step + 1, n, box, mark);
            mark[i] = 0;
        }
    }
    return;
}

void DFS2(int step, int & n, int * & box, int * & mark) {
    // finished one sorting.
    if (step == n + 1) {
        int fir = box[1] * 100 + box[2] * 10 + box[3];
        int mid = box[4] * 100 + box[5] * 10 + box[6];
        int las = box[7] * 100 + box[8] * 10 + box[9];
        if(fir + mid == las) {
            for (int i = 0; i < numbers2; i++)
                if( fir == repeat[i][1] && mid == repeat[i][0]) {
                    return;
                }
            
            repeat[numbers2][0] = fir;
            repeat[numbers2][1] = mid;
            numbers2++;
            
            for (int i = 1; i <= 3; i++)
                cout << box[i];
            cout << " + ";
            for (int i = 4; i <= 6; i++)
                cout << box[i];
            cout << " = ";
            for (int i = 7; i <= 9; i++)
                cout << box[i];
            cout << endl;
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (mark[i] == 0) {
            box[step] = i;
            mark[i] = 1;
            DFS2(step + 1, n, box, mark);
            mark[i] = 0;
        }
    }
    return;
}
