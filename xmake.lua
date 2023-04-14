add_requires("v8", "sfml", "cppzmq", "gtest")
set_languages("c++17")

target("main")
    set_kind("shared")
    add_files("src/*.cpp")
    add_packages("v8", "sfml", "cppzmq")
    add_defines("V8_COMPRESS_POINTERS")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_packages("gtest")
    if is_plat("windows") then
        -- fixes "LINK : fatal error LNK1561: entry point must be defined"
        add_ldflags("/subsystem:console")
    end
