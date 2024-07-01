from time import sleep
import os
from sys import argv
from sys import exit as leave

# passs
allow   = True
install = False



#vars 
filepth = ""
command = ""
message = ""
timeout = 1
filecon = ""
filecur = ""
argindx = 0
 
#arg parser
for arg in argv:
    argindx = argindx+1
    def help():
        print(
"""USAGE:
arr -f <file> -c <command>

OPTIONS
    -f <file>    file to be listened
    -c <command> sets the command run if the file is changed
    -m <message> sets a message to print on file change
    -t <timeout> set the interval at which the file is checked
""")
        leave()
    def ItA(index):
        return argv[argv.index(index)+1]
    if len(argv) == 1:
        # if user inputs zero real arguments
        # then skip and load help
        help()
    else:
        if argindx == 0: 
            pass
        else:
            # first argument cases
            if arg == "-f": 
               filepth = ItA("-f")
            elif arg == "-c":
               command = ItA("-c")
            elif arg == "-m": 
                message = ItA("-m")
            elif arg == "-t":
                timeout = ItA("-t")
            elif arg == "--help" or arg == "-h":
                help()
if allow == True:
    if command == "" or filepth == "":
        print("not enough options specifyed\nrun ar --help for more info")
        allow = False
    if allow == True: 
        try:
            filecon = open(filepth,"r").read()
        except:
            print("File "+filepth+" dosent exist")
            allow = False
    


while allow == True: 
    sleep(timeout)
    filecur = open(filepth,"r").read()
    if filecur != filecon:
        if message != "":
            print(message)   
        os.system(command)
        filecon = filecur
