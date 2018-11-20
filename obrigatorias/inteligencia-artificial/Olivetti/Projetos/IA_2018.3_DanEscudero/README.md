# IA_2018.3_DanEscudero

## UFABC AI Project

Daniel Escudero - 11005716

https://danescudero.github.io/IA_2018.3_DanEscudero/

This is a genetic algorithm to make rockets - which initially starts moving randomly - evolve and hit a target. PixiJS was used to make the visualization.

---

### How does the DNA and Genes works?

Each Rocket has a DNA, which has a genes array. Genes array contains a bunch of movements, which cn be UP, DOWN, LEFT or RIGHT. and the first genes position is the rocket speed, which is a random from 0 to 10.

On every frame, rocket takes the movement specified in the genes, and multiplied by it's speed, allowing it to move.

---

### How does the `fitness function` works?

Fitness function punishes rokets going off view, assigning 0 to these guys. It also benefits rockets that go in the target (end in distance <= `targetRadius` from the target position).

For any rocket that is on view bounds, but is notin target bounds, fitness function calculates euclidian distance between rocket position and target position, and fitness is 1 / distance, constrained to be grater than 0.

Fitness is also normalized between all rockets.

---

### What is this `Report` Object?

It contains some statistical information about the past generation. Some of it is displayed in the screen, some of it is not displayed, but was used during development for debugging.

---

### And what's about `Visualization` Class?

It's nothing but a class that takes care of showing the report and drawing the view stroke. Genetic algorithm itself works fine without it, but it's nice to have a visualization.
