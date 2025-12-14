#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <vector>
void load_hand_ranks(std::string filename);
int evaluate_5_cards(int c1, int c2, int c3, int c4, int c5);
int evaluate_7_cards(int c1, int c2, int c3, int c4, int c5, int c6, int c7);
#endif