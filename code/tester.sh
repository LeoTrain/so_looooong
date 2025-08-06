#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

BIN=./so_long
MAPS_DIR=maps

test_map() {
	map=$1
	expected=$2

	$BIN "$MAPS_DIR/$map" > /dev/null 2>&1
	result=$?
	if [ "$result" -eq "$expected" ]; then
		printf "Testing %-40s ${GREEN}[OK]${RESET}\n" "$map"
	else
		printf "Testing %-40s ${RED}[FAIL] Expected %d, got %d${RESET}\n" "$map" "$expected" "$result"
	fi
}

test_map wrong/1.ber 1
test_map wrong/2.ber 1
test_map wrong/empty.ber 1
test_map wrong/missing_a_wall.ber 1
test_map wrong/no_coins.ber 1
test_map wrong/no_rectangular_height.ber 1
test_map wrong/no_rectangular_width.ber 1
test_map wrong/no_walls.ber 1
test_map wrong/only_wall.ber 1
test_map wrong/two_exit.ber 1
test_map wrong/two_exit_same_line.ber 1
test_map wrong/two_player_spawn.ber 1
test_map wrong/two_player_spawn_same_line.ber 1
test_map map.ber 0
