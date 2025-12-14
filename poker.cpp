#include "poker.h"
#include <iostream>
#include <iomanip>
#include <bitset>
#include <algorithm>
using namespace std;
const int PRIMES[]={0,0,2,3,5,7,11,13,17,19,23,29,31,37,41};
const char RANK_CHARS[]="__23456789TJQKA";
const char SUIT_CHARS[]="hdcs";
int create_card(int rank,int suit){
    int prime=PRIMES[rank];
    int r=(rank<<8);
    int s=(1<<suit)<<12;
    int b=(1<<rank)<<16;
    
    return prime|r|s|b;
}
vector<int>init_deck(){
    vector<int>deck;
    deck.reserve(52);
    for(int suit=0;suit<4;suit++){
        for(int rank=2;rank<=14;rank++){
            deck.push_back(create_card(rank,suit));
        }
    }
    return deck;
}
string get_card_name(int card){
    int r=(card>>8)&0xF;
    int s_original=(card>>12)&0xF;
    int s=0;
    if(s_original==1)s=0;
    if(s_original==2)s=1;
    if(s_original==4)s=2;
    if(s_original==8)s=3;
    string name="";
    name+=RANK_CHARS[r];
    name+=SUIT_CHARS[s];
    return name;
}
void print_card_binary(int card){
    for(int i=31;i>=0;i--){
        cout<<((card>>i)&1);
        if(i%8==0)cout<<" ";
    }
    cout<<endl;
}
  
