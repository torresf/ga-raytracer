# ga-raytracer

> Florian Torres

Geometric Algebra 2D Raytracer using c2ga (from Garamon) and OpenGL.

## Getting started

```bash
git clone https://github.com/torresf/ga-raytracer
cd ga-raytracer
mkdir build
cd build
cmake ..
make -j
src/ga-raytracer
```

## Notes

The inner product of two normalized points gives the square of the Euclidean distance.

## Optimisation

- [x] glTexImage2D
- [x] Randomize array of pixel to draw
- [x] Draw only range by range of pixels
- [x] In fragment shader, fill the blanks based on neighbours pixels color.

## TODO

- [x] Create point
- [x] Create point pair
- [x] Create line
- [x] Create circle
- [x] Intersect lines
- [x] Intersect circles
- [x] Project point on line
- [x] Project point on circle
- [x] Display the two points from a point pair
- [x] IsPointInCircle
- [x] Fix mirror bug in intersection with circle
- [ ] Check for memory leak
