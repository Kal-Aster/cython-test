all:
	python setup.py build_ext -if

clean:
	-rm -r Quaternion.cpp *.so *.pyd build
