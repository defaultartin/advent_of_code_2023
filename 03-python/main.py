import sys

if len(sys.argv) != 2:
    print("ERROR: Only One input file! {file_path}")
    exit(1)

try:
    with open(sys.argv[1], "r") as file:
        lines = [line.strip() for line in file.readlines()]
except Exception as e:
    print(e)
    exit(1)

for i in range(len(lines)):
    lines[i] = "." + lines[i] + "."
period_line = "." * len(lines[0])
lines.insert(0, period_line)
lines.append(period_line)




def find_symbol(row, start_col, end_col, lines):
    for r in range(row - 1, row + 2):
        for c in range(start_col - 1, end_col + 1):
            if cell_has_symbol(r, c, lines):
                return r, c

    if cell_has_symbol(row, start_col - 1, lines):
        return row, start_col - 1

    if cell_has_symbol(row, end_col, lines):
        return row, end_col

    return None




def cell_has_symbol(row, col, lines) -> bool:
    cell = lines[row][col]
    if cell.isnumeric() or cell == ".":
        return False

    return True



sum1 = 0
number = 0
in_number = False
number_col = 0
gears = {}

for row, line in enumerate(lines):
    for col, char in enumerate(line):
        if char.isnumeric():
            number = number * 10 + int(char)

            if not in_number:
                in_number = True
                number_col = col

        elif in_number:
            symbol = find_symbol(row, number_col, col, lines)
            if symbol:
                sum1 += number

                if lines[symbol[0]][symbol[1]] == "*":
                    if symbol in gears:
                        gears[symbol][0] += 1
                        gears[symbol][1] *= number
                    else:
                        gears[symbol] = [1, number]

            in_number = False
            number = 0

sum2 = 0
for count, ratio in gears.values():
    if count == 2:
        sum2 += ratio

print(f"Part 1: {sum1}")
print(f"Part 2: {sum2}")