#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1500;
int R, C;
char lake[MAX][MAX];
bool is_melt[MAX][MAX] = {0, };
bool visited[MAX][MAX] = {false, };
typedef struct {
    int x;
    int y;
} Point;

Point swan1, swan2;
int parent[MAX][MAX] = {0, }; //RxC
vector<int> g_parent{0};

queue<Point> melt[2];
int qstate = 0;
int group_n = 1;
int time = 0;

vector<Point> around(int i, int j) {
    vector<Point> ret;
    if(i+1 < R) ret.push_back(Point{i+1, j});
    if(i-1 >= 0) ret.push_back(Point{i-1, j});
    if(j+1 < C) ret.push_back(Point{i, j+1});
    if(j-1 >= 0) ret.push_back(Point{i, j-1});
    return ret;
}

bool to_melt(int i, int j) {
    bool ret = false;
    if(i+1 < R) ret |= (lake[i+1][j] != 'X');      
    if(i-1 >= 0) ret |= (lake[i-1][j] != 'X');       
    if(j+1 < C) ret |= (lake[i][j+1] != 'X');       
    if(j-1 >= 0) ret |= (lake[i][j-1] != 'X'); 
    return ret;        
}

int find_g_ans(int i) {
    int res = i;
    while(g_parent[res] != res) {res = g_parent[res]; }
    return res;
}

void clock() {
    while(!melt[qstate].empty()) {

        int mx = melt[qstate].front().x;
        int my = melt[qstate].front().y;
        melt[qstate].pop();
        if(is_melt[mx][my]) continue; //중복 방지(이미 전에 꺼내서 녹은 지점이면 패스)
        is_melt[mx][my] = true;
        //얼음이 녹음으로 인해 연결되(ㄹ 수 있)는 집합들을 구하기
        vector<int> connect;

        //녹은 후 주변 칸들 조사
        for(auto &np : around(mx, my)) {
            int nx = np.x, ny = np.y;
            
            //얼음이 없는 칸이면 연결되지 않은 집합이 서로 연결될 수 있다
            if(is_melt[nx][ny]) {
                connect.push_back(parent[nx][ny]);
            }

            //얼음이 있는 칸이면 다음 차례때 녹아야 할 큐에 넣기
            //중복될 수 있는데, 그건 위에서 이미 처리해줌
            else {
                melt[!qstate].push(Point{nx, ny});
            }
        }

        //두 개 이상의 집합이 서로 연결되면, 가장 작은 번호를 가진 집합을 새로운 패런트로 지정
        if(!connect.empty()) {
            int new_parent = *min_element(connect.begin(), connect.end());
            for(auto &c : connect) 
                g_parent[find_g_ans(c)] = new_parent;      
            parent[mx][my] = new_parent;
        }
    }

    qstate = !qstate;
    time++;
}

void set_group(int i, int j) {

    queue<Point> q;
    q.push(Point{i, j});

    while(!q.empty()) {

        int x = q.front().x;
        int y = q.front().y;
        q.pop();

        parent[x][y] = group_n;
        for(auto &np : around(x, y)) {
            int nx = np.x, ny = np.y;

            if(!visited[nx][ny] && lake[nx][ny] != 'X') {
                visited[nx][ny] = true;
                q.push(Point{nx, ny});
            }
        }
    }    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> R >> C;
    queue<Point> q;

    for (int i = 0; i < R; i++) {
        cin >> lake[i];
        for (int j = 0; j < C; j++) {
            if (lake[i][j] == 'L') {
                q.push(Point{i, j});
                if (q.size() == 1) {
                    swan1 = Point{i, j};
                }
                else {
                    swan2 = Point{i, j};
                }
            }
        }
    }

    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            if(lake[i][j] == 'X') {
                is_melt[i][j] = false;
                if(to_melt(i, j)) melt[0].push(Point{i,j});       
            } else {
                is_melt[i][j] = true;
                if(parent[i][j] != 0) continue;

                set_group(i, j); 
                g_parent.push_back(group_n);
                group_n++;
            }
        }
    }
    
    while(true) {
        if(find_g_ans(parent[swan1.x][swan1.y]) == 
            find_g_ans(parent[swan2.x][swan2.y])) break;
        clock();
    }
    
    cout << time << endl;
}