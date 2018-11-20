class Visualization extends PIXI.Container {
    constructor(width, height, popSize) {
        super();

        this._width = width;
        this._height = height;
        this._popSize = popSize;

        this._background = new PIXI.Graphics();
        this.addChild(this._background);
        this._drawBackground();

        // Sets text style and initialText
        const style = {
            align: 'center',
            fontSize: 72,
            fontVariant: 'small-caps'
        };
        const initText = `topFitness: 0\naverageFitness: 0\nnumGenerations: 0`;

        // Creates text
        this._report = new PIXI.Text(initText, style);
        this.addChild(this._report);

        // Sets tewxt alpha
        this._report.alpha = 0.25;

        // Position text
        this._report.x = width / 2 - this._report.width / 2;
        this._report.y = height / 2 - this._report.height / 2;
    }

    /**
     * Prints report to the view
     * @param {Object} info Info about generation
     * @param {Number} info.avgFitness average of fitnesses of all rockets
     * @param {Number} info.numGenerations number of passed generations so far
     * @param {Number} info.topFitness highest fitness value of current
     * generation
     */
    printReport({ avgFitness, numGenerations, topFitness }) {
        this._report.text = `topFitness: ${topFitness}\naverageFitness: ${avgFitness}\nnumGenerations: ${numGenerations}`;
        this._report.x = width / 2 - this._report.width / 2;
        this._report.y = height / 2 - this._report.height / 2;
    }

    _drawBackground() {
        this._background.beginFill('0xffffff');
        this._background.lineStyle(3, '0x000000');
        this._background.drawRect(1, 0, this._width - 1, this._height - 1);
    }
}
