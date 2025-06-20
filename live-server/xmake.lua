target("live-server", function ()
    set_kind("binary")
    add_files("**.cpp")
    add_deps("base")
    add_deps(
        "protocol_http",
        "protocol_mp4",
        "protocol_rtmp",
        "protocol_rtp",
        "protocol_rtsp",
        "protocol_sdp",
        "protocol_ts"
    )
    add_deps("codec")
    add_deps("sdk_http")
    add_deps("server")

    add_packages(
        "spdlog",
        "boost",
        "yaml-cpp",
        "jsoncpp",
        "openssl3",
        "zlib",
        "libopus",
        "faac",
        "faad2",
        "ffmpeg",
        "srtp",
        "hiredis",
        "redis-plus-plus"
    )
end)
