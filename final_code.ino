// demo: CAN-BUS Shield, receive data with interrupt mode
// when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
// loovee, 2014-6-13

#include <SPI.h>
#include "mcp_can.h"

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10

typedef struct
{
    uint8_t pinNum;
    bool pinVal;
} pinInit_t;

pinInit_t digitPins[]= 
{
    {3, LOW},
    {5, LOW},
    {6, LOW},
    {7, LOW},
    {8, LOW},
    {9, LOW},
    {A0, LOW},
    {A1, LOW},
        
};


const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin


unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

uint8_t port_length=8;

char local_update_array_from_can=0x000000;
char receivedChar=0x00000000;
//char lowdata_local_update_array_from_can=LOW;



void updated_pin()
{
  for(uint8_t local_i = 0; local_i< port_length; local_i++ )
  {
    local_update_array_from_can=(receivedChar>>local_i)&0x01;
  /*  if(local_update_array_from_can==1)
    {
      lowdata_local_update_array_from_can=LOW;
    }
    else
    {
      
      lowdata_local_update_array_from_can=HIGH;
    }
    */
    digitalWrite(digitPins[local_i].pinNum,local_update_array_from_can);
    //delay(1000);
    Serial.print(digitPins[local_i].pinNum);
   // Serial.print(local_update_array_from_can,HEX); malik
    Serial.print(local_update_array_from_can,HEX);
    
    delay(100);
    //Serial.print(digital_pin_rx);
    
    
    
  }
  //delay(3000);
}

void setup()
{
    Serial.begin(115200);
    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");

    for(uint8_t i = 0; i < port_length; i++ )
    {
       pinMode(digitPins[i].pinNum, OUTPUT);
       digitalWrite(digitPins[i].pinNum, digitPins[i].pinVal);
   
    }
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        delay(2000);
        unsigned int canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Get data from ID: ");
        Serial.println(canId, HEX);
        if(canId==0x600)
        {
        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
        
        receivedChar=buf[1];
        Serial.println();
        Serial.println(receivedChar,HEX);
        updated_pin();
        }
        else
        {
        Serial.print("PLease send data on CAn ID 600");
        }
    }
 
      
            
        
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
