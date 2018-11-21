const _ = require('lodash');

const argmin = (seq, fn, gn) => _.sortBy(seq, [x => fn(x) + gn(x)])[0];

/**
 * Class with informed search algorithms.
 */
class InformedSearch {
  constructor (s0, isGoal, isFeasible, isTerminal, actions, apply, g, h) {
    this.s0 = s0;
    this.isGoal = isGoal;
    this.isFeasible = isFeasible;
    this.isTerminal = isTerminal;
    this.actions = actions;
    this.apply = apply;
    this.g = g;
    this.h = h;
  }

  /**
   * Perform the A* search algorithm
   * in the problem specified.
   * 
   * @returns the solution, if found.
   */
  aStar () {
    let nodes = [this.s0];
    let m = 0;

    while (nodes.length > 0) {
      let node = argmin(nodes, this.g, this.h);
      let sl = (!this.isTerminal(node)) ? this.actions().map(a => this.apply(a, node)) : [];
      sl = sl.filter(this.isFeasible);

      if (_.some(sl, s => this.isGoal(s)))
        return [sl.filter(this.isGoal)[0], m];
      nodes.splice(nodes.indexOf(node), 1);
      nodes = nodes.concat(sl);
      m++;
    }

    return [undefined, m];
  }
};

module.exports = InformedSearch; 
