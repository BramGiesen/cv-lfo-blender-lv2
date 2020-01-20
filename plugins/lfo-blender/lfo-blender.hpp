#ifndef DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED
#define DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include "onepole.hpp"
#include "invertedSawWave.h"
#include "oscillator.h"
#include "randomGen.h"
#include "sawWave.h"
#include "sineWave.h"
#include "squareWave.h"

START_NAMESPACE_DISTRHO

class LfoBlender : public Plugin
{
public:
    enum Parameters
    {
        paramBlend = 0,
        paramLfoFrequency,
        paramLfo1Type,
        paramLfo1Phase,
        paramLfo2Type,
        paramLfo2Phase,
        paramLfo3Type,
        paramLfo3Phase,
        paramLfo4Type,
        paramLfo4Phase,
        paramCount
    };

    LfoBlender();
    ~LfoBlender();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "LfoBlender";
    }

    const char* getDescription() const override
    {
        return "Transient Mangler";
    }

    const char* getMaker() const noexcept override
    {
        return "CSD";
    }

    const char* getHomePage() const override
    {
        return "http://";
    }

    const char* getLicense() const noexcept override
    {
        return "Custom";
    }

    uint32_t getVersion() const noexcept override
    {
        return d_version(1, 0, 8);
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('C', 'S', 'D', 's');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
    void  loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process
    void activate() override;
    void deactivate() override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;

private:

    Oscillator **oscillators1;
    Oscillator **oscillators2;
    Oscillator **oscillators3;
    Oscillator **oscillators4;

    OnePole lowpass;

    float sampleRate;

    float blend;
    float lfoFrequency;
    int   lfo1Type;
    float lfo1Phase;
    int   lfo2Type;
    float lfo2Phase;
    int   lfo3Type;
    float lfo3Phase;
    int   lfo4Type;
    float lfo4Phase;

    int counted_frames = 0;
    int current_frames = 0;

    bool tick = false;
    bool first_clock = false;
    bool clock_started = false;
    bool reset_phase = false;
    bool counting = false;

    float lfo1 = 0.0;
    float lfo2 = 0.0;
    float lfo3 = 0.0;
    float lfo4 = 0.0;

    void reset();

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LfoBlender)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED



