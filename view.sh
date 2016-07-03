#!/bin/bash

# CURR_DIR=$(pwd)

RECENTDIR=$(ls -t ./data | head -1)
cd ./data/$RECENTDIR/img

setsid viewnior 0.png & disown