public static class Solution
{
	public static void Main(string[] argv)
	{
		if (argv.Length != 1) {
			Console.WriteLine("Only One input file!");
			System.Environment.Exit(1);
		}

		string[] lines = System.IO.File.ReadAllLines(argv[0]);

		int part1_ans = 0;

		int[] cards = new int[lines.Length];
		for (int i = 0; i < lines.Length; i++)
			cards[i] = 1;

		string[] spliter = { "  ", " " };
		foreach (var line in lines) {
			int cards_num = int.Parse(line.Split(':')[0].Split("Card")[1].Trim());

			var parts = line.Split(": ")[1].Split(" | ");
			var winning_numbers = parts[0].Split(spliter, System.StringSplitOptions.RemoveEmptyEntries);
			var my_numbers = parts[1].Split(spliter, System.StringSplitOptions.RemoveEmptyEntries);

			int count = 0;
			int points = 0;

			for (int i = 0; i < winning_numbers.Length; i++) {
				int pos = Array.IndexOf(my_numbers, winning_numbers[i]);
				if (pos > -1)
					count++;
			}

			if (count == 0 || count == 1)
				points = count;
			else
				points = (int) Math.Pow(2, count-1);

			part1_ans += points;

			for (int c = 0; c < count; c++)
				for (int m = 0; m < cards[cards_num-1]; m++)
					cards[cards_num+c] = cards[cards_num+c]+1;
		}
		int part2_ans = cards.Sum();

		Console.WriteLine($"Part 1: {part1_ans}");
		Console.WriteLine($"Part 2: {part2_ans}");
	}
}
