# Magic Square

By [Alessandro Jean](https://github.com/alessandrojean/IA-2018.3/).

Breadth-first search, Depth-first search, A* and
CSP Backtracking search to create a `n × n` magic
square.

## Definition

> A magic square is a `n × n` square grid filled
> with distinct positive integers in the range
> `1, 2, …, n²` such that each cell contains
> a different integer and the sum of the integers
> in each row, column and diagonal is equal.
>
> &mdash; Wikipedia's definition.

## Using uninformed search

The generic BFS and DFS implementation are inside
the `UninformedSearch` class. The `magicSquare.js`
module implements the crucial functions like
`isGoal`, `isFeasible` etc. and create a 
`UninformedSearch` instance who can do BFS and DFS.

An `Array` of `n²` elements represents the grid,
and is filled from left to right.

## Using informed search

The generic iterative A* implementation is inside
the `InformedSearch` class. The methods needed are
implemented inside `magicSquare.js`. Here, the
heuristic is to select the nodes that have
the sum of the lines, columns and diagonals
within a given ratio related to the magic constant.

An `Array` of `n²` elements also represents the grid.

## Using CSP

The generic CSP implementation in 
`ConstraintSatisfactionProblem` class can solve 
it using recursive backtracking. The implementation 
is based on the [CSP class]. The `magicSquare.js` 
module also implements some functions like the 
constraints and creates a CSP instance that can 
solve the problem.

Here, an `Object` represents the assignment, that
is the solution at the end of the algorithm.

[CSP class]: https://folivetti.github.io/courses/IA/PDF/Aula04.pdf

## How to run it

For run the code, first you need to have
[NodeJS] and [NPM] installed in your system.

```bash
# Install the dependencies.
npm install
# Run the main entry.
npm run main
```

[NodeJS]: https://nodejs.org/en/
[NPM]: https://www.npmjs.com/

## Sample output

Above is an sample output of the execution of
the algorithms implemented in a `3 × 3` grid.

```text
BFS: [[[2,7,6,9,5,1,4,3,8],[]],986409], took 9.492s
DFS: [[[2,7,6,9,5,1,4,3,8],[]],1068211], took 1.549s
A*: [[[2,9,4,7,5,3,6,1,8],[]],3801], took 0.87s
CSP: {"0":2,"1":9,"2":4,"3":7,"4":5,"5":3,"6":6,"7":1,"8":8}, took 0.037s
```
