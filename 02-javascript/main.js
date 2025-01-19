import { readFileSync } from 'node:fs';

// Read file and check error
if (process.argv.length != 3) console.error("File path must be defined through the first argument!");
const data = readFileSync(process.argv[2]).toString().trim().split('\n');

// function to check play is possible or not
function check_play(play) {
	let Cubes = {};
	Cubes.red = 0;
	Cubes.green = 0;
	Cubes.blue = 0;

	const element = play.split(', ');
	element.forEach(cube => {

		if (cube.includes('red')) {
			Cubes.red = parseInt(cube.split(' ')[0]);
		}
		else if (cube.includes('green')) {
			Cubes.green = parseInt(cube.split(' ')[0]);
		}
		else if (cube.includes('blue')) {
			Cubes.blue = parseInt(cube.split(' ')[0]);
		}
		else console.log("FUCK Advent of Code!");
	});

	if (Cubes.red > 12 || Cubes.green > 13 || Cubes.blue > 14) {
		return false;
	}
	return true;
}
// end of function

let sum = 0;

data.forEach(line => {
	let Game = {};

	Game.game_num = parseInt(line.slice(5).split(': ')[0]);
	Game.play_bool = false

	const plays = line.slice(5).split(': ')[1].split('; ');
	for (const play of plays) {
		if (!check_play(play)) {
			Game.play_bool = false;
			break;
		}
		Game.play_bool = true;
	}

	if (Game.play_bool)
		sum += Game.game_num;
});

console.log(sum);