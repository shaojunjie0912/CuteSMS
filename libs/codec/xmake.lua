includes("aac")
includes("av1")
includes("g711")
includes("h264")
includes("hevc")
includes("mp3")
includes("opus")

-- TODO: track??
target("codec", function ()
    set_kind("static")
    add_files("track.cpp")
    add_deps("codec_aac", "codec_av1", "codec_g711", "codec_h264", "codec_hevc", "codec_mp3", "codec_opus")
end)
