/**
 * Alphabet of allowed positions
 */
const alphabet = [
    { x: +1, y: 0 }, // RIGHT
    { x: -1, y: 0 }, // LEFT
    { x: 0, y: +1 }, // UP
    { x: 0, y: -1 } // DOWN
];

/**
 * Returns array [1, ..., n]
 * @param {Number} n
 */
function arrayUpTo(n) {
    return [...Array(n).keys()].map((x) => x + 1);
}

/**
 * Returns euclidian distance between p1 and p2 (considering R^2)
 * @param {x, y} p1
 * @param {x, y} p2
 */
function euclidianDistance(p1, p2) {
    return Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
}

/**
 * Returns true with probability x. Probability distributes as function fn
 * demands. If fn is not passed as argument, it will assume uniform distribution
 * @param {Number} x
 * @param {*} fn
 */
function probability(x, fn = null) {
    if (fn) {
        return fn(x) >= Math.random();
    } else {
        return x >= Math.random();
    }
}

/**
 * Exponential logistic function. Has very small values near zero, and values
 * very close to 1 near 1, growing exponentially. Note that it's not 0 when
 * x = 0, and not 1 when x = 1.
 *
 * For better visualization of this function, fell free to plot it on Desmos,
 * or WolframAlpha.
 * @param {Number} x
 */
function probabilityFunction(x) {
    return 1 / (1 + Math.exp(-6 * x + 3));
}

/**
 * Returns random element from array `arr`
 * @param {*} arr
 */
function randomInArray(arr) {
    const idx = Math.random() * arr.length;
    return arr[Math.trunc(idx)];
}

/**
 * Randomizes array with passed elements
 * @param {Array} target array to be randomized
 * @param {Array} randomElements array with random elements to fill target
 */
function randomizeArray(target, randomElements = null) {
    randomElements = randomElements || target;
    for (let i = 0; i < target.length; i++) {
        target[i] = randomInArray(randomElements);
    }
}
