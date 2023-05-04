add_rules("mode.release", "mode.debug") 

add_requires("v8", "sfml", "cppzmq", "gtest")
set_languages("c++17")

add_defines("V8_COMPRESS_POINTERS")
add_includedirs("$(projectdir)/include")
add_packages("v8", "sfml", "cppzmq")

target("engine")
    set_kind("static")
    add_files("src/*.cpp")
    
includes("examples/**/xmake.lua", "test")
