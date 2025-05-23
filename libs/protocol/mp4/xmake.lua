target("protocol_mp4", function () 
    set_kind("static")
    add_files("src/**.cpp")
    add_includedirs("include", { public = true })
    add_deps("base")
end)

