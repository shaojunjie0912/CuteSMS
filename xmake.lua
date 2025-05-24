set_project("CuteSMS")
set_xmakever("2.9.8")

set_languages("c++20")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate")

set_defaultmode("debug")

-- 第三方依赖
add_requires("spdlog")
add_requires("boost", { configs = { asio = true, program_options = true, system = true, thread = true, date_time = true, regex = true, serialization = true, context = true, coroutine = true }})
add_requires("yaml-cpp")
add_requires("jsoncpp")
add_requires("boringssl")
add_requires("zlib")
add_requires("libopus")
add_requires("faac")
add_requires("faad2")
add_requires("ffmpeg")
add_requires("srtp")
add_requires("hiredis")
add_requires("redis-plus-plus")

includes("libs")
includes("live-server")
includes("tests")
