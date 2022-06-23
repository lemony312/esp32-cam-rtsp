# ESP32 Cam RTSP Streamer

A small example project to get an esp32 cam up and running through rtsp protocal.
This can be directly uploaded to an esp32 cam as is and it should run fine 
make sure to add your `wifikeys.h` into th src folder (described further down)

VLC player is an easy way to view the stream

I was able to achieve around 30fps with FRAMESIZE_VGA (640x480)
You can play around with image quality by adjusting `framesize_t frameSize` variable in the `initCameraConfig` method in `main.cpp`

# Configuration
In the `src/` folder
create a new file named `wifikeys.h`
add these 2 lines to the file

```
const char *ssid =     "MY_WIFI_NETWORK";          // Put the name of your wifi network
const char *password = "MY_PASSWORD";              // Put your PASSWORD here
```


# Uploading to esp32
My project uses PIO and an FTDI programmer
I found my cameras most stable using the 5v pin instead of 3v

Ensure your ftdi programmer is set to 5v mode
Wire up the ftdi to the esp32

![esp32-connections](docs/Esp32%20with%20ftdi.PNG)

ESP32      FTDI
5V     ->   5v (or vcc) pin
GND    ->   GND
U0R    ->   TX
U0T    ->   RX

To Flash new rom onto the esp32, we need to wire the esp32 to itself through 2 pins
GND to 1O0 (single wire that is connected on the same board) - only needed when flashing a new rom

GND -> 1O0 (on esp32 itself)

once all pins are connected,
Connect ftdi programmer to computer, and press the reset button on the esp32 cam

through pio, monitor and upload the program
Once uploaded, disconnect one of the wires that is connected to itself on the esp32 (the GND -> 1O0),
monitor the esp32 from pio and hit the reset button
the url to connect to the camera will be printed to the console

## Connect through vlc
Open vlc player and find "Open Network Stream"
provide the url to your camera
ex: 
rtsp://192.168.1.4:8554/mjpeg/1
(update the url with your cameras ip - this will be printed in the console)

## Debugging (OPTIONAL)
If you run the program and monitor the camera, it might display "could not send udp packet: 12"
From some preliminary google searching, adding a delay after sending the udp packet in the Micro-RTSP library can help mitigate this issue

in `platglue-esp32.h`
find the function `udpsocketsend`

look for the `endpacket` function call
it looks like this in the code
```
if(!sockfd->endPacket())
    printf("error sending udp packet\n");
```
add `delay(1)` after the if statement, NOT inside the if statement - make sure it is outside

it will look like this 
```
if(!sockfd->endPacket())
    printf("error sending udp packet\n");
delay(1);
```

This significantly redueced the number of times I saw the error in the console

## TODOs
 - Implement authorization
 - OTA updates (configure wifi network or framze size)