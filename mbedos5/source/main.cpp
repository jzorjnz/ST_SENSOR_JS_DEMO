/* Copyright (c) 2016 ARM Limited. All rights reserved. */

#include "mbed.h"

// Provides jsmbed_js_launch()
#include "jerryscript-mbed-launcher/launcher.h"

// Provides JSMBED_USE_WRAPPER()
#include "jerryscript-mbed-library-registry/registry.h"

// Provides the base wrapper registration symbol that JSMBED_USE_WRAPPER uses.
// This means all of the base handlers will be registered.
#include "jerryscript-mbed-drivers/lib_drivers.h"

#ifdef JSMBED_USE_RAW_SERIAL
mbed::RawSerial pc(USBTX, USBRX);
#endif




#include "jerryscript-mbed-event-loop/EventLoop.h"

#include "Callback.h"
#include "Serial.h"
#include "rtos/Thread.h"

#include "cmsis_os.h"

#include "HTS221_JS-js.h"

#include "LPS22HB_JS-js.h"

#include "LSM6DSL_JS-js.h"


using mbed::js::EventLoop;
using mbed::Callback;

void js_main() {
  JERRY_USE_MBED_LIBRARY(base);

  JERRY_USE_MBED_LIBRARY(HTS221_JS_library);
  
  JERRY_USE_MBED_LIBRARY(LPS22HB_JS_library);
  
  JERRY_USE_MBED_LIBRARY(LSM6DSL_JS_library);
  
  jsmbed_js_launch();
}

rtos::Thread jsThread(osPriorityNormal, 8192);

int main() {
#ifndef JSMBED_USE_RAW_SERIAL
  mbed::Serial pc(USBTX, USBRX);
#endif
  pc.baud(115200);

  int code = jsThread.start(js_main);
  return code;
}
