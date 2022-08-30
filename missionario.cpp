#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50;
struct no
{
    int qnt_missionarios_A;
    int qnt_canibais_A;
    int qnt_missionarios_B;
    int qnt_canibais_B;
    int lado;
};

no visitado[MAXN][MAXN][MAXN][MAXN][3];
const int dx[] = {0,1,2};
bool valid(no x){
    if(x.qnt_missionarios_A < 0 || x.qnt_missionarios_B < 0 || x.qnt_canibais_A < 0 || x.qnt_canibais_B < 0){
        return false;
    }
    if((x.qnt_missionarios_A != 0 && x.qnt_canibais_A > x.qnt_missionarios_A) ||(x.qnt_missionarios_B != 0 && x.qnt_canibais_B > x.qnt_missionarios_B)){
        return false;
    }
    return true;
}
bool isNew(no x){
    if(x.lado == 0) return true;
    return false;
}
string lado(int a){
    return (a == 1 ? "A" : "B" );
}
no bfs(int n){
   queue<no> q;
   q.push({n,n,0,0,1});
   visitado[n][n][0][0][1] = {0,0,0,0,-1};
   while(!q.empty()){
    no curr = q.front();
    q.pop();
    //cout<< curr.qnt_missionarios_A<<" "<< curr.qnt_canibais_A <<" " << curr.qnt_missionarios_B<<" "<<curr.qnt_canibais_B<<" "<<curr.lado<<endl;
    if(curr.qnt_missionarios_A == 0 && curr.qnt_canibais_A == 0){
        return curr;
    }
    if(curr.lado == 1){
        for(int i = 0; i< 3; i++){
            for(int j = 0 ; j< 3; j++){
                if(dx[i]+dx[j] > 2 || dx[i]+dx[j] == 0){
                    continue;
                }
                no novo = {curr.qnt_missionarios_A - dx[i],curr.qnt_canibais_A - dx[j],curr.qnt_missionarios_B + dx[i],curr.qnt_canibais_B + dx[j],2};
                if(valid(novo) && isNew(visitado[novo.qnt_missionarios_A][novo.qnt_canibais_A][novo.qnt_missionarios_B][novo.qnt_canibais_B][novo.lado])){
                    q.push(novo);
                    visitado[novo.qnt_missionarios_A][novo.qnt_canibais_A][novo.qnt_missionarios_B][novo.qnt_canibais_B][novo.lado] = curr;
                }
            }
        }
    }else{
        for(int i = 0; i< 3; i++){
            for(int j = 0 ; j< 3; j++){
                if(dx[i]+dx[j] > 2 || dx[i]+dx[j] == 0){
                    continue;
                }
                no novo = {curr.qnt_missionarios_A + dx[i],curr.qnt_canibais_A + dx[j],curr.qnt_missionarios_B - dx[i],curr.qnt_canibais_B - dx[j],1};
                if(valid(novo) && isNew(visitado[novo.qnt_missionarios_A][novo.qnt_canibais_A][novo.qnt_missionarios_B][novo.qnt_canibais_B][novo.lado])){
                    q.push(novo);
                    visitado[novo.qnt_missionarios_A][novo.qnt_canibais_A][novo.qnt_missionarios_B][novo.qnt_canibais_B][novo.lado] = curr;
                }
            }
        }
    }
   }
   return {0,0,0,0,-1};
}

int main(){
   ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
   no ans = bfs(3);
   if(ans.lado == -1){
       cout<<"Sem solucao"<<endl;
   }
   vector<no> solution;
   while(ans.lado != -1){
       no curr = ans;
       solution.push_back(ans);
       ans = visitado[curr.qnt_missionarios_A][curr.qnt_canibais_A][curr.qnt_missionarios_B][curr.qnt_canibais_B][curr.lado];
   }
   reverse(solution.begin(), solution.end());
   for(int i = 0; i< solution.size(); i++){
       cout<<"(Passo: "<< i<<") ";
       cout<<"Mi em A:("<<solution[i].qnt_missionarios_A<<") Ca em A:("<< solution[i].qnt_canibais_A <<") Mi em B:("<< solution[i].qnt_missionarios_B<<") Ca em B:8("<<solution[i].qnt_canibais_B<<") Lado:"<<lado(solution[i].lado)<<endl;
   }
   return 0;
}