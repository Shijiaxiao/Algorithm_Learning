//
//  main.cpp
//  High precision multiplication
//
//  Created by 史家箫 on 2022/3/11.
//

#include <iostream>
#include <cstring>

#define N 10000

using namespace std;

void output(int * & Result, int n, int i);

int main() {
    char *first = new char[N];
    char *second = new char[N];
    int First[N] {0};
    int Second[N] {0};
    cout << "Please input the first multiplier:" ;
    cin >> first;
    cout << "Please input the second multiplier:" ;
    cin >> second;
    int lenF = int(strlen(first));
    int lenS = int(strlen(second));
    int *Result = new int[lenF + lenS - 1]; // -1 -1 +1 = -1.
    for (int i = 0; i < lenF + lenS - 1; i++)
        Result[i] = 0;
    for (int i = 0; i < lenF; i++)
        First[i] = first[lenF - i - 1] - '0';
    for (int i = 0; i < lenS; i++)
        Second[i] = second[lenS - i - 1] - '0';
    delete [] first;
    delete [] second;
    // Begin to calculate.
    for (int i = 0; i < lenF; i++)
        for (int j = 0; j < lenS; j++)
            Result[i + j] += First[i] * Second[j];
    // Carry-over.
    for (int i = 0; i < lenF + lenS - 2; i++) {
        int next = Result[i] / 10;
        Result[i] %= 10;
        Result[i + 1] += next;
    }
    // Output.
    output(Result, lenF + lenS - 1, 0);
    return 0;
}

void output(int * & Result, int n, int i) {
    if (i == n) {
        if (Result[i] != 0)
            cout << Result[i];
        return;
    }
    output(Result, n, i + 1);
    cout << Result[i];
    if(i == 0)
        cout << endl;
}
