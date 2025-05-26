includes("http")

target("sdk", function ()
    set_kind("phony")
    add_deps("sdk_http")
end)
