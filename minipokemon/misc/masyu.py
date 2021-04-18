"""Masyu solver example.

Example puzzle can be found at https://en.wikipedia.org/wiki/Masyu.
"""

import sys
from z3 import Implies, Or

import grilops
import grilops.loops
from grilops.geometry import Vector


def solve(black, white):
    """Masyu solver example."""
    e, w, b = " ", chr(0x25E6), chr(0x2022)
    givens = [[e for i in range(10)] for j in range(10)]
    for i, j in black:
        givens[i][j] = b
    for i, j in white:
        givens[i][j] = w

    for row in givens:
        for cell in row:
            sys.stdout.write(cell)
        print()

    lattice = grilops.get_rectangle_lattice(len(givens), len(givens[0]))
    sym = grilops.loops.LoopSymbolSet(lattice)
    sym.append("EMPTY", " ")
    sg = grilops.SymbolGrid(lattice, sym)
    lc = grilops.loops.LoopConstrainer(sg, single_loop=True)

    # Choose a non-empty cell to have loop order zero, to speed up solving.
    p = min(p for p in lattice.points if givens[p.y][p.x] != e)
    sg.solver.add(lc.loop_order_grid[p] == 0)

    straights = [sym.NS, sym.EW]
    turns = [sym.NE, sym.SE, sym.SW, sym.NW]

    for p in lattice.points:
        given = givens[p.y][p.x]
        if given == b:
            # The loop must turn at a black circle.
            sg.solver.add(sg.cell_is_one_of(p, turns))

            # All connected adjacent cells must contain straight loop segments.
            for n in sg.edge_sharing_neighbors(p):
                if n.location.y < p.y:
                    sg.solver.add(
                        Implies(
                            sg.cell_is_one_of(p, [sym.NE, sym.NW]),
                            sg.cell_is(n.location, sym.NS),
                        )
                    )
                if n.location.y > p.y:
                    sg.solver.add(
                        Implies(
                            sg.cell_is_one_of(p, [sym.SE, sym.SW]),
                            sg.cell_is(n.location, sym.NS),
                        )
                    )
                if n.location.x < p.x:
                    sg.solver.add(
                        Implies(
                            sg.cell_is_one_of(p, [sym.SW, sym.NW]),
                            sg.cell_is(n.location, sym.EW),
                        )
                    )
                if n.location.x > p.x:
                    sg.solver.add(
                        Implies(
                            sg.cell_is_one_of(p, [sym.NE, sym.SE]),
                            sg.cell_is(n.location, sym.EW),
                        )
                    )
        elif given == w:
            # The loop must go straight through a white circle.
            sg.solver.add(sg.cell_is_one_of(p, straights))

            # At least one connected adjacent cell must turn.
            if 0 < p.y < len(givens) - 1:
                sg.solver.add(
                    Implies(
                        sg.cell_is(p, sym.NS),
                        Or(
                            sg.cell_is_one_of(p.translate(Vector(-1, 0)), turns),
                            sg.cell_is_one_of(p.translate(Vector(1, 0)), turns),
                        ),
                    )
                )
            if 0 < p.x < len(givens[0]) - 1:
                sg.solver.add(
                    Implies(
                        sg.cell_is(p, sym.EW),
                        Or(
                            sg.cell_is_one_of(p.translate(Vector(0, -1)), turns),
                            sg.cell_is_one_of(p.translate(Vector(0, 1)), turns),
                        ),
                    )
                )

    if sg.solve():
        sg.print()
        print()
        if sg.is_unique():
            print("Unique solution")
            return True
        else:
            print("Alternate solution")
            sg.print()
            return False
    else:
        print("No solution")
        return False


black = [
    (0, 0),
    (0, 2),
    (2, 6),
    (6, 2),
    (6, 7),
    (7, 1),
    (7, 8),
]
white = [
    (0, 4),
    (3, 0),
    (3, 3),
    (3, 4),
    (4, 2),
    (4, 7),
    (4, 8),
    (5, 3),
    (5, 5),
    (5, 6),
    (8, 3),
    (8, 4),
    (9, 3),
    (9, 6),
]
solve(black, white)
