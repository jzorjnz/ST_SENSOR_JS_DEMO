var led3 = DigitalOut(LED3);

led3.write(1);

var iv = setInterval(function() {
    led3.write(led3.read()? 0: 1);
}, 2000);

print("flash_leds.js has finished executing.");
