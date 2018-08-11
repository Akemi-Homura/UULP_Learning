#!/bin/bash
IP=$SERVER1
USER=$LOGINNAME1
PORT=$PORT1
SSHPATH=$SSHPATH1
SSHCOMMAND="ssh $USER@$IP -p$PORT -i $SSHPATH"

 while true
 do
     tmux send-keys -t "^.2" "$SSHCOMMAND" Enter
     sleep 3
     tmux send-keys -t "^.2" C-d
     sleep 3
 done
