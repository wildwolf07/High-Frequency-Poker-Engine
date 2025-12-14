#include <vector>
#include "poker.h"
#include "evaluator.h"
#include "monte_carlo.h"
using namespace std;
extern "C"{
    void init_engine(){
        load_hand_ranks("hand_ranks.dat");
    }
    float get_equity(int*my_cards_arr,int my_len,int* board_cards_arr,int board_len,int num_opponents,int iterations){
        vector<int>my_cards;
        for (int i=0;i<my_len;i++)my_cards.push_back(my_cards_arr[i]);
        vector<int> board;
        for (int i=0;i<board_len;i++)board.push_back(board_cards_arr[i]);
        return calculate_equity(my_cards,board,num_opponents,iterations);
    }
    int parse_card(const char* card_str){
        char r = card_str[0];
        char s = card_str[1];
        int rank = 0;
        if (r >= '2' && r <= '9') rank = r - '0';
        else if (r == 'T') rank = 10;
        else if (r == 'J') rank = 11;
        else if (r == 'Q') rank = 12;
        else if (r == 'K') rank = 13;
        else if (r == 'A') rank = 14;
        int suit = 0;
        if (s == 'c') suit = 0;
        if (s == 'd') suit = 1;
        if (s == 'h') suit = 2;
        if (s == 's') suit = 3;
        return create_card(rank, suit);
    }
}    