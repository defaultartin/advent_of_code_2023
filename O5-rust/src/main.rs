fn main() {
    let input = std::fs::read_to_string("input.txt").unwrap();
    let mut content = input
        .split('\n')
        .filter(|s| !s.is_empty())
        .collect::<Vec<_>>();

    let seeds = content[0]
        .split(": ")
        .filter(|t| !t.is_empty())
        .collect::<Vec<_>>()[1]
        .split(' ')
        .filter(|r| !r.is_empty())
        .map(|x| x.parse::<i64>().unwrap())
        .collect::<Vec<_>>();
    content.remove(0);

    let mut locations = Vec::new();

    for seed in seeds {
        let mut to_num: i64 = seed;
        let mut is_in_map: bool = false;
        for line in &content {
            if line.contains("map:") {
                is_in_map = true;
                continue;
            } else {
                if is_in_map {
                    let map_nums = line.split(' ').map(|i| i.parse::<i64>().unwrap()).collect::<Vec<_>>();
                    if to_num >= map_nums[1] && to_num < map_nums[1]+map_nums[2] {
                        to_num += map_nums[0] - map_nums[1];
                        is_in_map = false;
                    }
                } else {
                    continue;
                }
            }
        }
        locations.push(to_num);
    }
    let min = locations.iter().min().unwrap();

    println!("Part 1: {min}");
}
