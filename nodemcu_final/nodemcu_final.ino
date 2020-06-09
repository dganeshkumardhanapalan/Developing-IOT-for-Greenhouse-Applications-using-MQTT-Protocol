#include <ESP8266WiFi.h>
#include <WifiUDP.h>
#include <String.h>
#include <Wire.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <time.h>
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "ca.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)
#define CS_PIN  D8
// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char *ssid =  "GARTH 2.4";     // replace with your wifi ssid and wpa2 key
const char *pass =  "eyjolfso";
const char *mqtt_server="m16.cloudmqtt.com";
const char *mqtt_user= "yrzmecpp";
const char *mqtt_pass="5UbSz2Rz4gVk";
const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "vE37D6294FF6DD46"; //device ID from Pushingbox 
String deviceId = "vE66789A6CEFE8C6";//for notification
const char* logServer = "api.pushingbox.com";
String date;
String t;
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
const char * ampm[] = {"AM", "PM"} ;
int autos=0;
//THINGSPEAK ACTIVITY STARTS HERE
String apiKey = "7690LDRO7VXXTLEC";// THINGSPEAK API KEY
const char* server = "api.thingspeak.com";
int data1, data2, data3, data4, data6, data7, data8;
double data5=0.00;

char message_buff[100];

int table[]={0,0,0,0,0,0};
int q=0;
int w=0;
int e=0;
double r=0.00;
int tt=0;
int y=0;
int u=0;
int k=0;
int l=0;
int a=0;
int b=0;
#define soilmoisturepin A0 
long c;
WiFiClient espClient;
PubSubClient client(espClient);
long lastmsg=0;
char msg[50];
int value=0;

void setupwifi(){
  delay(100);
   Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      randomSeed(micros());
      Serial.println("IP ADDRESS: ");
      Serial.println(WiFi.localIP());

} 

void reconnect(){

//Loop until we're connected again
while (!client.connected()) {
  Serial.print("TRYING FOR MQTT CONNECTION...");
  //CREATING  A RANDOM CLIENT ID
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff),HEX);
  //ATTEMPTING TO CONNECT
  if (client.connect(clientId.c_str(), mqtt_user,mqtt_pass)){
    Serial.println("SUCCESSFULLY CONNECTED");
    //PUBLISHING AN ANNOUNCEMENT AFTER BEING SUCCESSFULLY CONNECTED...
    client.publish("outTopic", "hello world");
    //... AND RESUBSCRBING
    client.subscribe("inTopic");
  }
  else{
    Serial.print("failed,rc=");
    Serial.print(client.state());
    Serial.println(" TRY AGAIN IN 5 SECS");
    // WAITING FOR 5 SECONDS BEFORE TRYING AGAIN
    delay(5000);
  }
  }
}

void callback(char *led_control, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(led_control);
  Serial.println("] ");
  int i;
  for (i = 0; i <length; i++)
  {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  String msgString = String(message_buff);
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
  if (strcmp(led_control, "command") == 0)
  { 
    if (msgString == "on")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
autos=1;

    }
    if (msgString == "off")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
autos=0;
    }
   if (msgString == "hon")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
   if (msgString == "hoff")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
   if (msgString == "lon")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
   if (msgString == "loff")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
   if (msgString == "mon")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
   if (msgString == "moff")
    {
      
Serial.println("THE MESSAGE FROM THE CLOUD IS...................");
Serial.println(msgString);
    }
  }
  }


  

void setup() 
{
       Serial.begin(9600);
       delay(10);
       timeClient.begin();   // Start the NTP UDP client
  Serial.setDebugOutput(true);
       Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */       
       setupwifi();
       client.setServer(mqtt_server,13330);
        client.setCallback(callback);
       reconnect();
       
// Wire.onRequest(requestEvent); /* register request event */
}
 



void loop() {


 client.setCallback(callback);


  
 // timestamp operation starts here
 if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
  {   
    date = "";  // clear the variables
    t = "";
    
    // update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    unsigned long epochTime =  timeClient.getEpochTime();

    // convert received time stamp to time_t object
    time_t local, utc;
    utc = epochTime;

    // Then convert the UTC UNIX timestamp to local time
    TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -300};  //UTC - 5 hours - change this as needed
    TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -360};   //UTC - 6 hours - change this as needed
    Timezone usEastern(usEDT, usEST);
    local = usEastern.toLocal(utc);

    // now format the Time variables into strings with proper names for month, day etc
    date += days[weekday(local)-1];
    date += ", ";
    date += months[month(local)-1];
    date += " ";
    date += day(local);
    date += ", ";
    date += year(local);
    date +="-";
    date += hourFormat12(local);
    date += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      date += "0";
   date += minute(local);
    date += " ";
    date += ampm[isPM(local)];
    // format the time to 12-hour format with AM/PM and no seconds
    t += hourFormat12(local);
    t += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      t += "0";
    t += minute(local);
    t += " ";
    t += ampm[isPM(local)];

    // Display the date and time
    Serial.println("");
    Serial.print("Local date: ");
    Serial.print(date);
    Serial.println("");
    Serial.print("Local time: ");
    Serial.print(t);
  //table1[0]=date;
//  table[1]=t;
  }
  else // attempt to connect to wifi again if disconnected
  {
  
    WiFi.begin(ssid, pass);
   
    delay(1000);
  }
    
  delay(10000);    //Send a request to update every 10 sec (= 10,000 ms)
 
 //normal operation starts here
 
 Wire.beginTransmission(8); /* begin with device address 8 */

 Wire.write("hello");
  

 
 /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */     //changed for test purposes
