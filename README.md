# cv-lfo-blender-lv2

The CV-LFO-Blender is a plugin that has 4 LFOs. Each LFO has a parameter to select a waveform and a parameter to set a phase offset for each LFO independently. It has a global blend control to create a mix between the LFOs. The plugin has for 5 CV outputs, 1 for the LFO mix, and 4 for each LFO seperatly.

##### Installation

To build and install the plugin run:
```
make
make install
```

##### Roadmap

Still needs to be tested:
* CV reset feature

Currently the tempo is set by a master tempo control. But I would like to add the following option in the future:
* Sync LFOs to host tempo
