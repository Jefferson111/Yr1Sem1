#include <MeMCore.h>

#define LDR
#define MICROPHONE 
#define LEFT_IR 
#define RIGHT_IR 
#define RED
#define GREEN
#define BLUE

MeDCMotor motor_left(M1);
MeDCMotor motor_right(M2);

uint8_t motor_left_speed = 225; // Left
uint8_t motor_right_speed = -225; // Right

MeLightSensor lightSensor(PORT_6);
MeLineFollower lineFinder(2);

int getAvgReading(int times, int color){      
//find the average reading for the requested number of times of scanning LDR
  int reading;
  int total = 0;
//turn on the LED
  digitalWrite(color, HIGH);
  delay(/**/);
//take readings
  for(int i = 0;i < times;i++){
     reading = analogRead(LDR);
     total = reading + total;
     delay(/**/);
  }
//turn off the LED
  digitalWrite(color, LOW);
  delay(/**/);
//return average
  return (total / times);
}

void color_challenge() {
  float red;
  float green;
  float blue;

  red = getAvgReading(5, RED);
  green = getAvgReading(5, GREEN);
  blue = getAvgReading(5, BLUE);

  if ((red > /**/) && (green > /**/) && (blue > /**/)) {
    //white paper detected
    turn_180();
  }
  else if ((red > /**/) && (green > /**/) && (blue < /**/)) {
    //orange paper detected
    turn_left();
    move_one_grid();
    turn_left();
  }
  else if (red > /**/) {
    //red paper detected
    turn_left();
  }
  else if (green > /**/) {
    //green paper detected
    turn_right();
  }
  else if (blue > /**/) {
    //blue paper detected
    turn_right();
    move_one_grid();
    turn_right();
  }
  else {
    //black paper detected and end of challenge
    /*
     * play celebratory tune
     * and delay infinitely/switch off(by changing function to bool)
     */
  }
}

void sound_challenge() {
  int noise_A = get_noise(FREQUENCY_A);
  int noise_B = get_noise(FREQUENCY_B);
  //noise_diff = get_noise(FREQUENCY_A) - get_noise(FREQUENCY_B);

  if (noise_diff < /**/) {
    turn_left();
  }
  else if (noise_diff > /**/) {
    turn_right();
  }
  else {
    turn_180();
  }

}

void choose_challenge() {
  /* Code to
   * Check for paper above m_bot
   * 
   */
  if (/**/) {
    color_challenge();
  }
  else {
    sound_challenge();
  }
}

bool is_black_line(){
 int sensorState = lineFinder.readSensors();
 if (sensorState == S1_IN_S2_IN ||sensorState == S1_IN_S2_OUT||sensorState == S1_OUT_S2_IN){
    return true;
 } 
 else{
    return false;
 }
}

/**
 * If not enough memory, just code turn_left and move_one_grid
 * 
 */
void turn_left() {
  motor_left.run(-motor_left_speed);
  motor_right.run(motor_right_speed);
  delay(/**/);
  motor_left.stop();
  motor_right.stop();
}

void turn_right() {
  motor_left.run(motor_left_speed);
  motor_right.run(-motor_right_speed);
  delay(/**/);
  motor_left.stop();
  motor_right.stop();
}

void turn_180() {
  turn_left();
  turn_left();
}

void move_one_grid() {
  motor_left.run(motor_left_speed);
  motor_right.run(motor_right_speed);
  delay(/**/);
  motor_left.stop();
  motor_right.stop();
}

void setup() {
  // calibration of sensors

}

void loop() {
  float input_right = analogRead(RIGHT_IR);
  float input_left = analogRead(LEFT_IR);

  //adjust speed of motor left/right motor based on the input_left/right
  
  if (is_black_line()) {
    motor_left.stop();
    motor_right.stop();
    delay(/**/);
    choose_challenge();
    delay(/**/);
  }

  motor_left.run(/*adjusted speed to prevent hitting walls*/);
  motor_right.run(/*adjusted speed to prevent hitting walls*/);
  
}
