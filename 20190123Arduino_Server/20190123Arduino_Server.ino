//--------------------------------------------------------------
//
//                   ARDUINO SERVER
//
//
// Arduino ESP8266 sketch demonstrating methods of displaying and modifying data
// on a web page served by an Arduino. This sketch was built and tested on
// an Adafruit Feather HUZZAH device.
//
// Connect to wifi SSID "Arduino_Server", then load 192.168.4.1 in browser.
// 
// You may need to add a library to your IDE to see the ESP8266 device in your list.
// Please search on "<your ESP8266 device> setup".
//
//---------------------------------------------------------------

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//---------------------------------------------------------------
//                     HTML SCRIPT
//---------------------------------------------------------------

//HTML webpage contents are loaded in a char[] variable and stored in program memory

const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>ESP8266 Arduino_Server</title>
<style type="text/css">

body {
  background-color: darkgrey;
  } 
  
p, h1, h2 {
  text-align: center;
  color: white;
  } 

table {
  background-color: grey;
  text-align: center;
  color: white;
  margin-top: 60px;
  margin-bottom: 60px;
  margin-right: 80px;
  margin-left: 80px;
  padding-top: 10px;
  padding-right: 30px;
  padding-bottom: 50px;
  padding-left: 30px;
}

</style> 

<center>
<h1>SSID: Arduino_Server<br>
IP Address: 192.168.4.1</h1><p>

<table width=60%>

<tr><td colspan=2 align="center"><h1>Pin Output Control</h1</td></tr>

<tr><td align="center">
<form action="/LED2" method="POST"><input type="submit" id="mybutton" value="Blue LED"></form>
</td>
<td align="center">
<form action="/LED0" method="POST"><input type="submit" id="mybutton" value="Red LED"></form>
</td></tr>

<tr><td align="center">
Toggle Blue LED</td>
<td colspan=2>Toggle Red LED</td></tr>
</table>

<table width=60%>

<tr><td colspan=2 align="center"><h1>System Reports</h1</td></tr>
<h2>

<tr><td align="right" width=60%>
ADC Value is : </td>
<td id="ADCValue" align="left" width=40%>0</td></tr>

<tr><td align="right">
Wifi Networks Detected : </td>
<td id="wifiNetworks" align="left">0</td></tr>

<tr><td align="right">
Connected Wifi Stations: </td>
<td id="wifiStations" align="left">0</td></tr>

<tr><td align="right">
Free Heap Size : </td>
<td id="freeHeap" align="left">0</td></tr>

<tr><td align="right">
Flash Chip Size : </td>
<td id="flashChip" align="left">0</td></tr>

<tr><td align="right">
Flash Chip Speed (Hz) : </td>
<td id="chipSpeed" align="left">0</td></tr>

<tr><td align="right">
Time Since Restart (ms): </td>
<td id="currentMillis" align="left">0</td></tr>
</table>

<table width=60%>
<tr><td colspan=6 align="center"><h1>Variable Assignment</h1</td></tr>
<tr><td align="right" colspan=3>
<h2>Value of Variable: </td>
<td id="testValue" align="left" colspan=3>0</h2></td></tr>
<tr colspan=6><td><p></td></tr>
<tr><td align="center">
<form action="/add100Test" method="POST"><input type="submit" id="mybutton" value="Add 100"></form>
</td><td align="center">
<form action="/add10Test" method="POST"><input type="submit" id="mybutton" value="Add 10"></form>
</td><td align="center">
<form action="/add1Test" method="POST"><input type="submit" id="mybutton" value="Add 1"></form>
</td><td align="center">
<form action="/sub1Test" method="POST"><input type="submit" id="mybutton" value="Subtract 1"></form>
</td><td align="center">
<form action="/sub10Test" method="POST"><input type="submit" id="mybutton" value="Subtract 10"></form>
</td><td align="center">
<form action="/sub100Test" method="POST"><input type="submit" id="mybutton" value="Subtract 100"></form>
</td></tr>
<tr colspan=6><td><p></td></tr>
<tr><td align="center"colspan=6>
<form action="/enterTestValue">
Enter Variable Value: <br>
<input type="text" name="TestValue" >
<input type="submit" value="Submit">
</form>
</td></tr>
</table>

