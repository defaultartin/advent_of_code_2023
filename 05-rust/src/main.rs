fn seed_to_location(seed: i64, content: Vec<&str>) -> i64 {
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
    to_num
}

fn location_to_seed(location: i64, mut content: Vec<&str>) -> i64 {
    let mut to_num: i64 = location;
    let mut is_in_map: bool = true;
    content.reverse();
    for line in &content {
        if line.contains("map:") {
            is_in_map = true;
            continue;
        } else {
            if is_in_map {
                let map_nums = line.split(' ').map(|i| i.parse::<i64>().unwrap()).collect::<Vec<_>>();
                if to_num >= map_nums[0] && to_num < map_nums[0]+map_nums[2] {
                    to_num += map_nums[1] - map_nums[0];
                    is_in_map = false;
                }
            }
        }
    }
    to_num
}

fn is_seed_in_range(seeds: Vec<i64>, seed: i64) -> bool {
    let mut l: usize = 1;
    for _ in 1..=(seeds.len())/2 {
        if seed >= seeds[l-1] && seed < seeds[l-1]+seeds[l] {
            return true;
        }
        l += 2;
    }
    false
}

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

    for seed in &seeds {
        let to_num = seed_to_location(*seed, content.clone());
        locations.push(to_num);
    }
    let min = locations.iter().min().unwrap();

    let mut i: i64 = 15800000;
    loop {
        let seed = location_to_seed(i, content.clone());
        if is_seed_in_range(seeds.clone(), seed) {
            break;
        }
        i += 1;
    }

    println!("Part 1: {min}");
    println!("Part 2: {i}");
    // Don't Do this, It's Horrible :)
}
