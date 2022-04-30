# Wokwi Additional Commands

Well, I had trouble getting the Pico code to run on the Pico.  Not sure what's going on, but I took a break from figuring why something that shouldn't need porting needed porting, and did Part 2 of the homework, which was to add some commands to the table.

For my final project, one of the things I want to use the serial port for is to dump data about the colors of the LEDs.  So I made a simple data dump command ("data"), using some dummy data in data.h.

I had to create several new functions for reading and writing uint8_t numbers, so one of my extra commands is the uint8 reading and writing example.