from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = Extension("Quaternion",
                sources=["Quaternion.pyx", "Quaternion.cpp"],
                language="c++")

setup(name="RNG",
      ext_modules=cythonize(ext))
