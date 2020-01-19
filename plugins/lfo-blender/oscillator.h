#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include "math.h"

#define PI_2 6.28318530717959

class Oscillator
{
public:
    Oscillator(double samplerate, double frequency, double phase) :
    frequency(frequency), phase(phase), sample(0), samplerate(samplerate) {};
    virtual ~Oscillator(){};

    double getSample();
    void tick();
    void setPhase(double phase);
    void setPhaseOffset(double offset);
    void setFrequency(double frequency);
    double getFrequency();
protected:
    virtual void calculate() = 0;
    double frequency;
    double phase;
    double offset = 0.0;
    double sample;
    double samplerate;

};

inline double Oscillator::getSample() { return sample; }

inline void Oscillator::tick()
{
    phase += frequency / samplerate;

    if (phase >= 1)
        phase -= 1;

    //calculate new sample
    calculate();
}

inline void Oscillator::setPhase(double phase)
{
    this->phase = phase;
}

inline void Oscillator::setPhaseOffset(double offset)
{
    if (offset != this->offset) {
        phase = offset;
    }

    this->offset = offset;
}

inline void Oscillator::setFrequency(double frequency)
{
    this->frequency = frequency;
}

inline double Oscillator::getFrequency() { return frequency; }

#endif
