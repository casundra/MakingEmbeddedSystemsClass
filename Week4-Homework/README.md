# The palLED (working title) Diagrams & State Machine

For my final project, I want to create a tool that helps people pick LED colors using various color theory principals.  I think the ability to visualize various schemes using addressable LEDs and get the corresponding color data that details the main colors plus variables needed to implement in between colors could be really useful to anyone wanting to generate specific colors or color schemes with LEDs.  The working name for this is the palLED - like "palette" but it's also a helpful friend (pal) for LEDs.

## General Idea
This is going to be a box with an LCD, 4 knobs, 2 buttons, an addressable LED strip, an addressable LED ring, and possibly an addressable LED matrix and auxiliary LED strip connector, and possibly 4 analog RGB LEDs.  The "possibly" parts are nice-to-haves - it would be cool to compare various types of LEDs and strips, but that might be too much scope for the final project.  The analog RGB LEDs would have to be driven from an external I2C chip since there isn't enough Timer I/O for the minimum of 12 PWMs needed plus the knobs, which are encoders.  The knobs will be used to adjust the color and color parameters of all LEDs according to mode, so they need to be insensitive to absolute position since their function changes between moddes.  The LCD will output basic information about the base color and spacing of other colors from the main color, and output Settings in settings mode.  A USB port will provide power, and the ability to adjust settings and output verbose LED data via serial terminal.

![IMG_3637](https://user-images.githubusercontent.com/17057481/163748672-cb595b24-7bd1-4997-bd8f-5a66834cb5ba.jpg)

## Color Schemes
[Colorpedia](https://paletton.com/wiki/index3c21.html?title=Color_schemes) has nice explanations of color schemes, showing examples in color-block format which is similar to what I want to do with the main strip of LEDs (which may turn into a matrix).  The below images are from Colorpedia.  Note the swatch examples do not correspond to the colors indicated on the wheel, the wheel is just provided to get a visual of the angles.

### Monochromatic
In LED speak, this is basically varying brightnesses of a single color.  

![monochrome color wheel](https://paletton.com/wiki/images/9/9d/Mono.png)

![monochromatic color scheme](https://paletton.com/wiki/images/8/82/Model-mono-ex02.png)

When RANGE is referred to in the State Table, it's the range of monochromatic shades you see above.

### Complementary
The color directly opposite the base color on the color wheel.

![complementary color wheel](https://paletton.com/wiki/images/9/97/Compl.png)

![complementary color scheme](https://paletton.com/wiki/images/5/5b/Model-compl-ex02.png)

### Split Complementary
Two colors at even angles to either side of the complementary color on the color wheel.  This is the term used to describe angles under 60 from complementary.  When ANGLE is referred to in the state machine, it's this angle from the complement.

![split complementary color wheel](https://paletton.com/wiki/images/4/41/Split.png)

![split complementary color scheme](https://paletton.com/wiki/images/7/74/Model-split-ex02.png)

 At 60 degrees from complementary, you get 3 colors evenly spaced at 120 degrees around the color wheel.  This is called a Triad.  

![triad color wheel](https://paletton.com/wiki/images/d/d3/Triad.png)

![triad color scheme](https://paletton.com/wiki/images/2/2f/Model-split-ex03-triad.png)

When the angle increases to more than 60 degrees, the colors shift from complementary to adjacent.

![adjacent color wheel](https://paletton.com/wiki/images/a/a5/Analog.png)

![adjacent color scheme](https://paletton.com/wiki/images/2/2e/Model-analog-ex03.png)

### Split Complementary with Complement
This is the previous color scheme with the addition of the exact complement as a 4th color.  

![split complementary with complement color wheel](https://paletton.com/wiki/images/0/09/Split-accent.png)

![split complementary with complement color scheme](https://paletton.com/wiki/images/f/f5/Model-split-accent-ex01.png)

When all colors are a perfectly even 90 degrees from each other, they are a Tetrad.  

![tetrad color wheel](https://paletton.com/wiki/images/1/19/Tetrad.png)

![tetrad color scheme](https://paletton.com/wiki/images/c/cd/Model-dual-ex03-tetrad.png)

When the angle from complementary is greater than 90, it becomes an adjacent with complementary scheme.

![adjacent with complement color wheel](https://paletton.com/wiki/images/3/31/Analog-accent.png)

![adjacent with complement color scheme](https://paletton.com/wiki/images/5/53/Model-analog-accent-ex01.png)

### Dual Complementary
Two pairs of complementary colors.  If the angle between the base colors for the pair is 90 degrees, you get a Tetrad like above.

![dual complementary color wheel](https://paletton.com/wiki/images/3/37/Dual.png)

![dual complementary color scheme](https://paletton.com/wiki/images/c/c2/Model-dual-ex02.png)

### Gradient
Not a specific scheme, but useful.  This is blending between two colors, usually somewhat adjacent.  The below example is from [htmlcolorcodes.com](https://htmlcolorcodes.com/resources/best-color-palette-generators/)

![gradient example](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSlamvt39JIs17YUnayU4TfmXtnjWWfEx2PNg&usqp=CAU)

