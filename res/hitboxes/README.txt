Creating and editing hitboxes - guide.

1. File
Plain-text ASCII with the basename without extension. The basename must be the
same as the bitmap/directory name placed in the "textures" dir.

3. Theory
Every hitbox file contains from small rectangles with position and size. Note
that there is no possibility to create hitbox that contains more parts than
texture's pixels.

2. Syntax
(x, y) [w, h]

Every rectangle is described by its' position and size. Both in pixels. First
two values must be placed in the parenthesis and separated comma and at least
one space. Both of them points to the upper left corner of the rectangle.

x - horizontal position from the left side.
y - vertical one from up.
Above values can't be negative.

Separator between ')' and "[" is at least one space.

Width and height must be placed in the square brackets. Separated same as x and
y.

w - width.
h - height.
The minimal size of them equal 1.
