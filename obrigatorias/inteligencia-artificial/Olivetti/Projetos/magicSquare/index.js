const { createUninformedSearch, createInformedSearch, createCsp } = require('./src/magicSquare');

const uninformedSearch = createUninformedSearch();
const informedSearch = createInformedSearch();
const csp = createCsp();

const measureTime = (fn) => {
  const start = new Date();
  const ret = fn();
  const end = new Date();

  return [ret, (end - start) / 1000];
}

const logResult = (label, fn) => {
  const res = measureTime(fn);
  console.log(`${label}: ${JSON.stringify(res[0])}, took ${res[1]}s`);
}

const main = () => {
  logResult('BFS', () => uninformedSearch.bfs());
  logResult('DFS', () => uninformedSearch.dfs());
  logResult('A*', () => informedSearch.aStar());
  logResult('CSP', () => csp.solve());
};

main();
