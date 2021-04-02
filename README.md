# IoT-recording-light-esp8266

This device can be used to alert other people in your house that you are in an online meeting or video/sound recording session, to avoid disturbance. When the light is active, you can control it wirelessly from a webpage with buttons. The webpage also displays the battery voltage. 

The microcontroller (Wemos D1 mini) can be powered with a micro USB cable, however, there is also the option to use two AA batteries instead. The latter option is convenient if the device is placed far away from a USB socket, but it also limits the time that the MCU can run. Since the light is controlled via a web server, the MCU has to be active constantly while we want to use it. You could choose to manually turn it on and off whenever you wanted to use it, but why not do this automatically?

Once the device is turned on, the webserver will be active for 11 hours after which it enters deep-sleep for 13 hours, to save power. While the webserver is running, you can connect to it in your web browser and turn the light on and off. During deep sleep, the webserver is not active and therefore the light cannot be turned on. When the 13 hours of deep-sleep have passed, the device and webserver become active again. The specific amount of hours can be changed in the code. I chose 11 and 13 hours specifically because if you turn the device on at 08:00, it will be active until 19:00. Most people have to sleep and eat at some point during the day, so the webserver doesn't need to be active 24 hours a day. If the device is sleeping, but you need to use the light, you can simply turn it off and on, or just press the reset button to reset the timer. The reset button is also useful if you want to change the schedule (e.g. if you want to change wake-time from 8:00 to 11:00, just press the reset button at 11:00). 


## Hardware

circuit
buttons
*pictures*

### 3D print

*stl files*

## Software

...
