#include <iostream>
#include <vector>
#include <iomanip>
#include "poker.h"
#include "evaluator.h"
#include "monte_carlo.h"
using namespace std;
int main() {
    cout << "--- FINAL HFT ENGINE VERIFICATION ---" << endl;
    load_hand_ranks("hand_ranks.dat");
    vector<int> my_hand = { create_card(14, 0), create_card(14, 1) };
    vector<int> board;
    cout << "\n1. Simulating Aces vs 1 Opponent (Heads Up)..." << endl;
    float eq_hu = calculate_equity(my_hand, board, 1, 50000);
    cout << "   Equity: " << (eq_hu * 100) << "% (Expected: ~85%)" << endl;
    cout << "\n2. Simulating Aces vs 5 Opponents (6-Max Table)..." << endl;
    float eq_multi = calculate_equity(my_hand, board, 5, 50000);
    cout << "   Equity: " << (eq_multi * 100) << "% (Expected: ~35-49%)" << endl;
    if (eq_hu > 0.80 && eq_multi < 0.50) {
        cout << "\nSUCCESS: Engine handles multi-way equity correctly." << endl;
    } else {
        cout << "\nFAILURE: Probabilities are off." << endl;
    }

    return 0;
}