#!/bin/env bash
cur_dir=$(pwd)
echo "Welcome to multiprocess game. check player1.log and player2.log at the end."
echo "Starting process for player 1 in background"
$cur_dir/multiprocess_game 1 1 2 > $cur_dir/player1.log &
echo "Starting process for player 2. Press Ctrl+C to stop the player 2"
$cur_dir/multiprocess_game 0 2 1 > $cur_dir/player2.log
