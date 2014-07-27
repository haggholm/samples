#!/usr/bin/env python
"""Sample program to compare programming languages for my own edification.

This program reads the KJV bible (from a fixed location) and computes the
word frequency, printing the number of occurrences and frequency of the top
25 words.
"""

n_words = 25

freq = {}
with open('../data/kingjames.txt') as fh:
    for line in fh:
        words = [w for w in line.strip().lower().split(' ') if w]
        for word in words:
            freq[word] = freq[word]+1 if word in freq else 1

def numfmt(num):
    if not isinstance(num, basestring):
        num = str(num)
    if len(num) <= 3:
        return num
    else:
        return numfmt(num[:-3]) + ',' + num[-3:]

lst = sorted(freq.items(), lambda a, b: cmp(a[1], b[1]), reverse=True)
total_words = sum(freq.values())

print('Top %s words in the King James Bible' % numfmt(n_words))
print('(Total words: %s; %s distinct words)' % (numfmt(total_words),
                                                numfmt(len(freq))))
print('\n'.join(
    ['%-10s %8s (%.1f%%)' % (word, numfmt(n), float(n)/total_words*100)
     for (word, n) in lst[:n_words]]))
