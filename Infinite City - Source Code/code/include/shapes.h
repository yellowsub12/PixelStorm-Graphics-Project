#pragma once

#ifndef SHAPES_H
#define SHAPES_H

int createLine();

//Creates a VBO of a unit cube and adds it to the GPU
int createUnitCube(bool frontFaceOpaque);

int createUnitCubeReversed();

int createUnitPlane();

int createUnitPyramid();

#endif SHAPES_H


