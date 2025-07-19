# README

This is the README documentation for the project __Z·Calculator__ *.Derivative(2025)* (hereinafter referred to as _Derivative_).

## How to build it?

This project supports the CMake build system, so the build process follows the conventions of the CMake build system. 
The build steps are as follows:

```shell
mkdir -p build/
cd build/
cmake ../
make
make install
```

To specify the installation directory, you can use the `-DCMAKE_INSTALL_PREFIX` option in the CMake command above.
For example, the following command installs the software to `${HOME}/.local`:

```shell
cmake ../ -DCMAKE_INSTALL_PREFIX=${HOME}/.local
```

## What Is It?

_Derivative_ is a subproject of the unreleased project __Z·Calculator__. __Z·Calculator__ is a highly extensible and 
portable universal symbolic computation model. It computes user inputs entered in the console while allowing users to 
modify the program itself using its built-in programming language _Origami_.

In _Derivative_, we retain a portion of __Z·Calculator__'s fundamental framework and have predefined several types and 
tree transformation functions related to derivative calculations.

This project will be continuously updated and maintained until it is merged as a model into an official release version 
of __Z·Calculator__.


## How to Use It?

In the console, you can enter any string conforming to the following syntax rules after the input prompt `>>`:

|name               |category           |format                         |
|-------------------|-------------------|-------------------------------|
|number             |OBJECT             |(consists of `0123456789-.`)   |
|variable           |OBJECT             |(consists of letters and `_`)  |
|Derivative         |SPECIAL            |D([expression],[variable])     |
|bracket            |SPECIAL            |([expression])                 |
|Addition           |OPERATION          |[expression]+[expression]      |
|Subtraction        |OPERATION          |[expression]-[expression]      |
|Multiplication     |OPERATION          |[expression]\*[expression]     |
|Division           |OPERATION          |[expression]/[expression]      |
|Power              |OPERATION          |[expression]^[expression]      |
|Square Root        |FUNCTION           |sqrt([expression])             |
|Cube Root          |FUNCTION           |cbrt([expression])             |
|Natural Exponent   |FUNCTION           |e^([expression])               |
|Decimal Exponent   |FUNCTION           |10^([expression])              |
|Natural Logarithm  |FUNCTION           |ln([expression])               |
|Decimal Logarithm  |FUNCTION           |lg([expression])               |
|Sine               |FUNCTION           |sin([expression])              |
|Cosine             |FUNCTION           |cos([expression])              |
|Tangent            |FUNCTION           |tan([expression])              |
|Cotangent          |FUNCTION           |cot([expression])              |
|Secant             |FUNCTION           |sec([expression])              |
|Cosecant           |FUNCTION           |csc([expression])              |
|Inverse Sine       |FUNCTION           |arcsin([expression])           |
|Inverse Cosine     |FUNCTION           |acrcos([expression])           |
|Inverse Tangent    |FUNCTION           |arctan([expression])           |
|Inverse Cotangent  |FUNCTION           |arccot([expression])           |
|Inverse Secant     |FUNCTION           |arcsec([expression])           |
|Inverse Cosecant   |FUNCTION           |arccsc([expression])           |
(where [expression] consists of objects, functions and operations)

_Derivative_ will return the result after the output prompt `->`.

Here are some examples:

`>> D(arctan(ln(x+a)),x)`

`-> 1/((x+a)*(1+ln(x+a)^2))`

`>> D(sin(x)+x^3,x)`

`-> cosx+(x^3*3)/x`

> The excitement continues. Stay tuned.


## How to Contribute?

If you have any ideas regarding project __Z·Calculator__, please email us at jokerxin@126.com or collaborate with us on GitHub. Thank you for your strong support of project __Z·Calculator__!
