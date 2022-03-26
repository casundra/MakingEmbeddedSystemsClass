# The Reclaiming My Timer
Right.  So your dudebro coworkers don't think they hog all the speaking time in a meeting, huh?  Do they accuse you of interrupting them - when the reality is that you have to, just to make yourself heard at all?  Well this is a way to gather hard data and shut those bloviators up!  
![image](https://user-images.githubusercontent.com/17057481/160228451-81c2605b-ef88-42a0-89b5-14e12caf9d74.png)

(photo credit: https://www.blackenterprise.com/career-lessons-from-auntie-maxine-reclaim-time-boss/)

![IMG_3445](https://user-images.githubusercontent.com/17057481/160228813-111d75ea-d181-49aa-bac9-9facd490a778.jpg)

## Hardware Description, How It Works:
Each person has a big lighted arcade button in front of them, hooked up to a central controller.  When the person starts speaking, they hit the button.  When they stop speaking, they hit the button again.  The central controller has an LCD screen that shows the elapsed time for the person speaking, and their total speaking time, both as seconds and as a percentage of the meeting.  There's a button next to the LCD that allows you to scroll though stats from the last 5 meetings.  A USB port provides the ability to download all data from the controller.  A toggle switch sets the controller into "meeting" or "wait" modes.  A small speaker in the controller provides warnings for talking too much and fun sound effects.

## Hardware Block Diagram:
![IMG_3440](https://user-images.githubusercontent.com/17057481/160228203-d0a9d2ab-5e11-4dc1-a349-b955231d0aa5.jpg)

Elecia's Feedback: kudos here, clear, hardware background is obvious

## Software Block Diagram:
I intend to use the RP2040 because I want to learn about!  However, I've never worked with a processor that has no onboard flash, so I'm doing my best guess at where things go.  I'm not quite sure if more should be on the flash side vs inside the processor.  
![IMG_3444](https://user-images.githubusercontent.com/17057481/160228239-2e8dcb3e-644d-45e8-98a4-8ff2ddd1aa3b.jpg)

Elecia's Feedback: One giant blob for Gameplay in the middle isn't very clear, related things should be located physically close to one another, ex: data out and USB need to be near datalogging and flash.  Also, since there is currently no way to associate a user with a button, how valuable is the data I'm logging?  Does it really mean anything?  Blocks in the middle should start to reflect functions and code blocks.

## Hierarchy of Control:
The block under "Main" says LEDs.  Sorry, I figured I could either spend my time learning block diagram tools, or spend time thinking about the design.  The buttons & LEDs could prob be combined into some kind of block?
![IMG_3443](https://user-images.githubusercontent.com/17057481/160228310-fdd795b8-6fc1-40a2-85b6-5e5c1a4e6274.jpg)

Elecia's Feedback: Better, but main loop software is still not clear.  Consider adding blocks for timing, event-based sounds, LED handling, how data output is controlled, etc.  Flash is an obvious bottleneck and it's scary that not only is program code living there, but storage of fonts, graphics, sounds, and data too.  Waht happens if you need to display a graphic and make a sound?  Does one wait for the other?  Will there be display refresh rate issues?  Probably makes sense to at least separate out program code QSPI and put everything else on a storage flash/EEPROM via SPI.

## Layered Diagram:
Flash is definitely the big one here.
![IMG_3441](https://user-images.githubusercontent.com/17057481/160228378-3c4a4bf4-b6cc-40a5-8063-f457d63924f0.jpg)

Elecia's Feedback: didn't get into this diagram too much, but it reiterates the bottleneck of Flash.
