#!/bin/bash
git add .
echo "enter your commit message: "
if [[ -v 1  ]]; then
	git commit -m "$1"
else	
	read message
	git commit -m "$message"

fi
git push
