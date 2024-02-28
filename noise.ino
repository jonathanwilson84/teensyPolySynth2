void noiseEditScreenParams() {

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[28]);
encoder2.write(parameters[29]);
encoder3.write(parameters[30]);
encoder4.write(parameters[31]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[28] = map(encoderReadings[0], 0, 100, 0, 100);
parameters[29] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[30] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[31] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }
float pinkNoise = parameters[28]/100.0f;
float whiteNoise = parameters[29]/100.0f;
pink1.amplitude(pinkNoise/3.0);
white1.amplitude(whiteNoise/4.0);


}
///////////////////////////////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void noiseAdsrScreenParams(){
constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[20]/30);
encoder2.write(parameters[21]/40);
encoder3.write(parameters[22]);
encoder4.write(parameters[23]/60);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[20] = map(encoderReadings[0], 0, 100, 5, 3000);
parameters[21] = map(encoderReadings[1], 0, 100, 0, 4000);
parameters[22] = map(encoderReadings[2], 0, 100, 0, 100);
parameters[23] = map(encoderReadings[3], 0, 100, 0, 6000);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }

float noiseSustain1 = parameters[22]/100.0f;


noiseEnvelope.attack(parameters[20]);
noiseEnvelope.decay(parameters[21]);
noiseEnvelope.sustain(noiseSustain1);
noiseEnvelope.release(parameters[23]);
 
}

void noiseFilterScreenParams(){

 constrainEncoders();

    if (screenChanged) {
encoder1.write(parameters[24]/170);
encoder2.write(parameters[25]);
encoder3.write(parameters[26]*10);
encoder4.write(parameters[27]);

for (int i = 0; i < 4; i++) {
previousEncoderReadings[i] = encoderReadings[i];
}
}
screenChanged = false; // Reset flag after updating
for (int i = 0; i < 4; i++) {
        if (encoderReadings[i] != previousEncoderReadings[i]) {
           
parameters[24] = map(encoderReadings[0], 0, 100, 0, 17000);
parameters[25] = map(encoderReadings[1], 0, 100, 0, 100);
parameters[26] = map(encoderReadings[2], 0, 100, 0, 1000);
parameters[27] = map(encoderReadings[3], 0, 100, 0, 100);

        }

        // Update the previous reading for next comparison
        previousEncoderReadings[i] = encoderReadings[i];
    }
float noiseFilterResonance = parameters[25]/100.0f;
float noiseFilterLfoAmount = parameters[27]/100.f;
float noiseLfoSpeed = parameters[26]/100.0f;


noiseFilter.frequency(parameters[24]);
noiseFilter.resonance(noiseFilterResonance);

noiseFilterLfo.frequency(noiseLfoSpeed);
noiseFilterLfo.amplitude(noiseFilterLfoAmount);
}

