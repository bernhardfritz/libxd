# Typography

## Font

#### Description

Placeholder. Please refer to the [text example](examples/text.md) in the meanwhile.

---

## text()

#### Description

Draws text to the screen. Displays the information specified in the first parameter on the screen in the position specified by the additional parameters. A default font will be used unless a font is set with the [textFont()](typography.md) function and a default size will be used unless a font is set with [textSize()](typography.md). Change the color of the text with the [fill()](color.md) function. Change the outline of the text with the [stroke()](color.md) and [strokeWeight()](structure.md) functions.

#### Syntax

```C++
text(str, x, y)
```

#### Parameters

`str` string: the alphanumeric symbols to be displayed

`x` float: x-coordinate of text

`y` float: x-coordinate of text

---

## textFont()

#### Description

Sets the current font that will be drawn with the text() function.

#### Syntax

```C++
textFont(font)
```

#### Parameters

`font` Font: a font that has been properly setup following the instructions described [here](typography.md#Font).

---

## textSize()

#### Description

Sets the current font size. This size will be used in all subsequent calls to the [text()](typography.md#text) function. Font size is measured in pixels.

#### Syntax

```C++
textSize(theSize)
```

#### Parameters

`theSize` float: the size of the letters in units of pixels
