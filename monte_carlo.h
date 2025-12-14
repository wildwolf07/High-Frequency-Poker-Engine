#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include <vector>
float calculate_equity(const std::vector<int>&my_cards,const std::vector<int>&community_cards,int num_opponents,int iterations);
#endif