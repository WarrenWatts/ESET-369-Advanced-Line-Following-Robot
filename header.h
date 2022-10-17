#ifndef HEADER
#define HEADER
unsigned int adc_raw[3];

void beepSound(void);
void ultraSetup(void);
void ultraSensor(void);
void wallReached(void);
void servoSetup(void);
void servoOpen(void);
void servoClosed(void);
void readADC(void);
void stopFunction(void);
void completeShutdown(void);
void rotateFunction(void);
void turnLeft(void);
void turnRight(void);
void moveForward(void);

#endif
