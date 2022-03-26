# The Reclaiming My Timer
Right.  So your dudebro coworkers don't think they hog all the speaking time in a meeting, right?  Do they accuse you of interrupting them - when the reality is that you have to, just to make yourself heard at all?  Well this is a way to gather hard data and shut those bloviators up!  

## Hardware Description, How It Works:
Each person has a big lighted arcade button in front of them, hooked up to a central controller.  When the person starts speaking, they hit the button.  When they stop speaking, they hit the button again.  The central controller has an LCD screen that shows the elapsed time for the person speaking, and their total speaking time, both as seconds and as a percentage of the meeting.  There's a button next to the LCD that allows you to scroll though stats from the last 5 meetings.  A USB port provides the ability to download all data from the controller.  A toggle switch sets the controller into "meeting" or "wait" modes.  A small speaker in the controller provides warnings for talking too much and fun sound effects.

## Hardware Block Diagram:
![IMG_3440](https://user-images.githubusercontent.com/17057481/160228203-d0a9d2ab-5e11-4dc1-a349-b955231d0aa5.jpg)

I intend to use the RP2040 because I want to learn about!  However, I've never worked with a processor that has no onboard flash, so I'm doing my best guess at where things go.  I'm not quite sure if more should be on the flash side vs inside the processor.  

## Software Block Diagram:
![IMG_3444](https://user-images.githubusercontent.com/17057481/160228239-2e8dcb3e-644d-45e8-98a4-8ff2ddd1aa3b.jpg)

## Hierarchy of Control:
![IMG_3443](https://user-images.githubusercontent.com/17057481/160228310-fdd795b8-6fc1-40a2-85b6-5e5c1a4e6274.jpg)

## Layered Diagram:
![IMG_3441](https://user-images.githubusercontent.com/17057481/160228378-3c4a4bf4-b6cc-40a5-8063-f457d63924f0.jpg)
