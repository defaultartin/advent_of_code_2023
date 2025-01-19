package main

import (
	"fmt"
	"os"
	"regexp"
	"slices"
	"strconv"
	"strings"
)

func check_first(line string, words []string, m map[string]string) string {
	var str string
	for i := 0; i < len(line); i++ {
		str = line[:i]
		if !regexp.MustCompile(`^[0-9]+$`).MatchString(str) {
			for _, word := range words {
				if strings.HasSuffix(str, word) {
					str = strings.Replace(str, word, m[word], 1)
					return str + line[i:]
				}
			}
		} else {
			return line
		}
	}
	return line
}

func check_last(line string, words []string, m map[string]string) string {
	var str string
	for i := len(line)-1; i >= 0; i-- {
		str = line[i:]
		if !regexp.MustCompile(`^[0-9]+$`).MatchString(str) {
			for _, word := range words {
				if strings.HasPrefix(str, word) {
					str = strings.Replace(str, word, m[word], 1)
					return line[:i] + str
				}
			}
		} else {
			return line
		}
	}
	return line
}

func main() {
	if len(os.Args) != 2 {
		panic("Error: only one input (file path)")
	}
	file_path := os.Args[1]
	dat, err := os.ReadFile(file_path)
	if err != nil {
		panic(err)
	}
	file := string(dat)

	nums := []string{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"}
	words := []string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
	var digits [2]string
	sum := 0

	m := map[string]string{"one": "1", "two": "2", "three": "3", "four": "4", "five": "5", "six": "6", "seven": "7", "eight": "8", "nine": "9"}

	lines := strings.Split(file, "\n")

	for _, line := range lines {
		line = check_last(line, words, m)
		line = check_first(line, words, m)

		for i := 0; i < len(line); i++ {
			char := string(line[i])
			if slices.Contains(nums, char) {
				digits[0] = char
				break
			}
		}
		for j := len(line)-1; j >= 0; j-- {
			char := string(line[j])
			if slices.Contains(nums, char) {
				digits[1] = char
				break
			}
		}
		ints, _ := strconv.Atoi(strings.Join(digits[:], ""))
		sum += ints
	}
	fmt.Println(sum)
}