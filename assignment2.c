/**************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 2 - Echo Sensor - Tapeless Ruler
* File: assignment1b.c
*
* Description:
*
* To compile this file, enter make.
* To run this file, enter 
****************************************************************/

#include <stdio.h>
#include <wiringPi.h>
//#include <time.h> 

#define trigPin 1
#define echoPin 4
#define SPEED_OF_SOUND 340

void setup() {
    wiringPiSetup();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double calculate_distance() {
    double distance;
    unsigned int start, end, time_elapsed;
    //clock_t start, end, time_elapsed;

    printf("Calculating distance...")
    
    digitalWrite(trigPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    while(digitalRead(echoPin) == 0)
        start = millis() / 1000;
    //start = clock();

    while(digitalRead(echoPin) == 1)
        end = millis() / 1000;
    //end = clock();

    time_elapsed = end - start;
    distance = (time_elapsed * SPEED_OF_SOUND) / 2;
    
    return distance * 100;
}

int main(void) {
    setup();
    double distance;

    while(true) {
        distance = calculate_distance();
        printf("Distance: %d cm \n", distance);
    } 
    
    return 0;
}