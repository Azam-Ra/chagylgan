from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ChagylganConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "utfcpp/4.2.1", "llvm-core/19.1.7"
    generators = "CMakeDeps", "CMakeToolchain"

    # Compilation for z3 lib fails, so we skip it for now
    # z3 is not a strict requirement for IR facilities
    default_options = {
      "llvm-core/*:with_z3": False,
    }

    def layout(self):
        cmake_layout(self)
