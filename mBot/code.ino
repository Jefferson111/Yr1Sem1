#include <MeMCore.h>
#include "Wire.h"

/**
 * Macro/constant for victory tunes
 */
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494  
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define SEMIBREVE 1000
#define CRO 500 //CROTCHET
#define QUA 250 //QUAVER
#define SPEAKER 8 //pin for speaker

#define BOTH 2 // Indicators for which sides LED to be lit up/ both LED lights up
#define LEFT 1 // left LED lights up
#define RIGHT 0 // right LED lights up

/**
 * Macro/constant for Sensors
 */
#define LEFT_IR A1 //pin for left IR
#define RIGHT_IR A0 //pin for right IR
#define IR_LEFT_BIAS 1 //
#define IR_RIGHT_BIAS 1 //
#define LEFT_MOTOR_BIAS 1 //
#define RIGHT_MOTOR_BIAS 1 //
#define FSPEED 150 //
#define SPEED 225 //Base speed of MBot
#define SAMPLE 10 //Number of sampling times MBot performs
#define LED_PORT 1 //any random number to use the LED from MBot library
#define LDR 8 //pin for LDR
#define LED 13 //some sort of pin for LED
#define RED 0 //
#define GREEN 1 //
#define BLUE 2 //
#define ORANGE 3 //
#define BLACK 4 //
#define WHITE 5 //
#define FREQ_300 11 //digital pin 11 connected to 300Hz filter
#define FREQ_3000 12 //digital pin 12 connected to 3000Hz filter

//motor initialisation
MeDCMotor motor_left(M2);
MeDCMotor motor_right(M1);
int inputleftbase;
int inputrightbase;

//Sensor initialisation
MeBuzzer buzzer;
MeRGBLed led(LED_PORT);
MeLightSensor lightSensor(LDR);
MeUltrasonicSensor ultra(PORT_3);
MeLineFollower lineFinder(PORT_2);
uint8_t initial_red;
uint8_t initial_green;
uint8_t initial_blue;

//fluff
void glow(uint8_t light);
void victory_tune();
void play_music(uint16_t note[], uint16_t note_duration[]);
//sound
void sound_challenge();
bool read_noise(uint8_t noise_pin);
//color
uint8_t getColor(uint8_t color);
void color_challenge();
uint8_t get_max(uint8_t color[]);
//black line
bool is_black_line();
//wall bang prevention
int PIDdirection (int input, int inputbase, float Kp);
void calibrateinputbase(int *leftbase, int *rightbase);
//motor movements
void left_turn();
void right_turn();
void u_turn();
void move_one_grid();

//calibrates the sensor and stuff
void setup() {
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(FREQ_300, INPUT);
  pinMode(FREQ_3000, INPUT);
  pinMode(LDR, INPUT);
  led.setpin(LED);
  delay(2000);
  calibrateinputbase(&inputleftbase, &inputrightbase);
  initial_red = getColor(RED);
  initial_green = getColor(GREEN);
  initial_blue = getColor(BLUE);
}

void loop() {
   if (is_black_line()) {
    motor_left.stop();
    motor_right.stop();
    delay(300);
    color_challenge();
    delay(300);
  }  
  int leftinput = analogRead(LEFT_IR);
  int rightinput = analogRead(RIGHT_IR);
  int leftoffset = PIDdirection(leftinput, inputleftbase, 1.5);
  int rightoffset = PIDdirection(rightinput, inputrightbase, 1.5);                           
  int motor_left_speed = rightoffset * (SPEED / 75) - leftoffset * (SPEED / 75) + SPEED;
  int motor_right_speed = leftoffset * (SPEED / 75) - rightoffset * (SPEED / 75) + SPEED;
  motor_left.run(motor_left_speed);
  motor_right.run(-motor_right_speed); 
}

/**
 * Function that randomly generate color for LED
 * These numbers seem to produce the nicest variations of color
 * 
 * @param[in] light To determine which LED is to be lit up
 * @param[out] Glows LED
 */
void glow(uint8_t light) {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t limit;

  randomSeed(analogRead(0));
  limit = random(200);
  red = random(limit);
  limit = random(200);
  green = random(limit);
  limit = random(180);
  blue = random(limit);
  if (light == BOTH) {
    led.setColor(red, green, blue);
  }
  else {
    led.setColorAt(light, red, green, blue);
  }
  led.show();
}

/**
 * Function that plays the victory tune
 * 
 * @param[in] NIL
 * @param[out] xue_mao_jiao onto speaker
 */
