In order to build the external dependencies need to be placed in
the folder containing this file.  Current dependencies are in a zip
file found in the cpf releases area.  Download the file, decompress
and copy the contents to Cpf/External/Source.  Generate using CMake
and it will inject the dependencies into the build.

The dependencies will eventually be built into plugins in the future
in order to remove the overhead of including the sources in the
projects.  This will also allow things like physics to be built using
release while the rest of the engine is debug.
