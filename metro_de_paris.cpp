//
// Created by robson on 26/09/2022.
//
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
#define fi first
#define se second
#define pb push_back
const int INF = 0x3f3f3f3f;

#define MAXE 15 /*Numero máximo de estações*/
#define MAXL 5 /*Numero máximo de linhas*/
int dist[MAXE][MAXE];/*Distancia em linha reta entre as estações*/
int d[MAXE];/*Distancia de cada estação a estação inicial*/
pii p[MAXE][MAXL];/*Anterior de cada estação numa linha qualquer*/
vector<pii> way;/*Caminho entre a estação inicial e final*/
vector<int> edge[MAXE][MAXL];
/*
 *  @brief Inicializa o valor das distâncias entre as estações e também as aretas.
 */
void init(){
    /*Distancias*/
    dist[1][2] = 11;
    dist[1][3] = 20;
    dist[1][4] = 27;
    dist[1][5] = 40;
    dist[1][6] = 43;
    dist[1][7] = 39;
    dist[1][8] = 28;
    dist[1][9] = 18;
    dist[1][10] = 10;
    dist[1][11] = 18;
    dist[1][12] = 30;
    dist[1][13] = 30;
    dist[1][14] = 32;
    dist[2][3] = 9;
    dist[2][4] = 16;
    dist[2][5] = 29;
    dist[2][6] = 32;
    dist[2][7] = 28;
    dist[2][8] = 19;
    dist[2][9] = 11;
    dist[2][10] = 4;
    dist[2][11] = 17;
    dist[2][12] = 23;
    dist[2][13] = 21;
    dist[2][14] = 24;
    dist[3][4] = 7;
    dist[3][5] = 20;
    dist[3][6] = 22;
    dist[3][7] = 19;
    dist[3][8] = 15;
    dist[3][9] = 10;
    dist[3][10] = 11;
    dist[3][11] = 21;
    dist[3][12] = 21;
    dist[3][13] = 13;
    dist[3][14] = 18;
    dist[4][5] = 13;
    dist[4][6] = 16;
    dist[4][7] = 12;
    dist[4][8] = 13;
    dist[4][9] = 13;
    dist[4][10] = 18;
    dist[4][11] = 26;
    dist[4][12] = 21;
    dist[4][13] = 11;
    dist[4][14] = 17;
    dist[5][6] = 3;
    dist[5][7] = 2;
    dist[5][8] = 21;
    dist[5][9] = 25;
    dist[5][10] = 31;
    dist[5][11] = 38;
    dist[5][12] = 27;
    dist[5][13] = 16;
    dist[5][14] = 20;
    dist[6][7] = 4;
    dist[6][8] = 23;
    dist[6][9] = 28;
    dist[6][10] = 33;
    dist[6][11] = 41;
    dist[6][12] = 30;
    dist[6][13] = 17;
    dist[6][14] = 20;
    dist[7][8] = 22;
    dist[7][9] = 25;
    dist[7][10] = 29;
    dist[7][11] = 38;
    dist[7][12] = 28;
    dist[7][13] = 13;
    dist[7][14] = 17;
    dist[8][9] = 9;
    dist[8][10] = 22;
    dist[8][11] = 18;
    dist[8][12] = 7;
    dist[8][13] = 25;
    dist[8][14] = 30;
    dist[9][10] = 13;
    dist[9][11] = 12;
    dist[9][12] = 12;
    dist[9][13] = 23;
    dist[9][14] = 28;
    dist[10][11] = 20;
    dist[10][12] = 27;
    dist[10][13] = 20;
    dist[10][14] = 23;
    dist[11][12] = 15;
    dist[11][13] = 35;
    dist[11][14] = 39;
    dist[12][13] = 31;
    dist[12][14] = 37;
    dist[13][14] = 5;
    for(int i = MAXE - 1; i >= 1 ; i--){
        for(int j = 1; j < i; j++){
            dist[i][j] = dist[j][i];
        }
    }

    /*Arestas*/
    /* 1 : azul, 2: amarela, 3: vermelha, 4: verde*/
    edge[1][1].pb(2);
    edge[2][1].pb(1);
    edge[2][1].pb(3);
    edge[2][2].pb(10);
    edge[2][2].pb(9);
    edge[3][1].pb(2);
    edge[3][1].pb(4);
    edge[3][3].pb(9);
    edge[3][3].pb(13);
    edge[4][1].pb(3);
    edge[4][1].pb(5);
    edge[4][4].pb(8);
    edge[4][4].pb(13);
    edge[5][1].pb(4);
    edge[5][1].pb(6);
    edge[5][2].pb(8);
    edge[5][2].pb(7);
    edge[6][1].pb(5);
    edge[7][2].pb(5);
    edge[8][2].pb(9);
    edge[8][2].pb(5);
    edge[8][4].pb(12);
    edge[8][4].pb(4);
    edge[9][2].pb(2);
    edge[9][2].pb(8);
    edge[9][3].pb(11);
    edge[9][3].pb(3);
    edge[10][2].pb(2);
    edge[11][3].pb(9);
    edge[12][4].pb(8);
    edge[13][3].pb(3);
    edge[13][4].pb(14);
    edge[13][4].pb(4);
    edge[14][4].pb(13);
}
/*Calcula o caminho minimo de uma estação a outra*/
void f(int initial_station, int final_station, int line_station){
    priority_queue<pair<int,pii>, vector<pair<int,pii>>, greater<pair<int,pii>> > pq;
    pq.push({0,{initial_station,line_station}});
    for(int i = 1; i < MAXE ; i++){
        d[i] = INF;
        for(int j = 1; j< MAXL; j++){
            p[i][j] = {-1,-1};
        }
    }
    d[initial_station] = 0;
    while(!pq.empty()){
        pii v = pq.top().se;
        int curr_dist = pq.top().fi;
        pq.pop();
        if (curr_dist != d[v.fi]) continue;
        /*Ir para os vizinhos na mesma linha*/
        for(auto u : edge[v.fi][v.se]){
            if(curr_dist + dist[v.fi][u] < d[u]){
                d[u] = curr_dist + dist[v.fi][u];
                pq.push({d[u],{u,v.se}});
                p[u][v.se] = {v.fi,v.se};
            }
        }
        /*Mudar de linha e ir para os vizinhos*/
        for(int i = 1; i < MAXL; i++){
            if(i == v.se) continue;
            for(auto u : edge[v.fi][i]){
                if(curr_dist + dist[v.fi][u] + 2 < d[u]){
                    d[u] = curr_dist + dist[v.fi][u] + 2;
                    pq.push({d[u],{u,i}});
                    p[u][i] = {v.fi,v.se};
                }
            }
        }
    }
    pii current_v ={final_station,0};
    for(int i = 1; i < MAXL; i++){
        if(p[final_station][i].fi != -1){
            current_v.se = i;
            break;
        }
    }
    way.pb(current_v);
    while(p[current_v.fi][current_v.se].fi != initial_station){
        pii now = p[current_v.fi][current_v.se];
        way.pb(now);
        current_v.fi = now.fi;
        current_v.se = now.se;
    }
    way.pb({initial_station,line_station});
    reverse(way.begin(),way.end());
}
int main(){
    /*Inicializando*/
    init();
    int initial_station ; /*Estação inicial*/
    int final_station; /*Estação final*/
    int total_distance = INF; /*Distancia da estação incial a final*/
    double total_time = INF; /*Tempo de viagem da estação incial a final*/
    int line_station; /*A linha que ele inicia o trajeto*/
    cin >> initial_station >> final_station>>line_station;
    /* linhas: 1 : azul, 2: amarela, 3: vermelha, 4: verde*/
    /*Processando*/
    f(initial_station,final_station,line_station);
    total_distance = d[final_station];
    total_time = double(total_distance)*2;
    /*Showing results*/
    cout<<"Total distance(km): "<<total_distance<<"\n";
    cout<<"Total time(min): "<<total_time<<"\n";
    cout<<"The way: "<<"\n";
    for(int i = 0; i < way.size() - 1 ; i++){
        if(way[i].fi != way[i+1].fi && way[i].se == way[i+1].se ){
            cout << way[i].fi <<" move to station "<< way[i+1].fi<<"\n";
        }else{
            cout << way[i].se <<" change to line "<< way[i+1].se<<"\n";
            cout << way[i].fi <<" move to station "<< way[i+1].fi<<"\n";
        }
    }
    return 0;
}