if(!client.connected()){
reconnect();
}
Wire.requestFrom(8, 6);
while(Wire.available()){
for(int i=0;i<6;i++)//organizes the data from the slave in the table
{
int c = Wire.read(); // receive a byte as character
table[i]=c;
 Serial.print(table[i]);
}
}
//displays the data
 Serial.print('\n');
   Serial.print(table[0]);
    Serial.print('\t');
   Serial.print(table[1]);
    Serial.print('\t');
   Serial.print(table[2]);
   Serial.print('\n');
   Serial.print(table[3]);
   Serial.print('\n');
   Serial.print(table[4]);
   Serial.print('\n');
   Serial.print(table[5]);
   Serial.print('\n');
  // Serial.print(table[6]);
  // Serial.print('\n');
  // Serial.print(table[7]);
  // Serial.print('\n');
  // Serial.print(table[8]);
  // Serial.print('\n');
q=table[0];//light intensity
w=table[1];//soilmoisture
e=table[2];//soil temperature
a=table[3];//dhthum
b=table[4];//dhttemp
r=table[5];//phvalue
data1=b;
data2=a;
data3=q;
data4=w;
data5=r;
data6=e;
//tt=table[6];
//y=table[7];//humidifier actuator status
//u=table[8];//cooler actuator status
delay (5000);   

String hh=String(q);
String gg=String(w);
String jj=String(e);
int numq=q;
int numw=w;
int nume=e;
int numa=a;
int numb=b;
//int numt=tt;
int numd=0;
double numr=r;
//int numy=y;
//int numu=u;
char cstr[16];
char cssttr[16];
char cssstttr[16];
char astr[16];
char bstr[16];
char rstr[16];
/*if (numa==0)
{
  client.publish("Light State","OFF");
delay(10000);
}
else if (numa==1)
{
  client.publish("Light State","ON");
  sendNotification("The full spectrum light is switched ON!!!!!!!");
delay(10000);
}
if (numb==0)
{
  client.publish("Pump State","OFF");
delay(10000);
}
else if (numb==1)
{
  client.publish("Pump State","ON");
  sendNotification("The Pump is switched ON!!!!!!! for irrigation");
delay(10000);
}*/

//motor and light state

 if(autos==1)
 {
 if (numq < 20)
 {
  digitalWrite(8,LOW); // Turns ON Relays 1 for water pump
  Serial.println("Pump ON");
  k=1;
   client.publish("Pump State","ON");
  sendNotification("The Pump is switched ON!!!!!!! for irrigation");
  delay(10000);
  }
 else if(numq>20 && numq<80)
 {
  digitalWrite(8,LOW); // Turns ON Relays 1 for water pump
  Serial.println("Pump ON"); 
  k=1;
   client.publish("Pump State","ON");
  sendNotification("The Pump is switched ON!!!!!!! for irrigation");
  delay(15000);
 }
else if(numq>80)
 {
  digitalWrite(8,HIGH); // Turns OFF Relays 1 for water pump
  client.publish("Pump State","OFF"); 
  Serial.println("Pump OFF"); 
  k=0;
  delay(15000);
 }

if(numq<20)
{   digitalWrite(9, LOW);    // turn on relay 1 for light
    Serial.println("Light ON");
    sendNotification("The full spectrum light is switched ON!!!!!!!");
    client.publish("Light State","ON");
    delay (10000);
    l=1;
    
}
else if(numq>20)
{
   digitalWrite(9, HIGH);    // turn of relay 1 for light
     Serial.println("Light OFF");
      client.publish("Light State","OFF");
    sendNotification("The full spectrum light is switched ON!!!!!!!");
    delay (10000);
    l=0;
}
 }
itoa(numw,cstr,10);
itoa(numq,cssttr,10);
itoa(nume,cssstttr,10);
itoa(numa,astr,10);
itoa(numb,bstr,10);
itoa(numr,rstr,10);
client.publish("Soil Moisture",cstr);
delay(10000);
client.publish("Light Intensity",cssttr);
delay(10000);
client.publish("Temperature(soil)",cssstttr);
delay(10000);
client.publish("Temperature(air)",bstr);
delay(10000);
client.publish("Humidity",astr);
delay(10000);
client.publish("PH Value",rstr);
delay(10000);
long HumidityData= numa;
long TemperatureData= nume;
long LightintensityData= numq;
long SoilmoistureData= numw;
double phData= numr;// got to change this
 
 WiFiClient client;  //Instantiate WiFi object

    //Start or API service using our WiFi Client through PushingBox
    if (client.connect(WEBSITE, 80))
      { 
         client.print("GET /pushingbox?devid=" + devid
       + "&HumidityData=" + (String) HumidityData
       + "&TemperatureData="      + (String) TemperatureData
       + "&LightintensityData="     + (String) LightintensityData
       + "&SoilmoistureData="      + (String) SoilmoistureData
       + "&phData="      + (String) phData
         );

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
    if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += date;
    postStr += "&field2=";
    postStr += t;
    postStr += "&field3=";
    postStr += String(data1);
    postStr += "&field4=";
    postStr += String(data2);
    postStr += "&field5=";
    postStr += String(data3);
    postStr += "&field6=";
    postStr += String(data4);
    postStr += "&field7=";
    postStr += String(data5);
    postStr += "&field8=";
    postStr += String(data6);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println(postStr);
  }
  client.stop();
  Serial.println("Waiting...");
  delay(20000);  
}

// for notification
void sendNotification(String message){
   WiFiClient client;

  Serial.println("- connecting to pushing server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    
    String postStr = "devid=";
    postStr += String(deviceId);
    postStr += "&message=";
    postStr += String(message);
    postStr += "\r\n\r\n";
    
    Serial.println("- sending data...");
    
    client.print("POST /pushingbox HTTP/1.1\n");
    client.print("Host: api.pushingbox.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
}
