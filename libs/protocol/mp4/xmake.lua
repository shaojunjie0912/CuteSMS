target("protocol_mp4", function () 
    set_kind("static")
    add_files("**.cpp")
    add_deps("base")
end)