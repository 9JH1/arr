#!/bin/bash

files=$(find "$PWD" -type f)
colscur=0
filescur=""
contains() {
    if grep -q "$2" <<< "$1"; then
        return 0  # Success (true)
    else
        return 1  # Failure (false)
    fi
}
prettyPrint(){
	cols=$(($(tput cols)-${#1}))
	block=""
	for i in $(seq 1 $cols);do
		block="$block "
	done
	echo "$block$1"
}

while true;do
	if ! [[ $(tput cols) -eq $colscur ]]; then  
		colscur=$(tput cols)
		lineblock=""
		for i in $(seq 1 $(tput cols));do
			lineblock="$lineblock-"
		done
	else
		sleep 1
	fi
	clear
	echo "$lineblock"
	for file in $files; do
    			file_local="${file//$PWD/}"
    			if contains "$file_local" ".git"; then
       	 			# git was found, do nothing
				tmp=0
	    		else
				prettyPrint "${file_local:1}"
    			fi
	done
done
