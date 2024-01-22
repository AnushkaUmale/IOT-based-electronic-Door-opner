#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h> 
int tab=0;                                               //Open and Close                                            
int count = 0;                                          // count = 0   RFID
char input[12];                                         // character array of size 12   RFID
boolean flag = 0;                                       //RFID
int num=0;                                               //person counting
int cnt=2000;                                            //Program execution speed
int tab1=0;                                                   // set count
int set_value;                                                  //set count
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const char* ssid = "Anushka 24";
const char* password =  "24@Anushka";
void setup() {
              pinMode(25,OUTPUT);      // motor 1
              pinMode(33,OUTPUT);      // motor 2   
              pinMode(26,INPUT);       // IR 1
              pinMode(14,INPUT);       //IR2
              Serial.begin(9600);
              lcd.begin(16, 2);
              lcd.setCursor(3,0);
              lcd.print("IOT Based");
              lcd.setCursor(0,1);
              lcd.print("Electronic Door");
              delay(4000);
               lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Person Count:");
        lcd.setCursor(15,0);
        lcd.print(num);
              WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
             }

void loop() {
     if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 12)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         delay(5);
      }
      //Serial.println(input);                             // Print RFID tag number
    if(input[10]=='6' &&  input[11]=='F')
         {
          Serial.println("Welcome Member1!"); 
          open_door();
          delay(2000);
          close_door();
          num++;
         }
  else if(input[10]=='2' &&  input[11]=='4')
         {
          Serial.println("Welcome Member2");
          open_door();
          delay(2000);
          close_door(); 
          num++;
         }
  else if(input[10]=='1' &&  input[11]=='9')
         {
          Serial.println("Welcome Member3");
          open_door();
          delay(2000);
          close_door(); 
          num++;
         }
  else if(input[10]=='1' &&  input[11]=='2')
         {
          Serial.println("Welcome Member4"); 
          open_door();
          delay(2000);
          close_door();
          num++;
         }
  else if(input[10]=='8' &&  input[11]=='8')
         {
          Serial.println("Welcome Member5 "); 
          open_door();
          delay(2000);
          close_door();
          num++;
         }
  else if(input[10]=='0' &&  input[11]=='3')
         {
          Serial.println("Welcome Member6"); 
          open_door();
          delay(2000);
          close_door();
          num++;
         }
  else if(input[10]=='B' &&  input[11]=='8')
         {
          Serial.println("Welcome Member7");
          open_door();
          delay(2000);
          close_door(); 
          num++;
         }
  else if(input[10]=='2' &&  input[11]=='E')
         {
          Serial.println("Welcome Member8");
          open_door();
          delay(2000);
          close_door();
          num++; 
         }
  else if(input[10]=='8' &&  input[11]=='0')
         {
          Serial.println("Welcome Member9");
          open_door();
          delay(2000);
          close_door();
          num++; 
         }
  else if(input[10]=='1' &&  input[11]=='3')
         {
          Serial.println("Welcome Member10"); 
          open_door();
          delay(2000);
          close_door();
          num++;
         }
  else 
  {
    Serial.println("Waiting For Cards...!!");
  }
   }
     if (cnt>0)
       {
        //inc();
        dec();
       
        cnt=cnt-1;
       }
       if(cnt==0)
       {
          lcd.setCursor(0,1);
          lcd.print("Set Count =");
          lcd.setCursor(12,1);
          lcd.print(set_value); 
          link1(); 
          link2();
          cnt=2000;
       }   
         if (digitalRead(26)==0)
                      {
                        if(set_value>0)
                        set_value=set_value-1;
                        num++;
                         lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Person Count:");
        lcd.setCursor(15,0);
        lcd.print(num);
                        while(digitalRead(26)==0);
                        
                      if(set_value==0)
                      {
                      close_door();
                      tab1=0;
                      }

                      }
}

void inc(){                                            // Increment Function
           if (digitalRead(26)==0)
             {
              num++;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Person Count:");
               lcd.setCursor(15,0);
              lcd.print(num);
              while(digitalRead(26)==0);
             }
         }

void dec(){                                           // Decrement Function
           if (digitalRead(14)==0)
             {
              if(num>0)
                {
                 num--;
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("Person Count:");
                 lcd.setCursor(15,0);
                 lcd.print(num);
                 while(digitalRead(14)==0);
                }
             }
         }

void open_door(){
                   digitalWrite(25,1);
                   digitalWrite(33,0);
                   delay(4000);
                   digitalWrite(25,0);
                   digitalWrite(33,0);
                }
void close_door(){
                   digitalWrite(25,0);
                   digitalWrite(33,1);
                   delay(4000);
                   digitalWrite(25,0);
                   digitalWrite(33,0);
                 }
void stop_door(){
                   digitalWrite(25,0);
                   digitalWrite(33,0);
  
                }

void link1(){
              if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
 
    http.begin("https://mdbelectrosoft.in/MDBES/Workshop.php?unit=36"); //Specify the URL
    int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  //Serial.println(httpCode1);   //Print HTTP return code
   
 // Serial.println(payload);    //Print request response payload
  int myvalue=payload.toInt();
 // Serial.println(myvalue);
  if (myvalue==1 && tab==0)
               {
                open_door();
                tab=1;
               } 
  else if (myvalue==2 && tab==1)
          {
            close_door();
            tab=0;
          }
     }
 }

 void link2(){
              if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status // "Cloud Link"
    HTTPClient http1;
 
    http1.begin("https://mdbelectrosoft.in/MDBES/Workshop.php?unit=35"); //Specify the URL
    int http1Code = http1.GET();            //Send the request
  String payload1 = http1.getString();    //Get the response payload
 
  //Serial.println(httpCode1);   //Print HTTP return code
   
  //Serial.println(payload1);    //Print request response payload
  int myvalue1=payload1.toInt();
 
       if(myvalue1>0 && tab1==0)
         {      
               set_value=myvalue1;
               open_door();                            
               tab1=1;
                   
                 
        }
         
      }
 }
                
