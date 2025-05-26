target("cutesms", function () 
    set_kind("binary")
    add_files("**.cpp")
    add_includedirs("$(projectdir)/CuteSMS/src", { public = true })
    -- base
    add_deps("base")
    -- protocol
    add_deps(
        "protocol_http",
        "protocol_mp4",
        "protocol_rtmp",
        "protocol_rtp",
        "protocol_rtsp",
        "protocol_sdp",
        "protocol_ts"
    )
    -- codec
    add_deps(
        "codec"
    )
    -- sdk
    add_deps(
        "sdk_http"
    )
    -- server
    add_deps(
        "server_tcp",
        "server_tls",
        "server_udp"
    )
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

