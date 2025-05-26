target("cutesms", function () 
    set_kind("binary")
    add_files("**.cpp")

    -- TODO: 这里其实不规范, 加上 src 作为 include...
    add_includedirs("$(projectdir)/CuteSMS/src", { public = true })

    add_deps("base")     -- base
    add_deps("protocol")     -- protocol
    add_deps("codec")     -- codec
    add_deps("sdk")     -- sdk
    add_deps("server")     -- server

    -- 第三方库
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

