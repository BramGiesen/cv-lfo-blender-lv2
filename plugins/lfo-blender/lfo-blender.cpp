#include "lfo-blender.hpp"
#include <iostream>

START_NAMESPACE_DISTRHO


// -----------------------------------------------------------------------

LfoBlender::LfoBlender()
    : Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    loadProgram(0);

    sampleRate = (float)getSampleRate();

    lowpass.setFc(100.0/(double)sampleRate);

    blend        = 0.0;
    clockSource  = 0.0;
    lfoFrequency = 10.0;
    lfo1Type     = 0;
    lfo1Phase    = 0.0;
    lfo2Type     = 0;
    lfo2Phase    = 0.0;
    lfo3Type     = 0;
    lfo3Phase    = 0.0;
    lfo4Type     = 0;
    lfo4Phase    = 0.0;
    reset_phase  = false;

    const TimePosition& position = getTimePosition();

    float phase = 0.0;

    oscillators1 = new Oscillator*[5];
    oscillators2 = new Oscillator*[5];
    oscillators3 = new Oscillator*[5];
    oscillators4 = new Oscillator*[5];

    oscillators1[0] = new SineWave(sampleRate, 0, phase);
    oscillators1[1] = new SquareWave(sampleRate, 0, phase);
    oscillators1[2] = new SawWave(sampleRate, 0, phase);
    oscillators1[3] = new InvertedSawWave(sampleRate, 0, phase);
    oscillators1[4] = new RandomGenerator(sampleRate, 0, phase);

    oscillators2[0] = new SineWave(sampleRate, 0, phase);
    oscillators2[1] = new SquareWave(sampleRate, 0, phase);
    oscillators2[2] = new SawWave(sampleRate, 0, phase);
    oscillators2[3] = new InvertedSawWave(sampleRate, 0, phase);
    oscillators2[4] = new RandomGenerator(sampleRate, 0, phase);

    oscillators3[0] = new SineWave(sampleRate, 0, phase);
    oscillators3[1] = new SquareWave(sampleRate, 0, phase);
    oscillators3[2] = new SawWave(sampleRate, 0, phase);
    oscillators3[3] = new InvertedSawWave(sampleRate, 0, phase);
    oscillators3[4] = new RandomGenerator(sampleRate, 0, phase);

    oscillators4[0] = new SineWave(sampleRate, 0, phase);
    oscillators4[1] = new SquareWave(sampleRate, 0, phase);
    oscillators4[2] = new SawWave(sampleRate, 0, phase);
    oscillators4[3] = new InvertedSawWave(sampleRate, 0, phase);
    oscillators4[4] = new RandomGenerator(sampleRate, 0, phase);

    reset();
}

LfoBlender::~LfoBlender()
{
    delete[] oscillators1;
    oscillators1 = nullptr;
    delete[] oscillators2;
    oscillators2 = nullptr;
    delete[] oscillators3;
    oscillators3 = nullptr;
    delete[] oscillators4;
    oscillators4 = nullptr;
}

// -----------------------------------------------------------------------
// Init

void LfoBlender::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
    case paramBlend:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Blend";
        parameter.symbol     = "Blend";
        parameter.unit       = "";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 3.f;
        break;
    case paramClockSource:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "ClockSource";
        parameter.symbol     = "ClockSource";
        parameter.unit       = "";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.f;
        break;
    case paramLfoFrequency:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LfoFrequency";
        parameter.symbol     = "LfoFrequency";
        parameter.unit       = "";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 40.f;
        break;
    case paramLfo1Type:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_1_TYPE";
        parameter.symbol     = "LFO_1_TYPE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 4.f;
        break;
    case paramLfo1Phase:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_1_PHASE";
        parameter.symbol     = "LFO_1_PHASE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.1f;
        parameter.ranges.max = 1.f;
        break;
    case paramLfo2Type:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_2_TYPE";
        parameter.symbol     = "LFO_2_TYPE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 4.f;
        break;
    case paramLfo2Phase:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_2_PHASE";
        parameter.symbol     = "LFO_2_PHASE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.f;
        break;
    case paramLfo3Type:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_3_TYPE";
        parameter.symbol     = "LFO_3_TYPE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 4.f;
        break;
    case paramLfo3Phase:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_3_PHASE";
        parameter.symbol     = "LFO_3_PHASE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.f;
        break;
    case paramLfo4Type:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_4_TYPE";
        parameter.symbol     = "LFO_4_TYPE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 4.f;
        break;
    case paramLfo4Phase:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "LFO_4_PHASE";
        parameter.symbol     = "LFO_4_PHASE";
        parameter.unit       = "";
        parameter.ranges.def = 0.f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.f;
        break;
    }
}

void LfoBlender::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float LfoBlender::getParameterValue(uint32_t index) const
{
    switch (index)
    {
    case paramBlend:
        return blend;
    case paramClockSource:
        return clockSource;
    case paramLfoFrequency:
        return lfoFrequency;
    case paramLfo1Type:
        return lfo1Type;
    case paramLfo1Phase:
        return lfo1Phase;
    case paramLfo2Type:
        return lfo2Type;
    case paramLfo2Phase:
        return lfo2Phase;
    case paramLfo3Type:
        return lfo3Type;
    case paramLfo3Phase:
        return lfo3Phase;
    case paramLfo4Type:
        return lfo4Type;
    case paramLfo4Phase:
        return lfo4Phase;
    }
}

