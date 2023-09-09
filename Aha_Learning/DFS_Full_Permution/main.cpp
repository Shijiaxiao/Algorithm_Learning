//
//  main.cpp
//  DFS_Full Permutation
//
//  Created by 史家箫 on 2022/3/9.
//

#include <iostream>

using namespace std;

void DFS(int step, int & n, int * & box, int * & mark);

int main() {
    int n;
    int start = 1;
    cout << "Please input the magnitude of numbers:";
    cin >> n;
    int * box = new int[n];
    int * mark = new int[n];
    for (int i = 1; i <= n; i++)
        mark[i] = 0;
    DFS(start, n, box, mark);
    return 0;
}

void DFS(int step, int & n, int * & box, int * & mark) {
    // finished one sorting.
    if (step == n + 1) {
        for (int i = 1; i <= n; i++)
            cout << box[i];
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (mark[i] == 0) {
            box[step] = i;
            mark[i] = 1;
            DFS(step + 1, n, box, mark);
            mark[i] = 0;
        }
    }
    return;
}
