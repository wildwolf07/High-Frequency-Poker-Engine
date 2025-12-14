#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;
const int PRIMES[] = {0, 0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
map<long long, int> hand_rank_map;
int get_hex_score(int counts[], bool flush, bool straight) {
    int score = 0;
    int ranks[5] = {0};
    int k = 0; 
    bool four = false, three = false;
    int pairs = 0;
    int pair1 = 0, pair2 = 0, three_val = 0, four_val = 0;
    for(int r=14; r>=2; r--) {
        if(counts[r] == 4) { four=true; four_val=r; }
        else if(counts[r] == 3) { three=true; three_val=r; }
        else if(counts[r] == 2) {
            pairs++;
            if(pair1==0) pair1=r; else pair2=r;
        }
    }
    if (straight && flush) {
        for(int r=14; r>=2; r--) if(counts[r]) {
             if(r==14 && counts[2] && counts[3] && counts[4] && counts[5]) return 0x9050000; // Wheel SF (5 high)
             return 0x9000000 | (r << 16);
        }
    }
    if (four) {
        int kicker = 0;
        for(int r=14; r>=2; r--) if(counts[r]==1) kicker=r;
        return 0x8000000 | (four_val << 16) | (kicker << 12);
    }
    if (three && pairs >= 1) {
        return 0x7000000 | (three_val << 16) | (pair1 << 12);
    }
    if (straight) {
        for(int r=14; r>=2; r--) if(counts[r]) {
            if(r==14 && counts[2]) return 0x5050000; 
            return 0x5000000 | (r << 16);
        }
    }
    if (three) {
        int k1=0, k2=0;
        for(int r=14; r>=2; r--) if(counts[r]==1) { if(!k1) k1=r; else k2=r; }
        return 0x4000000 | (three_val << 16) | (k1 << 12) | (k2 << 8);
    }
    if (pairs >= 2) {
        int kicker = 0;
        for(int r=14; r>=2; r--) if(counts[r]==1) kicker=r;
        return 0x3000000 | (pair1 << 16) | (pair2 << 12) | (kicker << 8);
    }
    if (pairs == 1) {
        int k1=0, k2=0, k3=0;
        for(int r=14; r>=2; r--) if(counts[r]==1) { 
            if(!k1) k1=r; else if(!k2) k2=r; else k3=r; 
        }
        return 0x2000000 | (pair1 << 16) | (k1 << 12) | (k2 << 8) | (k3 << 4);
    }
    int c=0;
    int h[5] = {0};
    for(int r=14; r>=2; r--) if(counts[r]) h[c++] = r;
    return 0x1000000 | (h[0]<<16) | (h[1]<<12) | (h[2]<<8) | (h[3]<<4) | h[4];
}
void generate_hands(vector<int>& current_hand, int start_rank) {
    if (current_hand.size() == 5) {
        long long product = 1;
        int counts[15] = {0};
        for (int p : current_hand) {
            product *= p;
            for(int i=2; i<=14; i++) if(PRIMES[i] == p) counts[i]++;
        }
        bool straight = false;
        int consecutive = 0;
        for (int i=2; i<=14; i++) {
            if (counts[i]) consecutive++; else consecutive = 0;
            if (consecutive == 5) straight = true;
        }
        if (!straight && counts[14] && counts[2] && counts[3] && counts[4] && counts[5]) straight = true;
        int score = get_hex_score(counts, false, straight);
        hand_rank_map[product] = score;
        return;
    }
    for (int r = start_rank; r <= 14; r++) {
        int count = 0;
        for(int p : current_hand) if(p == PRIMES[r]) count++;
        if(count >= 4) continue;
        current_hand.push_back(PRIMES[r]);
        generate_hands(current_hand, r);
        current_hand.pop_back();
    }
}
int main() {
    cout << "Generating Granular Hand Ranks..." << endl;
    vector<int> hand;
    generate_hands(hand, 2);
    ofstream outfile("hand_ranks.dat");
    for(auto const& [prod, score] : hand_rank_map) {
        outfile << prod << " " << score << endl;
    }
    outfile.close();
    cout << "Done. Saved " << hand_rank_map.size() << " precision ranks." << endl;
    return 0;
}