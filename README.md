# cpp-documentation-example
An example of setting up Sphinx for C++ and building with CMake and Read the Docs

See the documentation [here](https://cpp-documentation-example.readthedocs.io/en/latest/)

## Dependencies

- [Python3](https://www.python.org/downloads/)
- [CMake](https://cmake.org/download/)
- [Doxygen](http://www.doxygen.nl/download.html)

## Activating

Activate the environment by running `activate.sh` or `activate.bat`
This also compiles the code and the documentation

## Building

Building the code as well as the documentation: `make`

## Rebuilding

To fix some dependencies: `make clean`
And sometimes: `cmake --build .`

## Usage

If you want to reuse this as a starting point for your development:

### Virtual environment

- Rename the virtual environment in `activate.*` and adapt `.gitignore` accordingly
- run `deactivate`
- remove the old virtual environment
- activate again


### Rename MySuperApp in

- `CMakeLists.txt` : To adapt the name of the CMake project (used as: `@CMAKE_PROJECT_NAME@`)
- `docs/source/conf.py` : Configuration of the Sphinx/Breathe documentation
  


