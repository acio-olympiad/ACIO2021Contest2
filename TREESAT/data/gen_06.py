import random
import sys

random.seed(266385743)

N = 1000
# Make M as we go
# Make K as we go

orig_edges = []
edges = []
conds = []

# Complete random

total_cost = 0

# Make sure a spanning tree exists
for i in range(2, N+1):
    cost = random.randint(1, 50000)
    total_cost += cost
    orig_edges.append([random.randint(1, i-1), i, cost])

edges = orig_edges[:]

for _ in range(97):
    for i, (u, v, c) in enumerate(orig_edges):
        ind = len(edges) + 1
        edges.append([u, v, c + 100000])
        if random.randint(0, 1):
            conds.append([2, ind, random.randint(1, len(orig_edges))])
        elif i > 0:
            conds.append([1, ind, ind-1])

sys.stderr.write("Total cost: %d\n" % total_cost)
#random.shuffle(edges)
#random.shuffle(conds)
print(N, len(edges), len(conds))
for e in edges:
    print(*e)
for c in conds:
    print(*c)
