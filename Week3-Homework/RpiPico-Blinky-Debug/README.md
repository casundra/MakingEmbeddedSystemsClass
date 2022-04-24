# Debugging with a Picoprobe, Platformio, Wizio Platform (RPi SDK)

Hoo!  See [RpiPico-Wizio](https://github.com/casundra/MakingEmbeddedSystemsClass/tree/main/Week3-Homework/RpiPico-Wizio) for instructions on how to get the base dev environment set up.

The good news is that you don't have to do any of the build on Windows crap that's in the Getting Started Guide.  Just drag the picoprobe.uf2 file onto your second Pico, and install the libusb32 driver with Zadig.

However, it doesn't seem like the current version of Wizio supports the serial pass-through of both serial data and programming between the "Probe" Pico and the "Device" Pico.  Which leads me to:

##**BIG WARNING NOTE**
I had hooked the two Picos together as shown in the Getting Started Guide.  I ended up DISCONNECTING power between the two, and running each off a USB port to my computer.  That way I could debug with the Probe and still get serial data and program (without pressing any buttons) on the Device.

Good enough for now, this toolchain shit drives me batty and I'm happy to wait for other enterprising souls to figure this out, update their repos, and I'll drop some beer money in their sponsor link.
