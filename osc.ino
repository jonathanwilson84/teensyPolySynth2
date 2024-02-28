void osc1EditScreenParams() {

 constrainEncoders();

    if (screenChanged) {


encoder1.write(parameters[0]);
encoder2.write(parameters[1]);
encoder3.write(parameters[2]);
encoder4.write(parameters[3]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[0] = map(encoderReadings[0], 0, 100, 0, 100);
parameters[1] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[2] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[3] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }

//WAVETYPE SELECTION
float synthLevel = parameters[1]/100.0f;

float noiseLevel = parameters[3]/100.0f;

for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.amplitude(synthLevel);
    }
voiceMixer.gain(2, noiseLevel);

 if (parameters[0] >= 0 && parameters[0] < 5) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.begin(WAVEFORM_SINE);
    }
  }
  else if (parameters[0] >= 5 && parameters[0] < 10) {
    

        for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.begin(WAVEFORM_SQUARE);
    }
  }
  else if (parameters[0] >= 10 && parameters[0] < 15) {
   
        for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.begin(WAVEFORM_SAWTOOTH);
    }
  }
  else if (parameters[0] >= 15 && parameters[0] < 20) {
    

        for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.begin(WAVEFORM_TRIANGLE);
    }
  }
   else if (parameters[0] >= 20 && parameters[0] < 25) {
  
        for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1.begin(WAVEFORM_PULSE);
    }
}
  else if (parameters[0] >= 25 && parameters[0] < 30) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV1, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 30 && parameters[0] < 35) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV2, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 35 && parameters[0] < 40) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV3, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 40 && parameters[0] < 45) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV4, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 45 && parameters[0] < 50) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV5, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 50 && parameters[0] < 55) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(XWAV4, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 55 && parameters[0] < 60) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV7, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 60 && parameters[0] < 65) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV8, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 65 && parameters[0] < 70) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV9, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 70 && parameters[0] < 75) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(WAV10, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 75 && parameters[0] < 80) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(SQWAVE1, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 80 && parameters[0] < 85) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(SQWAVE2, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 85 && parameters[0] < 90) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(XWAV1, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] >= 90 && parameters[0] < 95) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(XWAV2, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}
  else if (parameters[0] > 95) {
    for (int voice = 0; voice < POLY_COUNT; voice++) {
         poly_waveforms[voice].osc1.arbitraryWaveform(XWAV3, 172.0);
        poly_waveforms[voice].osc1.begin(WAVEFORM_ARBITRARY);
    }
}

 }



///////////////////////////////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void osc1AdsrScreenParams(){
constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[32]/30);
encoder2.write(parameters[33]/40);
encoder3.write(parameters[34]);
encoder4.write(parameters[35]/60);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[32] = map(encoderReadings[0], 0, 100, 5, 3000);
parameters[33] = map(encoderReadings[1], 0, 100, 0, 4000);
parameters[34] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[35] = map(encoderReadings[3], 0, 100, 0, 6000);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }

float osc1Sustain1 = parameters[34]/100.0f;


for (int voice = 0; voice < POLY_COUNT; voice++) {
     poly_waveforms[voice].osc1Envelope.attack(parameters[32]);
poly_waveforms[voice].osc1Envelope.decay(parameters[33]);
poly_waveforms[voice].osc1Envelope.sustain(osc1Sustain1);
poly_waveforms[voice].osc1Envelope.release(parameters[35]);
}
}

void osc1FilterScreenParams(){

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[4]/150);
encoder2.write(parameters[5]);
encoder3.write(parameters[6]*2);
encoder4.write(parameters[7]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[4] = map(encoderReadings[0], 0, 100, 0, 15000);
parameters[5] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[6] = map(encoderReadings[2], 0, 100, 0, 50);
parameters[7] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }
float osc1FilterResonance = parameters[5]/100.0f;
float osc1FilterLfoAmount = parameters[7]/100.f;


for (int voice = 0; voice < POLY_COUNT; voice++) {
poly_waveforms[voice].osc1Filter.resonance(osc1FilterResonance);
poly_waveforms[voice].osc1Filter.frequency(parameters[4]);
poly_waveforms[voice].filterEnvelopeMixer.gain(0, 1- osc1FilterLfoAmount);
 poly_waveforms[voice].filterEnvelopeMixer.gain(1, osc1FilterLfoAmount);
}

