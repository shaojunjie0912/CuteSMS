target("codec_g711", function ()
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", { public = true })
    add_deps("protocol_rtp", "protocol_sdp")
end)

