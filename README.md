# ST_SENSOR_JS_DEMO
Demo for accessing ST sensors using Javascript on Mbed OS.

# Installation
Before you begin, first follow this tutorial to have a pre built Mbed OS project with Jerryscript here: https://github.com/ARMmbed/mbed-js-example

After you have build the project, you should have a binary for your board. If not, resolve the errors to continue. 

Now, clone this repository and copy to the following directory of the mbed-js-example project:
```
mbed-js-example/build/jerryscript/targets/
```
Make sure to replace existing files in mbedos5 directory.

# Build
When you are building the project for the first time. Run this command:
```
cd mbed-js-example/build/jerryscript/targets/mbedos5
python ./build_all.py <BOARD>
```
This makes sure that all the required libraries are downloaded.

After that. Run this command:
```
cd mbed-js-example/build/jerryscript/targets/mbedos5
python ./build.py <BOARD>
```

# Development
Your Mbed OS project resides in mbedos5 directory, put js files in mbedos5/js directory. Building will take care of everything.
