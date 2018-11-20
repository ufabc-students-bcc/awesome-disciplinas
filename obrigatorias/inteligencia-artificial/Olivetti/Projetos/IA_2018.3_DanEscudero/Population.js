class Population {
    get rockets() {
        return this._rockets;
    }

    constructor(popSize, DNALength, childMR, individualMR) {
        this._popSize = popSize;
        this._DNALength = DNALength;
        this._childMR = childMR;
        this._individualMR = individualMR;

        this._rockets = Array(this._popSize);
    }

    /**
     * Returns object containign some informations.
     * Some of it was used for debugging, and was not removed from code.
     * Some of it is written to the view.
     */
    getReport() {
        return {
            counts: this._getDirectionsPercentage(),
            avgFitness: this._getAverageFitness(),
            avgTarget: this._getAverageTarget(),
            topFitness: Number(this._rockets[0].dna.fitness.toFixed(3))
        };
    }

    /**
     * Initialize population (create rockets)
     */
    initialize() {
        for (let iRocket = 0; iRocket < this._popSize; iRocket++) {
            const rocket = new Rocket(this._DNALength, this._individualMR);
            this._rockets[iRocket] = rocket;

            rocket.x = 100 + iRocket * 30;
            rocket.y = 100;
        }
    }

    /**
     * Update all rockets positions
     */
    update() {
        this._rockets.forEach((rocket) => {
            const nextMove = rocket.getNextGene();
            const { speed } = rocket;
            if (rocket.shouldMove) {
                rocket.x += nextMove.x * speed;
                rocket.y += nextMove.y * speed;
            }

            // Stop rocket if it is off bounds
            if (rocket.isOffBounds()) {
                rocket.x = Math.min(rocket.x, width);
                rocket.x = Math.max(rocket.x, 0);

                rocket.y = Math.min(rocket.y, height);
                rocket.y = Math.max(rocket.y, 0);

                rocket.shouldMove = false;
            }
        });
    }

    /**
     * Assigns fitness value for a rocket, calculated by fitness function
     * (which is passed as attribute)
     * @param {function} fitnessFunction function that returns fitness of an
     * individual rocket
     */
    evaluate(fitnessFunction) {
        this._rockets.forEach((rocket) => {
            rocket.dna.fitness = fitnessFunction(rocket);
        });

        // Normalizes fitness values
        this._rockets.sort((a, b) => b.dna.fitness - a.dna.fitness);
        const topFitness = this._rockets[0].fitness;
        this._rockets.forEach((rocket) => {
            rocket.fitness /= topFitness;
        });
    }

    /**
     * Selects rockets that should die or not
     */
    select() {
        this._rockets.forEach((rocket, idx) => {
            // TendenceToDie gets bigger as we get to the end of the array
            // This way, the ones in the beggining of it should not die
            // as often as the ones at the end.
            const tendenceToDie = idx / this._rockets.length;
            const shouldDie = probability(tendenceToDie, probabilityFunction);

            if (shouldDie) {
                // Remove rocket from population
                const [dead] = this._rockets.splice(idx, 1);

                // Destroy rocket (remove from PIXI tree, to avoid memory leak)
                dead.destroy(true);
            }
        });
    }

    /**
     * Repopulates population array (Any rocket from 'old generation' will be
     * left behind. All of them will generate children and die soon after)
     */
    repopulate() {
        const newChildren = [];

        for (let iChild = 0; iChild <= this._popSize; iChild++) {
            const child = this._getNewChild();
            newChildren.push(child);

            if (probability(this._childMR)) {
                child.dna.mutate();
            }
        }

        // Destroy all remaining rockets
        this._rockets.forEach((rocket) => {
            rocket.destroy(true);
        });

        // Empty array to make room for new children
        this._rockets = [];

        newChildren.forEach((rocket) => {
            this._rockets.push(rocket);
        });
    }

    /**
     * Generates a new child from population array
     */
    _getNewChild() {
        let parent1, parent2;
        parent1 = randomInArray(this._rockets);
        parent2 = randomInArray(this._rockets);

        // Pick random parents untiul their different.
        while (parent1 === parent2) {
            parent2 = randomInArray(this._rockets);
        }

        // Generate child
        const childDNA = DNA.reproduce(
            parent1.dna,
            parent2.dna,
            this._DNALength,
            this._individualMR
        );

        return new Rocket(this._DNALength, this._individualMR, childDNA);
    }

    /**
     * Average fitness, for statistical purposes
     */
    _getAverageFitness() {
        let sum = 0;
        this._rockets.forEach((rocket) => {
            sum += rocket.dna.fitness;
        });

        return Number((sum / this._popSize).toFixed(3));
    }

    /**
     * Average rockets end position, for debug/statistical purposes
     */
    _getAverageTarget() {
        let sumTargets = { x: 0, y: 0 };
        this._rockets.forEach((rocket) => {
            const { x, y } = rocket.getFinalPosition();
            sumTargets.x += x;
            sumTargets.y += y;
        });

        return {
            x: Number((sumTargets.x / this._popSize).toFixed(2)),
            y: Number((sumTargets.y / this._popSize).toFixed(2))
        };
    }

    /**
     * Info about rockets genes, for debug/statistical purposes
     *
     * Returns object containing percentage of genes of each direction, and
     * average speed
     */
    _getDirectionsPercentage() {
        // Initialize empty counts
        const counts = {
            speed: 0,
            UP: 0,
            DOWN: 0,
            LEFT: 0,
            RIGHT: 0
        };

        // Count for every gene
        this._rockets.forEach((rocket) => {
            const { genes } = rocket.dna;
            genes.forEach((gene, idx) => {
                if (idx) {
                    let key = '';
                    const { x, y } = gene;
                    if (x === +1) key = 'RIGHT';
                    if (x === -1) key = 'LEFT';
                    if (y === +1) key = 'DOWN';
                    if (y === -1) key = 'UP';

                    counts[key]++;
                }
            });
            counts['speed'] += genes[0];
        });

        // Normalize info
        const dirs = Object.keys(counts);
        dirs.forEach((dir) => {
            if (dir !== 'speed') {
                counts[dir] /= this._DNALength * this._popSize;
                counts[dir] = Number(counts[dir].toFixed(2));
            }
        });
        counts['speed'] /= this._popSize;
        counts['speed'] = Number(counts['speed'].toFixed(2));

        return counts;
    }
}
