#include <Bounce.h>
#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <Encoder.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include <Fonts/Picopixel.h>

#include "waveforms.h"

#define POLY_COUNT 8

//SCREEN SETUP STUFF/////////////////////////////////////////
#define OLED_CS 35
#define OLED_DC 34
#define OLED_RESET 35
Adafruit_SSD1305 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS, 7000000UL);
struct waveform_modulator {
  AudioSynthWaveformModulated osc1;
  AudioEffectEnvelope      osc1Envelope;
  AudioFilterLadder   osc1Filter;
  AudioEffectEnvelope      filterEnvelope;
  AudioSynthWaveformDc filterEnvelopeTrigger;
  AudioEffectMultiply filterMultiply;
  AudioMixer4 filterEnvelopeMixer;
AudioSynthWaveform        ModOsc1Dc;
  AudioEffectEnvelope       osc1ModEnvelope;
  int note;
  boolean in_use;
  unsigned long note_start_time;
};

waveform_modulator poly_waveforms[POLY_COUNT];




//AUDIO OBJECT SETUP///////////////////////////////////////////
AudioEffectFreeverb      freeverb1; 
AudioMixer4               reverbMixer;
AudioMixer4              noiseMixer1;

AudioMixer4               voiceMixer1;
AudioMixer4               voiceMixer2;

AudioMixer4              voiceMixer;
AudioMixer4              mixerBitcrushOsc1;
AudioEffectBitcrusher    bitcrushOsc1;

AudioFilterLadder   noiseFilter; 
  AudioEffectEnvelope     noiseEnvelope;  


  AudioSynthNoisePink      pink1; 
  AudioSynthNoiseWhite      white1; 

AudioSynthWaveformDc        osc1FilterCutoffInput;

AudioSynthWaveform        noiseFilterLfo;


AudioOutputI2S           i2s1;
AudioSynthWaveform        lfo;



AudioAmplifier        amp1;  
//AUDIO ROUTING SETUP////////////////////////////////////////////////////////


// Connections for Voice 1

// Connections for Voice 1

AudioConnection p1(poly_waveforms[0].osc1, 0, poly_waveforms[0].osc1Filter, 0);
AudioConnection p2(poly_waveforms[1].osc1, 0, poly_waveforms[1].osc1Filter, 0);
AudioConnection p3(poly_waveforms[2].osc1, 0, poly_waveforms[2].osc1Filter, 0);
AudioConnection p4(poly_waveforms[3].osc1, 0, poly_waveforms[3].osc1Filter, 0);
AudioConnection p5(poly_waveforms[4].osc1, 0, poly_waveforms[4].osc1Filter, 0);
AudioConnection p6(poly_waveforms[5].osc1, 0, poly_waveforms[5].osc1Filter, 0);
AudioConnection p7(poly_waveforms[6].osc1, 0, poly_waveforms[6].osc1Filter, 0);
AudioConnection p8(poly_waveforms[7].osc1, 0, poly_waveforms[7].osc1Filter, 0);

AudioConnection p9(poly_waveforms[0].filterEnvelopeTrigger, 0, poly_waveforms[0].filterEnvelope, 0);
AudioConnection p10(poly_waveforms[1].filterEnvelopeTrigger, 0, poly_waveforms[1].filterEnvelope, 0);
AudioConnection p11(poly_waveforms[2].filterEnvelopeTrigger, 0, poly_waveforms[2].filterEnvelope, 0);
AudioConnection p12(poly_waveforms[3].filterEnvelopeTrigger, 0, poly_waveforms[3].filterEnvelope, 0);
AudioConnection p13(poly_waveforms[4].filterEnvelopeTrigger, 0, poly_waveforms[4].filterEnvelope, 0);
AudioConnection p14(poly_waveforms[5].filterEnvelopeTrigger, 0, poly_waveforms[5].filterEnvelope, 0);
AudioConnection p15(poly_waveforms[6].filterEnvelopeTrigger, 0, poly_waveforms[6].filterEnvelope, 0);
AudioConnection p16(poly_waveforms[7].filterEnvelopeTrigger, 0, poly_waveforms[7].filterEnvelope, 0);

AudioConnection p17(poly_waveforms[0].filterEnvelope, 0, poly_waveforms[0].filterEnvelopeMixer, 0);
AudioConnection p18(poly_waveforms[1].filterEnvelope, 0, poly_waveforms[1].filterEnvelopeMixer, 0);
AudioConnection p19(poly_waveforms[2].filterEnvelope, 0, poly_waveforms[2].filterEnvelopeMixer, 0);
AudioConnection p20(poly_waveforms[3].filterEnvelope, 0, poly_waveforms[3].filterEnvelopeMixer, 0);
AudioConnection p21(poly_waveforms[4].filterEnvelope, 0, poly_waveforms[4].filterEnvelopeMixer, 0);
AudioConnection p22(poly_waveforms[5].filterEnvelope, 0, poly_waveforms[5].filterEnvelopeMixer, 0);
AudioConnection p23(poly_waveforms[6].filterEnvelope, 0, poly_waveforms[6].filterEnvelopeMixer, 0);
AudioConnection p24(poly_waveforms[7].filterEnvelope, 0, poly_waveforms[7].filterEnvelopeMixer, 0);

