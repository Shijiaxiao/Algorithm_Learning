//
//  main.cpp
//  Smart plumber
//
//  Created by 史家箫 on 2022/3/28.
//

/* Temp 0:
 5 6
 1 6
 (1,1) (2,1) (2,2)
 */

/* Temp 1:
 5 3 5 3
 1 5 3 0
 2 3 5 1
 6 1 1 5
 1 5 5 4
 (1, 1) -> (5, 4)
 (1,1) (1,2) (2,2) (3,2) (3,3) (3,4) (4,4) (5,4)
 */

/* Temp 2:
 2 4 1 5 4
 3 6 2 0 5
 1 5 1 3 1
 3 6 5 4 3
 4 4 0 1 4
 (1, 1) -> (5, 5)
 */

/* Temp 3:
 2 0 1 3 4
 1 2 2 3 1
 1 3 6 1 4
 3 6 1 0 3
 1 5 4 6 1
 (1, 4) -> (4, 5)
 */

/*
 
 */

#include <iostream>
#include <ctime>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

enum Status { tree = 0, ur = 1, rd = 2, dl = 3, lu = 4, lr = 5, ud = 6 };
enum Direction { left = 1, up = 2, right = 3, down = 4 };
enum Operation { none = 0, clockwise_90 = 1, anticlockwise_90 = 2, reverse = 3 };

struct Node {
    int x, y;
    int steps;
    Status Fstatus;
    Status Bstatus;
    Operation operation;
    Direction Fdirection;
    Direction Bdirection;
} ;

vector <Node> stack;
vector <vector <Node>> answer;

int rows, columns, COLS;
int steps = 0;

int * tempLand;
Status * landscape;
int * book;

int startx, starty;
int endx, endy;

Direction In;
Direction Out;

int ways = 0;

void set_node(int x, int y, Node & node, Direction front, Status status);
void DFS(int x, int y, Direction front);
void output(const Node & node);
void output_water_direction(Direction fore, Direction later);
void output_operation(Status fore, Status later, Operation operation);
void output_single_operation(Status later, Operation operation);
void output_single_later(Status later);

