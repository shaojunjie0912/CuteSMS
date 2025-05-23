#pragma once
#include <string>

#include "placeholder.h"

namespace cutesms {
class AuthConfig;
class Session;
class UrlParamPlaceHolder : public PlaceHolder {
public:
    UrlParamPlaceHolder(const std::string& name);
    virtual ~UrlParamPlaceHolder();

public:
    std::string get_val(StreamSession& session);

private:
    std::string name_;
};
};  // namespace cutesms