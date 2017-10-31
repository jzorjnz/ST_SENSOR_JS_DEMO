
var timeOut = 1000;
var timeStatus = timeOut/10;

var led1 = null;

//led2.write(0);

var i2c = null;
var spi = null;
var hts221 = null;
var lps22hb = null;
var lsm6dsl = null;
var lsm303agr = null;
var acc = null;
var gyr = null;
var acc2 = null;
var mag2 = null;

/*
if(window.TARGET_SENSOR_TILE !== undefined){
    print("TARGET_SENSOR_TILE exists!");
}
else{
    print("TARGET_SENSOR_TILE does not exist!");
}
*/

//print ("TARGET = " + TARGET);
/* 
if(TARGET == "NUCLEO_F429ZI"){
}
else if (TARGET == "NUCLEO_L476RG"){
    spi = SPI(PB_15, NC, PB_13);
    led1 = DigitalOut(0x6C);
    //spi = SPI(31, 4294967295, 29);
}
*/


//var spi = SPI(PB_15, NC, PB_13);
//var spi = SPI(31, 4294967295, 29);
//var TARGET = "NUCLEO";

var count = 0;

var iv = setInterval(function() {
    
    if(count < 2){
        print(".");
        count = count + 1;
    }
    else if(count == 2){
        count++;
        print ("TARGET = " + TARGET);
        if(TARGET == "NUCLEO_F429ZI"){
            i2c = DevI2C(D14, D15);
            led1 = DigitalOut(LED1);
            print("Loading HTS221 sensor...");
            hts221 = HTS221_JS();
            hts221.init_i2c(i2c);
            print("Loading complete.");
            print("Loading LPS22HB sensor...");
            lps22hb = LPS22HB_JS();
            lps22hb.init_i2c(i2c);
            print("Loading complete.");
            print("Loading LSM6DSL sensor...");
            lsm6dsl = LSM6DSL_JS();
            lsm6dsl.init_i2c(i2c);
            print("Loading complete.");
            print("Loading LSM303AGR sensor...");
            lsm303agr = LSM303AGR_JS();
            lsm303agr.init_acc_i2c(i2c);
            lsm303agr.init_mag_i2c(i2c);
            print("Loading complete.");
        }
        else if (TARGET == "NUCLEO_L476RG"){
            spi = SPI(PB_15, NC, PB_13);
            led1 = DigitalOut(0x6C);
            print("Loading LPS22HB sensor...");
            lps22hb = LPS22HB_JS();
            lps22hb.init_spi(spi, PA_3, NC, 3);
            print("Loading complete.");
            print("Loading LSM6DSL sensor...");
            lsm6dsl = LSM6DSL_JS();
            lsm6dsl.init_spi(spi, PB_12, NC, PA_2, 3);
            print("Loading complete.");
            print("Loading LSM303AGR sensor...");
            lsm303agr = LSM303AGR_JS();
            lsm303agr.init_acc_spi(spi, PC_4);
            lsm303agr.init_mag_spi(spi, PB_1);
            print("Loading complete.");
        }

        led1.write(0);

        

        /*
        
        print("Loading LSM303AGR sensor...");
        lsm303agr = LSM303AGR_JS(i2c);
        print("Loading complete.");
        */
        //hts221.led_on(led2);
    }
    else{    
        led1.write(led1.read()? 0: 1);
        
        print("");
        
        if(TARGET == "NUCLEO_F429ZI"){
            print("HTS221: [Temperature] " + hts221.get_temperature() + " C,   [Humidity] " + hts221.get_humidity() + "%");
        }
        
        print("LPS22HB: [Temperature] " + lps22hb.get_temperature() + " C,   [Pressure] " + lps22hb.get_pressure() + " mbar");
        
        acc = JSON.parse(lsm6dsl.get_accelerometer_axes());
        gyr = JSON.parse(lsm6dsl.get_gyroscope_axes());
    
        print("LSM6DSL: [Gyroscope]: " + gyr.x + ", " + gyr.y + ", " + gyr.z + 
        "   [Accelerometer]: " + acc.x + ", " + acc.y + ", " + acc.z);
        
        
        
        
        print("Printing LSM303AGR");
        acc2 = JSON.parse(lsm303agr.get_accelerometer_axes());
        mag2 = JSON.parse(lsm303agr.get_magnetometer_axes());
        print("LSM303AGR: [Magnetometer]: " + mag2.x + ", " + mag2.y + ", " + mag2.z + 
        "   [Accelerometer]: " + acc2.x + ", " + acc2.y + ", " + acc2.z);
        
        print("");
        setTimeout(function(){ led1.write(led1.read()? 0: 1) }, timeStatus);
        
        
    }
}, timeOut);



// Call this function to clear the interval started above
//clearInterval(iv);

print("main.js has finished executing.");
