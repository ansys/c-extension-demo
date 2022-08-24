"""
Test the functionality of C extension class point_demo.Point 

"""
import points_demo


def test_point_init_blank():
    point = points_demo.Point()
    assert point.x == 0
    assert point.y == 0
    assert point.z == 0


def test_point_init_specified():
    x = 1
    y = 2
    z = -3.5
    point = points_demo.Point(x=x, y=y, z=z)
    assert point.x == x
    assert point.y == y
    assert point.z == z


def test_point_clear():
    point = points_demo.Point(x=1, y=2, z=3)
    point.clear()
    assert point.x == 0
    assert point.y == 0
    assert point.z == 0


def test_point_repr():
    x = 1
    y = 2
    z = -3.5
    point = points_demo.Point(x=x, y=y, z=z)
    assert f"{x}" in str(point)
    assert f"{y}" in str(point)
    assert f"{z}" in str(point)
