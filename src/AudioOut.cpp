#include "AudioOut.h"

AudioOut::AudioOut() :
    infoFrom(48000, 2, 32),
    //infoTo(44100, 2, 16),
    //sineWave(32000),
    //sound(sineWave),
    //converter(in),    
    copier(out, in)
{
}

void AudioOut::Setup()
{
    AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

    // start I2S in
    Serial.println("starting audio in");
    //auto configIn = analogIn.defaultConfig(RX_MODE);
    //configIn.copyFrom(infoFrom);
    //configIn.adc_pin = MIC_PIN;

    auto configIn = in.defaultConfig(RX_MODE);
    configIn.copyFrom(infoFrom);
    //configIn.copyFrom(infoFrom);
    //configIn.i2s_format = I2S_STD_FORMAT;
    //configIn.is_master = true;
    //configIn.port_no = 0;
    //configIn.auto_clear = true;
    //configIn.sample_rate = sampleRate;
    //configIn.bits_per_sample = 16;
    //configIn.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
    //configIn.buffer_count = 4;
    //configIn.buffer_size = 240;
    //configIn.use_apll = true;
    //configIn.pin_bck = I2S_BCLK_IN;
    //configIn.pin_ws = I2S_LRC_IN;
    //configIn.pin_data_rx = I2S_DATA_IN;
    //configIn.fixed_mclk = 0;
    //configIn.pin_mck = I2S_MCLK_IN;
    //configIn.channels = 2;
    in.begin(configIn);

    //converter.begin(infoFrom, infoTo);

    // start I2S output
    Serial.println("Starting I2S audio out");
    auto configOut = out.defaultConfig(TX_MODE);
    configOut.copyFrom(infoFrom);
    //configOut.i2s_format = I2S_STD_FORMAT;
    //configOut.is_master = true;
    configOut.port_no = 1;
    //configOut.pin_bck = I2S_BCLK_OUT;
    //configOut.pin_ws = I2S_LRC_OUT;
    //configOut.pin_data = I2S_DATA_OUT;
    //configOut.channels = 1;
    out.begin(configOut);

    // Setup sine wave
    //sineWave.setFrequency(500);
    //sineWave.begin(info, N_B4);
    //Serial.println("Started sine wave");
}

void AudioOut::Tick()
{
    copier.copy();
}