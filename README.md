# IoT-recording-light-esp8266

This device can be used to alert other people in your house that you are in an online meeting or video/sound recording session, to avoid disturbance. When the light is active, you can control it wirelessly from a webpage with buttons. The webpage also displays the battery voltage. 

The microcontroller (Wemos D1 mini) can be powered with a micro USB cable, however, there is also the option to use two AA batteries instead. The latter option is convenient if the device is placed far away from a USB socket, but it also limits the time that the MCU can run. Since the light is controlled via a web server, the MCU has to be active constantly while we want to use it. You could choose to manually turn it on and off whenever you wanted to use it, but why not do this automatically?

Once the device is turned on, the webserver will be active for 11 hours after which it enters deep-sleep for 13 hours, to save power. While the webserver is running, you can connect to it in your web browser and turn the light on and off. During deep sleep, the webserver is not active and therefore the light cannot be turned on. When the 13 hours of deep-sleep have passed, the device and webserver become active again. The specific amount of hours can be changed in the code. I chose 11 and 13 hours specifically because if you turn the device on at 08:00, it will be active until 19:00. Most people have to sleep and eat at some point during the day, so the webserver doesn't need to be active 24 hours a day. If the device is sleeping, but you need to use the light, you can simply turn it off and on, or just press the reset button to reset the timer. The reset button is also useful if you want to change the schedule (e.g. if you want to change wake-time from 8:00 to 11:00, just press the reset button at 11:00). 

After testing the battery life, I can conclude that two AA-batteries will last for about a week, if the device is active for 8 hours once a day.


## Hardware

I used a Wemos D1 mini for this project. The board uses an ESP8266 chip and is more compact than a nodemcu board. To enable deep sleep on this board, you need to connect D0 to RST. I used a red super bright LED which was powered by the battery. The LED was controlled by the microcontroller using a transistor. 

### Pictures:

<img src="https://raw.githubusercontent.com/jakobrbr/IoT-recording-light-esp8266/main/Pictures/RecLight1.jpg" alt="alt text" width="450" height="600">
<img src="https://raw.githubusercontent.com/jakobrbr/IoT-recording-light-esp8266/main/Pictures/RecLight2.jpg" alt="alt text" width="450" height="600">
<img src="https://raw.githubusercontent.com/jakobrbr/IoT-recording-light-esp8266/main/Pictures/RecLight3.jpg" alt="alt text" width="450" height="600">
<img src="https://raw.githubusercontent.com/jakobrbr/IoT-recording-light-esp8266/main/Pictures/RecLight4.jpg" alt="alt text" width="450" height="600">

### 3D print

All plastic parts of this project apart from the translucent "lid" were 3D printed. The translucent lid originally comes from a plastic watch travel case. The 3D-printed parts have been glued together.

*stl files*

## Software

The arduino code was inspired by multiple online guides on how to make a webpage controlled LED with an ESP8266. The deep sleep code was taken from this website: https://panther.kapsi.fi/posts/2019-05-14_esp8266_deep_sleep

