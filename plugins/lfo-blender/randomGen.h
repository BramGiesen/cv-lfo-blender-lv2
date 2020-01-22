#ifndef _H_RANDOMGEN_
#define _H_RANDOMGEN_

#include <cstdlib>

class RandomGenerator : public Oscillator
{
public:

    //constructors and destructor
    RandomGenerator(double samplerate): RandomGenerator(samplerate, 0, 0) {};
    RandomGenerator(double samplerate, double frequency) :
    RandomGenerator(samplerate, frequency, 0) {};
    RandomGenerator(double samplerate, double frequency, double phase):
    Oscillator (samplerate, frequency, phase) {};
    ~RandomGenerator(){};
    //prevent the default constructor to be generated
    RandomGenerator() = delete;

    //override calculate
    //this method contains the sample calculation
    void calculate() override;

private:
    bool notSet=true;
    int randomValue = 0;

};


//override calculate method
//this method contains the sample calculation
inline void RandomGenerator::calculate()
{
    if(phase > 0.9 && notSet){
        randomValue = ((rand() % 100) * 0.02) - 1;
    }
    sample = randomValue;
}

#endif // _H_RANDOMGEN_
