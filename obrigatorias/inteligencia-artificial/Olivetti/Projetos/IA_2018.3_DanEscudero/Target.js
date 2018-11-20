class Target extends PIXI.Container {
    get radius() {
        return this._radius;
    }

    constructor({ radius = 50 } = {}) {
        super();

        this._radius = radius;

        this._style = {
            red: '0xff0000',
            white: '0xffffff',
            strokeColor: '0x000000',
            layers: 5
        };
        this._graphics = new PIXI.Graphics();
        this.addChild(this._graphics);

        this._drawTarget();
    }

    /**
     * Checks if a given { x, y } position is inBounds
     * @param {{x,y}} position to be checked
     * @return {boolean} true iff { x, y } is in target bounds
     */
    isInBounds({ x, y }) {
        return euclidianDistance(this, { x, y }) <= this._radius;
    }

    /**
     * Draws target
     */
    _drawTarget() {
        this._graphics.clear();

        const { red, white, strokeColor, layers } = this._style;
        const colors = [red, white];
        const layerRadiusStep = this._radius / layers;
        let currentRadius = this._radius;

        // Draw circle alternatelly, up to the center
        for (let iLayer = 0; iLayer < layers; iLayer++) {
            // Draw stroke
            this._graphics.beginFill(strokeColor);
            this._graphics.drawCircle(0, 0, currentRadius + 1);

            // Draw circle
            const color = colors[iLayer % colors.length];
            this._graphics.beginFill(color);
            this._graphics.drawCircle(0, 0, currentRadius);

            currentRadius -= layerRadiusStep;
        }
    }
}
