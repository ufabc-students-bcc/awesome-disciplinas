/**
 * Setting up PIXI stuff and visualization
 */
const width = 800;
const height = 800;

// Setup visualization canvas
const renderer = PIXI.autoDetectRenderer(width, height);
const app = new PIXI.Application(width, height);

// Adds canvas (app) to the webpage
document.body.appendChild(app.view);
renderer.render(app.stage);

// Set canvas dimensions and call main
const canvasDimensions = { width, height };
main(canvasDimensions, app);