int main() {
    
    // Input rows:
    cout << "Plese input rows: ";
    cin >> rows;
    
    // Input columns:
    cout << "Please input columns: ";
    cin >> columns;
    COLS = columns + 1; // For mathematical use! Important!
    
    // Allocate dynamic storage:
    tempLand = new int [(rows + 1) * (columns + 1)];
    landscape = new Status [(rows + 1) * (columns + 1)];
    book = new int [(rows + 1) * (columns + 1)];
    
    // Initialize map:
    cout << "Please initialize map:\n";
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= columns; j++) {
            cin >> tempLand[i * COLS + j]; // Columns + 1!!!!!
            landscape[i * COLS + j] = Status(tempLand[i * COLS + j]);
            book[i * COLS + j] = 0;
        }
    delete [] tempLand; // Free allocated dynamic storage.
    
    // Input start point:
    do {
        cout << "Please input start point((x = 1 or " << rows << ") || (y = 1 or " << columns << ")): ";
        cin >> startx >> starty;
    } while (startx != 1 && starty != 1 && startx != rows && startx != columns); // Must be boundaries!
    
    // Set in direction:
    // 1.Start with first row:
    if (startx == 1) {
        // 1.1.Start with first column:
        if (starty == 1) {
            cout << "Please input in direction(left 1/up 2): ";
            int temp;
            do { cin >> temp; } while (temp != 1 && temp != 2);
            if (temp == 1) In = left;
            else           In = up;
        }
        // 1.2.Start with last column:
        else if (starty == columns) {
            cout << "Please input in direction(up 2/right 3): ";
            int temp;
            do { cin >> temp; } while (temp != 2 && temp != 3);
            if (temp == 2) In = up;
            else           In = right;
        }
        // 1.3.
        else In = up;
    }
    // 2.Start with last row:
    else if (startx == rows) {
        // 2.1.Start with first column:
        if (starty == 1) {
            cout << "Please input in direction(left 1/down 4): ";
            int temp;
            do { cin >> temp; } while (temp != 1 && temp != 4);
            if (temp == 1) In = left;
            else           In = down;
        }
        // 2.2.Start with last column:
        else if (starty == columns) {
            cout << "Please input in direction(right 3/down 4): ";
            int temp;
            do { cin >> temp; } while (temp != 3 && temp != 4);
            if (temp == 3) In = right;
            else           In = down;
        }
        // 2.3.
        else In = down;
    }
    // 3.Start with ordinary row:
    else {
        // 3.1.Start with first column:
        if (starty == 1) In = left;
        // 3.2.Start with last column:
        else In = right;
    }
    
    // Input end point:
    do {
        cout << "Please input end point(((x = 1 or " << rows << ") || (y = 1 or " << columns
             << ")) && ((x ≠ " << startx << ") && (y ≠ " << starty << "))): ";
        cin >> endx >> endy;
    } while ( (endx != 1 && endy != 1 && endx != rows && endy != columns) || (endx == startx && endy == starty) );
    
    // Set out direction and cordination:
    // 1.End with first row:
    if (endx == 1){
        // 1.1.End with first column:
        if (endy == 1) {
            cout << "Please input in direction(left 1/up 2): ";
            int temp;
            do { cin >> temp; } while (temp != 1 && temp != 2);
            if (temp == 1) { Out = left; endy--; }
            else           { Out = up;   endx--; }
        }
        // 1.2.Start with last column:
        else if (endy == columns) {
            cout << "Please input out direction(up 2/right 3): ";
            int temp;
            do { cin >> temp; } while (temp != 2 && temp != 3);
            if (temp == 2) { Out = up;    endx--; }
            else           { Out = right; endy++; }
        }
        // 1.3.
        else { Out = up; endx--; }
    }
    // 2.End with last row:
    else if (endx == rows) {
        // 2.1.End with first column:
        if (endy == 1) {
            cout << "Please input in direction(left 1/down 4): ";
            int temp;
            do { cin >> temp; } while (temp != 1 && temp != 4);
            if (temp == 1) { Out = left; endy--; }
            else           { Out = down; endx++; }
        }
        // 2.2.Start with last column:
        else if (endy == columns) {
            cout << "Please input out direction(right 3/down 4): ";
            int temp;
            do { cin >> temp; } while (temp != 3 && temp != 4);
            if (temp == 3) { Out = right; endy++; }
            else           { Out = down;  endx++; }
        }
        // 2.3.
        else { Out = down; endx++; }
    }
    // 3.End with ordinary row:
    else {
        // 3.1.Start with first column:
        if (starty == 1) { Out = left; endy--; }
        // 3.2.Start with last column:
        else { Out = right; endy++; }
    }
    
    
    /* Test read-in:  {
        cout << "Start_x: " << startx << "  Start_y: " << starty << endl;
        cout << "End_x: " << endx << "  End_y: " << endy << endl;
        cout << "In: " << In << "  Out: " << Out << endl;
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= columns; j++)
                cout << landscape[i * COLS + j] << ' ';
            cout << '\n';
        }
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= columns; j++)
                cout << book[i * COLS + j] << ' ';
            cout << '\n';
        }
    } */

    
    // Depth-First Search:
    clock_t start = clock();
    // cout << start << endl;
    DFS(startx, starty, In);
    clock_t end = clock();
    // cout << end << endl;
    
    // Output:
    cout << "\nFound " << ways << " in total:\n\n" ;
    for (int i = 0; i < answer.size(); i++) {
        cout << "Solution " << i+1 << ": \n" ;
        for (int j = 0; j < answer[i].size(); j++)
            output(answer[i][j]);
        cout << '\n';
    }
    
    // Time:
    cout << "Excuted time: " << (double(end - start)) / CLOCKS_PER_SEC << " seconds.\n";
    
    // Free allocated dynamic storage:
    delete [] landscape;
    delete [] book;
    return 0;
}

void DFS(int x, int y, Direction front) {
    
    // Reach terminal:
    if (x == endx && y == endy) {
        // cout << "Find solution " << ++ways << '\n' ;
        // for (int i = 0; i < stack.size(); i++)
        //     cout << "( " << stack[i].x << ", " << stack[i].y << " )  ";
        // cout << endl;
        ways++;
        answer.push_back(stack) ;
        // absolutly not!!!
        // stack.pop_back();
        // steps--;
        return;
    }
    
    // Whether cross the border:
    if (x < 1 || x > rows || y < 1 || y > columns) return;
    
    // Whether search this point:
    if (book[x * COLS + y] == 1) return;
    
    // Mark current point:
    book[x * COLS + y] = 1;
    
    Node temp;
    stack.push_back(temp);
    set_node(x, y, stack[steps++], front, landscape[x * COLS + y]);
    
    book[x * COLS + y] = 0;
    stack.pop_back();
    steps--;
    return;
 
}

