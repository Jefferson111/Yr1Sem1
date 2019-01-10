/**
 * Melody.h - Library for several short tunes
 * for CG1111 project
 * Created on October 28, 2018
 * 
 */
#ifndef Melody_h
#define Melody_h

#include "Arduino.h"
#include <avr/wdt.h>

/**
 * Public functions contains
 * constuctor to initialise output pin,
 * 5 tunes, random tune and all tunes
 *
 * Users can call indivual tunes, random and play all
 * to play random tunes and all tunes respectively
 */
class Melody
{
  public:
    Melody(uint8_t pin);
    void little_happiness();
    void laputa();
    void kahoot();
    void konosuba_end();
    void moonlight();
    void xue_mao_jiao();
    void mary_had_a_little_lamb();
    void merry_christmas();
    void happy_birthday();
    void fur_elise();
    void korobeiniki();
    void play_all();
    void random_tune();
  private:
  	void sound(uint16_t frequency, uint32_t duration);
  	void no_sound();
    void play_music(uint16_t note[], uint16_t note_duration[], uint8_t bpm);
    uint8_t _pin;  
};

#endif
