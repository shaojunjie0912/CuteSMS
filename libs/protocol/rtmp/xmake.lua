target("protocol-rtmp", function () 
    set_kind("static")
    add_files("**.cpp")
    add_deps("base")
end)

