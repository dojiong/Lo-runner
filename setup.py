#!/usr/bin/python
#-*coding:utf-8*-

from distutils.core import setup, Extension


sources = [
    'lorun/cext/lorun.c', 'lorun/cext/convert.c', 'lorun/cext/access.c',
    'lorun/cext/limit.c', 'lorun/cext/run.c', 'lorun/cext/diff.c'
]

setup(name='lorun',
    version='1.0.1',
    description='loco program runner core',
    ext_modules=[Extension('lorun/_lorun_ext', sources=sources)],
    packages=['lorun']
)
