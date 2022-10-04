//
// Created by robso on 04/10/2022.
//
#include <bits/stdc++.h>

using namespace std;
const int MAXN = 10;
const int INF = 500000;
int dist[MAXN + 1][MAXN + 1];
void init(){
    for(int i = 1; i<= MAXN; i++){
        for(int j = 1; j<= MAXN; j++){
            if(i == j){
                dist[i][j] = 0;
            }else{
                dist[i][j] = INF;
            }
        }
    }
    /* 1 para todos */
    dist[1][2] = 30;
    dist[1][3] = 84;
    dist[1][4] = 56;
    dist[1][6] = 70;
    dist[1][8] = 75;
    dist[1][10] = 80;
    /* 2 para todos */
    dist[2][3] = 65;
    dist[2][7] = 70;
    dist[2][10] = 40;
    /* 3 para todos */
    dist[3][4] = 74;
    dist[3][5] = 52;
    dist[3][6] = 55;
    dist[3][8] = 135;
    dist[3][9] = 143;
    dist[3][10] = 48;
    /* 4 para todos */
    dist[4][5] = 135;
    dist[4][8] = 20;
    /* 5 para todos */
    dist[5][6] = 70;
    dist[5][8] = 122;
    dist[5][9] = 98;
    dist[5][10] = 80;
    /* 6 para todos */
    dist[6][7] = 63;
    dist[6][9] = 82;
    dist[6][10] = 35;
    /* 7 para todos */
    dist[7][9] = 120;
    dist[7][10] = 57;
    for(int i = 1; i<= MAXN; i++){
        for(int j = 1; j<= MAXN; j++){
            dist[i][j] = min(dist[i][j], dist[j][i]);
        }
    }
}
int f(vector<int> a){
    int ans = 0;
    a.insert(a.begin(), 1);
    a.push_back(1);
    for(int i = 0; i < a.size() - 1 ; i++){
        ans += dist[a[i]][a[i+1]];
    }
    return ans;
}
int main(){
    init();
    vector<int>x = {2,3,4,5,6,7,8,9,10};
    int ans = INF;
    vector<int> way;
    do {
        int curr = f(x);
        if(curr < ans){
            way = x;
            ans = curr;
        }
    } while(next_permutation(x.begin(), x.end()));
    cout<<ans<<endl;
    way.insert(way.begin(), 1);
    way.push_back(1);
    for(auto k : way){
        cout<<k<<" ";
    }
    cout<<endl;
    return 0;
}