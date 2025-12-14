#include "evaluator.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
map<long long,int>LOOKUP_TABLE;
void load_hand_ranks(string filename){
    ifstream infile(filename);
    if (!infile.is_open()){
        cout << "Error opening "<< filename << endl;
        exit(1);
    }
    long long product;
    long long score;
    while (infile>>product>>score){
        LOOKUP_TABLE[product]=score;
    }
    infile.close();
    cout << "Engine loaded " << LOOKUP_TABLE.size() << " ranks." << endl;
}
int evaluate_5_cards(int c1,int c2,int c3,int c4,int c5){
    bool is_flush = (c1&c2&c3&c4&c5)&0xF000;
    long long q=(long long)(c1&0xFF)*(c2&0xFF)*(c3&0xFF)*(c4&0xFF)*(c5&0xFF);
    int score=LOOKUP_TABLE[q];
    if(is_flush){
        int type=(score>>24)&0xF;
        if(type==5){
            return(score&0x0FFFFFFF)|0x90000000;
        }
        return(score&0x0FFFFFFF)|0x60000000;
    }
    return score;
}
int evaluate_7_cards(int c1,int c2,int c3,int c4,int c5,int c6,int c7){
    int pool[7]={c1,c2,c3,c4,c5,c6,c7};
    int max_score=0;
    for(int i=0;i<3;i++)
    for(int j=i+1;j<4;j++)
    for(int k=j+1;k<5;k++)
    for(int l=k+1;l<6;l++)
    for(int m=l+1;m<7;m++){
        int score=evaluate_5_cards(pool[i],pool[j],pool[k],pool[l],pool[m]);
        if(score>max_score)max_score=score;
    }
    return max_score;
}