target("game3-client")
    set_kind("binary")
    add_files("*.cpp|server.cpp")
    add_deps("engine")
    set_rundir(os.scriptdir())

target("game3-server")
    set_kind("binary")
    add_files("*.cpp|client.cpp")
    add_deps("engine")
    set_rundir(os.scriptdir())