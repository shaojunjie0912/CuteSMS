includes("tcp")
includes("udp")
includes("tls")

target("server", function ()
    set_kind("phony")
    add_deps("server_tcp", "server_udp", "server_tls")
end)
