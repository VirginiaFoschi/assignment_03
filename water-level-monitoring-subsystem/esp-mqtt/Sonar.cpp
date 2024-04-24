#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin)
{
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Sonar::getDistance()
{
    /* Triggering stage: sending the impulse */
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    /* Receiving the echo */
    float tUS = pulseIn(this->echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * vs;
    return d;
}

Sonar::~Sonar()
{
}