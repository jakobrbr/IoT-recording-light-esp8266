/* Jakob Rud Bernhardt, March 2021
 *  Github: https://github.com/jakobrbr/IoT-recording-light-esp8266
 *  WiFi controlled "recording light", uses deep sleep to save power (2xAA battery or micro usb).
 *  - The ESP8266 is active for a specified amount of hours after which it sleeps for
 *    another specified amount of hours, one hour at a time. 
 *  Deep sleep code: https://panther.kapsi.fi/posts/2019-05-14_esp8266_deep_sleep
*/

#include <ESP8266WiFi.h>
#include <TimedAction.h>

// WiFi and deep-sleep settings:
const char *ssid     = "Your WiFi name";
const char *password = "Your WiFi password";
float awakeTime = 3.96E7; // 3.96E7 is 11 hours in ms
int sleepTime = 13; // 13 = 13 hours

int LED = 5;
WiFiServer server(80);
unsigned int raw = 0;
unsigned long counter;
float volt = 0.0;

void goToSleep(uint32_t hours, bool end_of_setup = false) {
  // call this function to enter deep sleep for specified amount of hours
  // the mcu sleeps for one hour at a time
    uint32_t reset_counter = 0;
    bool waking_from_sleep = ESP.getResetReason() == "Deep-Sleep Wake";

    if (!end_of_setup) {
        if (waking_from_sleep) {
            Serial.print("Waking up from deep-sleep via reset pin. Reset counter: ");
            ESP.rtcUserMemoryRead(0, &reset_counter, sizeof(reset_counter));
            reset_counter++;
            ESP.rtcUserMemoryWrite(0, &reset_counter, sizeof(reset_counter));
            Serial.println(String(reset_counter));
        } else {
            Serial.println("Zeroing reset counter.");
            ESP.rtcUserMemoryWrite(0, &reset_counter, sizeof(reset_counter));
            return;
        }
    }

    // With larger values, deep-sleep is unrealiable: it might never wake up and consume a lot of power.
    // Therefore sleep one hour at a time.
    // In reality, the ESP sleeps a bit less than the 60 minutes it is told to.
    if (reset_counter < hours) {
        // If this is the first time going to sleep, do the radio calibration once.
        // Otherwise, disable radio (WiFi).
        RFMode wake_mode = waking_from_sleep ? WAKE_RF_DISABLED : WAKE_RFCAL;
        if (reset_counter + 1 == hours) {
            // Wake up with radio on if the next power cycle finishes sleeping.
            wake_mode = WAKE_NO_RFCAL;
        }
        Serial.println("Going to deep-sleep for 1 hour.");
        // 1: WAKE_RFCAL
        // 2: WAKE_NO_RFCAL
        // 4: WAKE_RF_DISABLED
        Serial.println("Radio mode will be: " + String(wake_mode));
        ESP.deepSleep(3600*1e6, wake_mode);
    }
    reset_counter = 0;
    ESP.rtcUserMemoryWrite(0, &reset_counter, sizeof(reset_counter));
}

void setup()
{
 Serial.begin(115200);
 Serial.setTimeout(2000);

 goToSleep(sleepTime); // check if sleep complete
 
 pinMode(LED, OUTPUT);
 pinMode (A0, INPUT);
 digitalWrite(LED, LOW);
 raw  = analogRead(A0);
 volt = raw/1023.0;
 volt=volt*4.2;

 Serial.print("Connecting to the Network");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(500);
   Serial.print(".");
 }
 Serial.println("WiFi connected");
 server.begin();  // Starts the Server
 Serial.println("Server started");

 Serial.print("IP Address of network: ");
 Serial.println(WiFi.localIP());
 Serial.println("/");
}

void loop()
{
 String v = String(volt);
 WiFiClient client = server.available();
 if (!client)
 {
   counter = millis();
   if (counter > awakeTime) {
     digitalWrite(LED, HIGH);
     delay(1);
     Serial.println("Going to sleep");
     goToSleep(sleepTime, true);
   }
   return;
 }
 
 Serial.println("Waiting for new client");
 while(!client.available())
 {
   delay(1);
 }

 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();

 int value = LOW;
 if(request.indexOf("/LED=ON") != -1)
 {
   digitalWrite(LED, HIGH); // Turn ON LED
   value = HIGH;
 }
 if(request.indexOf("/LED=OFF") != -1)
 {
   digitalWrite(LED, LOW); // Turn OFF LED
   value = LOW;
 }


 client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
 client.println("Content-Type: text/html");
 client.println("");
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");

 client.print("LED: ");

 if(value == HIGH)
 {
   client.print("ON");
 }
 else
 {
   client.print("OFF");
 }
 client.println("<br><br>");
 client.println("<a href=\"/LED=ON\"\"><button>ON</button></a>");
 client.println("<a href=\"/LED=OFF\"\"><button>OFF</button></a><br />");
 client.print("Battery voltage: ");
 client.println(v);
 client.println("</html>");

 delay(1);
 Serial.println("Client disonnected");
 Serial.println("");

}
