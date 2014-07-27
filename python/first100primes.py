#!/usr/bin/env python

import math

N_PRIMES = 100

def next_prime():
    n = 3
    while True:
        while not is_prime(n):
            n += 2
        else:
            yield n
            n += 2

def is_prime(x):
    for y in xrange(2, int(math.ceil(math.sqrt(x)) + 1)):
        if x % y == 0:
            return False
    else:
        return True

np = next_prime()
print [np.next() for p in range(N_PRIMES)]
