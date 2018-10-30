/**
 * Melody.h - Library for several short tunes
 * Created on October 18, 2018
 * 
 */
#ifndef Melody_h
#define Melody_h

#include "Arduino.h"

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
    Melody(int pin);
    void kahoot();
    void konosuba_end();
    void moonlight();
    void xue_mao_jiao();
    void mary_had_a_little_lamb();
    void merry_christmas();
    void happy_birthday();
    void fur_elise();
    void korobeiniki();
    void play_all(); //normal mbot memory will not support this
    void random_tune(); 
  private:
    void play_music(int note[], int note_duration[], int bpm);
    int _pin;  
};

#endif
