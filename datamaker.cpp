#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#define DEBUG 0
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
using namespace std;

string path;

struct Whole {
    int tim; // ms
    int mem; // kb
    string nam, std; // system_name
} whole;

struct Subtask {
    int id;
    int score;
    int ch[207], chNum;
} subtask[207];

struct Program {
    int testNum;
    string nam;
} program[207];

int sub_tot, sys_tot;
vector <int> st;

void Error(int id) {
    cerr << RED;
    if (id == 0) cerr << "Error: tab is not avalid.\n";
    if (id == 1) cerr << "Error: string is not avalid.\n";
    if (id == 2) cerr << "Error: compile error.\n";
    if (id == 3) cerr << "Error: can't find files\n";
    cerr << WHITE;
    exit(0);
}

int ToMS(string s) {
    if (s.substr((int) s.size() - 2) == "ms") 
        return atoi(s.substr(0, (int) s.size() - 2).c_str());
    return atoi(s.substr(0, (int) s.size() - 1).c_str()) * 1000;
}

int ToKB(string s) {
    if (s.substr((int) s.size() - 2) == "KB") 
        return atoi(s.substr(0, (int) s.size() - 2).c_str());
    return atoi(s.substr(0, (int) s.size() - 2).c_str()) * 1024;
}

void Compile(string s) {
    cerr << YELLOW << "compiling ./program/" << s << ".cpp\n" << WHITE;
    string ord = "g++ -O2 -Wall ./program/" + s + ".cpp -o ./program/" + s + ".exe";
    if (system(ord.c_str())) {
        Error(2);
    }
    cerr << GREEN << "compiling ./program/" << s << ".cpp successfully\n" << WHITE;
}

void Running(string data, string std, string nam) {
    cerr << YELLOW << "making ./data/" << nam << "\n" << WHITE;
    string in = path + "/data/" + nam + ".in";
    string out = path + "./data/" + nam + ".out";
    data = path + "/program/" + data + ".exe";
    std = path + "/program/" + std + ".exe";
    string ord1 = data + " > " + in;
    string ord2 = std + " < " + in + " > " + out;
    if (system(ord1.c_str())) Error(3);
    if (system(ord2.c_str())) Error(3);
    cerr << GREEN << "making ./data/" << nam << " successfully\n" << WHITE;
}

signed main() {
    freopen("config.yml", "r", stdin);
    char rt[100];
    getcwd(rt, 100);
    path = "";
    cout << rt << '\n';
    for (int i = 0; i < 100; i ++) {
        if (rt[i] != '\\' &&
            (rt[i] < 'A' || rt[i] > 'Z') &&
            (rt[i] < 'a' || rt[i] > 'z') &&
            rt[i] != ':' && rt[i] != '_')
            break;
        path += rt[i];
    }
    string s;
    while (getline(cin, s)) {
        int pre_space = 0;
        for (char c : s) {
            if (c != ' ') break;
            pre_space ++;
        }
        if (pre_space % 4 != 0) Error(0);
        pre_space /= 4;
        while (st.size() > pre_space)
            st.pop_back();
        s = s.substr(pre_space * 4);
        string val_nam = s.substr(0, s.find(':')), val = "";
        bool isLeaf = ((int) val_nam.size() != (int) s.size() - 1);
        if (isLeaf) val = s.substr(s.find(':') + 2);
        if ((int) st.size() == 0) {
            if (val_nam == "whole") {
                st.push_back(0);
            } else if (val_nam == "subtask") {
                st.push_back(++ sub_tot);
            } else {
                Error(1);
            }
        } else if ((int) st.size() == 1) {
            if (st[0] == 0) {
                if (val_nam == "time") {
                    whole.tim = ToMS(val);
                } else if (val_nam == "memory") {
                    whole.mem = ToKB(val);
                } else if (val_nam == "name") {
                    whole.nam = val;
                } else if (val_nam == "std") {
                    whole.std = val;
                } else {
                    Error(1);
                }
            } else {
                int id = st[0];
                if (isLeaf) {
                    if (val_nam == "id") {
                        subtask[id].id = atoi(val.c_str());
                    } else if (val_nam == "score") {
                        subtask[id].score = atoi(val.c_str());
                    } else {
                        Error(1);
                    }
                } else {
                    if (val_nam != "program") {
                        Error(1);
                    }
                    st.push_back(++ sys_tot);
                    subtask[id].ch[++ subtask[id].chNum] = sys_tot;
                }
            }
        } else if ((int) st.size() == 2) {
            int id = st[1];
            if (val_nam == "testNum") {
                program[id].testNum = atoi(val.c_str());
            } else if (val_nam == "name") {
                program[id].nam = val;
            } else {
                Error(1);
            }
        }
    }
    if (DEBUG) {
        cout << whole.tim << '\n';
        cout << whole.mem << '\n';
        cout << whole.nam << '\n';
        for (int i = 1; i <= sub_tot; i ++) {
            cout << "subtask" << ":\n";
            printf("    id: %d\n", subtask[i].id);
            printf("    score: %d\n", subtask[i].score);
            for (int j = 1; j <= subtask[i].chNum; j ++) {
                int id = subtask[i].ch[j];
                printf("    program:\n");
                printf("        testNum: %d\n", program[id].testNum);
                printf("        name: "); cout << program[id].nam << '\n';
            }
        }
    }
    system("md .\\data");
    freopen(".\\data\\config.yml", "w", stdout);
    int allTestNum = 0;
    for (int i = 1; i <= sub_tot; i ++) {
        int id = subtask[i].id;
        int score = subtask[i].score;
        int tim = whole.tim;
        int mem = whole.mem;
        for (int j = 1; j <= subtask[i].chNum; j ++) {
            int idx = subtask[i].ch[j];
            for (int k = 1; k <= program[idx].testNum; k ++) {
                allTestNum ++;
                cout << whole.nam << allTestNum << ".in:\n";
                printf("  timeLimit: %d\n", tim);
                printf("  memoryLimit: %d\n", mem);
                printf("  score: %d\n", score);
                printf("  subtaskId: %d\n", id);
                cout << '\n';
            }
        }
    }
    Compile(whole.std);
    for (int i = 1; i <= sys_tot; i ++) {
        Compile(program[i].nam);
    }
    allTestNum = 0;
    for (int i = 1; i <= sub_tot; i ++) {
        for (int j = 1; j <= subtask[i].chNum; j ++) {
            int idx = subtask[i].ch[j];
            for (int k = 1; k <= program[idx].testNum; k ++) {
                allTestNum ++;
                string testNam = whole.nam + to_string(allTestNum);
                Running(program[idx].nam, whole.std, testNam);
            }
        }
    }
    return 0;
}
