target("base", function () 
    set_kind("static")
    add_files("src/**.cpp")
    add_includedirs("include", { public = true })
    add_packages("boost", "jsoncpp", "boringssl", "spdlog", { public = true })
    -- TODO: tls 的 session 依赖有问题?
    -- add_deps("server_tls")
end)