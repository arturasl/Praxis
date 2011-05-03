#!/usr/bin/python3

# http://programmingpraxis.com/2011/04/29/rule-30-rng/

from math import log, floor
from functools import reduce

lst_lookup = [1, 1, 1, 0, 0, 0, 0, 1]

(state, iterations) = 123456789, 5
size = floor(log(state, 2)) + 1
main_index = size // 2

def gen_states2(n):
    cur_state = state
    for i in range(0, n):
        print([int((cur_state & (1 << i)) != 0) for i in range(size - 1, -1, -1)])
        yield cur_state

        cur_state = (cur_state << 1) | ((cur_state & 1) << (size + 1)) | (cur_state & (1 << (size - 1))) >> (size - 1)
        cur_state = reduce(lambda x, y: x + (lst_lookup[(cur_state >> y) & 7] << y), range(0, size))

print(reduce(lambda x, y: x * 2 + y, [((i >> main_index) & 1) for i in gen_states2(iterations)], 0))
