#include <Wire.h>
long sensorValuee;// soil moisture sensor variable need to change the name in the end
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SimpleDHT.h>
#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 10;

// used for the ph
const int analogInPin = A3; 
unsigned long int avgValue; 
int buf[10],temp;
double phValue=0.00;

int pin=2;//dht22
SimpleDHT22 dht22;
float humidity=0;;  //Stores humidity value
float temperature=0; //Stores temperature value


#define ONE_WIRE_BUS 7
long sensorValue =0;// reads the value of ldr
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
int c=0;
int d=0;//used for humidifier actuator
int e=0;// used for cooler actuator
int a=0;
int b=0;
 int Celcius=0;
 float Fahrenheit=0;
 long table[]={0,0,0,0,0,0,0,0,0,0};
int aa=0;
int bb=0;
int dhttemp=0;
int dhthum=0;

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */


 Wire.onReceive(receiveEvent); /* register receive event */

 
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);  /* start serial for debug */ 
 sensors.begin(); 
  pinMode(pinCS, OUTPUT);
}

void loop() {
ph();
delay(2000);
int err=SimpleDHTErrSuccess;
   if((err=dht22.read2(pin,&temperature,&humidity,NULL))!=SimpleDHTErrSuccess){
     Serial.println("Read DHT22 failed,err=");
     Serial.println(err);
     delay(2000);
     return;
   }
    Serial.println("Sample OK: ");
    Serial.println((int)temperature);
     dhttemp=((int)temperature);//temp from dht22
     Serial.println(dhttemp);
     Serial.println((int)humidity);
     dhthum=((int)humidity);//humidity from dht22
     Serial.println(dhthum);
     Serial.println("RH%");
    delay(2500); //Delay 2 sec.
sensorValue = analogRead(A1); // read the value from the sensor for ldr
Serial.println("LDR:");
Serial.println(sensorValue);
aa=map(sensorValue,0,1023,0,100);
Serial.println(aa);
if(aa<20)
{   digitalWrite(9, HIGH);    // turn oFF relay 1 for light
    Serial.println("Light OFF");
    delay (10000);
    a=0;
    
}
else if(aa>20)
{
   digitalWrite(9, LOW);    // turn oN relay 1 for light
     Serial.println("Light ON");
    delay (10000);
    a=1;
}
delay(1000);
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);
 delay(10000);
  // read the input on analog pin 0:
 sensorValuee = analogRead(A0); // for soil moisture sensor need to change the variable name in the end
  // print out the value you read:
  Serial.println("soil moisture sensor :");
  Serial.println(sensorValuee);
  bb=map(sensorValuee,0,1023,0,100);
Serial.println(bb);
  if (bb < 20)
 {
  digitalWrite(8,LOW); // Turns ON Relays 1 for water pump
  Serial.println("Pump ON");
  b=1;
  delay(10000);
 }
 else if(bb>20 && bb<50)
 {
  digitalWrite(8,LOW); // Turns ON Relays 1 for water pump
  Serial.println("Pump ON"); 
  b=1;
  delay(15000);
 }
else if(bb>80)
 {
  digitalWrite(8,HIGH); // Turns OFF Relays 1 for water pump
  Serial.println("Pump OFF"); 
  b=0;
  delay(15000);
 }

// humifier status
if(dhthum <80)
{
 digitalWrite(9,LOW); 
 Serial.println("Humidifier ON"); 
  c=1;
  delay(15000);
}
else
{
  digitalWrite(9,HIGH); 
 Serial.println("Humidifier OFF"); 
  c=0;
  delay(15000);
}
 
Serial.println("value of a");
Serial.println(a);
Serial.println("value of b");
Serial.println(b); 
Serial.println(c); 
  delay(1000);        // delay in between reads for stability
  table[0]=aa; // light intensity
  table[1]=bb;// soil moisture
  table[2]=Celcius;// soil temp
  table[3]=dhthum;
  table[4]=dhttemp;
  table[5]=phValue;//dhttemp
  sdoper();
}

// function that executes whenever data is received from master




void receiveEvent(int howMany) {
 while (0 <Wire.available()) 
 {    c = Wire.read();/* receive byte as a character */
      Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
//Wire.write(sensorValue);
 /*send string on request */
  uint8_t Buffer[6];
  Buffer[0]=table[0];
  Buffer[1]=table[1];
  Buffer[2]=table[2];
  Buffer[3]=table[3];
  Buffer[4]=table[4];
   Buffer[5]=table[5];
  //  Buffer[6]=table[6];
  //    Buffer[7]=table[7];// humifier
  //    Buffer[8]=table[8];
  //    Buffer[9]=table[9];// for ph
  Wire.write(Buffer,6);
}

void sdoper()
{
 // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("log.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
   myFile.println('<');
    myFile.print(aa);
    myFile.print(',');
     myFile.print(bb);
      myFile.print(',');
       myFile.print(Celcius);
        myFile.print(',');
         myFile.print(dhthum);
          myFile.print(',');
           myFile.print(dhttemp);
            myFile.print(',');
             myFile.print(phValue);// change it to ph when connected
              myFile.print('>');
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening log.txt");
  }
  // Reading the file
  myFile = SD.open("log.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening log.txt");
  }
  }

  void ph()
  {
     for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 phValue = -5.70 * pHVol + 21.34;
 Serial.print("sensor = ");
 Serial.println(phValue);
 
 delay(2000);
  }
