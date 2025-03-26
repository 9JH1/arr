```
"Auto Read-Runner"
* * * * * *
arr [OPTIONS]
OPTIONS:
--command    | command run when file is modifyed
--interval   | interval in seconds the file is checked
--message    | message showen when file is edited
--no-message | disable showing message
--no-command | disable running command
--no-startup | disable file check on script start

* * * * * *
copyright 2025 9JH1
```
## Compile & Run
```
git clone https://github.com/9jh1/arr && cd arr
gcc arr_2.c -o arr
clear
./arr
```
## Install
> ensure that there is not already a `arr` binary in your bin folder, if so rename or remove
```
sudo mv arr /usr/bin/arr
```
