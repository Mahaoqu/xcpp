add_requires("v8", "sfml", "cppzmq", "gtest")

target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("v8", "sfml", "cppzmq")
    add_defines("V8_COMPRESS_POINTERS")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_packages("gtest")
