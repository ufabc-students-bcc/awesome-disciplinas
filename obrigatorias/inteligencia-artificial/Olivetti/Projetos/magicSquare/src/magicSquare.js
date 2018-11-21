const _ = require('lodash');
const UninformedSearch = require('./uninformedSearch');
const InformedSearch = require('./informedSearch');
const { ConstraintSatisfactionProblem, allDiff } = require('./constraintSatisfactionProblem');

const ORDER = 3;
const MAGIC_CONSTANT = ORDER * (ORDER * ORDER + 1) / 2;

const s0 = [_.range(ORDER * ORDER).map(i => 0), []];

const actions = () => _.range(1, ORDER * ORDER + 1);

const isFeasible = (state) => {
  const [s, t] = state;
  // Checks if all elements are not filled.
  if (_.every(s, x => !x))
    return true;
  const withoutZero = s.filter(x => x !== 0);
  // It's only feasible if doesn't have duplicates.
  return _.uniq(withoutZero).length === withoutZero.length;
};

const isValid = (state) => {
  // Check if has duplicates.
  if (_.uniq(state[0]).length !== state[0].length)
    return false;
  const s = [];
  // Foreach index, add the sum to s.
  for (let idx of INDEXES_TO_CHECK)
    s.push(_.sum(_.map(idx, x => state[0][x])));
  // If all the sums are equals.
  return _.every(s, x => x === s[0]);
};

const isGoal = (state) => {
  return isValid(state) && _.every(state[0], Boolean);
};

const isTerminal = (state) => {
  const withoutZero = state[0].filter(x => x !== 0);
  return withoutZero.length === ORDER * ORDER;
}

const generateIndexes = () => {
  // Lines.
  let idx = _.range(ORDER).map(i => _.range(i * ORDER, i * ORDER + ORDER));
  // Columns.
  idx = idx.concat(_.range(ORDER).map(j => _.range(ORDER).map(i => j + ORDER * i)));
  // Diagonals.
  idx = idx.concat([_.range(ORDER).map(i => i + i * ORDER)]);
  idx = idx.concat([_.range(ORDER, 0, -1).map(i => ORDER * i - i)]);

  return idx;
};

const INDEXES_TO_CHECK = generateIndexes();

const apply = (action, state) => {
  ni = state[0].indexOf(0)
  const newState = _.cloneDeep(state[0]);
  newState[ni] = action;
  return [newState, _.cloneDeep(state[1])]
};

const g = (node) => {
  let s = 0;
  for (let i = 0; i < INDEXES_TO_CHECK.length; i++) {
    const idx = INDEXES_TO_CHECK[i];
    let sm = _.sum(_.map(idx, x => node[0][x]));
    const ratio = sm / parseFloat(MAGIC_CONSTANT);
    s -= (ratio <= 1 && ratio >= 0.7) ? 1 : 0;
  }
  return s;
};
const h = g;

const createUninformedSearch = () => new UninformedSearch(
  s0, isFeasible, isGoal, isTerminal, actions, apply
);

const createInformedSearch = () => new InformedSearch(
  s0, isGoal, isFeasible, isTerminal, actions, apply, g, h
);

const createCsp = () => {
  const csp = new ConstraintSatisfactionProblem();
  csp.X = _.range(0, ORDER * ORDER);

  for (let x of csp.X)
    csp.D[x] = _.range(1, ORDER * ORDER + 1);

  // All numbers must be distinct.
  csp.addConstraint(allDiff, csp.X);
  // For each line, column and diagonal,
  // the sum must be equal to the magic constant.
  const exactSum = (...args) => _.sum(args) === MAGIC_CONSTANT;
  for (let idx of INDEXES_TO_CHECK)
    csp.addConstraint(exactSum, idx);

  return csp;
}

module.exports = {
  createUninformedSearch,
  createInformedSearch,
  createCsp
}
