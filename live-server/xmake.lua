target("live-server", function () 
    set_kind("binary")
    add_files("**.cpp")
    add_includedirs("$(projectdir)/live-server", { public = true })
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
        "codec"-- TODO: 这里 track?
        -- "codec_aac",
        -- "codec_av1",
        -- "codec_g711",
        -- "codec_h264",
        -- "codec_hevc",
        -- "codec_mp3",
        -- "codec_opus",
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

