# 3D Graphics Math

## Vectors
Vertex = main input in OpenGL
-> has a number of attributes (position in xyz coordinate space)

xyz combination = triplet (can be represented by a vector)
-> represent a direction and magnitude

Go positive one unit on the:
- x-axis (1, 0, 0)
- y-axis (0, 1, 0)
- z-axis (0, 0, 1)

A vector is also how we point where we are going (direction):
- which way is de camera pointing
- what way do we need to move

A point in space is both a vertex and a vector

The length of a vector (magnitude):
- x-axis (1, 0, 0) -> the length of the vector is one (unit vector)

If a vector is not a unit vector we want to scale it to make one (normalization)
Normalizing a vector scales it's length to one = normalized

Unit vectors are important when we only want to show direction and not a magnitude.
Vector lengths of 1 are simpler to use in math equations.

Magnitude can be useful to note how far we want something to move.

## Making classes to represent vectors and matrices
