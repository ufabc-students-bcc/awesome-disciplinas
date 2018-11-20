class Rocket extends PIXI.Container {
    get dna() {
        return this._dna;
    }

    get speed() {
        return this._dna.genes[0];
    }

    get shouldMove() {
        return this._shouldMove;
    }

    set shouldMove(shouldMove) {
        this._shouldMove = shouldMove;
    }

    constructor(DNALength, mutationRate, dna = null) {
        super();

        this._style = {
            fillColor: '0x666666',
            rocketHeight: 25,
            rocketWidth: 15,
            entranceHeight: 5,
            rocketAlpha: 0.75
        };

        this._geneIndex = 0;
        this._dna = dna || new DNA(DNALength, mutationRate);
        this._shouldMove = true;

        this._graphics = new PIXI.Graphics();
        this.addChild(this._graphics);

        this._drawRocket();
    }

    /**
     * Returns final position considering current position and genes
     */
    getFinalPosition() {
        const { x, y } = this._dna.getGenesExpression();
        return { x: this.x + x, y: this.y + y };
    }

    /**
     * Returns next gene
     */
    getNextGene() {
        const idx = ++this._geneIndex % (this._dna.DNALength - 1);
        return this._dna.genes[idx + 1];
    }

    /**
     * Checks if rocket is off view bounds
     */
    isOffBounds() {
        const { rocketHeight, rocketWidth, entranceHeight } = this._style;
        return (
            this.x <= rocketWidth / 2 ||
            this.y <= rocketHeight - entranceHeight ||
            this.x >= width - rocketWidth / 2 ||
            this.y >= height - entranceHeight
        );
    }

    _drawRocket() {
        const { fillColor, rocketAlpha } = this._style;

        this._graphics.beginFill(fillColor, rocketAlpha);
        const points = this._getPathPoints();
        this._graphics.drawPolygon(points);
    }

    /**
     * Draws rocket
     * NOTE on points naming:
     *     C
     *    /\
     *   / A\
     *  / /\ \
     * /_/  \_\
     * D        B
     */
    _getPathPoints() {
        const { rocketHeight, rocketWidth, entranceHeight } = this._style;

        const points = [];
        // Point A
        const ptA = { x: 0, y: 0 };
        points.push(ptA);

        // Point B
        const ptB = { x: rocketWidth / 2, y: entranceHeight };
        points.push(ptB);

        // Point C
        const ptC = { x: 0, y: -rocketHeight + entranceHeight };
        points.push(ptC);

        // Point D
        const ptD = { x: -rocketWidth / 2, y: entranceHeight };
        points.push(ptD);

        return points.map(({ x, y }) => new PIXI.Point(x, y));
    }
}
