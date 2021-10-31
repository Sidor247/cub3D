#!/bin/bash

cd "$(dirname "$0")/cub3D_bonus"

make
echo STARTING CUB3D
echo DO NOT CLOSE
./cub3D map.cub



