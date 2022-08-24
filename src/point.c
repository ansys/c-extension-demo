#define PY_SSIZE_T_CLEAN
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

static int
Point_init(PointObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"x", "y", "z", NULL};
    PyObject *x = NULL, *y = NULL, *z = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOO", kwlist,
                                     &x, &y, &z))
        return -1;

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

static PyMemberDef Point_members[] = {
    {"x", T_DOUBLE, offsetof(PointObject, x), 0,
     "X Position."},
    {"y", T_DOUBLE, offsetof(PointObject, y), 0,
     "Y Position."},
    {"z", T_DOUBLE, offsetof(PointObject, z), 0,
     "Z Position."},
    {NULL}  /* Sentinel */
};


// Clear the point by setting all coordinates to 0.0
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

    int strlen = snprintf(buffer, sizeof(buffer), "Point(%f, %f, %f)", self->x, self->y, self->z);
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

// PointType object definition
static PyTypeObject PointType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "point.Point",
    .tp_doc = PyDoc_STR("Point objects"),
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

// Module definition
static PyModuleDef custommodule = {
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
    if (PyType_Ready(&PointType) < 0)
        return NULL;

    m = PyModule_Create(&custommodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PointType);
    if (PyModule_AddObject(m, "Point", (PyObject *) &PointType) < 0) {
        Py_DECREF(&PointType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
