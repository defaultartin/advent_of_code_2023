#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include <cstdlib>

using namespace std;

typedef enum {
	CARD_TWO,
	CARD_THREE,
	CARD_FOUR,
	CARD_FIVE,
	CARD_SIX,
	CARD_SEVEN,
	CARD_EIGHT,
	CARD_NINE,
	CARD_TEN,
	CARD_JACK,
	CARD_QUEEN,
	CARD_KING,
	CARD_ACE,
	CARD_NONE
} Card;

typedef enum {
	HAND_TYPE_HIGH_CARD,
	HAND_TYPE_ONE_PAIR,
	HAND_TYPE_TWO_PAIR,
	HAND_TYPE_THREE_OF_A_KIND,
	HAND_TYPE_FULL_HOUSE,
	HAND_TYPE_FOUR_OF_A_KIND,
	HAND_TYPE_FIVE_OF_A_KIND,
	HAND_TYPE_NONE
} HandType;

typedef struct {
	Card cards[5];
	HandType hand_type;
	int bid;
} Player;

Card get_card(char symbol)
{
	switch (symbol) {
		case '2': return CARD_TWO;
		case '3': return CARD_THREE;
		case '4': return CARD_FOUR;
		case '5': return CARD_FIVE;
		case '6': return CARD_SIX;
		case '7': return CARD_SEVEN;
		case '8': return CARD_EIGHT;
		case '9': return CARD_NINE;
		case 'T': return CARD_TEN;
		case 'J': return CARD_JACK;
		case 'Q': return CARD_QUEEN;
		case 'K': return CARD_KING;
		case 'A': return CARD_ACE;
	}

	return CARD_NONE;
}

HandType get_hand_type(string hand)
{
	set<char> cards_set;
	vector<char> cards;

	for (char c : hand) {
		cards_set.insert(c);
		cards.push_back(c);
	}

	if (cards_set.size() == 1)
		return HAND_TYPE_FIVE_OF_A_KIND; // "Five of a kind" AAAAA

	else if (cards_set.size() == 2) {
		for (char c : cards_set) {
			int cnt = count(cards.begin(), cards.end(), c);
			if (cnt == 1 || cnt == 4)
				return HAND_TYPE_FOUR_OF_A_KIND; // "Four of a kind" AA8AA

			else if (cnt == 2 || cnt == 3)
				return HAND_TYPE_FULL_HOUSE; // "Full house" 23332
		}
		return HAND_TYPE_NONE; // "Unreachable"
	}

	else if (cards_set.size() == 3) {
		for (char c : cards_set) {
			int cnt = count(cards.begin(), cards.end(), c);
			if (cnt == 3)
				return HAND_TYPE_THREE_OF_A_KIND; // "Three of a kind" TTT98

			else if (cnt == 2)
				return HAND_TYPE_TWO_PAIR; // "Two pair" 23432
		}
		return HAND_TYPE_NONE; // "Unreachable"
	}

	else if (cards_set.size() == 4)
		return HAND_TYPE_ONE_PAIR; // "One pair" A23A4

	else if (cards_set.size() == 5)
		return HAND_TYPE_HIGH_CARD; // "High card" 23456

	else
		return HAND_TYPE_NONE; // "Unreachable"
}

int cmp(const void* left, const void* right)
{
	if (!left && !right)
		return 0;

	if (!left)
		return -1;

	if (!right)
		return 1;

	const Player* left_player = (Player*)left;
	const Player* right_player = (Player*)right;

	int hand_diff = right_player->hand_type - left_player->hand_type;

	if (hand_diff)
		return hand_diff;

	for (int i = 0; i < 5; i++) {
		int card_diff = right_player->cards[i] - left_player->cards[i];

		if (card_diff)
			return card_diff;
	}

	return 0;
}

int main()
{
	vector<string> lines;
	string l;
	ifstream input("input.txt");
	while (getline(input, l))
		lines.push_back(l);
	input.close();

	const int size = lines.size();
	Player *players = new Player[size];

	for (int i = 0; i < size; i++) {
		string hand = lines[i].substr(0, 5);
		for (int c = 0; c < 5; c++) {
			assert(hand.size() == 5);
			players[i].cards[c] = get_card(hand[c]);
		}
		players[i].bid = stoi(lines[i].substr(6));
		players[i].hand_type = get_hand_type(hand);
	}

	qsort((void*)players, (unsigned)size, sizeof(*players), cmp);

	int part_1 = 0;
	int n = size;
	for (int c = 0; c < size; c++) {
		part_1 += players[c].bid * n;
		n--;
	}

	delete[] players;

	cout << "PART 1: " << part_1 << endl;

	return 0;
}