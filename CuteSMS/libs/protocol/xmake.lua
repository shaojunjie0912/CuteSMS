includes("http")
includes("mp4")
includes("rtmp")
includes("rtp")
includes("rtsp")
includes("sdp")
includes("ts")

target("protocol", function ()
    set_kind("phony")
    add_deps(
        "protocol_http",
        "protocol_mp4",
        "protocol_rtmp",
        "protocol_rtp",
        "protocol_rtsp",
        "protocol_sdp",
        "protocol_ts"
    )
end)

