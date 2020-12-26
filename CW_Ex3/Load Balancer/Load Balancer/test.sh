#! /usr/bin/env bash


./ex3_lb &
disown
sleep 0.1

python3 ex3_server.py `cat server_port` &
disown
python3 ex3_server.py `cat server_port` &
disown
python3 ex3_server.py `cat server_port` &
disown



pkill -x -u `whoami` "ex3_lb"
pkill -x -u `whoami` "ex3_server.py"
pkill -f -u `whoami` "python2.7"
pkill -f -u `whoami` "python"

pkill -9 -x -u `whoami` "ex3_lb"
pkill -9 -x -u `whoami` "ex3_server.py"
pkill -9 -f -u `whoami` "python2.7"
pkill -9 -f -u `whoami` "python"
