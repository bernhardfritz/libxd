# Color

## background()

#### Description

The `background()` function sets the color used for the background of the window. The default background is light gray. This function is typically used within [draw()](structure.md#draw) to clear the display window at the beginning of each frame, but it can be used inside [setup()](structure.md#setup) to set the background on the first frame of animation or if the background need only be set once.

#### Syntax

```C++
background(color)
```

#### Parameters

`color` vec4: any value of datatype vec4

---

## clear()

#### Description

This function clears everything to make all of the pixels 100% transparent.

#### Syntax

```C++
clear()
```

---

## fill()

#### Description

Sets the color used to fill shapes. For example, if you run `fill(vec4(0.8f, 0.4f, 0.0f, 1.0f))`, all subsequent shapes will be filled with orange.

#### Syntax

```C++
fill(color)
```

#### Parameters

`color` vec4: any value of datatype vec4

---

## noFill()

#### Description

Disables filling geometry. If both [noStroke()](color.md#noStroke) and [noFill()](color.md#noFill) are called, nothing will be drawn to the screen.

#### Syntax

```C++
noFill()
```

---

## noStroke()

#### Description

Disables drawing the stroke (outline). If both [noStroke()](color.md#noStroke) and [noFill()](color.md#noFill) are called, nothing will be drawn to the screen.

#### Syntax

```C++
noStroke()
```

---

## stroke()

#### Description

Sets the color used to draw lines and borders around shapes.

#### Syntax

```C++
stroke(color)
```

#### Parameters

`color` vec4: any value of datatype vec4