void victory_tune() {
  uint16_t note[] = {NOTE_FS5, NOTE_GS5, NOTE_AS5, NOTE_CS5, NOTE_FS5, NOTE_AS5, NOTE_AS5,
                NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_CS6, NOTE_CS6, NOTE_CS6, NOTE_CS6,
                NOTE_FS5, NOTE_F5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5,
                NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_CS5, 
                NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_DS5,
                NOTE_CS5, NOTE_AS4, NOTE_CS5, NOTE_AS4, NOTE_CS5, NOTE_GS5, NOTE_FS5,
                NOTE_CS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_B5, NOTE_CS6, NOTE_FS5,
                NOTE_FS5, NOTE_AS5, NOTE_GS5, 1};

  uint16_t note_duration[] = {QUA, QUA, QUA, QUA, QUA, QUA, CRO, QUA, QUA, QUA, QUA,
                         QUA, QUA, CRO, QUA, QUA, QUA, QUA, QUA, QUA, CRO, QUA, 
                         QUA, QUA, QUA, QUA, QUA, CRO, QUA, QUA, QUA, QUA, QUA, 
                         QUA, CRO, QUA, QUA, QUA, QUA, QUA, QUA, CRO + QUA, QUA,
                         QUA, QUA, QUA, QUA, QUA, QUA, QUA, QUA, SEMIBREVE};
  while(true) {
    play_music(note, note_duration);
  }
}

/**
 * Function that plays a tune
 * Tempo is fixed in this version to save memory space
 * To save more memory, the length of note array can be hardcoded
 * 
 * @param[in] note The array consisting of the all the notes
 *            note_duration The array consisting of the length of the note in microseconds
 * @param[out] plays tune onto speaker
 */
void play_music(uint16_t note[], uint16_t note_duration[]) {
  uint16_t len = 0;
  uint16_t i = 0;
  while (note[len] != 1) {
    len++;
  }
  for (i = 0; i < len; i++) {
    glow(BOTH);
    buzzer.tone(SPEAKER, note[i], note_duration[i]);
    delay(note_duration[i] * 0.5);
    buzzer.noTone(SPEAKER);
  }
}

/**
 * Function that deals with the sound challenge
 * Detects for 300 and 3000HZ noise and perform action accordingly
 * 
 * @param[in] NIL
 * @param[out] turn the MBot/victory tune
 */
void sound_challenge() {
  bool noise_300 = read_noise(FREQ_300);
  delay(100);
  bool noise_3000 = read_noise(FREQ_3000);
  delay(100);
  if (noise_300 && !noise_3000) {
    turn_left();
  }
  else if (noise_300 && noise_3000) {
    u_turn();
  }
  else if (!noise_300 && noise_3000) {
    turn_right();
  }
  else {
    victory_tune();
  }
}

/**
 * Function that reads in the noise for a particular frequency
 * 
 * @param[in] noise_pin The digital pin that is connected to MBot to
 *                      either 300 or 3000HZ band-pass filter
 * @return return true if there is noise and false otherwise
 */
bool read_noise(uint8_t noise_pin) {
  uint8_t counter = 0; 
  for (uint8_t i = 0; i < SAMPLE; i++) {
    //change this part if compiling error
    //counter += digitalRead(noise_pin);
    if(digitalRead(noise_pin) == HIGH) {
      counter += 1;
    }
    delayMicroseconds(10);
  }
  uint8_t threshold = 2;
  if (counter > threshold) {
    return true;
  } 
  return false;
}

/**
 * Function that outputs R/G/B values
 * Assumes perfect grayscale black(0, 0, 0) and white(255, 255, 255)
 * Works pretty well, even better than trying to calibrate against white & black paper
 * 
 * @param[in] color The R/G/B color we want to obtain value for
 * @return return the R/G/B values
 */
uint8_t getColor(uint8_t color) {
  switch(color) {
    case RED: led.setColor(255, 0, 0); break;
    case GREEN: led.setColor(0, 255, 0); break;
    case BLUE: led.setColor(0, 0, 255); break;
  }
  led.show();
  delay(50);
  uint16_t total = 0;

  for(uint8_t i = 0; i < SAMPLE; i++) {
    total = lightSensor.read() + total;
    delay(50);
  }
  led.setColor(0, 0, 0);
  led.show();
  
  return  (255 / SAMPLE) / 1023 * total; //conversion to 255 RGB values
}

/**
 * Function that deals with the color challenge and 
 * detects the color above the MBot
 * 
 * @param[in] NIL
 * @param[out] turn the MBot or proceed to sound challenge(black color above MBot)
 */
void color_challenge() {
  uint8_t color_arr[3];
  color_arr[RED] = getColor(RED);
  color_arr[GREEN] = getColor(GREEN);
  color_arr[BLUE] = getColor(BLUE);
  uint8_t color = get_max(color_arr);

  switch(color) {
    case BLACK: sound_challenge(); break;
    case WHITE: u_turn(); break;
    case RED: turn_left(); break;
    case BLUE: turn_right(); move_one_grid(); turn_right(); break;
    case GREEN: turn_right(); break;
    case ORANGE: turn_left(); move_one_grid(); turn_left(); break;
  }
}

