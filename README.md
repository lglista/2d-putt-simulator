# 2d-putt-simulator
This project uses SFML 2.5.1. This program runs a simulation based on .hole and .settings files and at the end of the simulation will show to the screen
an SFML window showing how far each simulated putt landed from the hole. Red means the ball landed very far away from the hole at the end of the simulation.
White means that the shot went into the hole. Closing the window at the end of the simulation saves the window to `screenshots/name_of_hole.png`

## Compiling
Navigate to the root directoy and run `make simulate.exe`

## Simulating
To begin a simulation you must first create a hole and settings file in `2d-putt-simulator/config/`. Examples exist in the directory and an explanation
 of the settings file is also in the directory. Files must be named with the pattern name_of_hole.hole and name_of_hole.settings. You can then run a 
 simulation with `./simulate.exe name_of_hole`
 
 The time it takes to run a simulation is dependent mainly on the increment setting in your .setting file, but may also be sped up by increasing the
 velocity divisor. A big slowdown is also from how many walls you have in your hole.
 
 ## Viewing holes
 To view a hole, you must first create a hole and settings as above. Then you can compile the hole viewer with `make editor.exe` and run it with
 `./editor.exe name_of_hole`

## .hole files
.hole files define the layout of your hole by setting the starting location of your ball and hole as well as horizontal and vertical lines for the walls.
| Keyword | Parameter 1 | Parameter 2 | Parameter 3 |
| ------- | ----------- | ----------- | ----------- |
| Ball    | Starting X Location of the ball | Starting Y Location of the ball | Radius of the ball (used to determine wall collisions) |
| Hole    | X Location of the hole | Y Location of the ball | Radius of the hole (used to determine if ball makes it in hole) |
| HorizontalWall | X Location of the left point of the line segment | Y Location of the left point of the line segment | Length of the line segment |
| VerticalWall | X Location of the top point of the line segment | Y location of the top point of the line segment | Length of the line segment |

Example:

Ball 400 500 4  
Hole 400 100 10  
VerticalWall 250 50 525  
VerticalWall 550 50 525  
HorizontalWall 250 50 300  
HorizontalWall 250 575 300

The above will create a hole that looks like this
![hole1](images/hole1_hole.png?raw=true "Render of hole 1")

## .settings files
.settings files define the settings of the simulation.
| Keyword | Parameter 1 |
| ------- | ----------- |
| WindowWidth | How wide the window will be in the simulation results and the editor. Runtime is largely affected by WindowWidth * WindowHeight |
| WindowHeight | How tall the window will be in the simulation results and the editor. Runtime is largely affected by WindowWidth * WindowHeight |
| Increment | How far apart each putt will be in terms of pixels. A 100x1 window with increment 10 will only simulate 10 shots |
| VelocityDivisor | Inversly affects how fast a ball is putt based on pixel being putt to. A large VelocityDivisor will cause putts to travel very short distances. A small VelocityDivisor will cause putts to launch around the green at wild speeds |
| MaxDistanceForColorSpectrum | The distance that a shot appears as red on the simulation results. The lower the number the easier it will be to tell apart distances to the hole |

Example:

WindowWidth 800  
WindowHeight 600  
Increment 1  
VelocityDivisor 150  
MaxDistanceForColorSpectrum 475  

The above in conjunction with the hole above will produce these results (this can be acheived by running `./simulate.exe hole1`)
![hole1 simulation](images/hole1_simulation.png?raw=true "Simulation of hole 1")

There are a total of 6 holes pre-made in this project that you can take examples and inspiration from as you choose. Please share your cool simulation
results in the discussions section of this repo!
