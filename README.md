# latent box

![Latent box interface](Title_Card.jpg)

An interactive capacitive touch instrument designed as a performable audio response to Allison Denny's photon motion series—silent looping videos of refracted light in continuous motion. Rather than a fixed soundtrack, this system enables real-time sonic interpretation of visual material through gestural control.

## System Architecture

**Hardware:**

- 5×5 capacitive touch grid (copper tape inlaid into acrylic)
- Velostat pressure strip for global modulation
- Rotary encoder and potentiometer for continuous control
- Arduino Mega with 2× MPR121 capacitive breakout boards
- Dual-layer laser-cut transparent acrylic enclosure

**Software:**

- Serial communication to Max/MSP
- RAVE (Realtime Audio Variational autoEncoder) for timbral transfer
- Custom granular synthesizer
- Audio routing via BlackHole to Ableton Live for final output

## Signal Flow

- **Capacitive Grid** → Latent variable values for RAVE timbral characteristics
- **Pressure Strip** → Note randomization delta in granular synth
- **Rotary Encoder** → Grain size
- **Potentiometer** → Buffer playback position

Multiple RAVE models trained on distinct datasets (foley, glitches, textures). Accepts external audio input for real-time timbral transfer.

## Performance

System designed for installation and live performance. Encourages gestural exploration—subtle changes in finger position or pressure create evolving textures. TouchDesigner generates audio-reactive visuals.

## Demo

[YouTube](https://youtu.be/wfQgLpoa4WQ)

## Credits

Interactive audio response to photon motion series by Allison Denny

## Performance with latent-box

[YouTube](https://www.youtube.com/live/DRAJDqn2mIU?si=ZvYdFi8UbhPlXkzf&t=4440)