lfo.frequency(parameters[6]);
lfo.amplitude(1);


}
void osc1FilterEnvelopeScreenParams(){

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[36]/20);
encoder2.write(parameters[37]/50);
encoder3.write(parameters[38]);
encoder4.write(parameters[39]/50);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[36] = map(encoderReadings[0], 0, 100, 0, 2000);
parameters[37] = map(encoderReadings[1], 0, 100, 0, 5000);
parameters[38] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[39] = map(encoderReadings[3], 0, 100, 0, 5000);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }
float filterEnvelopeSustain = parameters[38]/100.0f;

for (int voice = 0; voice < POLY_COUNT; voice++) {
poly_waveforms[voice].filterEnvelope.attack(parameters[36]);
poly_waveforms[voice].filterEnvelope.decay(parameters[37]);
poly_waveforms[voice].filterEnvelope.sustain(filterEnvelopeSustain);
poly_waveforms[voice].filterEnvelope.release(parameters[39]);
}


}

////////////////////////////OSC1 MOD SCREEN&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void osc1ModScreenParams() {

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[8]);
encoder2.write(parameters[9]);
encoder3.write(parameters[10]/90);
encoder4.write(parameters[11]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[8] = map(encoderReadings[0], 0, 100, 0, 100);
parameters[9] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[10] = map(encoderReadings[2], 0, 100, 0, 9000);
parameters[11] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }

float osc1PhaseAmount =  parameters[8]/100.0F;

for (int voice = 0; voice < POLY_COUNT; voice++) {
 poly_waveforms[voice].osc1.phaseModulation(parameters[10]);
poly_waveforms[voice].ModOsc1Dc.amplitude(osc1PhaseAmount);
}



if (parameters[9] >= 0 && parameters[9] < 10) {
osc1ModValue = 1;
}
if (parameters[9] >= 10 && parameters[9] < 20) {
osc1ModValue = 2;
}
if (parameters[9] >= 20 && parameters[9] < 30) {
osc1ModValue = 3;
}
if (parameters[9] >= 30 && parameters[9] < 40) {
osc1ModValue = 4;
}
if (parameters[9] >= 40 && parameters[9] < 50) {
osc1ModValue = 5;
}
if (parameters[9] >= 50 && parameters[9] < 60) {
osc1ModValue = 6;
}
if (parameters[9] >= 60 && parameters[9] < 70) {
osc1ModValue = 7;
}
if (parameters[9] >= 70 && parameters[9] < 80) {
osc1ModValue = 8;
}
if (parameters[9] >= 80 && parameters[9] < 90) {
osc1ModValue = 9;
}
if (parameters[9] >= 90 && parameters[9] <= 100) {
osc1ModValue = 10;
}
}

void osc1ModEnvelopeScreenParams(){
constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[12]/30);
encoder2.write(parameters[13]/40);
encoder3.write(parameters[14]);
encoder4.write(parameters[15]/60);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[12] = map(encoderReadings[0], 0, 100, 5, 3000);
parameters[13] = map(encoderReadings[1], 0, 100, 0, 4000);
parameters[14] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[15] = map(encoderReadings[3], 0, 100, 0, 6000);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }

float osc1ModSustain = parameters[14]/100.0f;



for (int voice = 0; voice < POLY_COUNT; voice++) {
poly_waveforms[voice].osc1ModEnvelope.attack(parameters[12]);  
poly_waveforms[voice].osc1ModEnvelope.decay(parameters[13]);  
poly_waveforms[voice].osc1ModEnvelope.sustain(osc1ModSustain);  
poly_waveforms[voice].osc1ModEnvelope.release(parameters[15]);  
}

}

void osc1FxScreenParams(){

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[16]);
encoder2.write(parameters[17]);
encoder3.write(parameters[18]);
encoder4.write(parameters[19]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[16] = map(encoderReadings[0], 0, 100, 0, 100);
parameters[17] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[18] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[19] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }
float reverbAmount = parameters[16]/100.0f;
float reverbRoomSize = parameters[17]/100.0f;

reverbMixer.gain(0, 1 - reverbAmount);
reverbMixer.gain(1, reverbAmount);
freeverb1.roomsize(reverbRoomSize);

float osc1BitcrushAmount = parameters[18]/100.0f;
float osc1BitcrushDepth = parameters[19];

bitcrushOsc1.bits(osc1BitcrushDepth);
mixerBitcrushOsc1.gain(0, 1 - osc1BitcrushAmount);
mixerBitcrushOsc1.gain(1, osc1BitcrushAmount);


}