</h2>
<table width=60%>
<tr>
<td colspan=8 align="center"><h1>Operating Time</h1</td></tr>
<tr>
<td>Days</td><td>:</td>
<td>Hours</td><td>:</td>
<td>Minutes</td><td>:</td>
<td>Seconds</td></tr> 
<tr>
<td align="center" id="days">0</</td><td align="center">:</td>
<td align="center" id="hours">0</td><td align="center">:</td>
<td align="center" id="minutes">0</td><td align="center">:</td>
<td align="center" id="seconds">0</td></tr>
</table>

<p>
<h2>ESP8266 Web Server
<br>
20190123Arduino_Server.ino
</center>

<script>

function loadDoc(url, cFunction) {
  var xhttp;
  xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      cFunction(this);
    }
  };
  xhttp.open("GET", url, true);
  xhttp.send();
}

function callTest(xhttp) {
document.getElementById("testValue").innerHTML =
      xhttp.responseText;
}

function callADC(xhttp) {
document.getElementById("ADCValue").innerHTML =
      xhttp.responseText;
}

function callHeap(xhttp) {
document.getElementById("freeHeap").innerHTML =
      xhttp.responseText;
}

function callWifiStations(xhttp) {
document.getElementById("wifiStations").innerHTML =
      xhttp.responseText;
}

function callWifiNetworks(xhttp) {
document.getElementById("wifiNetworks").innerHTML =
      xhttp.responseText;
}

function callFlashChip(xhttp) {
document.getElementById("flashChip").innerHTML =
      xhttp.responseText;
}

function callChipSpeed(xhttp) {
document.getElementById("chipSpeed").innerHTML =
      xhttp.responseText;
}

function callCurrentMillis(xhttp) {
document.getElementById("currentMillis").innerHTML =
      xhttp.responseText;
}

function callDays(xhttp) {
document.getElementById("days").innerHTML =
      xhttp.responseText;
}

function callHours(xhttp) {
document.getElementById("hours").innerHTML =
      xhttp.responseText;
}

function callMinutes(xhttp) {
document.getElementById("minutes").innerHTML =
      xhttp.responseText;
}

function callSeconds(xhttp) {
document.getElementById("seconds").innerHTML =
      xhttp.responseText;
}

setInterval(function() {
  // Call a function repetatively with 2 Second interval
loadDoc('readADC', callADC);
loadDoc('readHeap', callHeap);
loadDoc('readWifiStations', callWifiStations);
loadDoc('readWifiNetworks', callWifiNetworks);
loadDoc('readFlashChip', callFlashChip);
loadDoc('readChipSpeed', callChipSpeed);
loadDoc('readMillis', callCurrentMillis);
loadDoc('readDays', callDays);
loadDoc('readHours', callHours);
loadDoc('readMinutes', callMinutes);
loadDoc('readSeconds', callSeconds);
loadDoc('readTest', callTest);

}, 1000); //2000mSeconds update rate

</script>

</body>
</html>
)=====";

//---------------------------------------------------------------
//        END HTML ARRAY, BEGIN INITIAL SKETCH
//---------------------------------------------------------------

// Set global variable for Variable Assignment section 
int test = 0;  

