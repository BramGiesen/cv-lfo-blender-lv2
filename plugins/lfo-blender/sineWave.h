#ifndef _SINEWAVE_H_
#define _SINEWAVE_H_
#include "oscillator.h"

class SineWave : public Oscillator
{
public:

    //constructors and destructor
    SineWave(double samplerate): SineWave(samplerate, 0, 0) {};
    SineWave(double samplerate, double frequency) :
    SineWave(samplerate, frequency, 0) {};
    SineWave(double samplerate, double frequency, double phase):
    Oscillator (samplerate, frequency, phase) {};
    ~SineWave(){};
    //prevent the default constructor to be generated
    SineWave() = delete;

    //override calculate
    //this method contains the sample calculation
    void calculate() override;


};


//override calculate method
//this method contains the sample calculation
inline void SineWave::calculate()
{
    sample = sin(phase * PI_2 );
}


#endif
