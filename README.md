# Enable live audio for DJI FPV Goggles/AU 
Enables the live audio transmission from Airunit to Goggles.

This is only working with v1 goggles and the airunit with microphone (Vista / Runcam Link is not working!)

##### Install

- `opkg install live-audio-dji`


Live Audio will

Audio volume can be set:
- by playing back a video that doesn't contain any audio and adjust the volume with the goggles joystick up/down commands.
- manually with `setprop persist.dji.volume.headphone 6` with persistent values from 1-6.


##### Known issues

- If live audio is enabled videos containing audio can not be played
