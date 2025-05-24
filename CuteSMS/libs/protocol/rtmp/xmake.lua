target("protocol_rtmp", function () 
    set_kind("static")
    add_files("**.cpp")
    add_includedirs("include", { public = true })
    add_deps("base")
end)

