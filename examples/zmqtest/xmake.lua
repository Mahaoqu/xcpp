add_packages("cppzmq")

target("zmqtest-server")
    set_kind("binary")
    add_files("server.cpp")

target("zmqtest-client")
    set_kind("binary")
    add_files("client.cpp")

