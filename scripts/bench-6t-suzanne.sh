#!/bin/bash

set -e

make -C cmake-build-release

for way in oo fp dod; do
  echo Testing $way:
  time ./cmake-build-release/bin/pt_three_ways \
    --width 256 --height 256 \
    --num-cpus 6 --spp 48 --scene suzanne \
    --way $way /dev/null
done