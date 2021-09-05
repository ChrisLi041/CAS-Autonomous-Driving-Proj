#include "gps.h"
#include <Arduino.h>
#define GpsSerial  Serial
#define DebugSerial Serial


int L = 13;

 struct
{
  char GPS_Buffer[80];
  bool isGetData;   //check if data is obtained successfully
  bool isParseData; //check if data is parsed successfully
  char UTCTime[11];   //UTC time
  char latitude[11];    
  char N_S[2];    //N/S
  char longitude[12];   
  char E_W[2];    //E/W
  bool isUsefull;   //check if position signal is valid
} Save_Data;
  const unsigned int gpsRxBufferLength = 600;
  char gpsRxBuffer[gpsRxBufferLength];
  unsigned int ii = 0;

//Initialize UART、GPS
void setupGPS()
{

  GpsSerial.begin(9600);      
  DebugSerial.begin(9600);
  DebugSerial.println("Start Initialize GPS...");
  DebugSerial.println("Wating...");

  Save_Data.isGetData = false;
  Save_Data.isParseData = false;
  Save_Data.isUsefull = false;
}


//GPS data GPRMC, UART reception and analysis of GGA
void updateGPS()
{
  gpsRead();  //get GPS data
  parseGpsBuffer();//parse GPS data
  printGpsBuffer();//output 

}


void errorLog(int num)
{
  DebugSerial.print("ERROR");
  DebugSerial.println(num);
  while (1)
  {
    digitalWrite(L, HIGH);
    delay(300);
    digitalWrite(L, LOW);
    delay(300);
  }
}

void printGpsBuffer()
{
  if (Save_Data.isParseData)
  {
    Save_Data.isParseData = false;
    
    DebugSerial.print("Save_Data.UTCTime = ");
    DebugSerial.println(Save_Data.UTCTime);

    if(Save_Data.isUsefull)
    {
      Save_Data.isUsefull = false;
      DebugSerial.print("Save_Data.latitude = ");
      DebugSerial.println(Save_Data.latitude);
      DebugSerial.print("Save_Data.N_S = ");
      DebugSerial.println(Save_Data.N_S);
      DebugSerial.print("Save_Data.longitude = ");
      DebugSerial.println(Save_Data.longitude);
      DebugSerial.print("Save_Data.E_W = ");
      DebugSerial.println(Save_Data.E_W);
    }
    else
    {
      DebugSerial.println("GPS DATA is not usefull!");
    }
    
  }
}

void parseGpsBuffer()
{
  char *subString;
  char *subStringNext;
  if (Save_Data.isGetData)
  {
    Save_Data.isGetData = false;
    DebugSerial.println("**************");
    DebugSerial.println(Save_Data.GPS_Buffer);
    
    for (int i = 0 ; i <= 6 ; i++)
    {
      if (i == 0)
      {
        if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
          errorLog(1); 
      }
      else
      {
        subString++;
        if ((subStringNext = strstr(subString, ",")) != NULL)
        {
          char usefullBuffer[2]; 
          switch(i)
          {
            case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break; 
            case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break; 
            case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;  
            case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break; 
            case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break; 
            case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break; 

            default:break;
          }

          subString = subStringNext;
          Save_Data.isParseData = true;
          if(usefullBuffer[0] == 'A')
            Save_Data.isUsefull = true;
          else if(usefullBuffer[0] == 'V')
            Save_Data.isUsefull = false;

        }
        else
        {
          errorLog(2);  
        }
      }


    }
  }
}


void gpsRead() {
  while (GpsSerial.available())
  {
    gpsRxBuffer[ii++] = GpsSerial.read();
    if (ii == gpsRxBufferLength)clrGpsRxBuffer();
  }

  char* GPS_BufferHead;
  char* GPS_BufferTail;
  if ((GPS_BufferHead = strstr(gpsRxBuffer, "$GPRMC,")) != NULL || (GPS_BufferHead = strstr(gpsRxBuffer, "$GNRMC,")) != NULL )
  {
    if (((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL) && (GPS_BufferTail > GPS_BufferHead))
    {
      memcpy(Save_Data.GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead);
      Save_Data.isGetData = true;

      clrGpsRxBuffer();
    }
  }
}

void clrGpsRxBuffer(void)
{
  memset(gpsRxBuffer, 0, gpsRxBufferLength);      
  ii = 0;
}