void set_node(int x, int y, Node & node, Direction front, Status status) {
    node.x = x;
    node.y = y;
    node.steps = steps;
    // Straight pipe:
    if (status == lr || status == ud) {
        // Enter from left:
        if (front == left) {
            node.Fdirection = left;
            node.Bdirection = right;
            node.Bstatus = lr;
            if (status == lr) {
                node.Fstatus = lr;
                node.operation = none;
            }
            else {
                node.Fstatus = ud;
                node.operation = reverse;
            }
            DFS(x, y+1, left);
        }
        // Enter from up:
        else if (front == up) {
            node.Fdirection = up;
            node.Bdirection = down;
            node.Bstatus = ud;
            if (status == lr) {
                node.Fstatus = lr;
                node.operation = reverse;
            }
            else {
                node.Fstatus = ud;
                node.operation = none;
            }
            DFS(x+1, y, up);
        }
        // Enter from right:
        else if (front == right) {
            node.Fdirection = right;
            node.Bdirection = left;
            node.Bstatus = lr;
            if (status == lr) {
                node.Fstatus = lr;
                node.operation = none;
            }
            else {
                node.Fstatus = ud;
                node.operation = reverse;
            }
            DFS(x, y-1, right);
        }
        // Enter from down:
        else if (front == down) {
            node.Fdirection = down;
            node.Bdirection = up;
            node.Bstatus = ud;
            if (status == lr) {
                node.Fstatus = lr;
                node.operation = reverse;
            }
            else {
                node.Fstatus = ud;
                node.operation = none;
            }
            DFS(x-1, y, down);
        }
    }
    
    
    // Bent pipe:
    else if (status >= ur && status <= lu) {
        // Enter from left:
        if (front == left) {
            node.Fdirection = left;
            if (status == ur) {
                node.Fstatus = ur;
                /* Case 1 */ {
                    node.Bstatus = lu;
                    node.Bdirection = up;
                    node.operation = anticlockwise_90;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = down;
                    node.operation = reverse;
                    DFS(x+1, y, up);
                }
            }
            else if (status == rd) {
                node.Fstatus = rd;
                /* Case 1 */ {
                    node.Bstatus = lu;
                    node.Bdirection = up;
                    node.operation = reverse;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = down;
                    node.operation = clockwise_90;
                    DFS(x+1, y, up);
                }
            }
            else if (status == dl) {
                node.Fstatus = dl;
                /* Case 1 */ {
                    node.Bstatus = lu;
                    node.Bdirection = up;
                    node.operation = clockwise_90;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = down;
                    node.operation = none;
                    DFS(x+1, y, up);
                }
            }
            else if (status == lu) {
                node.Fstatus = lu;
                /* Case 1 */ {
                    node.Bstatus = lu;
                    node.Bdirection = up;
                    node.operation = none;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = down;
                    node.operation = anticlockwise_90;
                    DFS(x+1, y, up);
                }
            }
        }
        
        // Enter from up:
        else if (front == up) {
            node.Fdirection = up;
            if (status == ur) {
                node.Fstatus = ur;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = right;
                    node.operation = none;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = lu;
                    node.Bdirection = left;
                    node.operation = anticlockwise_90;
                    DFS(x, y-1, right);
                }
            }
            else if (status == rd) {
                node.Fstatus = rd;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = right;
                    node.operation = anticlockwise_90;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = lu;
                    node.Bdirection = left;
                    node.operation = reverse;
                    DFS(x, y-1, right);
                }
            }
            else if (status == dl) {
                node.Fstatus = dl;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = right;
                    node.operation = reverse;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = lu;
                    node.Bdirection = left;
                    node.operation = clockwise_90;
                    DFS(x, y-1, right);
                }
            }
            else if (status == lu) {
                node.Fstatus = lu;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = right;
                    node.operation = clockwise_90;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = lu;
                    node.Bdirection = left;
                    node.operation = none;
                    DFS(x, y-1, right);
                }
            }
        }
        
        // Enter from right:
        else if (front == right) {
            node.Fdirection = right;
            if (status == ur) {
                node.Fstatus = ur;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = up;
                    node.operation = none;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = rd;
                    node.Bdirection = down;
                    node.operation = clockwise_90;
                    DFS(x+1, y, up);
                }
            }
            else if (status == rd) {
                node.Fstatus = rd;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = up;
                    node.operation = anticlockwise_90;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = rd;
                    node.Bdirection = down;
                    node.operation = none;
                    DFS(x+1, y, up);
                }
            }
            else if (status == dl) {
                node.Fstatus = dl;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = up;
                    node.operation = reverse;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = rd;
                    node.Bdirection = down;
                    node.operation = anticlockwise_90;
                    DFS(x+1, y, up);
                }
            }
            else if (status == lu) {
                node.Fstatus = lu;
                /* Case 1 */ {
                    node.Bstatus = ur;
                    node.Bdirection = up;
                    node.operation = clockwise_90;
                    DFS(x-1, y, down);
                }
                /* Case 2 */ {
                    node.Bstatus = rd;
                    node.Bdirection = down;
                    node.operation = reverse;
                    DFS(x+1, y, up);
                }
            }
        }
        
        // Enter from down:
        else if (front == down) {
            node.Fdirection = down;
            if (status == ur) {
                node.Fstatus = ur;
                /* Case 1 */ {
                    node.Bstatus = rd;
                    node.Bdirection = right;
                    node.operation = clockwise_90;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = left;
                    node.operation = reverse;
                    DFS(x, y-1, right);
                }
            }
            else if (status == rd) {
                node.Fstatus = rd;
                /* Case 1 */ {
                    node.Bstatus = rd;
                    node.Bdirection = right;
                    node.operation = none;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = left;
                    node.operation = clockwise_90;
                    DFS(x, y-1, right);
                }
            }
            else if (status == dl) {
                node.Fstatus = dl;
                /* Case 1 */ {
                    node.Bstatus = rd;
                    node.Bdirection = right;
                    node.operation = anticlockwise_90;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = left;
                    node.operation = none;
                    DFS(x, y-1, right);
                }
            }
            else if (status == lu) {
                node.Fstatus = lu;
                /* Case 1 */ {
                    node.Bstatus = rd;
                    node.Bdirection = right;
                    node.operation = reverse;
                    DFS(x, y+1, left);
                }
                /* Case 2 */ {
                    node.Bstatus = dl;
                    node.Bdirection = left;
                    node.operation = anticlockwise_90;
                    DFS(x, y-1, right);
                }
            }
        }
    }
    return;
}

