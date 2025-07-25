import math

file = open("input.txt", "r")
data = file.read().split('\n')
file.close

inst = list(data[0])
nav = {}
for line in data[2:]:
    node, nexts = line.split(" = ")
    nav[node] = {k: v for k, v in zip(["L", "R"], nexts[1:-1].split(", "))}

curr = [node for node in nav.keys() if node.endswith("A")]
inst_idx = 0
steps = 0

least_steps = [0] * len(curr)

while 0 in least_steps:
    for i, node in enumerate(curr):
        if node.endswith("Z") and least_steps[i] == 0:
            least_steps[i] = steps

    curr = [nav[node][inst[inst_idx]] for node in curr]
    inst_idx = (inst_idx + 1) % len(inst)
    steps += 1

print(math.lcm(*least_steps))