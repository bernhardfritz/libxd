# Structure

## destroy()

#### Description

The `destroy()` function is called once the program is about to end. It should be used to free memory that has previously been allocated on the heap (i.e. by [Image](image.md#Image)). There can only be one `destroy()` function for each program and it is mandatory to implement this function even if there is no memory to be freed. An empty function body should suffice in this case.

#### Syntax

```C++
destroy()
```

---

## draw()

#### Description

Called directly after [setup()](structure.md#setup), the `draw()` function continuously executes the lines of code contained inside its block until the program is stopped or [noLoop()](structure.md#noLoop) is called. Note if [noLoop()](structure.md#noLoop) is called in [setup()](structure.md#setup), [draw()](structure.md#draw) will still be executed once before stopping. [draw()](structure.md#draw) is called automatically and should never be called explicitly.

It should always be controlled with [noLoop()](structure.md#noLoop), [redraw()](structure.md#redraw) and [loop()](structure.md#loop). After [noLoop()](structure.md#noLoop) stops the code in `draw()` from executing, redraw() causes the code inside `draw()` to execute once, and [loop()](structure.md#loop) will cause the code inside `draw()` to resume executing continuously. 

#### Syntax

```C++
draw()
```

---

## loop()

#### Description

By default, **libxd** loops through [draw()](structure.md#draw) continuously, executing the code within it. However, the [draw()](structure.md#draw) loop may be stopped by calling [noLoop()](structure.md#noLoop). In that case, the [draw()](structure.md#draw) loop can be resumed with `loop()`.

#### Syntax

```C++
loop()
```

---

## noLoop()

#### Description

Stops **libxd** from continuously executing the code within [draw()](structure.md#draw). If [loop()](structure.md#loop) is called, the code in [draw()](structure.md#draw) begins to run continuously again. If using `noLoop()` in [setup()](structure.md#setup), it should be the last line inside the block.

When `noLoop()` is used, it's not possible to manipulate or access the screen inside event handling functions such as [mousePressed()](events.md#mousePressed) or [keyPressed()](events.md#keyPressed). Instead, use those functions to call [redraw()](structure.md#redraw) or [loop()](structure.md#loop), which will run [draw()](structure.md#draw), which can update the screen properly.

Note that if the sketch is resized, [redraw()](structure.md#redraw) will be called to update the sketch, even after `noLoop()` has been specified. Otherwise, the sketch would enter an odd state until [loop()](structure.md#loop) was called.

#### Syntax

```C++
noLoop()
```

---

## push()

#### Description

The `push()` function saves the current drawing style settings and transformations, while [pop()](structure.md#pop) restores these settings. Note that these functions are always used together. They allow you to change the style and transformation settings and later return to what you had. When a new state is started with `push()`, it builds on the current style and transform information. The `push()` and [pop()](structure.md#pop) functions can be embedded to provide more control.

`push()` stores information related to the current transformation state and style settings controlled by the following functions: [fill()](color.md#fill), [stroke()](color.md#stroke), [strokeWeight()](structure.md#strokeWeight), [imageMode()](image.md#imageMode), [rectMode()](shape.md#rectMode), [ellipseMode()](shape.md#ellipseMode).

---

## pop()

#### Description

The [push()](structure.md#push) function saves the current drawing style settings and transformations, while `pop()` restores these settings. Note that these functions are always used together. They allow you to change the style and transformation settings and later return to what you had. When a new state is started with [push()](structure.md#push), it builds on the current style and transform information. The [push()](structure.md#push) and `pop()` functions can be embedded to provide more control.

[push()](structure.md#push) stores information related to the current transformation state and style settings controlled by the following functions: [fill()](color.md#fill), [stroke()](color.md#stroke), [strokeWeight()](structure.md#strokeWeight), [imageMode()](image.md#imageMode), [rectMode()](shape.md#rectMode), [ellipseMode()](shape.md#ellipseMode).

---

## redraw()

#### Description

Executes the code within [draw()](structure.md#draw) one time. This functions allows the program to update the display window only when necessary, for example when an event registered by [mousePressed()](events.md#mousePressed) or [keyPressed()](events.md#keyPressed) occurs.

In structuring a program, it only makes sense to call `redraw()` within events such as [mousePressed()](events.md#mousePressed). This is because `redraw()` does not run [draw()](structure.md#draw) immediately (it only sets a flag that indicates an update is needed).

The `redraw()` function does not work properly when called inside [draw()](structure.md#draw). To enable/disable animations, use [loop()](structure.md#loop) and [noLoop()](structure.md#noLoop).

#### Syntax

```C++
redraw()
```

---

## setup()

#### Description

The `setup()` function is called once when the program starts. It's used to define initial environment properties such as screen size and background color and to load media such as images and fonts as the program starts. There can only be one `setup()` function for each program and it shouldn't be called again after its initial execution.

Note: Variables declared within `setup()` are not accessible within other functions, including [draw()](structure.md#draw).

#### Syntax

```C++
setup()
```

---

## strokeWeight()

#### Description

Sets the width of the stroke used for lines, points, and the border around shapes. All widths are set in units of pixels.

#### Syntax

strokeWeight(weight)

#### Parameters

`weight` float: the weight (in pixels) of the stroke 
