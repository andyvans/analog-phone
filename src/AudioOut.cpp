#include "AudioOut.h"

AudioOut::AudioOut() :
    info(44100, 2, 16),
    sineWave(32000),
    sound(sineWave),
    copier(out, sound)
{
}

void AudioOut::Setup()
{
    AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

    // start I2S output
    Serial.println("Starting I2S audio out");
    auto config = out.defaultConfig(TX_MODE);
    config.copyFrom(info);
    config.i2s_format = I2S_STD_FORMAT;
    config.is_master = true;
    config.port_no = 0;
    config.pin_bck = I2S_BCLK_OUT;
    config.pin_ws = I2S_LRC_OUT;
    config.pin_data = I2S_DIN_OUT;
    out.begin(config);

    // Setup sine wave
    sineWave.setFrequency(500);
    sineWave.begin(info, N_B4);
    Serial.println("Started sine wave");
}

void AudioOut::Tick()
{
    copier.copy();
}