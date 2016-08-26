# 3D Graphics Math

## Vectors
**Vertex** is a main input in OpenGL -> has a number of attributes (position in *xyz coordinate space*)

**xyz triplet** (can be represented by a vector) -> represent a direction and magnitude

**Go positive one unit:**
- x-axis (1, 0, 0)
- y-axis (0, 1, 0)
- z-axis (0, 0, 1)

A **vector** is also **how we point** where we are going (direction):
- which way is de camera pointing
- what way do we need to move

A point in space is both a vertex and a vector

The **length** of a vector (magnitude):
- x-axis (1, 0, 0) -> the length of the vector is one (*unit vector*)

If a vector is *not a unit vector* we want to *scale* it to make one (normalization)
Normalizing a vector scales it's length to one = normalized

**Unit vectors** are important when we only want to *show direction* and not a magnitude.
Vector lengths of 1 are simpler to use in *math equations*.

**Magnitude** can be useful to note *how far* we want something to move.

## Making classes to represent vectors and matrices
**3 component vectors** (x, y, z)
```c++
vec3(-0.5f, 1.0f, -0.2f);
```

**4 component vectors** (x, y, z, w)

w component is added to make the vector *homogeneous* -> typically set to 1.0
x, y, z values might later be divided by w (when in 1.0 leaves x, y, z alone)
```c++
vec4(-0.5f, 1.0f, -0.2f, 1.0f);
```

**The w component**

Vertex position mostly done with a *vec3*. To transform *matrices* we need a *vec4*.

To transform a 3d vertex, you must multiply it by a **4 x 4** transformation matrix.

## Common vector operations
**Operations on vectors**: addition, subtraction, unary negation, ...
These operators perform a *per-component* calculations -> result in a vector of the same size as the input. Overriding the operations provide such functionalities.
```c++
vec3 a (1.0f, 2.0f, 3.0f);
vec3 b (4.0f, 5.0f, 6.0f);
vec3 c;

c = a + b;
c = a - b;
c += b;
c = -c;
```
