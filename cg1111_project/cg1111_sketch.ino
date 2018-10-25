#include <MeMCore.h>

#define LDR
#define MICROPHONE 
#define LEFT_IR 
#define RIGHT_IR 
#define RED
#define GREEN
#define BLUE
/*
 * define all the sensors
 */

int getAvgReading(int times){      
//find the average reading for the requested number of times of scanning LDR
  int reading;
  int total =0;
//take the reading as many times as requested and add them up
  for(int i = 0;i < times;i++){
     reading = analogRead(LDR);
     total = reading + total;
     delay(/**/);
  }
//calculate the average and return it
  return total/times;
}

void color_challenge() {
  float red;
  float green;
  float blue;
  
  digitalWrite(RED, HIGH);
  delay(/**/);
  red = getAvgReading(5);
  digitalWrite(RED, LOW);
  delay(/**/);
  
  digitalWrite(GREEN, HIGH);
  delay(/**/);
  green = getAvgReading(5);
  digitalWrite(GREEN, LOW);
  delay(/**/);

  digitalWrite(BLUE, HIGH);
  delay(/**/);
  blue = getAvgReading(5);
  digitalWrite(BLUE, LOW);
  delay(/**/);

  if ((red > /**/) && (green > /**/) && (blue > /**/)) {
    //white
    turn_180();
  }
  else if ((red > /**/) && (green > /**/) && (blue < /**/)) {
    //orange
    turn_left();
    move_one_grid();
    turn_left();
  }
  else if (red > /**/) {
    //red
    turn_left();
  }
  else if (green > /**/) {
    //green
    turn_right();
  }
  else if (blue > /**/) {
    //blue
    turn_right();
    move_one_grid();
    turn_right();
  }
  else {
    //black
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
  
}

void turn_right() {
  
}

void turn_180() {
  
}

void move_one_grid() {
  
}

void setup() {
  // calibration of sensors

}

void loop() {
  // put code here to prevent hittting walls
  // and keep motor running/moving forward

  if (is_black_line) {
    //stop motors
    delay(/**/);
    choose_challenge();
    delay(/**/);
  }

  
}
