const _ = require('lodash')

/**
 * Class with uninformed search algorithms.
 */
class UninformedSearch {
  constructor (s0, isFeasible, isGoal, isTerminal, actions, apply) {
    this.s0 = s0;
    this.isFeasible = isFeasible;
    this.isGoal = isGoal;
    this.isTerminal = isTerminal;
    this.actions = actions;
    this.apply = apply;
  }

  /**
   * Given an array of states, apply
   * every possible action into every
   * element of the array.
   * 
   * @param {Array} states the current states of BFS.
   * @returns the new states
   */
  nextNodes (states) {
    const newStates = [];
    for (let state of states) {
      const actions = this.actions();
      for (let action of actions) {
        const applied = this.apply(action, state);
        newStates.push(applied);
      }
    }
    return newStates;
  }

  /**
   * Perform the Breadth-first search
   * algorithm in the problem specified.
   * 
   * @returns the solution, if found.
   */
  bfs () {
    let states = [this.s0];
    let goal = states.filter(this.isGoal);
    let m = 0;

    while (goal.length === 0) {
      states = this.nextNodes(states).filter(this.isFeasible);
      goal = states.filter(this.isGoal);
      m += states.length;
    }

    return [goal[0], m];
  }

  /**
   * Perform the Depth-first search
   * algorithm in the problem specified.
   * 
   * @returns the solution, if found.
   */
  dfs () {
    let stack = [this.s0];
    let m = 0;

    while (stack.length > 0) {
      const state = stack.pop();
      m++;

      if (this.isGoal(state))
        return [state, m];
      if (!this.isFeasible(state))
        continue;
      // If it's terminal and isn't goal, 
      // there's nothing to do.
      if (this.isTerminal(state))
        continue;
      
      for (let x of this.actions().reverse()) {
        const newState = this.apply(x, state);
        stack.push(newState);
      }
    }

    return [undefined, m];
  }
};

module.exports = UninformedSearch;
