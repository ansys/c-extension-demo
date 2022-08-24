import points_demo


def test_point():
    point = points_demo.Point()
    assert point.x == 0
    assert point.y == 0
    assert point.z == 0
