# ST_SENSOR_JS_DEMO
Demo for accessing ST sensors using Javascript on Mbed OS.

## Installation
* Before you begin, first follow this tutorial to have a pre built Mbed OS project with Jerryscript here: https://github.com/ARMmbed/mbed-js-example

* After you have built the project, you should have a binary for your board. If not, resolve the errors to continue. If you have errors related to generation of pins, checkout the known issues below.

* Now, clone this repository and copy to the following directory of the mbed-js-example project:
```
mbed-js-example/build/jerryscript/targets/
```
Make sure to replace existing files in mbedos5 directory.

## Build
* When you are building the project for the first time, run this command:
```
cd mbed-js-example/build/jerryscript/targets/mbedos5
python ./build_all.py <BOARD>
```
This makes sure that all the required libraries are downloaded.

* If building next time, run this command:
```
cd mbed-js-example/build/jerryscript/targets/mbedos5
python ./build.py <BOARD>
```

## Development
Your Mbed OS project resides in mbedos5 directory, put js files in mbedos5/js directory. Building will take care of everything.

## Known issues
### Pin generation error
For some boards, pin generation is failing in Jerryscript. For the time being, you can skip some pin expressions in configuration to build for most boards by following these steps:

Open mbed-js-example/jerryscript/targets/mbedos5/tools/generate_pins.py

Put this line in try statement:
```
        try:
            pins[pin.name] = evaluator.eval(expr.strip())
        except:
            print("[Warning] Skipping pin name: " + expr.strip())
```

After doing this, do installation again and then try building.
