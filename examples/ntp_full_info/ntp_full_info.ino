/*
 * NTP Client example
 * Retreving Year, Month, Day, Day of the week, Day of the year, Day of te month
 *           Formatd date string YMD DMY MDY, Formatted Time string
 *           Hour, Minute, seconds
 * xx-xx-2020 Johan Nijtmans
 * 
 */

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const char *ssid     = "<SSID>";      // Set your router SSID
const char *password = "<PASSWORD>";  // Set your router password

char monthOfTheYear[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(74880);
  delay(100);
  Serial.println("\nNTP Example");
  Serial.print("Connecting to network");
  WiFi.begin(ssid, password);
  /* wait for WiFi connect */
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nConnected to ");
  Serial.prntln(ssid);
  
  timeClient.begin();
}

void loop() {
  timeClient.update();
  Serial.print("Epoch time in sec: ");
  Serial.println(timeClient.getEpochTime());
  
  Serial.print("Curent Epoch days: ");
  Serial.println(timeClient.getEpochDays());
  
  Serial.print("Day of the Year: ");
  Serial.println(timeClient.getDayOTY());
  
  Serial.print("Month: ");
  Serial.print(timeClient.getMonth());
  Serial.print(" = ");
  Serial.println(monthOfTheYear[timeClient.getMonth()-1]); //Library returns human month number January = 1 array starts at 0
  
  Serial.print("Day of the Month: ");
  Serial.println(timeClient.getDayOTM());
  
  Serial.print("Formatted date YYYY-MM-DD: " );
  Serial.println(timeClient.getFormattedDateYMD());
  
  Serial.print("Formatted date DD/MM/YYYY: " );
  Serial.println(timeClient.getFormattedDateDMY());

  Serial.print("Formatted date MM/DD/YYYY: " );
  Serial.println(timeClient.getFormattedDateMDY());

  Serial.print("Day Of the week: ");
  Serial.print(timeClient.getDayOTW());
  Serial.print(" = ");
  Serial.println(daysOfTheWeek[timeClient.getDayOTW()]);
  
  Serial.print("Hours: ");
  Serial.println(timeClient.getHours());
  
  Serial.print("Minutes: ");
  Serial.println(timeClient.getMinutes());
  
  Serial.print("seconds: ");
  Serial.println(timeClient.getSeconds());
  
  Serial.print("Formated time hr:min:sec : ");
  Serial.println(timeClient.getFormattedTime());
  
  delay(1000);
}
