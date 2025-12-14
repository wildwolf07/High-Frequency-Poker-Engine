#ifndef POKER_H
#define POKER_H

#include <vector>
#include <string>
typedef int Card;
extern const int PRIMES[];
extern const char RANK_CHARS[];
extern const char SUIT_CHARS[];

int create_card(int rank,int suit);
std::vector<int>init_deck();
std::string get_card_name(int card);
void print_card_binary(int card);

#endif