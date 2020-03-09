/**************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 2 - Echo Sensor - Tapeless Ruler
* File: assignment2.c
*
* Description:
*
* To compile this file, enter make.
* To run this file, enter 
****************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <time.h> 

#define trigPin 21
#define echoPin 22
#define SPEED_OF_SOUND 340

void setup() {
    wiringPiSetup();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double calculate_distance() {
    double distance;
    clock_t start, end, time_elapsed;

    printf("Calculating distance...");
    
    digitalWrite(trigPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    while(digitalRead(echoPin) == 0)
        start = clock();
    
    while(digitalRead(echoPin) == 1) 
        end = clock();
    
    time_elapsed = (double)(end-start);
    distance = (time_elapsed * SPEED_OF_SOUND) / 2.0;
    
    return distance * 100 / CLOCKS_PER_SEC;
}

int main(void) {
    setup();
    double distance;
    
    while(1) {
        distance = calculate_distance();
        printf("Distance: %f cm \n", distance);
    } 
    
    return 0;
}
