#include <Python.h>
#include "structmember.h"

/* 

Point Module.

This module defines a new Point class using the CPython C-API

Class contains x, y, and z double attributes and a single clear method.

Class should be nearly identical to the following python class:

class Point:
    """Point Class

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

    """

    def __init__(self, *, x=0.0, y=0.0, z=0.0):
        self.x = x
        self.y = y
        self.z = z

    def clear(self):
        """Clear this point."""
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0

    def __repr__(self):
        return f"Point({self.x}, {self.y}, {self.z})"

*/


// PointObject defintion
typedef struct {
  PyObject_HEAD
  double x; // X position
  double y; // X position
  double z; // X position
} PointObject;

static void
Point_dealloc(PointObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
Point_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PointObject *self;
    self = (PointObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->x = 0.0;
        self->y = 0.0;
        self->z = 0.0;
    }
    return (PyObject *) self;
}

// __init__ Constructor for the PointType class
static int
Point_init(PointObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"x", "y", "z", NULL};
    PyObject *x = NULL, *y = NULL, *z = NULL;

    // Accept at maximum three python objects. At runtime these will be type checked
    // due to PyFloat_AsDouble.
    //
    // Note how there is nothing before |, indicating that this constructor
    // accepts no args. These kwarg args are optional.
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOO", kwlist, &x, &y, &z))
        return -1;

    // Convert the python object to a C double
    if (x) {
      self->x = PyFloat_AsDouble(x);
    }
    if (y) {
      self->y = PyFloat_AsDouble(y);
    }
    if (z) {
      self->z = PyFloat_AsDouble(z);
    }
    return 0;
}

// This section contains the defintion of the class attributes (members)
static PyMemberDef Point_members[] = {
    {"x", T_DOUBLE, offsetof(PointObject, x), 0,
     "X Position."},
    {"y", T_DOUBLE, offsetof(PointObject, y), 0,
     "Y Position."},
    {"z", T_DOUBLE, offsetof(PointObject, z), 0,
     "Z Position."},
    {NULL}  /* Sentinel */
};


// Method clearing the PointObject by setting all coordinates to 0.0
static PyObject *
Point_clear(PointObject *self, PyObject *Py_UNUSED(ignored))
{
  self->x = 0.0;
  self->y = 0.0;
  self->z = 0.0;
  return Py_None;
}


// __repr__ of PointType
static PyObject *
point_repr(PointObject *self)
{
    PyObject *result;
    char buffer[100];

    int strlen = snprintf(buffer, sizeof(buffer), "Point(%f, %f, %f)",
                          self->x, self->y, self->z);
    result = _PyUnicode_FromASCII(buffer, strlen);
    return result;
}


// Define the methods of PointObject
static PyMethodDef Point_methods[] = {
    {"clear", (PyCFunction) Point_clear, METH_NOARGS,
     "Clear the point, effectively setting it to (0.0, 0.0, 0.0)."
    },
    {NULL}  /* Sentinel */
};

// PointType class definition
static PyTypeObject PointType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "point.Point",
    .tp_doc = PyDoc_STR(
"Examples\n"
"--------\n"
"Create a point.\n"
"\n"
">>> from point import Point\n"
">>> point = Point()\n"
">>> point\n"
"Point(0.0, 0.0, 0.0)\n"
"\n"
"Modify the x coordinate.\n"
"\n"
">>> point.x = 2.0\n"
">>> point.x\n"
"2.0\n"
"\n"
"Initialize with non-default coordinates\n"
"\n"
">>> point = Point(x=2.0, y=-1.0, z=4.0)\n"
">>> point\n"
"Point(2.0, -1.0, 4.0)\n"
"\n"
"Clear the point.\n"
"\n"
">>> point.clear()\n"
">>> point\n"
"Point(0.0, 0.0, 0.0)\n"),
    .tp_basicsize = sizeof(PointObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Point_new,
    .tp_init = (initproc) Point_init,
    .tp_dealloc = (destructor) Point_dealloc,
    .tp_members = Point_members,
    .tp_methods = Point_methods,
    .tp_repr = (reprfunc)point_repr,
};

// Module definition. This includes the name and docstring of the module.
static PyModuleDef point_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "point",
    .m_doc = "Example point module that contains the Point class.",
    .m_size = -1,
};

// Initialize the module
PyMODINIT_FUNC
PyInit_point(void)
{
    PyObject *m;
    m = PyModule_Create(&point_module);
    if (m == NULL)
        return NULL;

    if (PyType_Ready(&PointType) < 0)
        return NULL;

    // Define the point class here
    Py_INCREF(&PointType);
    if (PyModule_AddObject(m, "Point", (PyObject *) &PointType) < 0) {
        Py_DECREF(&PointType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
