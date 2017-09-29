
//#define 0 'LOW
uint8_t digital_pin_rx=0;
uint8_t digital_pin_tx=1;
typedef struct
{
    uint8_t pinNum;
    bool pinVal;
} pinInit_t;



pinInit_t digitPins[]= 
{
    {2, HIGH},
    {3, LOW},
    {11, LOW},
    {5, LOW},
    {6, LOW},
    {7, LOW},
    {8, LOW},
    {12, LOW},
};
uint8_t port_length=8;

char update_array_from_can=0x000003;
char local_update_array_from_can=0x000000;
char receivedChar=0x000000;

void recvOneChar()
{
    if(Serial.available() > 0)
    {
     
            receivedChar =Serial.read();
            //readString += receivedChar; //makes the String readString
            delay(2);
            update_array_from_can=receivedChar;
            Serial.println(receivedChar,HEX);
           // newData = true;
            updated_pin();
      
           
    }
    
}


void updated_pin()
{
  for(uint8_t local_i = 0; local_i< port_length; local_i++ )
  {
    local_update_array_from_can=(receivedChar>>local_i)&0x01;
    
    digitalWrite(digitPins[local_i].pinNum,local_update_array_from_can);
    //delay(1000);
    Serial.print(digitPins[local_i].pinNum);
    Serial.print(local_update_array_from_can,HEX);
    //delay(1000);
    //Serial.print(digital_pin_rx);
    
    
    
  }
  delay(3000);
}

/*void converting_updating()
{
  for(uint8_t local_i = 0; local_i< port_length; local_i++ )
  
  local_update_array_from_can[local_i]

}*/



void setup()
{

Serial.begin(9600);
pinMode(digital_pin_rx,LOW);
for(uint8_t i = 0; i < port_length; i++ )
{
   pinMode(digitPins[i].pinNum, OUTPUT);
   digitalWrite(digitPins[i].pinNum, digitPins[i].pinVal);
   
}
  
  // put your setup code here, to run once:
}




void loop()
{
 recvOneChar();
 
  //Serial.print(F("Test serial communcation"));
  //Serial.print(F(""));
 // digitalWrite(in1, LOW);
  //delay(3000);
 // digitalWrite(in1, HIGH);
  //delay(3000);
  
  // put your main code here, to run repeatedly:
}
