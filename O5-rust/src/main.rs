fn main() {
    let input = std::fs::read_to_string("test_first.txt").unwrap();
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
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<_>>();
    content.remove(0);

    println!("{:?}", seeds);

    println!("{:?}", content);
}