void LfoBlender::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    case paramBlend:
        blend = value;
        break;
    case paramClockSource:
        clockSource = value;
        break;
    case paramLfoFrequency:
        lfoFrequency = value;
        break;
    case paramLfo1Type:
        lfo1Type = value;
        break;
    case paramLfo1Phase:
        lfo1Phase = value;
        break;
    case paramLfo2Type:
        lfo2Type = value;
        break;
    case paramLfo2Phase:
        lfo2Phase = value;
        break;
    case paramLfo3Type:
        lfo3Type = value;
        break;
    case paramLfo3Phase:
        lfo3Phase = value;
        break;
    case paramLfo4Type:
        lfo4Type = value;
        break;
    case paramLfo4Phase:
        lfo4Phase = value;
        break;
    }
}

void LfoBlender::loadProgram(uint32_t index)
{
}

void LfoBlender::reset()
{
}

// -----------------------------------------------------------------------
// Process

void LfoBlender::activate()
{
}

void LfoBlender::deactivate()
{
}



void LfoBlender::run(const float** inputs, float** outputs, uint32_t frames)
{
    const float* cv_blend = inputs[0];
    const float* cv_clock = inputs[1];
    const float* cv_reset = inputs[2];

    float* output1 = outputs[0];
    float* output2 = outputs[1];
    float* output3 = outputs[2];
    float* output4 = outputs[3];
    float* output5 = outputs[4];


    // Main processing body
    for (uint32_t f = 0; f < frames; ++f)
    {

        if (cv_clock[f] > 0.0 && !tick) {

            counting = true;
            counted_frames = current_frames;
            current_frames = 0;

            if (first_clock)
                clock_started = true;

            first_clock = true;
            tick = true;

        } else if (cv_clock[f] == 0.0 && tick) {
            tick = false;
        }

        if (clockSource > 0.0) {
            if (clock_started) {
                lfoFrequency = 48000 / counted_frames;
            }
        }

        if (counting)
            current_frames++;

        if (cv_reset[f] > 0.0 && !reset_phase) {
            for (unsigned osc = 0; osc < 5; osc++) {
                oscillators1[osc]->setPhase(lfo1Phase);
                oscillators2[osc]->setPhase(lfo2Phase);
                oscillators3[osc]->setPhase(lfo3Phase);
                oscillators4[osc]->setPhase(lfo4Phase);
            }
            reset_phase = true;
        } else if (cv_reset[f] == 0.0 && reset_phase) {
            reset_phase = false;
        }


        for (unsigned osc = 0; osc < 5; osc++) {
            oscillators1[osc]->setFrequency(lfoFrequency);
            oscillators2[osc]->setFrequency(lfoFrequency);
            oscillators3[osc]->setFrequency(lfoFrequency);
            oscillators4[osc]->setFrequency(lfoFrequency);

            oscillators1[osc]->setPhaseOffset(lfo1Phase);
            oscillators2[osc]->setPhaseOffset(lfo2Phase);
            oscillators3[osc]->setPhaseOffset(lfo3Phase);
            oscillators4[osc]->setPhaseOffset(lfo4Phase);
        }

        int switcher = (int)blend + (int)cv_blend[f];
        switcher = (switcher <= 3) ? switcher : 3;
        float mix = 0.f;
        float fBlend = (blend + (float)cv_blend[f]) - switcher;
        fBlend = (fBlend > 0) ? fBlend : 0;
        float sampleA = 0.f;
        float sampleB = 0.f;

        switch(switcher)
        {
            case 0:
                sampleA = (float)oscillators1[lfo1Type]->getSample();
                sampleB = (float)oscillators2[lfo2Type]->getSample();

                mix = (sampleA * ((fBlend * -1) + 1)) + (sampleB * fBlend);

                break;
            case 1:
                sampleA = (float)oscillators2[lfo2Type]->getSample();
                sampleB = (float)oscillators3[lfo3Type]->getSample();

                mix = (sampleA * ((fBlend * -1) + 1)) + (sampleB * fBlend);

                break;
            case 2:
                sampleA = (float)oscillators3[lfo3Type]->getSample();
                sampleB = (float)oscillators4[lfo4Type]->getSample();

                mix = (sampleA * ((fBlend * -1) + 1)) + (sampleB * fBlend);

                break;
            case 3:
                mix = (float)oscillators4[lfo4Type]->getSample();

                break;
        }

        lfo1 = oscillators1[lfo1Type]->getSample();
        lfo2 = oscillators2[lfo2Type]->getSample();
        lfo3 = oscillators3[lfo3Type]->getSample();
        lfo4 = oscillators4[lfo4Type]->getSample();

        for (unsigned osc = 0; osc < 5; osc++) {
            oscillators1[osc]->tick();
            oscillators2[osc]->tick();
            oscillators3[osc]->tick();
            oscillators4[osc]->tick();
        }
        //        // Clearing output buffer from random garbage (if not in-place processing)
        //        if (input != output) output[f] = 0.f;

        output1[f] = mix;
        output2[f] = lfo1;
        output3[f] = lfo2;
        output4[f] = lfo3;
        output5[f] = lfo4;
    }
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new LfoBlender();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
