import sys
import random

random.seed(599492832)

N, M, _ = [int(x) for x in input().split()]
K = 100000

edges = []
conds = []

for _ in range(M):
    u, v, w = [int(x) for x in input().split()]
    edges.append([u, v, w * 3])

with open("t1.sol") as f:
    uses = set(int(x) for x in f.read().split()[1:])

for _ in range(K):
    i = random.randint(1, M)
    j = i
    while j == i:
        j = random.randint(1, M)

    if (i in uses) == (j in uses):
        conds.append([1, i, j])
    else:
        conds.append([2, i, j])

print(N, M, len(conds))
for x in edges:
    print(*x)
for x in conds:
    print(*x)
