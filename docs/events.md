# Events

## mouseMoved()

#### Description

The `mouseMoved()` function can be used to define a callback function that is called every time the mouse moves. The callback function (typically called onMouseMoved) ought to have 2 floating-point parameters representing the mouse position.

#### Syntax

```C++
mouseMoved(onMouseMoved)
```

#### Parameters

`onMouseMoved` void (*onMouseMoved)(float, float): the callback function

---

## mousePressed()

#### Description

The `mousePressed()` function can be used to define a callback function that is called every time a mouse button is pressed. The callback function (typically called onMousePressed) ought to have 1 integer parameter representing the mouse button identifier.

#### Syntax

```C++
mousePressed(onMousePressed)
```

#### Parameters

`onMousePressed` void (*onMousePressed)(int): the callback function

---

## mouseReleased()

#### Description

The `mouseReleased()` function can be used to define a callback function that is called every time a mouse button is released. The callback function (typically called onMouseReleased) ought to have 1 integer parameter representing the mouse button identifier.

#### Syntax

```C++
mouseReleased(onMouseReleased)
```

#### Parameters

`onMouseReleased` void (*onMouseReleased)(int): the callback function

---

## mouseWheel()

#### Description

The `mouseWheel()` function can be used to define a callback function that is called every time a vertical mouse event is detected, either triggered by an actual mouse or by a touchpad. The callback function (typically called onMouseWheel) ought to have 1 floating-point parameter representing the amount the mouse wheel has scrolled since the last frame.

#### Syntax

```C++
mouseWheel(onMouseWheel)
```

#### Parameters

`onMouseWheel` void (*onMouseWheel)(float): the callback function
