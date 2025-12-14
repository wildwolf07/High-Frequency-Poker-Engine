import ctypes
import os
import time
lib_name = "libpoker.dylib"
lib_path = os.path.abspath(lib_name)
poker = ctypes.CDLL(lib_path)
poker.get_equity.argtypes = [
    ctypes.POINTER(ctypes.c_int), ctypes.c_int,
    ctypes.POINTER(ctypes.c_int), ctypes.c_int,
    ctypes.c_int, ctypes.c_int
]
poker.get_equity.restype = ctypes.c_float
poker.parse_card.argtypes = [ctypes.c_char_p]
poker.parse_card.restype = ctypes.c_int
def get_equity(my_hand, board=[], num_opponents=1, iterations=50000):
    my_cards_arr = (ctypes.c_int * len(my_hand))()
    for i, c in enumerate(my_hand):
        my_cards_arr[i] = poker.parse_card(c.encode('utf-8'))
    board_arr = (ctypes.c_int * len(board))()
    for i, c in enumerate(board):
        board_arr[i] = poker.parse_card(c.encode('utf-8'))
    return poker.get_equity(
        my_cards_arr, len(my_hand),
        board_arr, len(board),
        num_opponents, iterations
    )
def make_decision(hand, board, pot_size, call_cost, num_opponents=1):
    print(f"\n--- DECISION POINT ---")
    print(f"Hand: {hand} | Board: {board}")
    print(f"Pot: ${pot_size} | Cost to Call: ${call_cost}")
    start = time.time()
    equity = get_equity(hand, board, num_opponents, iterations=50000)
    duration = (time.time() - start) * 1000
    print(f"Engine Time: {duration:.2f} ms")
    print(f"Win Probability: {equity * 100:.2f}%")
    final_pot = pot_size + call_cost
    ev = (equity * final_pot) - call_cost
    print(f"Expected Value (EV): ${ev:.2f}")
    if ev > 0:
        print("RECOMMENDATION: CALL / RAISE (Positive EV)")
        return "CALL"
    else:
        print("RECOMMENDATION: FOLD (Negative EV)")
        return "FOLD"
if __name__ == "__main__":
    poker.init_engine()
    make_decision(["As", "Ad"], [], pot_size=100, call_cost=20, num_opponents=5)
    make_decision(["9h", "Th"], ["2h", "5h", "Ks"], pot_size=200, call_cost=150, num_opponents=1)