import os
import subprocess
from subprocess import call
import sys

# default board name
board_name = "NUCLEO_F429ZI"

# get the input argument
if len(sys.argv) != 2:
    print 'usage : build.py <BOARD> \ne.g build.py ' + board_name +'\nYou must specify which board to target'
    sys.exit(1)
else:
    board_name = sys.argv[1]

# mbed configuration
call("mbed config root .", shell=True)
call("mbed toolchain GCC_ARM", shell=True)
call("mbed target " + board_name, shell=True)
#call("mbed deploy", shell=True)

# make dirs
if not os.path.exists("./source"):
    os.makedirs("./source")

if not os.path.exists("./js"):
    os.makedirs("./js")

# generate target.js
target_board = subprocess.check_output(['mbed', 'target']).split( )

if(len(target_board) != 2):
    print 'Error generating target!'
    sys.exit(1)
with open("js/target.js", "w") as text_file:
    text_file.write("var TARGET = '%s';" % target_board[1])

# generate pins.js
call("python tools/generate_pins.py " + board_name, shell=True)
call("python ../../tools/js2c.py --dest ./source --js-source js --ignore pins.js", shell=True)


# compile using mbed cli
call("mbed compile -j0 --source . --source ../../ -D \"CONFIG_MEM_HEAP_AREA_SIZE=(1024*16)\" -t GCC_ARM", shell=True)


