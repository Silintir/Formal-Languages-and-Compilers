#!/usr/bin/env python3

def find_trans(pattern, alphabet):
    transition_function = {}
    m = len(pattern)
    for q in range(m + 1):
        for char in alphabet:
            k = min(m, q + 1)
            while not (pattern[:q] + char).endswith(pattern[:k]):
                k -= 1
            transition_function[(q, char)] = k
    return transition_function


def search(text, pattern, alphabet):
    trans = find_trans(pattern, alphabet)
    result = []
    q = 0
    pattern_length = len(pattern)
    for i, t in enumerate(text):
        q = trans[(q, t)]
        if q == pattern_length:
            shift = i - pattern_length + 1
            result.append(shift)
    return result



print(search("78787999997878787879","0","7890"))
print(search("78787999997878787879","9","7890"))
print(search("78787999997878787879","787","7890"))
print(search("78787999997878787879","99","7890"))
print(search("78787999997878787879","879","7890"))
print(search("78787999997878787879","978","7890"))