/**
 * Function that determined the color above the MBot
 * 
 * @param[in] color The array consisting of RGB values
 * @return return the color above the MBot
 */
uint8_t get_max(uint8_t color[]) {
  if ((color[RED] >  0.8 * initial_red) && (color[BLUE] > 0.8 * initial_blue) && (color[GREEN] > 0.8 * initial_green)) {
    return WHITE;
  }
  
  if ((color[RED] < 0.4 * initial_red) && (color[BLUE] < 0.4 * initial_blue) && (color[GREEN] < 0.4 * initial_green)) {
    return BLACK;
  }
  
  if ((color[RED] > color[GREEN]) && (color[RED] > color[BLUE])) {
    if (color[GREEN] > color[BLUE]) {
      return ORANGE;
    }
    else {
      return RED;
    }
  }
  
  if (color[GREEN] > color[RED] && color[GREEN] > color[BLUE]) {
    return GREEN;
  }
  
  return BLUE;
}

/**
 * Function that detects for Black line
 * 
 * @param[in] NIL
 * @return return true if there is black line on the floor
 */
bool is_black_line() {
  int sensorState = lineFinder.readSensors();
  if (sensorState == S1_IN_S2_IN ||sensorState == S1_IN_S2_OUT||sensorState == S1_OUT_S2_IN) {
    return true;
  } 
  else{
    return false;
  }
}

/**
 * Function that accounts for PID using IR sensors reading
 * 
 * @param[in] input IR reading from MBot
 *            inputbase Value calculated from he intial IR reading before MBot begin the challenge
 *            Kp The proportional term of PID obtain after numerous trial and error
 * 
 * @return return the offset speed that will allow MBot to go back to original course
 */
int PIDdirection (int input, int inputbase, float Kp) {
   int error = 0;
   int processedoutput;
   if (input > inputbase) {
     input = inputbase;
   }
   error = input - inputbase; /*deviation from standard*/
   processedoutput = Kp * error;
   if (processedoutput < -100) {
     processedoutput = -100;
   }
   return processedoutput;  
}

/**
 * Function that calibrate the initial IR values to use for PID later
 * 
 * @param[in] leftbase The initial left IR value
 *            rightbase The initial right IR value
 * @param[out] calibrates leftbase and rightbase
 */
void calibrateinputbase(int *leftbase, int *rightbase) {

  unsigned int sum_left = 0;
  unsigned int sum_right = 0;
  int i;
  for (i = 0; i < SAMPLE; i++) {
    int InputRight = analogRead(RIGHT_IR);
    int InputLeft = analogRead(LEFT_IR);
    sum_left += InputLeft;
    sum_right += InputRight;
    delay(5);
  }
  *leftbase = sum_left / 10;
  *rightbase = sum_right / 10;
}

/**
 * Function that turns MBot to left
 * Left LED lights up too
 * 
 * @param[in] NIL
 * @param[out] MBot turn to the left
 */
void turn_left() {
  glow(LEFT);
  motor_left.run(FSPEED);
  motor_right.run(FSPEED);
  delay(420);
  motor_left.stop();
  motor_right.stop();
  led.setColor(0, 0, 0);
  led.show();
}

/**
 * Function that turns MBot to right
 * Right LED lights up too
 * 
 * @param[in] NIL
 * @param[out] MBot turn to the right
 */
void turn_right() {
  glow(RIGHT);
  motor_left.run(-FSPEED);
  motor_right.run(-FSPEED);
  delay(420);                                                                                                                                                                                                                                      
  motor_left.stop();
  motor_right.stop();
  led.setColor(0, 0, 0);
  led.show();
}

/**
 * Function that moves MBot by one grid
 * Both LED lights up too
 * 
 * @param[in] NIL
 * @param[out] MBot moves one grid
 */
void move_one_grid() {
  glow(BOTH);
  motor_left.run(FSPEED);
  motor_right.run(-FSPEED); 
  delay(900);
  motor_left.stop();
  motor_right.stop();
  led.setColor(0, 0, 0);
  led.show();  
}

/**
 * Function that u-turns MBot
 * Both LED lights up too
 * 
 * @param[in] NIL
 * @param[out] MBot u-turns
 */
void u_turn() {
  glow(BOTH);
  motor_left.run(FSPEED);
  motor_right.run(FSPEED);
  delay(900);                                                        
  motor_left.stop();
  motor_right.stop();
  led.setColor(0, 0, 0);
  led.show();
}
