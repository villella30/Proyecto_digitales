class Motor
{
  int pin_dir;
  int pin_step;
  int stepDelay = 1000;

public:
  Motor(int pin_dir, int pin_step)
  {
    this->pin_dir = pin_dir;
    this->pin_step = pin_step;

    pinMode(pin_dir, OUTPUT);
    pinMode(pin_step, OUTPUT);
  }

  void move()
  {
    digitalWrite(this->pin_step, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(this->pin_step, LOW);
    delayMicroseconds(stepDelay);
  }
  void dirUp()
  {
    digitalWrite(this->pin_dir, HIGH);
  }
  void dirDown()
  {
    digitalWrite(this->pin_dir, LOW);
  }
  void stop()
  {
    digitalWrite(this->pin_dir, LOW);
    digitalWrite(this->pin_step, LOW);
  }
};
const int stepPin = 8;
const int steps = 200;
int stepDelay;
int estado;
char dato;

enum MOTORESTADOS
{
  MOTOR_SUBIR,
  MOTOR_BAJAR,
  MOTOR_FRENAR
}

int estado = MOTOR_FRENAR;

#define SUBIR 'F'
#define BAJAR 'B'
#define FRENAR 'H'
#define PIN_MOTOR_DIR 2
#define PIN_MOTOR_STEP 3

Motor *motor = new Motor(PIN_MOTOR_DIR, PIN_MOTOR_STEP);
void setup()
{

  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    dato = Serial.read();
    Serial.println(dato);
    if (dato == SUBIR)
      estado = MOTOR_SUBIR;
    if (dato == BAJAR)
      estado = MOTOR_BAJAR;
    if (dato == FRENAR)
      estado = MOTOR_FRENAR;
  }

  switch (estado)
  {
  case MOTOR_SUBIR:
  {
    motor->dirUp();
    motor->move();
    break;
  }
  case MOTOR_BAJAR:
  {
    motor->dirDown();
    motor->move();
    break;
  }
  case MOTOR_FRENAR:
  default:
  {
    motor->stop();
    break;
  }
  }
}