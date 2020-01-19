#ifndef _SquareWave_H_
#define _SquareWave_H_
#include "oscillator.h"

class SquareWave : public Oscillator
{
public:

    //constructors and destructor
    SquareWave(double samplerate): SquareWave(samplerate, 0, 0) {};
    SquareWave(double samplerate, double frequency) :
    SquareWave(samplerate, frequency, 0) {};
    SquareWave(double samplerate, double frequency, double phase):
    Oscillator (samplerate, frequency, phase) {};
    ~SquareWave(){};
    //prevent the default constructor to be generated
    SquareWave() = delete;

    //override calculate
    //this method contains the sample calculation
    void calculate() override;


};


//override calculate method
//this method contains the sample calculation
inline void SquareWave::calculate()
{
    sample = sin(phase * PI_2 );
    sample = (sample > 0 ) ? 1 : 0;
}


#endif
