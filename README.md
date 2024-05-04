# Flocking-IMGD4000
This is an implementation of the Boids Algorithm for IMGD 4000. I implemented the 3 rules of boids, which are functions labeled rule1(), rule2(), and rule3(). These three rules are as follows: <br>
1. Boids try to fly towards the centre of mass of neighbouring boids. <br>
2. Boids try to keep a small distance away from other objects (including other boids). <br>
3. Boids try to match velocity with near boids. <br> <br>

My main function flock() takes inputs from these three rule functions. I also implemented two additional features, AKA tweaks, as described at http://www.kfish.org/boids/pseudocode.html, which were checking for boundaries and controlling velocity.  

Each of the rules functions goes over all other boids to implement all three rules. The resulting value determines the speed and location of the boid's next position. 

Here is a link to my video: https://youtu.be/lNLjH_JhHxk <br>

The video is also available within this repository as a raw mp4 file. Thank you very much. 
