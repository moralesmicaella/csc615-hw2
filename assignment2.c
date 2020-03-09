/**************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 2 - Echo Sensor - Tapeless Ruler
* File: assignment2.c
*
* Description:
* This file uses the WiringPi library to create a tapeless
* ruler. An echo sensor (HC-SR04) was used to measure
* the distance.
* To compile this file, enter make.
* To run this file, enter ./assignment2
****************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <time.h> 

#define trigPin 21
#define echoPin 22
#define SPEED_OF_SOUND 340

// initializes the wiringPi and sets up the trigger and echo pins
void setup() {
    wiringPiSetup();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// calculates the distance using the formula distance = (velocity*time)/2
double calculate_distance() {
    double distance;
    clock_t start, end, time_elapsed;

    printf("Calculating distance...");
    
    digitalWrite(trigPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // records the time when ultrasonic is transmitted
    while(digitalRead(echoPin) == 0)
        start = clock();
    
    // records the time when ultrasonic is received.
    while(digitalRead(echoPin) == 1) 
        end = clock();
    
    time_elapsed = (double)(end-start);
    distance = (time_elapsed * SPEED_OF_SOUND) / 2.0;
    
    // returns distance in the unit of cm
    return distance * 100 / CLOCKS_PER_SEC;
}

int main(void) {
    setup();
    double distance;
    
    while(1) {
        distance = calculate_distance();
        printf("Distance: %fcm \n", distance);
    } 
    
    return 0;
}
