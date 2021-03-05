import random

random.seed(477361552)

N = 1000
# Make M as we go
# Make K as we go
intervals = 100

edges = []
conds = []
done = set()

# Complete random

for _ in range(intervals):
    i = random.randint(1, N)
    j = i
    while j == i:
        j = random.randint(1, N)
    if i > j: 
        i, j = j, i
    if _ == 0:
        i = 1
        j = 97
    if _ == 1:
        i = 945
        j = N
    cost = random.randint(1, 500000)
    first = len(edges) + 1
    for x in range(i, j):
        ind = len(edges) + 1
        edges.append((x, x+1, cost))
        if ind != first:
            conds.append((1, first, ind))

print(N, len(edges), len(conds))
for e in edges:
    print(*e)
for c in conds:
    print(*c)