AudioConnection p25(poly_waveforms[0].filterEnvelope, 0, poly_waveforms[0].filterMultiply, 1);
AudioConnection p26(poly_waveforms[1].filterEnvelope, 0, poly_waveforms[1].filterMultiply, 1);
AudioConnection p27(poly_waveforms[2].filterEnvelope, 0, poly_waveforms[2].filterMultiply, 1);
AudioConnection p28(poly_waveforms[3].filterEnvelope, 0, poly_waveforms[3].filterMultiply, 1);
AudioConnection p29(poly_waveforms[4].filterEnvelope, 0, poly_waveforms[4].filterMultiply, 1);
AudioConnection p30(poly_waveforms[5].filterEnvelope, 0, poly_waveforms[5].filterMultiply, 1);
AudioConnection p31(poly_waveforms[6].filterEnvelope, 0, poly_waveforms[6].filterMultiply, 1);
AudioConnection p32(poly_waveforms[7].filterEnvelope, 0, poly_waveforms[7].filterMultiply, 1);

AudioConnection p33(poly_waveforms[0].filterMultiply, 0, poly_waveforms[0].filterEnvelopeMixer, 1);
AudioConnection p34(poly_waveforms[1].filterMultiply, 0, poly_waveforms[1].filterEnvelopeMixer, 1);
AudioConnection p35(poly_waveforms[2].filterMultiply, 0, poly_waveforms[2].filterEnvelopeMixer, 1);
AudioConnection p36(poly_waveforms[3].filterMultiply, 0, poly_waveforms[3].filterEnvelopeMixer, 1);
AudioConnection p37(poly_waveforms[4].filterMultiply, 0, poly_waveforms[4].filterEnvelopeMixer, 1);
AudioConnection p38(poly_waveforms[5].filterMultiply, 0, poly_waveforms[5].filterEnvelopeMixer, 1);
AudioConnection p39(poly_waveforms[6].filterMultiply, 0, poly_waveforms[6].filterEnvelopeMixer, 1);
AudioConnection p40(poly_waveforms[7].filterMultiply, 0, poly_waveforms[7].filterEnvelopeMixer, 1);

AudioConnection p41(poly_waveforms[0].filterEnvelopeMixer, 0, poly_waveforms[0].osc1Filter, 1);
AudioConnection p42(poly_waveforms[1].filterEnvelopeMixer, 0, poly_waveforms[1].osc1Filter, 1);
AudioConnection p43(poly_waveforms[2].filterEnvelopeMixer, 0, poly_waveforms[2].osc1Filter, 1);
AudioConnection p44(poly_waveforms[3].filterEnvelopeMixer, 0, poly_waveforms[3].osc1Filter, 1);
AudioConnection p45(poly_waveforms[4].filterEnvelopeMixer, 0, poly_waveforms[4].osc1Filter, 1);
AudioConnection p46(poly_waveforms[5].filterEnvelopeMixer, 0, poly_waveforms[5].osc1Filter, 1);
AudioConnection p47(poly_waveforms[6].filterEnvelopeMixer, 0, poly_waveforms[6].osc1Filter, 1);
AudioConnection p48(poly_waveforms[7].filterEnvelopeMixer, 0, poly_waveforms[7].osc1Filter, 1);




AudioConnection p49(poly_waveforms[0].osc1Filter, 0, poly_waveforms[0].osc1Envelope, 0);
AudioConnection p50(poly_waveforms[1].osc1Filter, 0, poly_waveforms[1].osc1Envelope, 0);
AudioConnection p51(poly_waveforms[2].osc1Filter, 0, poly_waveforms[2].osc1Envelope, 0);
AudioConnection p52(poly_waveforms[3].osc1Filter, 0, poly_waveforms[3].osc1Envelope, 0);
AudioConnection p53(poly_waveforms[4].osc1Filter, 0, poly_waveforms[4].osc1Envelope, 0);
AudioConnection p54(poly_waveforms[5].osc1Filter, 0, poly_waveforms[5].osc1Envelope, 0);
AudioConnection p55(poly_waveforms[6].osc1Filter, 0, poly_waveforms[6].osc1Envelope, 0);
AudioConnection p56(poly_waveforms[7].osc1Filter, 0, poly_waveforms[7].osc1Envelope, 0);


AudioConnection p57(poly_waveforms[0].osc1Envelope, 0, voiceMixer1, 0);
AudioConnection p58(poly_waveforms[1].osc1Envelope, 0, voiceMixer1, 1);
AudioConnection p59(poly_waveforms[2].osc1Envelope, 0, voiceMixer1, 2);
AudioConnection p60(poly_waveforms[3].osc1Envelope, 0, voiceMixer1, 3);
AudioConnection p61(poly_waveforms[4].osc1Envelope, 0, voiceMixer2, 0);
AudioConnection p62(poly_waveforms[5].osc1Envelope, 0, voiceMixer2, 1);
AudioConnection p63(poly_waveforms[6].osc1Envelope, 0, voiceMixer2, 2);
AudioConnection p64(poly_waveforms[7].osc1Envelope, 0, voiceMixer2, 3);


AudioConnection p65(voiceMixer1, 0, voiceMixer, 0);
AudioConnection p66(voiceMixer2, 0, voiceMixer, 1);
AudioConnection p67(noiseFilter, 0, voiceMixer, 2);



