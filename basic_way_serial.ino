
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
    {2, LOW},
    {3, LOW},
    {4, LOW},
    {5, LOW},
    {6, LOW},
    {7, LOW},
    {8, LOW},
    {9, LOW},
};
uint8_t port_length=8;

char update_array_from_can=0x03;
char local_update_array_from_can=0x00;
char receivedChar=0x00;

void recvOneChar()
{
    if (Serial.available() > 0)
    {
        receivedChar = Serial.read();
        update_array_from_can=receivedChar;
        Serial.print(receivedChar,HEX);
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
    Serial.print(local_update_array_from_can);
    //delay(1000);
    //Serial.print(digital_pin_rx);
    
    
    
  }
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