//SSID and Password to be used for the Arduino server
const char* ssid = "Arduino_Server";
const char* password = "12345678";
// Note that the password is disabled, to add one, see WiFi.softAP(ssid) function below
// See line 441

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//---------------------------------------------------------------
//                   HANDLE* FUNCTIONS
//---------------------------------------------------------------

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleAdd5Test() {   
  test = test + 5;      
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleAdd1Test() {              
  test = test + 1;     
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleAdd10Test() {             
  test = test + 10;     
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleAdd100Test() {            
  test = test + 100;     
  server.sendHeader("Location","/");  
  server.send(303);                   
}
void handleSub1Test() {               
  test = test - 1;      
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleSub10Test() {             
  test = test - 10;     
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleSub100Test() {            
  test = test - 100;     
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleLED0() {                  
  digitalWrite(0,!digitalRead(0));   
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleLED2() {                  
  digitalWrite(2,!digitalRead(2));   
  server.sendHeader("Location","/"); 
  server.send(303);                  
}

void handleSeconds() {
 unsigned long t = millis();
 int d = t / 86400000;
 t = t - (d * 86400000);
 int h = t / 3600000;
 t = t - (h * 3600000);
 int m = t / 60000;
 t = t - (m * 60000);
 int s = t / 1000;   
 String seconds = String(s);
 server.send(200, "text/plain", seconds); 
}

void handleMinutes() {
 unsigned long t = millis();
 int d = t / 86400000;
 t = t - (d * 86400000);
 int h = t / 3600000;
 t = t - (h * 3600000);
 int m = t / 60000;
 String minutes = String(m);
 server.send(200, "text/plain", minutes); 
}

void handleHours() {
 unsigned long t = millis();
 int d = t / 86400000;
 t = t - (d * 86400000);
 int h = t / 3600000;
 String hours = String(h);
 server.send(200, "text/plain", hours); 
}

void handleDays() {
 unsigned long t = millis();
 int d = t / 86400000;
 String days = String(d);
 server.send(200, "text/plain", days); 
}

void handleMillis() {
 unsigned long t = millis();
 String currentMillis = String(t);
 server.send(200, "text/plain", currentMillis); 
}

void handleWifiStations() {
 int t = WiFi.softAPgetStationNum();
 String wifiStations = String(t);
 server.send(200, "text/plain", wifiStations); 
}

void handleWifiNetworks() {
 int t = WiFi.scanNetworks();
 String wifiNetworks = String(t);
 server.send(200, "text/plain", wifiNetworks); 
}

void handleChipSpeed() {
 int t = ESP.getFlashChipSpeed();
 String chipSpeed = String(t);
 server.send(200, "text/plain", chipSpeed); 
}

void handleFlashChip() {
 int t = ESP.getFlashChipSize();
 String flashChip = String(t);
 server.send(200, "text/plain", flashChip); 
}

void handleHeap() {
 int t = ESP.getFreeHeap();
 String freeHeap = String(t);
 server.send(200, "text/plain", freeHeap); 
}

void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 server.send(200, "text/plain", adcValue); //Send ADC value only to client ajax request
}

void handleTest() {
 int a = test;
 // test++;
 String testValue = String(a);
 server.send(200, "text/plain", testValue); //Send ADC value only to client ajax request
}

void handleenterTestValue() {
  String value = server.arg("TestValue");
   test = value.toInt();
   server.sendHeader("Location","/"); 
   server.send(303); 
} 

//--------------------------------------------------------------
//                  SETUP
//--------------------------------------------------------------

void setup(void){
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);   // You may password protect the access point by
  // replacing this line with: 
  // WiFi.softAP(ssid,password);
  //The password is set on line 268.
  // According to documentation, the following can be set:   WiFi.softAP(ssid, passphrase, channel, ssid_hidden, max_connection)  

  Serial.println("");

  pinMode(0,OUTPUT); 
  pinMode(2,OUTPUT);

//----------------------------------------------------------------
//                  SERVER.ON()
//----------------------------------------------------------------
  
  server.on("/", handleRoot);  
  server.on("/readADC", handleADC);
  server.on("/readHeap", handleHeap);
  server.on("/readFlashChip", handleFlashChip);
  server.on("/readChipSpeed", handleChipSpeed);
  server.on("/readWifiStations", handleWifiStations);
  server.on("/readWifiNetworks", handleWifiNetworks);
  server.on("/readMillis", handleMillis);
  server.on("/readDays", handleDays);
  server.on("/readHours", handleHours);
  server.on("/readMinutes", handleMinutes);
  server.on("/readSeconds", handleSeconds);
  server.on("/LED2", HTTP_POST, handleLED2); 
  server.on("/LED0", HTTP_POST, handleLED0);  
  server.on("/readTest", handleTest);
  server.on("/add5Test", HTTP_POST, handleAdd5Test);  
  server.on("/add1Test", HTTP_POST, handleAdd1Test);  
  server.on("/add10Test", HTTP_POST, handleAdd10Test);  
  server.on("/add100Test", HTTP_POST, handleAdd100Test);  
  server.on("/sub1Test", HTTP_POST, handleSub1Test);  
  server.on("/sub10Test", HTTP_POST, handleSub10Test);  
  server.on("/sub100Test", HTTP_POST, handleSub100Test);  
  server.on("/enterTestValue", handleenterTestValue);  
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("Device IP: ");
  Serial.println(myIP);
}
//--------------------------------------------------------------
//                     LOOP
//--------------------------------------------------------------

void loop(void){
  server.handleClient();          //Handle client requests
}
