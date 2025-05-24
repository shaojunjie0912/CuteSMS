target("protocol_rtp", function () 
    set_kind("static")
    add_files("src/**.cpp")
    add_includedirs("include", { public = true })
    add_deps("base")
end)

