#define S2 A0  // Left Sensor
#define S3 A1  // Middle Sensor
#define S4 A2  // Right Sensor

#define ENA 5   // Enable pin for left motor (PWM)
#define ENB 6   // Enable pin for right motor (PWM)

#define IN1 9   // Left Motor Forward
#define IN2 10  // Left Motor Backward
#define IN3 11  // Right Motor Forward
#define IN4 12  // Right Motor Backward

#define SPEED 127  // Speed value (0-255)

void setup() {
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    stopMotors();  // Ensure motors are off at start
}

void loop() {
    int leftSensor = digitalRead(S2);
    int middleSensor = digitalRead(S3);
    int rightSensor = digitalRead(S4);

    if (leftSensor == 1 && middleSensor == 1 && rightSensor == 1) {
        moveForward();  // Move forward
    } 
    else if (leftSensor == 0 && middleSensor == 1 && rightSensor == 1) {
        turnSlightLeft();  // Slight correction left
    } 
    else if (leftSensor == 1 && middleSensor == 1 && rightSensor == 0) {
        turnSlightRight();  // Slight correction right
    }
    else if (leftSensor == 0 && middleSensor == 0 && rightSensor == 1) {
        turnHardLeft();  // Hard left correction
    }
    else if (leftSensor == 1 && middleSensor == 0 && rightSensor == 0) {
        turnHardRight();  // Hard right correction
    }
    else if (leftSensor == 0 && middleSensor == 0 && rightSensor == 0) {
        stopMotors();  // Stop if completely off track
    }
}

void moveForward() {
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnSlightLeft() {
    analogWrite(ENA, SPEED / 2);  // Reduce left motor speed
    analogWrite(ENB, SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnSlightRight() {
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED / 2);  // Reduce right motor speed
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void turnHardLeft() {
    analogWrite(ENA, SPEED / 2);  // Slower left motor for sharper turn
    analogWrite(ENB, SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnHardRight() {
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED / 2);  // Slower right motor for sharper turn
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors() {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
