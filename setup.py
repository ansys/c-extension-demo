"""Setup file for points_demo."""

from io import open as io_open
import os
from setuptools import setup, Extension, find_packages

# get version from version info
__version__ = None
this_file = os.path.dirname(__file__)
version_file = os.path.join(this_file, "points_demo", "_version.py")
with io_open(version_file, mode="r") as fd:
    # execute file from raw string
    exec(fd.read())

setup(
    version = __version__,
    name="points-demo",
    packages=['points_demo'],
    package_data = {
            '': [ '**.txt', '**.md', '**.py', '**.h', '**.hpp', '**.c', '**.cpp' ],
        },

    # build the extension modules
    ext_modules = [
        Extension(
            name = 'points_demo.point',
            sources = [
                'src/point.c',
            ],
            include_dirs = ['src'],
        )
    ],
)
