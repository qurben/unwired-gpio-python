#!/usr/bin/python

from distutils.core import setup, Extension

__version__ = "0.1"

macros = [('MODULE_VERSION', __version__)]

setup(name         = "unwired-gpio-python",
      version      = __version__,
      author       = "G.J.W. Oolbekkink",
      author_email = "g.j.w.oolbekkink@gmail.com",
      url          = "https://github.com/qurben/unwired-gpio-python",
      download_url = "https://github.com/qurben/unwired-gpio-python",
      description  = "GPIO bindings for Python for the Unwired One",
      license      = "MIT",
      platforms    = ["Unwired One"],
      ext_modules  = [
        Extension(name='unwired.gpio', sources=['unwired/gpio.c','unwired/native-gpio.c'], define_macros=macros)
      ]
)