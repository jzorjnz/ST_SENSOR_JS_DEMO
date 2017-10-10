import os
from subprocess import call
import sys

board_name = ""

if len(sys.argv) != 2:
    print 'usage : build.py <BOARD> \nYou must specify which baord to target.\nFor example: build_all.py NUCLEO_F429ZI'
    sys.exit(1)
else:
    board_name = sys.argv[1]

if not os.path.exists("./source"):
    os.makedirs("./source")

call("python tools/generate_pins.py " + board_name, shell=True)
call("python ../../tools/js2c.py --dest ./source --js-source js --ignore pins.js", shell=True)

call("mbed config root .", shell=True)
call("mbed toolchain GCC_ARM", shell=True)
call("mbed target " + board_name, shell=True)
call("mbed deploy", shell=True)

call("mbed compile -j0 --source . --source ../../ -D \"CONFIG_MEM_HEAP_AREA_SIZE=(1024*16)\" -t GCC_ARM", shell=True)


