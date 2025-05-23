add_packages("boost")

target("test_io_context", function () 
    set_kind("binary")
    add_files("test_io_context.cpp")
end)