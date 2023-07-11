# nBodyGravitySim

A program that simulates the gravitational interactions of celestial bodies (an [N-Body](https://en.wikipedia.org/wiki/N-body_simulation) simulation).
Written in C++, and uses the SDL2 library to handle rendering and GUI. Implemented using the [Barnes-Hut algorithm](https://en.wikipedia.org/wiki/Barnes%E2%80%93Hut_simulation).

## Using the Program

You can try out the simulation in your browser [here](https://nbodygravitysim.pages.dev/), where the program's C++ source code has been converted to WebAssembly using [Emscripten](https://emscripten.org/).

Press ```z``` to zoom in on cursor,  ```LSHIFT z``` to zoom out, and arrow keys to move the camera.

Spawn particles (planets/stars) manually in desired locations using the ```SPAWN PARTICLES``` button, or choose one of the example particle configurations that are provided by the program. 

### Spawning Particles Manually

First, press the ```SPAWN PARTICLES``` drop-down button:

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/5932de72-ac9f-4710-8a91-661d339f4acb)

Select the number of particles you want to spawn at once, and select the desired weight for your particle(s). 

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/af2dbf2d-6f9e-4bb5-9d87-ce8291063970)

Then, press ```PLACE PARTICLES``` to spawn particles with the selected settings.

### Using an Example Config

The simulation's GUI provides a few example planet/star configurations you can play around with. 

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/9dc9bc53-a7ff-47c9-9d00-0334e97a5b9d)

```STAR SYSTEM``` is a generic star system with one star and two planets. The planets orbit the star in such a way that the system has a fixed center of mass, which keeps the entire system in one place.

```BINARY STAR SYSTEM``` is just that, a star system with two stars of equal masses orbiting each other.

```UNSTABLE 3 BODY``` is more interesting. With three masses of equal mass, this system is **highly**
chaotic -- even the slightest differences in initial conditions lead to vastly different outcomes. 
The configuration is also **extremely** sensitive -- using doubles vs floats in simulation computations leads to hugely different results. 
Most three-body configurations are similarly chaotic and sensitive, and most of the time the masses fling themselves out of orbit in the end
and part ways (perhaps why similarly chaotic star systems are so rare in nature). This is a case illustrating the difficulties of the notorious [three-body-problem](https://en.wikipedia.org/wiki/Three-body_problem), which seeks to 
solve for the motion of a three-body system given each body's initial position and velocity. Unlike the two-body-problem, no closed-form
solution exists to this day for the three-body-problem. 

```EULER'S 3 BODY``` While "most" three-body configurations are highly unstable, there are some special configurations where the three masses lock themselves
into a stable and repeating orbit -- permanently. Leonhard Euler himself has found several such special three-body configurations, and one of them has
been included here in this program. There is one mass in the middle, locked in the system's center of mass, and two masses on the left and right sides
orbit the center mass in a sideways figure-eight.



