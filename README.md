## IOT IN GREEN HOUSE USING MQTT PROTOCOL

## Abstract:

There are resources wasted during farming due to over usage without knowing. In this project, resources wasted during the agricultural processes 
are taken into concern using the Internet of Things. Resources such as water and light are used in abundance during the growth of a plant. Various 
sensors are used to minimize resources and maximize agricultural efficiency connected with Arduino UNO. This project concentrates on measuring soil
moisture and providing the required water content using FC28. Measuring the light intensity surrounding the plant and providing the required 
electrical resources. Light intensity is measured using a photo resistor. Low light intensity is detected when the resistance of the photo resistor
is high. Actuators respond to the sensor’s values and are used to on/off the resources. The Arduino is serially connected with node MCU. Using the
node MCU which has Wi-Fi capabilities, all the values generated in the Arduino IDE are stored in the google sheet using push bullet service and are
also stored locally in SD card module. The SD card module is connected with the Arduino UNO. Using the MQTT protocol, these values are displayed
within the android application for the user’s purpose. Users can check the changing sensor values from time to time and can also control the
actuators by themselves. The agricultural environment also depends upon the factors like pH level, temperature, and humidity. In this case, the 
DHT11 sensor is used to measure temperature of the air and humidity. After measuring, to solve the problem of humidity, a humidifier is made from
scratch and controlled by an actuator. The DS18B20 has been used to monitor the temperature of soil. An android application has been developed for
controlling and monitoring the sensor data. The application has features like cloud login, signup that allows a first-time user to register and to
control the actuators. It takes personal information. The major uses of this android application are to manually control the actuators to on/off 
the resources and to monitor the sensors in real-time using cloud mqtt.

