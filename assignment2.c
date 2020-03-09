/**************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 2 - Echo Sensor - Tapeless Ruler
* File: assignment2.c
*
* Description:
* This file uses the WiringPi library to create a tapeless
* ruler. An echo sensor (HC-SR04), which has a transmitter
* and receiver, was used to measure the distance.
* Basically, the transmitter sends sound waves, which is
* reflected back to the receiver once it encounters an obstacle.
* The time it takes for the sound waves to get back to the
* sensor is used to calculate the distance using the formula
* s = vt/2, wherein v represents the speed of sound,
* which is 340m/s.
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

// returns the distance using the formula distance = (velocity*time)/2
double calculate_distance() {
    double distance;
    clock_t start, end, time_elapsed;

    printf("Calculating distance...\n");
    
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
    
    time_elapsed = end - start;
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
