file = open("input.txt", "r")
lines = file.read().split('\n')
file.close

instructions = lines[0]

elements = []
lefts = []
rights = []

for line in lines[2:]:
    sections = line.split('=')
    element = sections[0].strip()
    left = sections[1].strip().split(', ')[0][1:].strip()
    right = sections[1].strip().split(', ')[1][:-1].strip()
    elements.append(element)
    lefts.append(left)
    rights.append(right)

start = "AAA"
end = "ZZZ"

step = 0
instructions_index = 0

while start != end:
    i = elements.index(start)
    if instructions[instructions_index] == "L":
        start = lefts[i]
    elif instructions[instructions_index] == "R":
        start = rights[i]
    instructions_index += 1
    if instructions_index >= len(instructions):
        instructions_index = 0
    step += 1

print(step)