AudioConnection p68(voiceMixer, 0, mixerBitcrushOsc1, 0);
AudioConnection p69(voiceMixer, 0, bitcrushOsc1, 0);
AudioConnection p70(bitcrushOsc1, 0, mixerBitcrushOsc1, 1);

AudioConnection p71(pink1, 0, noiseMixer1, 0);
AudioConnection p72(white1, 0, noiseMixer1, 1);
AudioConnection p73(noiseMixer1, 0, noiseEnvelope, 0);
AudioConnection p74(noiseEnvelope, 0, noiseFilter, 0);
AudioConnection p75(noiseFilterLfo, 0, noiseFilter, 1);

AudioConnection p77(lfo, 0, poly_waveforms[0].filterMultiply, 0);
AudioConnection p78(lfo, 0, poly_waveforms[1].filterMultiply, 0);
AudioConnection p79(lfo, 0, poly_waveforms[2].filterMultiply, 0);
AudioConnection p80(lfo, 0, poly_waveforms[3].filterMultiply, 0);
AudioConnection p81(lfo, 0, poly_waveforms[4].filterMultiply, 0);
AudioConnection p82(lfo, 0, poly_waveforms[5].filterMultiply, 0);
AudioConnection p83(lfo, 0, poly_waveforms[6].filterMultiply, 0);
AudioConnection p84(lfo, 0, poly_waveforms[7].filterMultiply, 0);


AudioConnection p85(mixerBitcrushOsc1, 0, freeverb1, 0);
AudioConnection p86(mixerBitcrushOsc1, 0, reverbMixer, 0);
AudioConnection p87(freeverb1, 0, reverbMixer, 1);

AudioConnection p88(reverbMixer, 0, amp1, 0);

AudioConnection p89(amp1, 0, i2s1, 0);
AudioConnection p90(amp1, 0, i2s1, 1);
AudioConnection p91(poly_waveforms[0].osc1ModEnvelope, 0, poly_waveforms[0].osc1, 0);
AudioConnection p92(poly_waveforms[1].osc1ModEnvelope, 0, poly_waveforms[1].osc1, 0);
AudioConnection p93(poly_waveforms[2].osc1ModEnvelope, 0, poly_waveforms[2].osc1, 0);
AudioConnection p94(poly_waveforms[3].osc1ModEnvelope, 0, poly_waveforms[3].osc1, 0);
AudioConnection p95(poly_waveforms[4].osc1ModEnvelope, 0, poly_waveforms[4].osc1, 0);
AudioConnection p96(poly_waveforms[5].osc1ModEnvelope, 0, poly_waveforms[5].osc1, 0);
AudioConnection p97(poly_waveforms[6].osc1ModEnvelope, 0, poly_waveforms[6].osc1, 0);
AudioConnection p98(poly_waveforms[7].osc1ModEnvelope, 0, poly_waveforms[7].osc1, 0);

AudioConnection p99(poly_waveforms[0].ModOsc1Dc, 0, poly_waveforms[0].osc1ModEnvelope, 0);
AudioConnection p100(poly_waveforms[1].ModOsc1Dc, 0, poly_waveforms[1].osc1ModEnvelope, 0);
AudioConnection p101(poly_waveforms[2].ModOsc1Dc, 0, poly_waveforms[2].osc1ModEnvelope, 0);
AudioConnection p102(poly_waveforms[3].ModOsc1Dc, 0, poly_waveforms[3].osc1ModEnvelope, 0);
AudioConnection p103(poly_waveforms[4].ModOsc1Dc, 0, poly_waveforms[4].osc1ModEnvelope, 0);
AudioConnection p104(poly_waveforms[5].ModOsc1Dc, 0, poly_waveforms[5].osc1ModEnvelope, 0);
AudioConnection p105(poly_waveforms[6].ModOsc1Dc, 0, poly_waveforms[6].osc1ModEnvelope, 0);
AudioConnection p106(poly_waveforms[7].ModOsc1Dc, 0, poly_waveforms[7].osc1ModEnvelope, 0);

AudioControlSGTL5000                sgtl5000_1;

int encoderReadings[4];
int previousEncoderReadings[4];


//MODE SETUP///////////////////////////////////////////////////////////////////////
enum Mode {
oscMode,
noiseMode,
patchMode
};

Mode currentMode = oscMode;
//SCREEN SETUP////////////////////////////////////////////////////////////////////

enum screen {
EditScreen,
AdsrScreen,
FilterScreen,
FilterEnvelopeScreen,
ModScreen,
ModEnvelopeScreen,
FxScreen,
noiseEditScreen,
noiseAdsrScreen,
noiseFilterScreen,
patchScreen
};

screen currentScreen = EditScreen;

bool screenChanged = false;
bool modeChanged = false;

//////////OSC1///////////////////////////////////////////////////////////////////////////////////////////////
const char* osc1EditLabels[] = {"WvTp", "VOL", "Dtune", "NOISE"};
const char* osc1AdsrLabels[] = {"Attk", "Dcky", "Sstn", "Rlse"};
const char* osc1FilterLabels[] = {"CtOff", "Res", "LFOSpd", "LFOAmt"};
const char* osc1FilterEnvelopeLabels[] = {"Attk", "Dcky", "Sstn", "Rlse"};
const char* osc1ModLabels[] = {"PhsAmt", "PhsSpd", "PhsDpth", "xx"};
const char* osc1ModEnvelopeLabels[] = {"Attk", "Dcky", "Sstn", "Rlse"};
const char* osc1FxLabels[] = {"BtCrMx", "BtCrDpt", "BtCrSmp", "xx"};

