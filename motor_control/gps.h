#ifndef _GPS_h
#define _GPS_h

#define GPSUART Serial

void setupGPS();
void updateGPS();
void errorLog(int num);
void printGpsBuffer();
void parseGpsBuffer();
void gpsRead();
void clrGpsRxBuffer(void);


#endif
