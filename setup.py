import re
from setuptools import setup, Extension, find_packages

__version__ = '0.1.0'

PACKAGE_NAME = 'points-demo'
SOURCE_DIRECTORY = 'src'
SOURCE_PACKAGE_REGEX = re.compile(rf'^{SOURCE_DIRECTORY}')

source_packages = find_packages(include=[SOURCE_DIRECTORY, f'{SOURCE_DIRECTORY}.*'])
proj_packages = [SOURCE_PACKAGE_REGEX.sub(PACKAGE_NAME, name) for name in source_packages]


setup(
    version = __version__,
    name=PACKAGE_NAME,
    packages=proj_packages,
    package_dir={PACKAGE_NAME: SOURCE_DIRECTORY},
    package_data = {
            '': [ '**.txt', '**.md', '**.py', '**.h', '**.hpp', '**.c', '**.cpp' ],
        },
    ext_modules = [
        Extension(
            name = 'src/points_demo.point',
            sources = [
                'src/c_point/point.c',
            ],
            include_dirs = ['src'],
        )
    ],
)