const char* osc1EditScreenHeading = "PROPERTIES";
const char* osc1AdsrScreenHeading = "OSC ADSR";
const char* osc1FilterScreenHeading = "OSC FILTER";
const char* osc1FilterEnvelopeScreenHeading = "OSC FILTER ADSR";
const char* osc1ModScreenHeading = "OSC PHASE MOD";
const char* osc1ModEnvelopeScreenHeading = "OSC PHASE MOD ADSR";
const char* osc1FxScreenHeading = "OSC FX";

const char* noiseEditLabels[] = {"PNK", "WHT", "XX", "XX"};
const char* noiseAdsrLabels[] = {"Attk", "Dcky", "Sstn", "Rlse"};
const char* noiseFilterLabels[] = {"CtOff", "Res", "LFOSpd", "LFOAmt"};
const char* noiseAdsrScreenHeading = "NOISE ADSR";

const char* noiseEditScreenHeading = "NOISE PROPERTIES";

const char* noiseFilterScreenHeading = "NOISE FILTER";





//FUNCTION DECLARATIONS///////////////////////////////////////////////////////
void applyAllParameters();


void osc1EditScreenParams();
void osc1FilterScreenParams();
void osc1AdsrScreenParams();
void osc1ModScreenParams();
void osc1ModEnvelopeScreenParams();
void osc1FxScreenParams();
void noiseAdsrScreenParams();
void noiseEditScreenParams();
void noiseFilterScreenParams();

void osc1FilterEnvelopeScreenParams();



void savePatch();
void loadPatch();
void updateDisplay(const char** labels, const char* heading);
void showTemporaryMessage(String message);
void displayPatches(int currentPatch);

void convertFloatToInt(const float* sourceArray, unsigned int* destArray, int arraySize);
void savePatch(const float* array, int arraySize, int patchIndex);
void unsignedIntToFloat(const unsigned int* sourceArray, float* destArray, int arraySize);
void loadPatch(int patchIndex, int arraySize);
void displayPatches(int currentPatch);
void patchScreenLogic();
void restoreDefaultParameters();
void constrainEncoders();


//PATCH SCREEN SETUP//////////////////////////////////////////////////////
unsigned long buttonPressStartTime;
bool isButtonPressed = false;
const unsigned long longPressDuration = 5000; // 5000 milliseconds = 5 seconds
String message = "";
unsigned long messageTime = 0;
const int messageDuration = 2000; // Message display duration in milliseconds
int topPatchIndex = 0; // Global variable to track the top patch index on the 
int currentPatch = 0; // Currently selected patch (0 - 12)

int parameterNumber = 44;
float parameters[44];
unsigned int parametersConverted[44];
unsigned int patchStorage[32][44];

const int totalPatchCount = 32;

//SD CARD SETUP////////////////////////////////////////////////////////////

const int chipSelect = BUILTIN_SDCARD;

//INPUT SETUP////////////////////////////////////////////////////////////////

Encoder encoder4(1, 2);
Encoder encoder3(5, 4);
Encoder encoder2(9, 8);
Encoder encoder1(12, 32);



Bounce enc1Button = Bounce(3, 5); 
Bounce enc2Button = Bounce(6, 5); 
Bounce enc3Button = Bounce(10, 5); 
Bounce enc4Button = Bounce(30, 5); 

Bounce screenButton1 = Bounce(37, 5);
Bounce screenButton2 = Bounce(38, 5);
Bounce screenButton3 = Bounce(22, 5);
Bounce screenButton4 = Bounce(29, 5);
Bounce screenButton5 = Bounce(28, 5);
Bounce screenButton6 = Bounce(39, 5);


Bounce etcButton1 = Bounce(14, 5);
Bounce etcButton2 = Bounce(15, 5);
Bounce etcButton3 = Bounce(16, 5);
Bounce etcButton4 = Bounce(17, 5);
Bounce etcButton5 = Bounce(18, 5);
Bounce etcButton6 = Bounce(19, 5);
Bounce etcButton7 = Bounce(24, 5);
Bounce etcButton8 = Bounce(25, 5);
Bounce etcButton9 = Bounce(26, 5);
Bounce etcButton10 = Bounce(27, 5);




int volumePot = A17;

//PHASEMOD SETUP/////////////////////////////////////////////////////

int osc1ModValue = 0;


//OSC TUNE MODE SETUP//////////////////////////////////////////////////



//MIDI SETUP//////////////////////////////////////////////////////////

MIDI_CREATE_DEFAULT_INSTANCE();

void OnNoteOn(byte channel, byte note, byte velocity);
void OnNoteOff(byte channel, byte note, byte velocity);


int midiNoteToFrequency(int note) {
  return 440.0 * pow(2.0, (note - 69.0) / 12.0);
}

