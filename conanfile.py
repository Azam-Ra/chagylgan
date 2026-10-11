from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ChagylganConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "utfcpp/4.2.1"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)
