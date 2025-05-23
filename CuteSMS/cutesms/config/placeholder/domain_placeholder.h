#pragma once
#include "placeholder.h"
namespace cutesms {
class StreamSession;
class DomainPlaceHolder : public PlaceHolder {
public:
    DomainPlaceHolder();
    ~DomainPlaceHolder() override;

public:
    std::string get_val(StreamSession& session) override;
};
};  // namespace cutesms