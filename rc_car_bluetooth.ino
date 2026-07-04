/*
  Bluetooth RC Car
  Hardware: Arduino Uno + HC-05 + L298N Motor Driver + 4x DC Motors
  Control via any Bluetooth serial app (e.g. "Bluetooth RC Controller")

  Commands received over Serial (Bluetooth):
    'F' - Forward
    'B' - Backward
    'L' - Turn Left
    'R' - Turn Right
    'S' - Stop
*/

// ── Motor A (Left side: FL + RL wired together) ──
#define IN1  4
#define IN2  5
#define ENA  3   // PWM pin

// ── Motor B (Right side: FR + RR wired together) ──
#define IN3  6
#define IN4  7
#define ENB  9   // PWM pin

// Fixed speed (0–255)
#define MOTOR_SPEED 200

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopCar();

  // HC-05 default baud rate is 9600
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': moveForward();  break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft();     break;
    case 'R': turnRight();    break;
    case 'S': stopCar();      break;

    default: break;
  }
}

// ── Motion functions ──────────────────────────────

void moveForward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  // Left motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Right motors forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  // Left motors backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Right motors backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  // Left motors slower/stop, right motors full
  analogWrite(ENA, MOTOR_SPEED / 2);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Right motors slower/stop, left motors full
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED / 2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
