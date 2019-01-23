The Arduino sketch "Arduino_Server.ino" is a demonstration of methods to update a webpage with data, served from the Arduino ESP8266.  

Installation and Start Up

To use the application, upload the sketch to an ESP8266 Arduino such as an Adafruit Feather HUZZAH device.  After start up, look for a wifi SSID "Arduino_Server" and connect.  No password entry is required.  Go to 192.168.4.1 in a browser, and the main page will be displayed.  There is only one page as part of this sketch. 

Pin Output Control

Two digital pins may be toggled HIGH or LOW by pressing a button on the webpage, as shown by onboard LED display.  The code could be modified to set other pins high or low.  

System Reports

A selection of system data is sent using AJAX/XMLHTTPRequest, which updates the data on the page without refreshing the HTML document.  The data is set to update every second, although due to processing load the refresh rate seems to be every 5 or 6 seconds. 

Variable Assignment

A variable value is displayed, and the user can modify the value by pressing buttons to add or subtract from the variable, or by a text entry box which resets the value to the selected integer value.

Operating Time

The Operating Time shows the Days, Hours Minutes and Seconds since restart of the Arduino.

Program Comments

My intent was to push the limits of the Arduino processor and see how it performed.  If one wishes to use parts of this sketch to control the Arduino, I recommend removing the wifi network scan, as well as any other unneeded functions.

The HTML and Javascript webpage is included in the sketch and is loaded into the device as a character array.  This has the advantage of being easy to edit, but the disadvantage of not being able to include Arduino variable values as part of the HTML text when the page is served.  The HTML and script text could be loaded into a number of character arrays and Arduino values could be inserted between the arrays as the HTML is parsed to the user.

Toggling the LED pin outputs seems to cause some interference when trying to read the pin state.  I tried to report the state of pins 0 and 2, but could not get a consistent result while toggling the LEDs and then looking at the reported pin state.  I removed this functionality from the sketch.

Creating a New Variable, Updating Data Without Refreshing the Webpage

AJAX and XMLHTTPRequest are somewhat complex.  In order to display a new variable, find an existing variable that works the way you want your new variable to work.  For a display similar to the System Report display:

In the HTML section:
Create an HTML element (td, span, h1, etc.) with an id that identifies the variable.  Make sure that the HTML is valid, for example, a <td> must be inside a <table>.

In the script section:
Create a call* function to call the id using the format in the examples. This function is called by the loadDoc() function.

Add a loadDoc() function line with the arguments read* and call*, with the call function being the same as above but without "()".  The read* variable becomes a url as if it were a webpage. The loadDoc() function is inside the setInterval function which runs the loadDoc functions every second or so, as specified in the end of the setInterval function.

In the sketch prior to setup(), create a handle* function using an example similar to the variable you wish to display. The variable must be in string format prior to sending it to through the server. The variable in the handler function must be the same as the id in the HTML element.

At the end of the setup() section, add a server.on line with the "read" variable which matches the loadDoc read variable, and with the name of the handle function without "()".

This completes the coding process to update data without refreshing the entire page.
