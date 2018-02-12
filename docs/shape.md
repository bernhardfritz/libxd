# Shape

## ellipse()

#### Description

Draws an ellipse (oval) to the screen. An ellipse with equal width and height is a circle. By default, the first two parameters set the location, and the third and fourth parameters set the shape's width and height. The origin may be changed with the [ellipseMode()](shape.md#ellipseMode) function.

#### Syntax

```C++
ellipse(x, y, w, h)
```

#### Parameters

`x` float: x-coordinate of the ellipse

`y` float: y-coordinate of the ellipse

`w` float: width of the ellipse

`h` float: height of the ellipse

---

## ellipseMode()

#### Description

Modifies the location from which ellipses are drawn by changing the way in which parameters given to [ellipse()](shape.md#ellipse) are interpreted.

The default mode is `ellipseMode(CENTER)`, which interprets the first two parameters of [ellipse()](shape.md#ellipse) as the shape's center point, while the third and fourth parameters are its width and height.

`ellipseMode(RADIUS)` also uses the first two parameters of [ellipse()](shape.md#ellipse) as the shape's center point, but uses the third and fourth parameters to specify half of the shapes's width and height.

`ellipseMode(CORNER)` interprets the first two parameters of [ellipse()](shape.md#ellipse) as the upper-left corner of the shape, while the third and fourth parameters are its width and height.

`ellipseMode(CORNERS)` interprets the first two parameters of [ellipse()](shape.md#ellipse) as the location of one corner of the ellipse's bounding box, and the third and fourth parameters as the location of the opposite corner.

The parameter must be written in ALL CAPS because C++ is a case-sensitive language.

#### Syntax

```C++
ellipseMode(mode)
```

#### Parameters

`mode` DrawMode: either CENTER, RADIUS, CORNER, or CORNERS

---

## line()

#### Description

Draws a line (a direct path between two points) to the screen. To color a line, use the [stroke()](color.md#stroke) function. A line cannot be filled, therefore the [fill()](color.md#fill) function will not affect the color of a line. Lines are drawn with a width of one pixel by default, but this can be changed with the [strokeWeight()](structure.md#strokeWeight) function.

#### Syntax

```C++
line(x1, y1, x2, y2)
```

#### Parameters

`x1` float: x-coordinate of the first point

`y1` float: y-coordinate of the first point

`x2` float: x-coordinate of the second point

`y2` float: y-coordinate of the second point

---

## point()

#### Description

Draws a point (a single pixel) to the screen. To color a point, use the [stroke()](color.md#stroke) function. A point cannot be filled, therefore the [fill()](color.md#fill) function will not affect the color of a point.

#### Syntax

```C++
point(x, y)
```

#### Parameters

`x` float: x-coordinate of the point

`y` float: y-coordinate of the point

---

## rect()

#### Description

Draws a rectangle to the screen. A rectangle is a four-sided shape with every angle at ninety degrees. By default, the first two parameters set the location of the upper-left corner, the third sets the width, and the fourth sets the height. The way these parameters are interpreted, however, may be changed with the [rectMode()](shape.md#rectMode) function.

#### Syntax

```C++
rect(x, y, w, h)
```

#### Parameters

`x` float: x-coordinate of the rectangle

`y` float: y-coordinate of the rectangle

`w` float: width of the rectangle

`h` float: height of the rectangle

---

## rectMode()

#### Description

Modifies the location from which rectangles are drawn by changing the way in which parameters given to [rect()](shape.md#rect) are interpreted.

The default mode is `rectMode(CORNER)`, which interprets the first two parameters of [rect()](shape.md#rect) as the upper-left corner of the shape, while the third and fourth parameters are its width and height.

`rectMode(CORNERS)` interprets the first two parameters of [rect()](shape.md#rect) as the location of one corner, and the third and fourth parameters as the location of the opposite corner.

`rectMode(CENTER)` interprets the first two parameters of [rect()](shape.md#rect) as the shape's center point, while the third and fourth parameters are its width and height.

`rectMode(RADIUS)` also uses the first two parameters of [rect()](shape.md#rect) as the shape's center point, but uses the third and fourth parameters to specify half of the shapes's width and height.

The parameter must be written in ALL CAPS because C++ is a case-sensitive language.

#### Syntax

```C++
rectMode(mode)
```

#### Parameters

`mode` DrawMode: either CORNER, CORNERS, CENTER, or RADIUS

---

## triangle()

#### Description

A triangle is a plane created by connecting three points. The first two arguments specify the first point, the middle two arguments specify the second point, and the last two arguments specify the third point.

#### Syntax

```C++
triangle(x1, y1, x2, y2, x3, y3)
```

#### Parameters

`x1` float: x-coordinate of the first point

`y1` float: y-coordinate of the first point

`x2` float: x-coordinate of the second point

`y2` float: y-coordinate of the second point

`x3` float: x-coordinate of the third point

`y3` float: y-coordinate of the third point
