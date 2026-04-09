#include "TextToAudioAzure.h"
#include "_Secrets.h"

#define AZURE_SPEECH_REGION "australiaeast"

TextToAudioAzure::TextToAudioAzure()
{
}

TextToAudioAzure::~TextToAudioAzure()
{
    Teardown();
}

void TextToAudioAzure::Setup()
{
    i2s = new I2SStream();
    auto configI2S = i2s->defaultConfig(TX_MODE);
    configI2S.sample_rate = 8000;
    configI2S.bits_per_sample = 16;
    configI2S.channels = 1;
    configI2S.pin_ws = I2S_LRC_OUT;
    configI2S.pin_bck = I2S_BCLK_OUT;
    configI2S.pin_data = I2S_DATA_OUT;
    i2s->begin(configI2S);

    urlStream = new URLStream(WIFI_SSID, WIFI_PASSWORD);
    urlStream->addRequestHeader("Ocp-Apim-Subscription-Key", AZURE_SPEECH_KEY);
    urlStream->addRequestHeader("X-Microsoft-OutputFormat", "raw-8khz-16bit-mono-pcm");
    urlStream->addRequestHeader(USER_AGENT, String(String("Arduino with Audiotools version:") + AUDIOTOOLS_VERSION).c_str());
}

void TextToAudioAzure::Play(const String& text)
{
    Serial.println("Playing text: " + text);

    const String language = "en-US";
    const String gender = "Female";
    const String voice = "en-US-JennyNeural";
    const String url = String("https://") + AZURE_SPEECH_REGION + ".tts.speech.microsoft.com/cognitiveservices/v1";
    const String ssml = "<speak version='1.0' xml:lang='" + language + "'><voice xml:lang='" + language
        + "' xml:gender='" + gender + "' name='" + voice + "'>" + text + "</voice></speak>";

    urlStream->begin(url.c_str(), "audio/wav", POST, "application/ssml+xml", ssml.c_str());

    copier = new StreamCopy(*i2s, *urlStream);
}

void TextToAudioAzure::Stop()
{
    if (copier != nullptr)
    {
        copier->end();
        delete copier;
        copier = nullptr;
    }
    if (urlStream != nullptr)
    {
        urlStream->end();
    }
}

void TextToAudioAzure::Teardown()
{
    Stop();
    if (urlStream != nullptr)
    {
        delete urlStream;
        urlStream = nullptr;
    }
    if (i2s != nullptr)
    {
        i2s->end();
        delete i2s;
        i2s = nullptr;
    }
}

void TextToAudioAzure::Tick()
{
    if (copier == nullptr) return;
    copier->copy();
}