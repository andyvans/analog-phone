#include "AudioCapture.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"
#include "_Secrets.h"

AudioCapture::AudioCapture()
{
}

void AudioCapture::Setup()
{
}

void AudioCapture::Stop()
{
    if (copier != nullptr)
    {
        copier->end();
        delete copier;
        copier = nullptr;
    }
    if (in != nullptr)
    {
        in->end();
        delete in;
        in = nullptr;
    }
    if (out != nullptr)
    {
        out->end();
        delete out;
        out = nullptr;
    }

    if (infoFrom != nullptr)
    {
        delete infoFrom;
        infoFrom = nullptr;
    }
}

void AudioCapture::Start()
{
    /*
    Serial.println("Starting analog mic audio in");

    infoFrom = new AudioInfo(44100, 1, 16);

    // Setup audio input    
    auto analogStream = new AnalogAudioStream();
    in = analogStream;
    copier = new StreamCopy(*out, *analogStream);

    auto configIn = analogStream->defaultConfig(RX_MODE);
    configIn.copyFrom(*infoFrom);
    configIn.adc_pin = MIC_PIN;
    analogStream->begin(configIn);

    // start I2S output
    Serial.println("Starting I2S audio out");
    out = new I2SStream();
    auto configOut = out->defaultConfig(TX_MODE);
    configOut.copyFrom(*infoFrom);
    configOut.port_no = 1;
    //configOut.pin_bck = I2S_BCLK_OUT;
    //configOut.pin_ws = I2S_LRC_OUT;
    //configOut.pin_data = I2S_DATA_OUT;
    //configOut.channels = 1;
    out->begin(configOut);
    */
}

void AudioCapture::Tick()
{
    if (copier == nullptr) return;
    copier->copy();
}