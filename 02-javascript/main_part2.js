import { readFileSync } from 'node:fs';

// Read file and check error
if (process.argv.length != 3) console.error("File path must be defined through the first argument!");
const data = readFileSync(process.argv[2]).toString().trim().split('\n');

function check_play(play, red, green, blue) {

	const element = play.split(', ');
	element.forEach(cube => {

		if (cube.includes('red')) {
			red.push(parseInt(cube.split(' ')[0]));
		}
		else if (cube.includes('green')) {
			green.push(parseInt(cube.split(' ')[0]));
		}
		else if (cube.includes('blue')) {
			blue.push(parseInt(cube.split(' ')[0]));
		}
		else console.log("FUCK Advent of Code!");
	});
}

let power = 0;

data.forEach(line => {
	let red = [0];
	let green = [0];
	let blue = [0];

	const plays = line.slice(5).split(': ')[1].split('; ');
	for (const play of plays) {
		check_play(play, red, green, blue);
	}
	const mult = Math.max(...red) * Math.max(...green) * Math.max(...blue);
	power += mult;
});

console.log(power);