#!/bin/bash
git add .
if [[ -v 1  ]]; then
	echo "Your commit message: $1"
	git commit -m "$1"
else	
	echo "Enter your commit message: "
	read message
	git commit -m "$message"

fi
git push
