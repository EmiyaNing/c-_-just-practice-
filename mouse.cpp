/**
 * 该代码模拟老鼠走迷宫问题。
 * 在该代码中用二维整数数组maze表示迷宫的地图，其中0表示通路，1表示墙壁。
 * 整个算法基于回溯思想。
 * 定义二维数组incr表示行进的方向，该数组第一列表示横坐标行进的方向，第二列元素表示纵坐标行进方向。
 * 路径信息通过一个全局栈path来实现存储，每一步通过三元组（i，j，dire）来表示，i是横坐标，j是纵坐标，dire表示方向。
 * 当遇到死路时会回上一步，由于我们知道该步骤的dire之前的方向已经探测过，应此从该步骤的dire + 1 开始遍历。。
*/


#include <iostream>
#include <stack>
using namespace std;

typedef struct{
    int row,col,dire;
}mazeposition;

stack<mazeposition> path;


int Mazetravle(int maze[10][10], int n, int m){
    int i=1,j=1,k,h,dire = 0;
    mazeposition temp;
    int incr[8][2] = {
        0,1,
        1,1,
        1,0,
        1,-1,
        0,-1,
        -1,-1,
        -1,0,
        -1,1
    };
    temp.row = i;
    temp.col = j;
    temp.dire = dire;
    path.push(temp);
    maze[i][j] = -1;
    while(!path.empty() || dire < 8){
        if(dire < 8){
            k = i + incr[dire][0];
            h = j + incr[dire][1];
            if(maze[k][h]!=1 && maze[k][h]!=-1){
                maze[k][h] = -1;
                temp.row = k;
                temp.col = h;
                temp.dire = dire;
                path.push(temp);
                i = k;j = h; dire = 0;
                if(i == n-2 && j == m-2){
                    cout << "congraduation !! you have find the right way !!!" << endl;
                    return 1;
                }
            }else{
                dire ++;
            }
        }else{
            dire = path.top().dire + 1;
            path.pop();
            if(!path.empty()){
                i = path.top().row;
                j = path.top().col;
            }
        }
    }
    return 0;
}

int main(){
    int maze1[10][10] = {
        1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,1,1,0,1,1,1,
        1,1,0,1,0,1,0,0,0,1,
        1,0,1,1,0,0,1,0,1,1,
        1,0,0,0,1,0,1,1,0,1,
        1,1,0,1,1,1,1,1,1,1,
        1,0,0,1,0,1,0,1,1,1,
        1,0,1,1,1,0,1,0,1,1,
        1,1,0,0,0,1,1,0,0,1,
        1,1,1,1,1,1,1,1,1,1
    };
    int l, k = Mazetravle(maze1, 10, 10);
    if(k == 0){
        cout << "No way from initial position to end" << endl;
    }else{
        int count = 0;
        int length = path.size();
        while(!path.empty()){
            cout << "Step" << length - count << " is " << path.top().row << " " << path.top().col << endl;
            count++;
            mazeposition temp = path.top();
            path.pop();
        }
    }
    return 0;
}
