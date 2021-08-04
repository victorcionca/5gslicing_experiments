#!/bin/bash

if [ "$#" -lt 1 ]; then
	echo "Usage: db_init.sh <MONGODB IP> [NUM_UEs]"
	exit 1
fi

MONGO_IP=$1

if [ "$#" -eq 2 ]; then
    NUM_UES=$2
else
    NUM_UES=100
fi

for (( i=1 ; i<=${NUM_UES} ; i++ )); do
    ./open5gs-dbctl $MONGO_IP add $(( $i+901700000000000 )) 465B5CE8B199B49FAA5F0A2EE238A6BC E8ED289DEBA952E4283B54E88E6183CA
done
