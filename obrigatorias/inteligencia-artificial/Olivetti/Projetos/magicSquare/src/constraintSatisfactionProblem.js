const _ = require('lodash');

const argmin = (seq, fn) => _.sortBy(seq, [x => fn(x)])[0];

/**
 * Class that represents an CSP problem.
 */
class ConstraintSatisfactionProblem {
  constructor () {
    this.X = [];
    this.D = {};
    this.C = {};
  }

  /**
   * Add the constraint that involves the
   * variables specified to all the variables.
   * 
   * @param {Function} constraint the function that verifies the constraint
   * @param {Array} variables the variables that the constraint uses
   */
  addConstraint (constraint, variables) {
    // We need to add the constraint to each
    // variable that it's refered.
    for (let x of variables) {
      if (this.C[x] === undefined)
        this.C[x] = [];

      this.C[x].push([constraint, variables]);
    }
  }

  /**
   * Solve the CSP problem using backtrack.
   * 
   * @returns the solution, if found.
   */
  solve () {
    return this.backtrackSearch();
  }

  /**
   * Given an assignment and a constraint,
   * apply it and returns the value.
   * 
   * @param {Object} assignment the assignment of the variables.
   * @param {Array} constraint the constraint that will be called.
   * @returns `true` if the constraint is valid.
   */
  callConstraint (assignment, constraint) {
    // Generate the parameters to call the constraint.
    const params = constraint[1].map(x => assignment[x]);
    // Group the params that are unassigned.
    const unassigned = params.filter(x => x === undefined).length;
    // If some of the parameters of the constraint aren't 
    // yet assigned, the constraint must return true.
    return unassigned > 0 || constraint[0](...params);
  }

  /**
   * Select an unassigned variable of X in
   * the assignment. Uses the minimum remaining
   * value heuristic.
   * 
   * @param {Object} assignment the assignment of the variables.
   * @return the unassigned variable
   */
  selectUnassignedVariable(assignment) {
    // First unassigned variable.
    // return this.X.filter(x => assignment[x] === undefined)[0];

    // Minimum remaining value heuristic.
    // Generate the variables that are unassigned.
    const unassigned = this.X.filter(x => assignment[x] === undefined);
    // Return the variable that have the minimum domain.
    return argmin(unassigned, v => this.D[v].length);
  }

  /**
   * Order the domain of `x` using the 
   * least constraining value heuristic.
   * 
   * @param {any} x the variable.
   * @param {Object} assignment the assignment of the variables.
   * @returns the domain of `x` sorted.
   */
  orderDomainValues (x, assignment) {
    // Natural value order.
    // return this.D[x];

    // Least constraining value heuristic.
    // Sort the domain by the values based on the conflicts.
    return _.sortBy(this.D[x], [val => this.conflictNumber(x, val, assignment)]);
  }

  /**
   * Given an variable `x` and a value
   * to assign to it, return the number
   * of conflicts that `x` will have.
   * 
   * @param {any} x the variable.
   * @param {any} val the value assigned to `x`.
   * @param {Object} assignment the assignment of the variables.
   * @returns the number of conflicts
   */
  conflictNumber (x, val, assignment) {
    const old = assignment[x];
    let count = 0;

    assignment[x] = val;
    // Foreach constraint that involves x,
    // call it and check if the result it's true.
    for (let c of this.C[x])
      if (!this.callConstraint(assignment, c))
        count += 1;
    // We need to delete the value case previously was undefined.
    if (old === undefined)
      delete assignment[x]
    else
      assignment[x] = old;

    return count;
  }

  /**
   * Checks if the variable `x` with
   * the value assigned `val` doesn't
   * have any conflict.
   * 
   * @param {any} x the variable.
   * @param {any} val the value assigned to.
   * @param {Object} assignment the assignment of the variables.
   * @returns `true` if is consistent
   */
  isConsistent(x, val, assignment) {
    return this.conflictNumber(x, val, assignment) === 0;
  }

  /**
   * Assign the value `val` to `x`
   * in the assignment, and returns
   * the elements removed of the domain.
   * 
   * @param {Object} assignment the assignment of the variables.
   * @param {any} x the variable.
   * @param {any} val the value assigned to `x`.
   * @returns the elements removed of the domain of `x`.
   */
  assign (assignment, x, val) {
    assignment[x] = val;
    // Limit the domain of x for only the val.
    const removed = this.D[x].filter(a => a !== val).map(a => [x, a]);
    this.D[x] = [val];
    return removed;
  }

  /**
   * Restore the previous domain of the variables.
   * 
   * @param {Array} removed the elements removed from the domain.
   */
  restoreDomain (removed) {
    for (let [B, b] of removed)
      this.D[B].push(b);
  }

  /**
   * Perform an recursive backtrack 
   * search algorithm in the CSP problem.
   * 
   * @returns the solution, if found.
   */
  backtrackSearch () {
    const self = this;

    const backtrack = (assignment={}) => {
      if (Object.keys(assignment).length === self.X.length)
        return assignment;
      
      const x = self.selectUnassignedVariable(assignment);
      for (let val of self.orderDomainValues(x, assignment)) {
        if (self.isConsistent(x, val, assignment)) {
          const removed = self.assign(assignment, x, val);
          const result = backtrack(assignment);
          if (result !== undefined)
            return result;
          self.restoreDomain(removed);
        }
      }
      if (assignment[x] !== undefined)
        delete assignment[x];

      return undefined;
    };

    return backtrack();
  }
}

/**
 * Check if all the parameters passed are distinct.
 * 
 * @param  {...any} args the arguments to be checked
 * @returns `true` if they are distinct.
 */
const allDiff = (...args) => _.uniq(args).length === args.length;

module.exports = {
  ConstraintSatisfactionProblem,
  allDiff
};
