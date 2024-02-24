#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
from conans.tools import Version
from os import mkdir, path, remove


required_conan_version = ">=1.48.0"

class CommonLibSSE(ConanFile):
    name = "commonlibsse-ng"
    version = "3.5.0"
    license = "MIT"
    url = "https://github.com/CharmedBaryon/CommonLibSSE"
    description = "A fork of CommonLibSSE with advanced features for modern SKSE development."
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "testing": [True, False],
        "ae": [True, False],
        "se": [True, False],
        "vr": [True, False],
        "xbyak": [True, False]
    }
    default_options = {
        "testing": False,
        "ae": True,
        "se": True,
        "vr": True,
        "xbyak": False,
        "spdlog:header_only": True
    }
    exports_sources = "CMakeLists.txt", "CMakePresets.json", "cmake/**", "include/**", "src/**", "tests/**", \
                      ".clang-format", "CommonLibSSE.natvis"

    def requirements(self):
        if self.options.testing:
            self.requires("catch2/3.1.0")
        self.requires("rapidcsv/8.62")
        self.requires("spdlog/1.10.0")
        self.requires("xbyak/6.61.2")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

        # Project requires using existing CMake presets, remove the generated user presets file.
        user_presets = path.join(self.source_folder, "CMakeUserPresets.json")
        if path.exists(user_presets):
            remove(user_presets)

    def configure(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration("Windows is the only supported OS")
        if self.settings.compiler != "Visual Studio":
            raise ConanInvalidConfiguration("Unsupported compiler provided, only Visual Studio is supported")
        if Version(self.settings.compiler.version) < "16":
            raise ConanInvalidConfiguration("Visual Studio 2019 (MSVC 16) or newer is required")
        if self.settings.arch != "x86_64":
            raise ConanInvalidConfiguration("x86_64 is the only supported architecture")

    def build(self):
        defs = {"ENABLE_SKYRIM_AE": "ON" if self.options.ae else "OFF",
                "ENABLE_SKYRIM_SE": "ON" if self.options.se else "OFF",
                "ENABLE_SKYRIM_VR": "ON" if self.options.vr else "OFF",
                "BUILD_TESTS": "ON" if self.options.testing else "OFF",
                "SKSE_SUPPORT_XBYAK": "ON" if self.options.xbyak else "OFF"}
        def_args = " ".join(['-D{}="{}"'.format(k, v) for k, v in defs.items()])
        build_type = str(self.settings.build_type).lower()
        self.run(f"cmake --preset=build-{build_type}-msvc-conan-all {def_args}", cwd=self.source_folder)
        self.run(f"cmake --build --preset={build_type}-msvc-conan-all", cwd=self.source_folder)

    def package(self):
        build_type = str(self.settings.build_type).lower()
        self.run(f'cmake --install "{path.join(self.build_folder, f"{build_type}-msvc-conan-all")}" ' +
                 f'--prefix "{self.package_folder}"', cwd=self.source_folder)
        self.copy("LICENSE*", dst="licenses",  ignore_case=True, keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["commonlibsse-ng"]
