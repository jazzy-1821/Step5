Jasmine Richardson

Piano Synthesizer works by playing piano samples found on the class website called Complete Piano.

The component uses:

PianoInstrument, PianoInstrumentFactory, Waveplayer, and Synthesizer

The score file indicates what measure, beat, duration the note is played (in seconds), pedal effect is indicated by pressed or released. Dynamics are implemented by the velocity in the score depending on how fast the piano key is struck the louder the note will play and vice versa when it is played slower. For advanced dynamics I found a softer sounding piano string getting struck wave file and a louder piano string getting struck wave file and implemented an Interpolating function to interpolate between the two files. On the score it should say advanceDynamic = "struck" and that is when the interpolating should happen. Lastly, it gets the note that should play.

After the Pianofactory gets all of the attributes, it will create a new PianoInstrument and pass any persistent variables to it. PianoInstrument handles the actual notes that are being played. First load the note sample and creating the initial wave that will eventually be passed to WavePlayer. The Envelope function which I had the help from ChatGPT and googling to help me come up with a way to implements an ADRS envelope. Once all changes have been accounted for, the wave is generated in the WavePlayer class. 

Score File:

pianoTestScore.score

<?xml version="1.0" encoding="utf-8"?>
<score bpm="120" beatspermeasure="4">
        <instrument instrument="PianoInstrument">
    		<note measure="1" beat="1" duration="3" velocity="35" note="CompletePiano/E6s.wav"/>
		<note measure="1" beat="1" duration="0.5" note="CompletePiano/E6s.wav"/>
		<note measure="1" beat="3.5" pedal="pressed" note="CompletePiano/C6s.wav"/>
		<note measure="2" beat="1" pedal="released" note="CompletePiano/E6s.wav"/>
		<note measure="2" beat="2" note="CompletePiano/E6s.wav"/>
		<note measure="2" beat="3" velocity="60" note="CompletePiano/E6s.wav"/>
		<note measure="2" beat="4" note="CompletePiano/A2s.wav"/>
		<note measure="3" beat="1" velocity="90" note="CompletePiano/A2s.wav"/>
		<note measure="3" beat="2.5" duration="2.5" velocity="127" advanceDynamic="struck" note="CompletePiano/D6s.wav"/>
		<note measure="3" beat="3" note="CompletePiano/E3s.wav"/>
		<note measure="3" beat="1"  note="CompletePiano/A4s.wav"/>
		<note measure="4" beat="1" velocity="90" note="CompletePiano/A2s.wav"/>
		<note measure="4" beat="1" velocity="90" note="CompletePiano/C2s.wav"/>
		<note measure="4" beat="1" velocity="90" note="CompletePiano/E2s.wav"/>
		<note measure="5" beat="2.5" duration="2.5" velocity="127" note="CompletePiano/A2s.wav"/>
		<note measure="5" beat="3" advanceDynamic="struck" note="CompletePiano/A2s.wav"/>
		<note measure="5" beat="1" velocity="40" note="CompletePiano/A2s.wav"/>
		<note measure="5" beat="2.5" duration="2.5" velocity="127" note="CompletePiano/A2s.wav"/>
		</instrument></score>

twinkle_twinkle_little_star_score.score

<?xml version="1.0" encoding="utf-8"?>
<score bpm="60" beatspermeasure="4">
    <instrument instrument="PianoInstrument">
        <note measure="1" beat="1" duration="0.5" velocity="80" note="CompletePiano/C4s.wav"/>
        <note measure="1" beat="1.5" duration="0.5" note="CompletePiano/C4s.wav"/>
        <note measure="1" beat="2" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="1" beat="2.5" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="1" beat="3" duration="0.5" note="CompletePiano/A4s.wav"/>
        <note measure="1" beat="3.5" duration="0.5" note="CompletePiano/A4s.wav"/>
        <note measure="1" beat="4" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="2" beat="1" duration="0.5" velocity="80" note="CompletePiano/F4s.wav"/>
        <note measure="2" beat="1.5" duration="0.5" note="CompletePiano/F4s.wav"/>
        <note measure="2" beat="2" duration="0.5" note="CompletePiano/E4s.wav"/>
        <note measure="2" beat="2.5" duration="0.5" note="CompletePiano/E4s.wav"/>
        <note measure="2" beat="3" duration="0.5" note="CompletePiano/D4s.wav"/>
        <note measure="2" beat="3.5" duration="0.5" note="CompletePiano/D4s.wav"/>
        <note measure="2" beat="4" duration="0.5" note="CompletePiano/C4s.wav"/>
        <note measure="3" beat="1" duration="0.5" velocity="80" note="CompletePiano/C4s.wav"/>
        <note measure="3" beat="1.5" duration="0.5" note="CompletePiano/C4s.wav"/>
        <note measure="3" beat="2" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="3" beat="2.5" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="3" beat="3" duration="0.5" note="CompletePiano/A4s.wav"/>
        <note measure="3" beat="3.5" duration="0.5" note="CompletePiano/A4s.wav"/>
        <note measure="3" beat="4" duration="0.5" note="CompletePiano/G4s.wav"/>
        <note measure="4" beat="1" duration="0.5" velocity="80" note="CompletePiano/F4s.wav"/>
        <note measure="4" beat="1.5" duration="0.5" note="CompletePiano/F4s.wav"/>
        <note measure="4" beat="2" duration="0.5" note="CompletePiano/E4s.wav"/>
        <note measure="4" beat="2.5" duration="0.5" note="CompletePiano/E4s.wav"/>
        <note measure="4" beat="3" duration="0.5" note="CompletePiano/D4s.wav"/>
        <note measure="4" beat="3.5" duration="0.5" note="CompletePiano/D4s.wav"/>
        <note measure="4" beat="4" duration="0.5" note="CompletePiano/C4s.wav"/>
    </instrument>
</score>

Wave Files
wave/twinkle_twinkle.wav
wave/piano_test.wav

Grading components description:

Playing piano notes - The component plays piano notes from a wav file.
Envelope generation - The component uses an envelope to ensure ADSR to generate the waveform.
Pedal simulation - The component allows notes to sustain for their full duration
Basic dynamics - The velocity attribute determines how loud a note is based on how hard the key is pressed
Pedal noise - The component has a noise for the pedal that is played when the pedal is pressed/released
Advanced dynamics - The component interpolates between a soft and a loud sample to simulate how hard the piano is being played.
Grading components supported:

Playing piano notes - Functions properly 10/10
Envelope generation - Kinda glitchy sometimes 7/10
Pedal simulation - Functions properly 10/10
Basic dynamics - Functions properly 10/10
Pedal noise - Functions properly 10/10
Advanced dynamics - Kinda works 5/10

Total 42/50

