target("codec_aac", function ()
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", {public = true})
    add_deps("protocol_rtp", "protocol_sdp", "codec_base")
    add_packages("faac", "faad2")
end)

