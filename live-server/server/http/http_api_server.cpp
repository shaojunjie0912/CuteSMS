#include "log/log.h"

#include <boost/shared_ptr.hpp>
#include <memory>
#include <string>

#include "http_api_server.hpp"
#include "http_server_session.hpp"
#include "http_flv_server_session.hpp"
#include "http_ts_server_session.hpp"
#include "http_m3u8_server_session.hpp"
#include "http_mpd_server_session.hpp"
#include "http_m4s_server_session.hpp"

#include "http_long_mp4_server_session.hpp"
#include "http_long_ts_server_session.hpp"

#include "core/stream_session.hpp"
#include "core/source_manager.hpp"

#include "config/config.h"
#include "config/app_config.h"
#include "app/app_manager.h"
#include "app/app.h"
#include "../../version.h"

using namespace mms;
HttpApiServer::~HttpApiServer() {

}

bool HttpApiServer::register_route() {
    bool ret;
    ret = on_get("/api/version", std::bind(&HttpApiServer::get_api_version, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    if (!ret) {
        return false;
    }

    ret = on_get("/api/domain_apps", std::bind(&HttpApiServer::get_domain_apps, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    if (!ret) {
        return false;
    }

    ret = on_get("/api/domain_streams", std::bind(&HttpApiServer::get_domain_streams, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    if (!ret) {
        return false;
    }

    ret = on_get("/api/app_streams", std::bind(&HttpApiServer::get_app_streams, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    if (!ret) {
        return false;
    }

    ret = on_get("/api/cut_off_stream", std::bind(&HttpApiServer::cut_off_stream, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    if (!ret) {
        return false;
    }

    auto & static_file_server_cfg = Config::get_instance()->get_http_api_config().get_static_file_server_config();
    if (static_file_server_cfg.is_enabled()) {
        auto path_map = static_file_server_cfg.get_path_map();
        for (auto it = path_map.begin(); it != path_map.end(); it++) {
            ret = on_static_fs(it->first, it->second);
            CORE_INFO("register static file map:{} --> {}", it->first, it->second);
            if (!ret) {
                return false;
            }
        }
    }

    return true;
}

boost::asio::awaitable<void> HttpApiServer::get_api_version(std::shared_ptr<HttpServerSession> session, std::shared_ptr<HttpRequest> req, std::shared_ptr<HttpResponse> resp) {
    (void)session;
    (void)req;
    Json::Value root;
    root["version"] = VERSION_STR;
    std::string body = root.toStyledString();
    resp->add_header("Access-Control-Allow-Origin", "*");
    if (!(co_await resp->write_header(200, "OK"))) {
        resp->close();
        co_return;
    }

    bool ret = co_await resp->write_data((const uint8_t*)(body.data()), body.size());
    if (!ret) {
        resp->close();
        co_return;
    }

    resp->close();
    co_return;
}

boost::asio::awaitable<void> HttpApiServer::get_domain_apps(std::shared_ptr<HttpServerSession> session, 
                                                            std::shared_ptr<HttpRequest> req, 
                                                            std::shared_ptr<HttpResponse> resp) {
    (void)session;
    (void)req;
    auto config = Config::get_instance();
    if (!config) {
        if (!(co_await resp->write_header(500, "Server Error"))) {
            resp->close();
        }
        co_return;
    }

    auto domain_confs = config->get_domain_confs();
    Json::Value jdomain_confs;
    for (auto it_domain = domain_confs.begin(); it_domain != domain_confs.end(); it_domain++) {
        jdomain_confs[it_domain->first] = it_domain->second->to_json();
    }
    Json::Value root;
    root["code"] = 0;
    root["data"] = jdomain_confs;
    root["msg"] = "";
    std::string body = root.toStyledString();
    resp->add_header("Content-type", "application/json");
    resp->add_header("Access-Control-Allow-Origin", "*");
    if (!(co_await resp->write_header(200, "OK"))) {
        resp->close();
        co_return;
    }

    bool ret = co_await resp->write_data((const uint8_t*)(body.data()), body.size());
    if (!ret) {
        resp->close();
        co_return;
    }

    resp->close();
    co_return;
}

boost::asio::awaitable<void> HttpApiServer::get_domain_streams(std::shared_ptr<HttpServerSession> session, 
                                                            std::shared_ptr<HttpRequest> req, 
                                                            std::shared_ptr<HttpResponse> resp) {
    (void)session;
    (void)req;
    Json::Value root;
    auto domain = req->get_query_param("domain");
    auto app_streams = SourceManager::get_instance().get_sources(domain);
    for (auto it_app = app_streams.begin(); it_app != app_streams.end(); it_app++) {
        Json::Value japp_streams;
        for (auto & stream : it_app->second) {
            japp_streams[stream.first] = stream.second->to_json();
        }
        root[it_app->first] = japp_streams;
    }

    std::string body = root.toStyledString();
    resp->add_header("Content-type", "application/json");
    resp->add_header("Access-Control-Allow-Origin", "*");
    if (!(co_await resp->write_header(200, "OK"))) {
        resp->close();
        co_return;
    }

    bool ret = co_await resp->write_data((const uint8_t*)(body.data()), body.size());
    if (!ret) {
        resp->close();
        co_return;
    }

    resp->close();
    co_return;
}  

boost::asio::awaitable<void> HttpApiServer::get_app_streams(std::shared_ptr<HttpServerSession> session, 
                                                            std::shared_ptr<HttpRequest> req, 
                                                            std::shared_ptr<HttpResponse> resp) {
    (void)session;
    (void)req;
    Json::Value root;
    auto domain = req->get_query_param("domain");
    auto app = req->get_query_param("app");
    if (app.empty()) {
        co_return co_await response_json(resp, -1, "param error");
    }

    auto streams = SourceManager::get_instance().get_sources(domain, app);
    std::string body;
    try {
        Json::Value jstreams;
        for (auto it = streams.begin(); it != streams.end(); it++) {
            jstreams.append(it->second->to_json());
        }
        root["data"] = jstreams;
        root["code"] = 0;
        body = root.toStyledString();
    } catch (const std::exception &exp) {
        CORE_ERROR("Exception occurred: {}", exp.what());
    }
    
    resp->add_header("Content-type", "application/json");
    resp->add_header("Access-Control-Allow-Origin", "*");
    if (!(co_await resp->write_header(200, "OK"))) {
        resp->close();
        co_return;
    }

    bool ret = co_await resp->write_data((const uint8_t*)(body.data()), body.size());
    if (!ret) {
        resp->close();
        co_return;
    }

    resp->close();
    co_return;
} 

boost::asio::awaitable<void> HttpApiServer::cut_off_stream(std::shared_ptr<HttpServerSession> session, 
                                                            std::shared_ptr<HttpRequest> req, 
                                                            std::shared_ptr<HttpResponse> resp) 
{
    (void)session;
    auto domain = req->get_query_param("domain");
    auto app = req->get_query_param("app");
    auto stream = req->get_query_param("stream");
    auto source = SourceManager::get_instance().get_source(domain, app, stream);
    if (!source) {
        co_return co_await response_json(resp, -1, "stream not found");
    }

    source->close();
    co_await response_json(resp, 0, "succeed");
    co_return;
}

boost::asio::awaitable<void> HttpApiServer::response_json(std::shared_ptr<HttpResponse> resp, int32_t code, const std::string & msg) {
    Json::Value root;
    root["code"] = code;
    root["msg"] = msg;
    std::string body = root.toStyledString();
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Content-Length", std::to_string(body.size()));
    if (!(co_await resp->write_header(200, "OK"))) {
        resp->close();
        co_return;
    }

    bool ret = co_await resp->write_data((const uint8_t*)(body.data()), body.size());
    if (!ret) {
        resp->close();
        co_return;
    }

    resp->close();
    co_return;
}