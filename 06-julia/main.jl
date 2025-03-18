function time_to_ways(time :: Int64, iter :: Int64) :: Int64
	ways = 0
	for i in 1:time-1
		distance = (time - i) * i
		if distance > distances[iter]
			ways += 1
		end
	end
	return ways
end

lines = []

open("input.txt") do f
	while ! eof(f)
		line = readline(f)
		push!(lines, line)
	end
end

times = map((x) -> parse(Int64, x), split(lines[1])[2:end])
distances = map((x) -> parse(Int64, x), split(lines[2])[2:end])

answer = 1

index = 1
for time in times
	global answer
	global index
	ways = time_to_ways(time, index)
	answer *= ways
	index += 1
end

println("Part 1: $(answer)")

time_2 = parse(Int64, join(split(lines[1])[2:end]))
distance_2 = parse(Int64, join(split(lines[2])[2:end]))

part_2_ways = 0

for i in 1:time_2-1
	global part_2_ways
	distance = (time_2 - i) * i
	if distance > distance_2
		part_2_ways += 1
	end
end

println("Part 2: $(part_2_ways)")