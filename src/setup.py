#!/usr/bin/python
#-*coding:utf-8*-

from distutils.core import setup, Extension

baserun = Extension('baserun',
                sources = ['baserun.c','convert.c','access.c','limit.c','run.c','diff.c'],
                )

setup (name = 'baserun',
       version = '1.0',
       description = 'baserun judge',
       ext_modules = [baserun]
      )
