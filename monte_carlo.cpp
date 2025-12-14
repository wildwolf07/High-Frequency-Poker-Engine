#include "monte_carlo.h"
#include "poker.h"
#include "evaluator.h"
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <future>
using namespace std;
void remove_cards(vector<int>& deck, const vector<int>& to_remove) {
    for (int card : to_remove) {
        auto it = remove(deck.begin(), deck.end(), card);
        if (it != deck.end()) deck.erase(it, deck.end());
    }
}
pair<int, int> run_simulation_batch(int iterations, vector<int> full_deck, vector<int> my_cards, vector<int> community_cards, int num_opponents, int seed_offset){
    int wins = 0;
    int ties = 0;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count() + seed_offset;
    mt19937 rng(seed);
    vector<int> deck(full_deck.size());
    vector<int> board;
    board.reserve(5);
    for (int i = 0; i < iterations; i++) {
        deck = full_deck;
        shuffle(deck.begin(), deck.end(), rng);
        board = community_cards;
        int deck_idx = 0;
        while (board.size() < 5) board.push_back(deck[deck_idx++]);
        int my_score = evaluate_7_cards(
            my_cards[0], my_cards[1],
            board[0], board[1], board[2], board[3], board[4]
        );
        int best_opp_score = 0;
        for (int k = 0; k < num_opponents; k++) {
            int o1 = deck[deck_idx++];
            int o2 = deck[deck_idx++];
            int opp_score = evaluate_7_cards(
                o1, o2,
                board[0], board[1], board[2], board[3], board[4]
            );
            if (opp_score > best_opp_score) best_opp_score = opp_score;
        }

        if (my_score > best_opp_score) wins++;
        else if (my_score == best_opp_score) ties++;
    }

    return {wins, ties};
}
float calculate_equity(const vector<int>& my_cards, const vector<int>& community_cards, int num_opponents, int iterations) {
    vector<int> full_deck = init_deck();
    remove_cards(full_deck, my_cards);
    remove_cards(full_deck, community_cards);
    int num_threads = thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    int batch_size = iterations / num_threads;
    vector<future<pair<int, int>>> futures;
    for (int i = 0; i < num_threads; i++) {
        int actual_batch = (i == num_threads - 1) ? (iterations - (batch_size * i)) : batch_size;
        futures.push_back(async(launch::async, run_simulation_batch, actual_batch, full_deck, my_cards, community_cards, num_opponents, i));
    }
    int total_wins = 0;
    int total_ties = 0;
    for (auto& f : futures) {
        pair<int, int> result = f.get();
        total_wins += result.first;
        total_ties += result.second;
    }
    return (total_wins + (total_ties * 0.5f)) / (float)iterations;
}