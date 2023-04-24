target("test")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("gtest")
    if is_plat("windows") then
        -- fixes "LINK : fatal error LNK1561: entry point must be defined"
        add_ldflags("/subsystem:console")
    end
