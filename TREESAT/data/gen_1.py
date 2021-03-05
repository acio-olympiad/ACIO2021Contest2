import random

random.seed(243987340)

N = 1000
M = 100000
K = 0

edges = []
conds = []

# Complete random

# Make sure a spanning tree exists
for i in range(2, N+1):
    edges.append((1, i, 1000000))

while len(edges) != M:
    i = random.randint(1, N)
    j = i
    while j == i:
        j = random.randint(1, N)
    edges.append([i, j, random.randint(1, 500000)])

while len(conds) != K:
    tp = random.randint(1, 2)
    i = random.randint(1, M)
    j = i
    while j == i:
        j = random.randint(1, M)
    conds.append([tp, i, j])

random.shuffle(edges)
random.shuffle(conds)
print(N, M, K)
for e in edges:
    print(*e)
for c in conds:
    print(*c)
