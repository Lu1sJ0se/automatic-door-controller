// Pines
const int TRIG_PIN = 6;      // ultrasónico TRIG (PWM-capable también, pero lo usamos digital normal)
const int ECHO_PIN = 5;      // ultrasónico ECHO
const int IN1 = 3;            // <-- debe ser pin PWM!
const int IN2 = 9;            // <-- debe ser pin PWM!

// Parámetros
const long DIST_THRESHOLD_CM = 20;
const unsigned long AUTO_CLOSE_DELAY = 3000;
const unsigned long DEAD_TIME_MS = 500;
const unsigned long MOVE_TIMEOUT_MS = 400;

// Estados
enum State {CLOSED, OPENING, OPENED, CLOSING};
State state = CLOSED;

// Tiempos
unsigned long stateStartTime = 0 ;
unsigned long lastPresenceTime = 0;

// Velocidades (0-255)
const int SPEED_OPEN  = 40;  // qué tan rápido abre
const int SPEED_CLOSE = 40;  // un poco más lento cerrando por seguridad

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  stopMotor();
  Serial.begin(9600);

  state = CLOSED;
  stateStartTime = millis();
}

void loop() {
  unsigned long now = millis();
  long dist = readUltrasonicCM();

  Serial.print("Dist(cm): ");
  Serial.print(dist);
  Serial.print("  State: ");
  Serial.println(state);

  switch (state) {

    case CLOSED:
      if (dist < DIST_THRESHOLD_CM) {
        openDoor();
      }
      break;

    case OPENING:
      if (now - stateStartTime >= MOVE_TIMEOUT_MS) {
        stopMotor();
        state = OPENED;
        stateStartTime = now;
        lastPresenceTime = now;
      }
      break;

    case OPENED:
      if (dist < DIST_THRESHOLD_CM) {
        lastPresenceTime = now; // alguien todavía ahí
      }
      if ((now - lastPresenceTime) >= AUTO_CLOSE_DELAY) {
        closeDoor();
      }
      break;

    case CLOSING:
      // safety: si alguien se mete, reabrimos
      if (dist < DIST_THRESHOLD_CM) {
        openDoor();
        break;
      }
      if (now - stateStartTime >= MOVE_TIMEOUT_MS) {
        stopMotor();
        state = CLOSED;
        stateStartTime = now;
      }
      break;
  }

  delay(50);
}

// -------- Funciones de movimiento --------

void stopMotor() {
  // apagar ambas ramas -> motor libre/parado
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}

// gira en la dirección "abrir"
void driveOpen(int speedVal) {
  // Sentido abrir = IN1 activo en PWM, IN2 apagado
  analogWrite(IN1, speedVal);
  analogWrite(IN2, 0);
}

// gira en la dirección "cerrar"
void driveClose(int speedVal) {
  // Sentido cerrar = IN2 activo en PWM, IN1 apagado
  analogWrite(IN1, 0);
  analogWrite(IN2, speedVal);
}

void openDoor() {
  stopMotor();
  delay(DEAD_TIME_MS);

  driveOpen(SPEED_OPEN);

  state = OPENING;
  stateStartTime = millis();
}

void closeDoor() {
  stopMotor();
  delay(DEAD_TIME_MS);

  driveClose(SPEED_CLOSE);

  state = CLOSING;
  stateStartTime = millis();
}

// -------- Sensor ultrasónico --------
long readUltrasonicCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return 999;
  return duration / 58L;
}
