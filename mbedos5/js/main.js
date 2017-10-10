/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var led1 = DigitalOut(LED1);
var led2 = DigitalOut(LED2);

led1.write(1);
led2.write(0);

var i2c = I2C(D14, D15);

var count = 0;
var hts221 = null;
var lps22hb = null;
var lsm6dsl = null;
var acc = null;
var gyr = null;

var iv = setInterval(function() {
    led1.write(led1.read()? 0: 1);
    if(count == 2){
        count++;
        
        print("Loading HTS221 sensor...");
        hts221 = HTS221_JS(i2c);
        print("Loading complete.");
        
        print("Loading LPS22HB sensor...");
        lps22hb = LPS22HB_JS(i2c);
        print("Loading complete.");
        
        print("Loading LSM6DSL sensor...");
        lsm6dsl = LSM6DSL_JS(i2c);
        print("Loading complete.");
        
        hts221.led_on(led2);
    }
    else if(count < 2){
        print(".")
        count = count + 1;
    }
    else{
        print("");
        print("HTS221: [Temperature] " + hts221.get_temperature() + " C,   [Humidity] " + hts221.get_humidity() + "%");
        print("LPS22HB: [Temperature] " + lps22hb.get_temperature() + " C,   [Pressure] " + lps22hb.get_pressure() + " mbar");
        
        acc = JSON.parse(lsm6dsl.get_accelerometer_axes());
        gyr = JSON.parse(lsm6dsl.get_gyroscope_axes());

        print("LSM6DSL: [Gyroscope]: " + gyr.x + ", " + gyr.y + ", " + gyr.z + 
        "   [Accelerometer]: " + acc.x + ", " + acc.y + ", " + acc.z);
        
        print("");
    }
}, 1000);

// Call this function to clear the interval started above
//clearInterval(iv);

print("main.js has finished executing.");