void setup() {
Serial.begin(9600);
SD.begin(chipSelect);
 AudioMemory(100);
display.begin(0x3C);
display.clearDisplay();  
MIDI.begin(1); 
sgtl5000_1.enable();
sgtl5000_1.volume(1);
  MIDI.setHandleNoteOn(OnNoteOn);
  MIDI.setHandleNoteOff(OnNoteOff);


//INITIALIZE INPUTS///////////////////////////////////////////////
pinMode(3, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
pinMode(30, INPUT_PULLUP);

pinMode(16, INPUT_PULLUP);
pinMode(19, INPUT_PULLUP);
pinMode(26, INPUT_PULLUP);
pinMode(29, INPUT_PULLUP);

pinMode(14, INPUT_PULLUP);
pinMode(15, INPUT_PULLUP);
pinMode(17, INPUT_PULLUP);
pinMode(18, INPUT_PULLUP);
pinMode(24, INPUT_PULLUP);
pinMode(25, INPUT_PULLUP);
pinMode(27, INPUT_PULLUP);
pinMode(28, INPUT_PULLUP);

pinMode(1, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(32, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);

pinMode(22, INPUT_PULLUP);
pinMode(37, INPUT_PULLUP);
pinMode(38, INPUT_PULLUP);
pinMode(39, INPUT_PULLUP);

pinMode(volumePot, INPUT);

//INITIALIZE AUDIO OBJECTS///////////////////////////////////////////////
for (int voice = 0; voice < POLY_COUNT; voice++) {
    poly_waveforms[voice].osc1Envelope.attack(10);
    poly_waveforms[voice].osc1Envelope.decay(2000);
    poly_waveforms[voice].osc1Envelope.sustain(.5);
    poly_waveforms[voice].osc1Envelope.release(2000);

    poly_waveforms[voice].osc1.frequency(440); 
    poly_waveforms[voice].osc1.amplitude(.5);  
    poly_waveforms[voice].osc1.begin(WAVEFORM_SINE);  
    poly_waveforms[voice].osc1.phaseModulation(0);  
    poly_waveforms[voice].osc1.offset(0);

          poly_waveforms[voice].osc1Filter.frequency(10000);
          poly_waveforms[voice].osc1Filter.resonance(0);

  poly_waveforms[voice].filterEnvelope.attack(0);
  poly_waveforms[voice].filterEnvelope.decay(500);
  poly_waveforms[voice].filterEnvelope.sustain(.5);
  poly_waveforms[voice].filterEnvelope.release(500);

  poly_waveforms[voice].filterEnvelopeTrigger.amplitude(-1);
 poly_waveforms[voice].filterEnvelopeMixer.gain(0, 1);
 poly_waveforms[voice].filterEnvelopeMixer.gain(1, 0);

poly_waveforms[voice].ModOsc1Dc.frequency(440);
poly_waveforms[voice].ModOsc1Dc.amplitude(0);
poly_waveforms[voice].ModOsc1Dc.begin(WAVEFORM_SINE);

poly_waveforms[voice].osc1ModEnvelope.attack(0);
poly_waveforms[voice].osc1ModEnvelope.decay(0);
poly_waveforms[voice].osc1ModEnvelope.sustain(0);
poly_waveforms[voice].osc1ModEnvelope.release(0);
}

       pink1.amplitude(.2);  
        white1.amplitude(.2);
 noiseEnvelope.attack(10);
noiseEnvelope.decay(2000);
 noiseEnvelope.sustain(.5);
 noiseEnvelope.release(2000);
       noiseFilter.frequency(12000);
       noiseFilter.resonance(0);
    


freeverb1.roomsize(.5);
freeverb1.damping(.5);

lfo.frequency(0);
lfo.amplitude(1);
lfo.begin(WAVEFORM_SINE);
noiseFilterLfo.frequency(0);
noiseFilterLfo.amplitude(0);
noiseFilterLfo.begin(WAVEFORM_SINE);

reverbMixer.gain(0, 1);
reverbMixer.gain(1, 0);

freeverb1.roomsize(.5);
freeverb1.damping(.2);

voiceMixer1.gain(0, .2);
voiceMixer1.gain(1, .2);
voiceMixer1.gain(2, .2);
voiceMixer1.gain(3, .2);

voiceMixer2.gain(0, .2);
voiceMixer2.gain(1, .2);
voiceMixer2.gain(2, .2);
voiceMixer2.gain(3, .2);

voiceMixer.gain(0, .3);
voiceMixer.gain(1, .3);
voiceMixer.gain(2, .3);
voiceMixer.gain(3, 0);



amp1.gain(.9);
bitcrushOsc1.bits(12);
bitcrushOsc1.sampleRate(22000);

//INITIALIZE MIXERS/////////////////////////////////////////////////////////////

mixerBitcrushOsc1.gain(0, 1);
mixerBitcrushOsc1.gain(1, 0);


//FILL PARAMETERS ARRAY///////////////////////////////////////////////
restoreDefaultParameters();
applyAllParameters();

//SET SCREEN SELECTION FLAGS///////////////////////////////////////////


 screenChanged = true; 
 currentMode = oscMode;
 currentScreen = EditScreen;
}

void loop() {
  MIDI.read();


//VOLUME///////////////////////////////////////////////////////
//int volume = analogRead(volumePot);
//int volumeMapped = map(volume, 0, 1023, 0, 100);
//float volumeDivided = volumeMapped/100.00f;

//mixDownFilter.gain(0, volumeMapped);
//BUTTONS///////////////////////////////////////////////////
enc1Button.update();
enc2Button.update();
enc3Button.update();
enc4Button.update();


screenButton1.update();
screenButton2.update();
screenButton3.update();
screenButton4.update();
screenButton5.update();
screenButton6.update();

etcButton1.update();
etcButton2.update();
etcButton3.update();
etcButton4.update();
etcButton5.update();
etcButton6.update();
etcButton7.update();
etcButton8.update();
etcButton9.update();
etcButton10.update();



if (screenButton1.fallingEdge()) {
currentMode = oscMode;
currentScreen = EditScreen;
screenChanged = true;
}

if (screenButton2.fallingEdge()) {
currentMode = noiseMode;
currentScreen = noiseEditScreen;
screenChanged = true;
}

if (screenButton6.fallingEdge()) {
currentMode = patchMode;
currentScreen = patchScreen;

}

//BUTTON SCREEN LOGIC////////////////////////////////////////


if (etcButton1.fallingEdge() && currentMode == oscMode) { 
currentScreen = EditScreen;
 screenChanged = true; // Set flag to true when screen changes
}

if (etcButton2.fallingEdge() && currentMode == oscMode) { 
currentScreen = AdsrScreen;
 screenChanged = true; // Set flag to true when screen changes
}



if (etcButton3.fallingEdge() && currentMode == oscMode) { 
currentScreen = FilterScreen;
 screenChanged = true; // Set flag to true when screen changes
}

if (etcButton4.fallingEdge() && currentMode == oscMode) { 
currentScreen = FilterEnvelopeScreen;
 screenChanged = true; // Set flag to true when screen changes
}
if (etcButton5.fallingEdge() && currentMode == oscMode) { 
currentScreen = ModScreen;
 screenChanged = true; // Set flag to true when screen changes
}
if (etcButton6.fallingEdge() && currentMode == oscMode) { 
currentScreen = ModEnvelopeScreen;
 screenChanged = true; // Set flag to true when screen changes
}

if (etcButton7.risingEdge() && currentMode == oscMode) { 
  currentScreen = FxScreen;
 screenChanged = true; // Set flag to true when screen changes
}



if (etcButton1.fallingEdge() && currentMode == noiseMode) { 
currentScreen = noiseEditScreen;
 screenChanged = true; // Set flag to true when screen changes
}
if (etcButton2.fallingEdge() && currentMode == noiseMode) { 
currentScreen = noiseAdsrScreen;
 screenChanged = true; // Set flag to true when screen changes
}
if (etcButton3.fallingEdge() && currentMode == noiseMode) { 
currentScreen = noiseFilterScreen;
 screenChanged = true; // Set flag to true when screen changes
}


//ENCODER READING//////////////////////////////////////////////
encoderReadings[0] = encoder1.read();
encoderReadings[1] = encoder2.read();
encoderReadings[2] = encoder3.read();
encoderReadings[3] = encoder4.read();






//SCREEN CHANGING LOGIC/////////////////////////////////////////
const char** labels;
  const char* heading;

switch(currentScreen) {

   case EditScreen: {
osc1EditScreenParams();
updateDisplay(osc1EditLabels, osc1EditScreenHeading);
break;
}
   case AdsrScreen: {
osc1AdsrScreenParams();
updateDisplay(osc1AdsrLabels, osc1AdsrScreenHeading);
break;
}
 case FilterScreen: {
osc1FilterScreenParams();
updateDisplay(osc1FilterLabels, osc1FilterScreenHeading);
break;
 }
 case FilterEnvelopeScreen: {
  osc1FilterEnvelopeScreenParams();
  updateDisplay(osc1FilterEnvelopeLabels, osc1FilterEnvelopeScreenHeading);
  break;
 }
case ModScreen: {
osc1ModScreenParams();
updateDisplay(osc1ModLabels, osc1ModScreenHeading);
break;
 }
case ModEnvelopeScreen: {
osc1ModEnvelopeScreenParams();
updateDisplay(osc1ModEnvelopeLabels, osc1ModEnvelopeScreenHeading);
break;
 }


 case FxScreen: {
osc1FxScreenParams();
updateDisplay(osc1FxLabels, osc1FxScreenHeading);
break;
 }
   case noiseEditScreen: {
noiseEditScreenParams();
updateDisplay(noiseEditLabels, noiseEditScreenHeading);
break;
}
   case noiseAdsrScreen: {
noiseAdsrScreenParams();
updateDisplay(noiseAdsrLabels, noiseAdsrScreenHeading);
break;
}
 case noiseFilterScreen: {
noiseFilterScreenParams();
updateDisplay(noiseFilterLabels, noiseFilterScreenHeading);
break;
 }
  case patchScreen: {
patchScreenLogic();

break;
 }
}


applyAllParameters();

}

void OnNoteOn(byte channel, byte note, byte velocity) {
    int freq = static_cast<int>(440.0 * pow(2.0, (note - 69.0) / 12.0));
    int poly_index = -1;
    unsigned long oldest_note_start_time = ULONG_MAX;

    // Search for an unused slot or the oldest note
    for (int i = 0; i < POLY_COUNT; i++) {
        if (!poly_waveforms[i].in_use) {
            poly_index = i;
            break; // Found an unused slot, use it
        } else if (poly_waveforms[i].note_start_time < oldest_note_start_time) {
            oldest_note_start_time = poly_waveforms[i].note_start_time;
            poly_index = i; // Keep track of the oldest note
        }
    }

    if (poly_index != -1) {
        // Set the slot for the new note
        poly_waveforms[poly_index].in_use = true;
        poly_waveforms[poly_index].note = note;
        poly_waveforms[poly_index].note_start_time = millis();

        // Set frequencies for oscillators
        poly_waveforms[poly_index].osc1.frequency(freq);

        // Set amplitudes based on velocity (scaled appropriately)
        float amplitude = velocity / 127.0f; // Assuming velocity is a value between 0 and 127
        poly_waveforms[poly_index].osc1.amplitude(amplitude);
    poly_waveforms[poly_index].osc1ModEnvelope.noteOn();
    poly_waveforms[poly_index].ModOsc1Dc.frequency(freq * osc1ModValue);
        // Trigger envelopes for the voice
        poly_waveforms[poly_index].osc1Envelope.noteOn();
                poly_waveforms[poly_index].filterEnvelope.noteOn();
    }

    // Consider whether global envelopes should be triggered here or under specific conditions

    noiseEnvelope.noteOn();




}
void OnNoteOff(byte channel, byte note, byte velocity) {
    for (int i = 0; i < POLY_COUNT; i++) {
        if (poly_waveforms[i].note == note && poly_waveforms[i].in_use) {
            // Turn off the voice
            poly_waveforms[i].osc1Envelope.noteOff();
    poly_waveforms[i].filterEnvelope.noteOff();
        poly_waveforms[i].osc1ModEnvelope.noteOff();
            poly_waveforms[i].in_use = false;
             noiseEnvelope.noteOff();

            // Reset modulation frequencies or other per-note settings if needed
            // Example: poly_waveforms[i].ModOsc1Dc.frequency(defaultFrequency);
            break; // Note turned off, exit loop
        }
    }

    // Review whether these should be here or managed elsewhere
    // osc2ModEnvelope.noteOff();
    // osc1ModEnvelope.noteOff();
    // pwmModEnvelope.noteOff();
}

void restoreDefaultParameters() {
//OSC1 EDIT SCREEN
parameters[0] = 0;
parameters[1] = 50;
parameters[2] = 0;
parameters[3] = 0;
//OSC1 FILTER SCREEN
parameters[4] = 10000;
parameters[5] = 0;
parameters[6] = 0;
parameters[7] = 0;
// OSC1 MOD SCREEN
parameters[8] = 0;
parameters[9] = 0;
parameters[10] = 0;
parameters[11] = 0;
//OSC1 MOD ADSR
parameters[12] = 0;
parameters[13] = 300;
parameters[14] = .5;
parameters[15] = 500;
//OSC1 FX SCREN
parameters[16] = 0;
parameters[17] = 0;
parameters[18] = 0;
parameters[19] = 0;
//noise ADSR 
parameters[20] = 1;
parameters[21] = 500;
parameters[22] = 50;
parameters[23] = 500;
//noise filt
parameters[24] = 10000;
parameters[25] = 0;
parameters[26] = 0;
parameters[27] = 0;
//noise edit
parameters[28] = 25;
parameters[29] = 25;
parameters[30] = 0;
parameters[31] = 0;
//osc adsr
parameters[32] = 1;
parameters[33] = 800;
parameters[34] = 50;
parameters[35] = 800;
//osc filter envelope
parameters[36] = 0;
parameters[37] = 500;
parameters[38] = 50;
parameters[39] = 1000;
// PWM EDIT
parameters[40] = 0;
parameters[41] = 0;
parameters[42] = 0;
parameters[43] = 0;

}

  
void updateDisplay(const char** labels, const char* heading) {
    // Constants for layout
    const int elements = 4; // Number of elements to display
    const int yOffset = 22; // Initial y-offset for the first label
    const int labelWidth = 64; // Width reserved for labels

    // Clear the display buffer
    display.clearDisplay();
    display.setFont(&Picopixel);
    display.setTextSize(1); // Set text size to half
    display.setTextColor(WHITE); // Set text color

    // Display the heading
    display.setCursor(0, 8);
    display.println(heading);

    // Display labels and values in rows
    for (int i = 0; i < elements; i++) {
        // Calculate y position for label and value
        int y = yOffset + i * 12; // 12 pixels per row

        // Display label at the beginning of the row
        display.setCursor(0, y);
        display.print(labels[i]);

        // Display value aligned to the center of the screen
        display.setCursor(labelWidth, y); // Start from the center
        display.println(encoderReadings[i]);
    }

    // Update the display with new content
    display.display();
}





void showTemporaryMessage(String message) {
  display.clearDisplay();
  display.setCursor(0, display.height() / 2 / 2);
  display.println(message);
  display.display();
  delay(2000); // Display the message for 2 seconds
  displayPatches(currentPatch); // Redisplay the patches
}

void displayPatches(int currentPatch) {
    display.clearDisplay();
    display.setFont(&Picopixel);
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // Calculate the range of patches to display
    int halfScreen = 5; // Half the number of patches to display
    int startPatch = max(0, currentPatch - halfScreen);
    int endPatch = min(totalPatchCount - 1, currentPatch + halfScreen);

    // Adjust startPatch if we're at the end of the list to still show 7 items
    if (currentPatch > totalPatchCount - halfScreen - 1) {
        startPatch = max(0, totalPatchCount - 7);
    }

    for (int i = startPatch; i <= endPatch; i++) {
        int y = 10 + (i - startPatch) * 8; // Adjust y position for each patch
        if (i == currentPatch) {
            display.setCursor(0, y);
            display.print("> "); // Indicate the selected patch
        }
        display.setCursor(10, y);
        display.print("Patch" + String(i + 1)); // Display patch names
    }
    display.display();
}

void patchScreenLogic() {
    static unsigned long buttonPressStartTime = 0; // Time when the button was pressed
    const unsigned long holdDuration = 2000; // 2 seconds in milliseconds
    int encoderValue = encoderReadings[0] / 4; // Adjust this to match your encoder's 
       if (encoderValue < 0) {
      encoderValue = 0;
    }
    if (encoderValue > totalPatchCount) {
      encoderValue = totalPatchCount;
    }
    currentPatch = constrain(encoderValue, 0, totalPatchCount - 1);

    displayPatches(currentPatch); // Update the display with the current patch selection

    // Check if the button is pressed
    if (screenButton5.fallingEdge()) {
        buttonPressStartTime = millis(); // Record the time the button was pressed
    }

    // Check if the button is still pressed after 2 seconds
    if (screenButton5.read() == LOW && millis() - buttonPressStartTime >= holdDuration) {
        // Save to the selected patch
        savePatch(parameters, parameterNumber, currentPatch);
        showTemporaryMessage("Patch " + String(currentPatch + 1) + " Saved");
        buttonPressStartTime = 0; // Reset the start time
    }

    if (screenButton4.fallingEdge()) {
        // Load the selected patch
        loadPatch(currentPatch, parameterNumber);
        showTemporaryMessage("Patch " + String(currentPatch + 1) + " Loaded");
    }
}

void convertFloatToInt(const float* sourceArray, unsigned int* destArray, int arraySize) {
for (int i = 0; i < arraySize; i++) {
        destArray[i] = static_cast<unsigned int>(sourceArray[i]);
    }
}

void savePatch(const float* array, int arraySize, int patchIndex) {
applyAllParameters();

 for (int i = 0; i < arraySize; i++) {
        Serial.print("Parameter ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(array[i]);
    }

    unsigned int parametersConverted[44];
    convertFloatToInt(array, parametersConverted, arraySize);
 Serial.println("converting float to int");
    // Copy to patchStorage at specified patchIndex
    for (int i = 0; i < arraySize; i++) {
        patchStorage[patchIndex][i] = parametersConverted[i];
        Serial.println("parametersConverted:");
        Serial.println(parametersConverted[i]);
    }

    // Open the file on SD card
   File file = SD.open("gotterand.bin", FILE_WRITE);
if (file) {
    for (int i = 0; i < arraySize; i++) {
        file.write((byte*)&patchStorage[patchIndex][i], sizeof(unsigned int));
    }
    file.close();
    } else {
        // Error handling if the file didn't open
        Serial.println("Error opening patchBay.txt");
        
    }
}
void unsignedIntToFloat(const unsigned int* sourceArray, float* destArray, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        destArray[i] = static_cast<float>(sourceArray[i]);
    }
}

void loadPatch(int patchIndex, int arraySize) {


   File file = SD.open("gotterand.bin", FILE_READ);
    if (file) {
     file.seek(patchIndex * arraySize * sizeof(unsigned int));
        
        unsigned int tempStorage[arraySize];
        for (int i = 0; i < arraySize; i++) {
            file.read((byte*)&tempStorage[i], sizeof(unsigned int));
        }
        file.close();

            unsignedIntToFloat(tempStorage, parameters, arraySize);
            for (int i = 0; i < arraySize; i++) {
                Serial.print("Parameter ");
                Serial.print(i);
                Serial.print(": ");
                Serial.println(parameters[i]);
            }
        applyAllParameters();
            for (int i = 0; i < POLY_COUNT; i++) { 
poly_waveforms[i].osc1Envelope.noteOff();


}

    }

}
 void constrainEncoders() {
    if (encoderReadings[0] < 0) {
  encoder1.write(0);
}
if (encoderReadings[0] > 100) {
  encoder1.write(100);
}
encoderReadings[0] = constrain(encoderReadings[0], 0, 100);
if (encoderReadings[1] < 0) {
  encoder2.write(0);
}
if (encoderReadings[1] > 100) {
  encoder2.write(100);
}
encoderReadings[1] = constrain(encoderReadings[1], 0, 100);
if (encoderReadings[2] < 0) {
  encoder3.write(0);
}
if (encoderReadings[2] > 100) {
  encoder3.write(100);
}
encoderReadings[2] = constrain(encoderReadings[2], 0, 100);

if (encoderReadings[3] < 0) {
  encoder4.write(0);
}
if (encoderReadings[3] > 100) {
  encoder4.write(100);
}
encoderReadings[3] = constrain(encoderReadings[3], 0, 100);
 }




