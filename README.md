# nBodyGravitySim

A program that simulates the gravitational interactions of celestial bodies (an [N-Body](https://en.wikipedia.org/wiki/N-body_simulation) simulation).
Written in C++. Uses the SDL2 library to handle rendering and GUI. Implemented using the [Barnes-Hut algorithm](https://en.wikipedia.org/wiki/Barnes%E2%80%93Hut_simulation).

## Using the Program

You can try the simulation in your browser [here](https://nbodygravitysim.pages.dev/), where the program's C++ source code has been converted to WebAssembly using [Emscripten](https://emscripten.org/).

Press ```z``` to zoom in on cursor,  ```LSHIFT z``` to zoom out, and arrow keys to move the camera.

Spawn particles (planets/stars) manually in desired locations using the ```SPAWN PARTICLES``` button, or choose one of the example particle configurations that are provided by the program. 

### Spawning Particles Manually

First, press the ```SPAWN PARTICLES``` drop-down button:

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/5932de72-ac9f-4710-8a91-661d339f4acb)

Select the number of particles you want to spawn at once, and select the desired mass for your particle(s). 

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/71c5d000-079a-43ec-85b7-b16244d4da7d)


Then, press ```PLACE PARTICLE(s)``` to place particles with the selected settings.

### Using an Example Config

The simulation program provides a few example planet/star configurations you can play around with. 

![image](https://github.com/michahn01/nBodyGravitySim/assets/113268235/9dc9bc53-a7ff-47c9-9d00-0334e97a5b9d)

```STAR SYSTEM``` is a generic star system with one star and two planets that orbit it.

```BINARY STAR SYSTEM``` is a star system with two stars of equal mass orbiting each other.

```UNSTABLE 3 BODY``` is more interesting. With three bodies of equal mass, this system is highly
chaotic and also extremely sensitive -- using double vs floating point precision in simulation computations leads to hugely different results. Most configurations with three bodies are similarly chaotic and sensitive, and in most three-body systems the masses fling themselves out of orbit in the end and part ways (perhaps why similarly chaotic star systems are so rare in nature). This is a case illustrating the difficulties of the infamous [three-body-problem](https://en.wikipedia.org/wiki/Three-body_problem), which seeks to 
solve for the motion of a three-body system given each body's initial position and velocity. Unlike the two-body-problem, no closed-form
solution exists to this day for the three-body-problem. 

```EULER'S 3 BODY``` While "most" three-body configurations are highly unstable, there are some special configurations where the three masses lock themselves into a stable and repeating orbit. Leonhard Euler himself has found several such special three-body configurations, and one of them has been included here in this program. There is one mass locked in the system's center of mass, and two opposite masses orbit the center mass in a sideways figure-eight.

## How the Simulation Works

Newton's equation for gravitational attraction is given by:

$$ F = G \cdot \frac{{m_1 \cdot m_2}}{{r^2}} \$$

where:
- \( F \) is the magnitude of the gravitational force between two objects,
- \( G \) is the gravitational constant,
- \( m_1 \) and \( m_2 \) are the masses of the two objects, and
- \( r \) is the distance between the centers of the two objects.

Every object in a system exerts gravitational attractive force on every other object in the system, which gives n * (n - 1) = n^2 - n interactions happening every second. A naiive implementation of the simulation that goes through every interaction would therefore have time complexity O(n^2).

But objects that are very far apart exert very little (close to zero) gravity upon each other. As such, we can group nearby bodies and use their _center of mass_ to approximate the force that the group as a whole exerts on some object that's sufficiently far away. This is the core idea of the [Barnes-Hut algorithm](https://en.wikipedia.org/wiki/Barnes%E2%80%93Hut_simulation), usually implemented (here as well) using a quad-tree. By approximating rather than computing exactly forces exchanged by very far away bodies, the simulation becomes more efficient, with time complexity O(nlogn).
