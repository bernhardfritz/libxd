# Math

## random()

#### Description

Returns a random floating-point number from the first argument up to (but not including) the second argument.

#### Syntax

```C++
random(min, max)
```

#### Parameters

`min` float: the lower bound (inclusive)

`max` float: the upper bound (exclusive)

#### Returns

float: the random number

---

## randomSeed()

#### Description

Sets the seed value for [random()](math.md#random). By default, [random()](math.md#random) produces different results each time the program is run. Set the `seed` parameter to a constant to return the same pseudo-random numbers each time the software is run.

#### Syntax

```C++
randomSeed(seed)
```

#### Parameters

`seed` unsigned int: seed value
