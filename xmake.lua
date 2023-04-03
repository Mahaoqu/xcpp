add_requires("v8", "sfml", "zeromq")

target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("v8")
    add_defines("V8_COMPRESS_POINTERS")