
#ifndef _INVERTEDSAWWAVE_H_
#define _INVERTEDSAWWAVE_H_
#include "oscillator.h"
#include <iostream>

class InvertedSawWave : public Oscillator
{
public:
    
    //constructors and destructor
    InvertedSawWave(double samplerate): InvertedSawWave(samplerate, 0, 0) {};
    InvertedSawWave(double samplerate, double frequency) :
    InvertedSawWave(samplerate, frequency, 0) {};
    InvertedSawWave(double samplerate, double frequency, double phase):
    Oscillator (samplerate, frequency, phase) {};
    ~InvertedSawWave(){};
    //prevent the default constructor to be generated
    InvertedSawWave() = delete;
    
    //override calculate
    //this method contains the sample calculation
    void calculate() override;
    
    
};


//override calculate method
//this method contains the sample calculation
inline void InvertedSawWave::calculate()
{
    sample = phase *-1 + 1;
}


#endif
