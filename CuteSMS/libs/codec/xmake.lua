includes("base")
includes("aac")
includes("av1")
includes("g711")
includes("h264")
includes("hevc")
includes("mp3")
includes("opus")

target("codec", function ()
    set_kind("phony")
    add_deps(
        "codec_base",
        "codec_aac",
        "codec_av1",
        "codec_g711",
        "codec_h264",
        "codec_hevc",
        "codec_mp3",
        "codec_opus"
    )
end)
