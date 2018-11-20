class DNA {
    get fitness() {
        return this._fitness;
    }

    set fitness(f) {
        this._fitness = f;
    }

    get genes() {
        return this._genes;
    }

    get DNALength() {
        return this._DNALength;
    }

    /**
     * Given parents 1 and two, generates a child, merging randomly parent's
     * genes Also, sets child's length and mutation rate
     * @param {DNA} parent1
     * @param {DNA} parent2
     * @param {Number} length
     * @param {Number} mr
     */
    static reproduce(parent1, parent2, length, mr) {
        const child = new DNA(length, mr);

        child.genes.forEach((_, idx) => {
            const shouldUseParent1 = probability(0.5);
            if (shouldUseParent1) {
                child.genes[idx] = parent1.genes[idx];
            } else {
                child.genes[idx] = parent2.genes[idx];
            }
        });

        return child;
    }

    /**
     * Creates instance of DNA
     * NOTE: Methods with name starting with '_' are private methods
     * @param {Number} DNALength
     * @param {Number} mutationRate
     *
     */
    constructor(DNALength, mutationRate) {
        this._mutationRate = mutationRate;
        this._DNALength = DNALength;
        this._fitness = -1;
        this._genes = Array(this._DNALength).fill(-1);

        this._initialize();
    }

    /**
     *
     */
    getGenesExpression() {
        const finalPos = { x: 0, y: 0 };
        const speed = this._genes[0];

        this._genes.forEach(({ x, y }, idx) => {
            if (idx) {
                finalPos.x += x * speed;
                finalPos.y += y * speed;
            }
        });

        return finalPos;
    }

    /**
     * For each gene in this gene set, mutates to a random gene with mutation_rate chance
     */
    mutate() {
        this._genes.forEach((gene, idx) => {
            if (probability(this._mutationRate)) {
                if (idx) {
                    this._genes[idx] = randomInArray(alphabet);
                } else {
                    this._genes[0] = Math.random() * 10;
                }
            }
        });
    }

    /**
     * Initializes gene set array
     */
    _initialize() {
        randomizeArray(this._genes, alphabet);
        this._genes[0] = Math.random() * 10;
    }
}
