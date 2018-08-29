# A-new-global-optimization-algorithm

The algorithm subdivides the feasible region into subrectangles and sequentially chooses the next subrectangle to subdivide according to a certain numerical value.

The algorithm operates by decomposing $[0,1]^d$ into hyper-rectangles as follows. The first operation is to evaluate $f$ at the center of the unit hyper-cube $(1/2,1/2,\ldots ,1/2)$. The unit hyper-cube is sequentially subdivided as follows.
Given a current decomposition, choose one of the hyper-rectangles (according to the maximal value of a criterion to be defined) and trisect it along the longest axis.
The central sub-hyperrectangle retains its central function value, while the function is evaluated at the centers of the two other hyperrectangles.

The code here has different versions. It use c++/matlab to implement the new global optimization algorithm above. It use Rastrigin function as test objective function.