void output(const Node & node) {
    
    // Steps and cordination:
    cout << "Step " << node.steps << ": Node";
    cout << "(" << node.x << ", " << node.y << ") ";
    
    // The direction of water:
    output_water_direction(node.Fdirection, node.Bdirection);
    
    // Status and operation:
    output_operation(node.Fstatus, node.Bstatus, node.operation);
    
}
   
void output_water_direction(Direction fore, Direction later) {
    cout << "Water enters from ";
    switch (fore) {
        case left:  cout << "left  to "; break;
        case up:    cout << "up    to "; break;
        case right: cout << "right to "; break;
        case down:  cout << "down  to "; break;
    }
    switch (later) {
        case left:  cout << "left,     ";   break;
        case up:    cout << "up,       ";   break;
        case right: cout << "right,    ";   break;
        case down:  cout << "down,     ";   break;
    }
}

void output_operation(Status fore, Status later, Operation operation) {
    if (operation == none) {
        switch (fore) {
            case ur: cout << "keep pipe status as up-right.\n";    break;
            case rd: cout << "keep pipe status as right-down.\n";  break;
            case dl: cout << "keep pipe status as down-left.\n";   break;
            case lu: cout << "keep pipe status as left-up.\n";     break;
            case lr: cout << "keep pipe status as left-right.\n";  break;
            case ud: cout << "keep pipe status as up-down.\n";     break;
            case tree: cout << "oops, wrong!\n";                   return;
        }
        return;
    }
    switch(fore) {
        case ur:   cout << "pepe status from up-right,        ";  output_single_operation(later, operation); break;
        case rd:   cout << "pipe status from right-down,      ";  output_single_operation(later, operation); break;
        case dl:   cout << "pipe status from down-left,       ";  output_single_operation(later, operation); break;
        case lu:   cout << "pipe status from left-up,         ";  output_single_operation(later, operation); break;
        case lr:   cout << "pipe status from left-right,      ";  output_single_operation(later, operation); break;
        case ud:   cout << "pipe status from up-down,         ";  output_single_operation(later, operation); break;
        case tree: cout << "oops, wrong!\n";                                                                 return;
    }
}

void output_single_operation(Status later, Operation operation) {
    switch (operation) {
        case clockwise_90:     cout << "rotate 90 degrees clockwise, to        "; output_single_later(later); break;
        case anticlockwise_90: cout << "rotate 90 degrees anticlockwise, to    "; output_single_later(later); break;
        case reverse:          cout << "reverse, to                            "; output_single_later(later); break;
        case none:             cout << "oops, wrong!\n";                                                      return;
    }
}

void output_single_later(Status later) {
    switch(later) {
        case ur:   cout << "up-right.\n";     break;
        case rd:   cout << "right-down.\n";   break;
        case dl:   cout << "down-left.\n";    break;
        case lu:   cout << "left-up.\n";      break;
        case lr:   cout << "left-right.\n";   break;
        case ud:   cout << "up-down.\n";      break;
        case tree: cout << "oops, wrong!\n";  return;
    }
}











