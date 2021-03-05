import random

random.seed(477361552)

N = 1000
M = 1001
K = 350

edges = []
conds = []
done = set()

# Complete random

# Make sure a spanning tree exists
for i in range(2, N+1):
    edges.append((random.randint(1, i-1), i, random.randint(1, 500000)))

while len(edges) != M:
    i = random.randint(1, N)
    j = i
    while j == i:
        j = random.randint(1, N)
    edges.append([i, j, random.randint(1, 500000)])

while len(conds) != K:
    tp = random.randint(1, 1)
    i = random.randint(1, M)
    j = i
    while j == i or (min(i, j), max(i, j)) in done:
        j = random.randint(1, M)
    done.add((i, j))
    conds.append([tp, i, j])

random.shuffle(edges)
random.shuffle(conds)
print(N, M, K)
for e in edges:
    print(*e)
for c in conds:
    print(*c)
