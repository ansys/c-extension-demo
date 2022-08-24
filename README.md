## CPython - Creating an Extension Type

This repository contains a simple demo to create a new `Point` class directly
from the CPython C-API. It seeks to extend the [Defining Extension Types:
Tutorial](https://docs.python.org/3/extending/newtypes_tutorial.html) by
including a `Makefile`, class example with attributes, and a `setup.py` and
shell library to demonstrate both integration with Python.

### Quick Demo

This `Point` can be imported directly from a shared library with:

```
>>> from point import Point
>>> point
Point(0.000000, 0.000000, 0.000000)
```

It contains basic functionality like getters and setters for `x`, `y`, and `z`
attributes as well as a `clear` method:

```
Examples
--------
Create a point.

>>> from point import Point
>>> point = Point()
>>> point
Point(0.0, 0.0, 0.0)

Modify the x coordinate.

>>> point.x = 2.0
>>> point.x
2.0

Initialize with non-default coordinates

>>> point = Point(x=2.0, y=-1.0, z=4.0)
>>> point
Point(2.0, -1.0, 4.0)

Clear the point.

>>> point.clear()
>>> point
Point(0.0, 0.0, 0.0)

```

## Build

This repository contains two approaches for building this extension module.

- Native C build using a `Makefile` to create a standalone `*.so`
- Build using `setup.py` and generate a self-contained `*.whl` or install in-place.

### Native C Build

You can build the CPython extension directly from `gcc` with make. This
`Makefile` assumes Python3.10, but you change the version of Python you're building against by changing ``-I/usr/include/python3.10``.

From this directory create the shared library ``point.so``.

```
$ make
$ ls bin
point.so
```

This library can be directly imported into Python from the `bin` directory with
`import point`. You can test this functionality with a simple command from
Python:

```
$ cd bin
$ python3.10 -c "from point import Point;my_point = Point(x=1.0, y=2.0, z=3.0);print(my_point)"
Point(1.000000, 2.000000, 3.000000)
```

#### Class description and help

The C Extension contains basic help as defined by the [tp_doc](https://docs.python.org/3/c-api/typeobj.html#c.PyTypeObject.tp_doc):

```
$ python3.10
>>> from point import Point
>>> help(Point)
Help on class Point in module point:

class Point(builtins.object)
 |  Examples
 |  --------
 |  Create a point.
 |  
 |  >>> from point import Point
 |  >>> point = Point()
 |  >>> point
 |  Point(0.0, 0.0, 0.0)
 |  
 |  Modify the x coordinate.
 |  
 |  >>> point.x = 2.0
 |  >>> point.x
 |  2.0
 |  
 |  Initialize with non-default coordinates
 |  
 |  >>> point = Point(x=2.0, y=-1.0, z=4.0)
 |  >>> point
 |  Point(2.0, -1.0, 4.0)
 |  
 |  Clear the point.
 |  
 |  >>> point.clear()
 |  >>> point
 |  Point(0.0, 0.0, 0.0)
 |  
 |  Methods defined here:
 |  
 |  __init__(self, /, *args, **kwargs)
 |      Initialize self.  See help(type(self)) for accurate signature.
 |  
 |  __repr__(self, /)
 |      Return repr(self).
 |  
 |  clear(...)
 |      Clear the point, effectively setting it to (0.0, 0.0, 0.0).
 |  
 |  ----------------------------------------------------------------------
 |  Static methods defined here:
 |  
 |  __new__(*args, **kwargs) from builtins.type
 |      Create and return a new object.  See help(type) for accurate signature.
 |  
 |  ----------------------------------------------------------------------
 |  Data descriptors defined here:
 |  
 |  x
 |      X Position.
 |  
 |  y
 |      Y Position.
 |  
 |  z
 |      Z Position.
```

### From `setup.py`

Alternatively, you can create the extension as a self-contained Python wheel
using ``setup.py``. This effectively replaces the functionality of the
`Makefile` and always builds with the version of Python invoking `setup.py`.

Create the Python wheel using the [build](https://pypi.org/project/build/)
package with:

```
$ pip install build
$ python -m build --wheel
$ ls dist/
points_demo-0.1.dev0-cp38-cp38-linux_x86_64.whl
```

This wheel can then be installed with:

```
pip install dist/*
```

Alternatively, you can install this package in-place in development mode with:
```
pip install -e .
```

The advantage of this approach is you can quickly rebuild the package as needed
without having to perform a full reinstall from a wheel.

This installs the `points-demo` package, which is simply a shell around.



#### Testing the package

This repository contains the `test` directory with several unit tests to
validate the `Point` class. Install the testing requirements with:


```
pip install -r requirements_test.txt
```

And run the unit tests with:

```
$ pytest
==================================== test session starts =====================================
platform linux -- Python 3.10.6, pytest-7.1.2, pluggy-1.0.0
rootdir: /home/akaszyns/source/cpython-class-extension
collected 4 items                                                                            

tests/test_point_demo.py ....                                                          [100%]

===================================== 4 passed in 0.01s ======================================
```
