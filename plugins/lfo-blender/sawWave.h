#ifndef _SQUAREWAVE_H_
#define _SQUAREWAVE_H_
#include "oscillator.h"
#include <iostream>

class SawWave : public Oscillator
{
public:

    //constructors and destructor
    SawWave(double samplerate): SawWave(samplerate, 0, 0) {};
    SawWave(double samplerate, double frequency) :
    SawWave(samplerate, frequency, 0) {};
    SawWave(double samplerate, double frequency, double phase):
    Oscillator (samplerate, frequency, phase) {};
    ~SawWave(){};
    //prevent the default constructor to be generated
    SawWave() = delete;

    //override calculate
    //this method contains the sample calculation
    void calculate() override;


};


//override calculate method
//this method contains the sample calculation
inline void SawWave::calculate()
{
    sample = phase;
}


#endif
