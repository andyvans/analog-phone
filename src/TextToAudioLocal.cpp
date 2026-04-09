#include "TextToAudioLocal.h"

TextToAudioLocal::TextToAudioLocal()
{
}

TextToAudioLocal::~TextToAudioLocal()
{
    Teardown();
}

void TextToAudioLocal::Setup()
{
    i2s = new I2SStream();
    auto cfg = i2s->defaultConfig(TX_MODE);
    cfg.sample_rate = 22050;
    cfg.bits_per_sample = 16;
    cfg.channels = 1;
    cfg.pin_ws = I2S_LRC_OUT;
    cfg.pin_bck = I2S_BCLK_OUT;
    cfg.pin_data = I2S_DATA_OUT;
    i2s->begin(cfg);

    espeak = new ESpeak(*i2s);
    espeak->setOutputEndCallback([](){});
    if (!espeak->begin()) {
        Serial.println("ERROR: espeak initialization failed!");
    }
}

void TextToAudioLocal::Play(const String& text)
{
    Serial.println("Playing text (local): " + text);
    speaking = true;
    espeak->say(text.c_str());
    speaking = false;
}

void TextToAudioLocal::Stop()
{
    // espeak synthesis is synchronous; nothing to cancel mid-stream
}

void TextToAudioLocal::Teardown()
{
    Stop();
    if (espeak != nullptr)
    {
        delete espeak;
        espeak = nullptr;
    }
    if (i2s != nullptr)
    {
        i2s->end();
        delete i2s;
        i2s = nullptr;
    }
}

void TextToAudioLocal::Tick()
{
    // espeak::say() is blocking, so no incremental copying needed
}
