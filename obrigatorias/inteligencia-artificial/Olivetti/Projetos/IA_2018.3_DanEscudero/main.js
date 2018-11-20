function main({ width, height }, app) {
    /**
     * General genetic algorithm structure
     *
     * Initialize
     *   Population
     *   DNA
     *
     * Select
     *   Fitness
     *
     * Reproduce
     *   Pick Parents
     *   Crossover
     *   Mutate
     *
     * Evaluate
     */

    /**
     * Evolution Parameters:
     * DNA_LENGTH: number of genes in the DNA
     * MAX_CYCLES: how many frames should be animated in a generation before
     *  reseting
     * POPULATION_SIZE: number of dna's evolvind on every generation
     * MAX_GENERATIONS: Sets a limit to the number of generations.
     * MUTATED_CHILDREN: percentage of children that should be mutated on every
     *  new generation
     * MUTATION_RATE: percentage of chance to mutate a every child's individual
     *  character
     * INITIAL_POSITION: initial position of the rockets
     * TARGET_POSITION: position of the target
     */
    const PARAMETERS = Object.freeze({
        // MAX_CYCLES must be >= DNA_LENGHT.
        // Else, there will be a set of the dna that won't be used
        MAX_CYCLES: 250,
        DNA_LENGTH: 250,

        // These parameters can be tweaked until find a good set of values that
        // lead to a faster evolution
        POPULATION_SIZE: 100,
        MAX_GENERATIONS: 500,
        MUTATED_CHILDREN: 0.01,
        MUTATION_RATE: 0.1,

        INITIAL_POSITION: { x: width / 2, y: 200 },
        TARGET_POSITION: { x: 700, y: 700 }
    });

    let shouldRun = true;
    let cyclesCount = 0;
    let numGenerations = 0;

    // Initialize visualization
    const view = new Visualization(width, height, PARAMETERS.POPULATION_SIZE);
    app.stage.addChild(view);

    const target = new Target();
    target.x = PARAMETERS.TARGET_POSITION.x;
    target.y = PARAMETERS.TARGET_POSITION.y;

    view.addChild(target);

    // Initialization
    let population = new Population(
        PARAMETERS.POPULATION_SIZE,
        PARAMETERS.DNA_LENGTH,
        PARAMETERS.MUTATED_CHILDREN,
        PARAMETERS.MUTATION_RATE
    );
    population.initialize();
    addChildren(population.rockets);
    repositionRockets();
    animate();

    /**
     * Animate function works like a game loop.
     * On very frame, we update rockets positions, and sum cycles number. On
     * the end ofthe needed cycles, proceed to next generation.
     */
    function animate() {
        renderer.render(app.stage);
        window.requestAnimationFrame(animate);
        if (shouldRun) {
            population.update();
            cyclesCount++;

            if (cyclesCount > PARAMETERS.MAX_CYCLES) {
                shouldRun = false;
                proceedToNextGen();
            }
        }
    }

    function proceedToNextGen() {
        population.evaluate(fitnessFunction);

        numGenerations++;
        const report = population.getReport();
        view.printReport(Object.assign(report, { numGenerations }));

        population.select();
        population.repopulate();

        addChildren(population.rockets);
        repositionRockets();

        // Stop condition is arbitrarly set to 0.95
        const hitGoal = report.topFitness >= 0.95;
        if (numGenerations <= PARAMETERS.MAX_GENERATIONS && !hitGoal) {
            cyclesCount = 0;

            // Wait 1 sec before starting running again
            setTimeout(() => {
                shouldRun = true;
            }, 1000);
        }
    }

    function addChildren(children) {
        children.forEach((child) => {
            view.addChild(child);
        });
    }

    function fitnessFunction(rocket) {
        // Punish rocket going off bounds
        if (rocket.isOffBounds()) return 0;

        // Benefit rocket hitting target
        if (target.isInBounds(rocket)) return 1;

        // For rockets that are in bounds, but haven't hit target yet, our
        // fitness function is the inverse of the distance between the rocket
        // and the edge of the target
        const dist = Math.max(
            euclidianDistance(PARAMETERS.TARGET_POSITION, rocket) -
                target.radius,
            1
        );

        return 1 / dist;
    }

    /**
     * Reset all rockets position to the initial position
     */
    function repositionRockets() {
        population.rockets.forEach((rocket) => {
            rocket.x = PARAMETERS.INITIAL_POSITION.x;
            rocket.y = PARAMETERS.INITIAL_POSITION.y;
        });
    }
}
