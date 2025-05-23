#pragma once
#include <memory>
#include <vector>

#include "box.h"


namespace cutesms {
class Mp4Builder;
class MvhdBuilder;
class MoovBox : public Box {
public:
    MoovBox();
    virtual ~MoovBox() = default;

    int64_t size() override;
    int64_t encode(NetBuffer& buf) override;
    int64_t decode(NetBuffer& buf) override;

public:
    void add_box(std::shared_ptr<Box> child);
    std::shared_ptr<Box> find_box(Box::Type type);

protected:
    std::vector<std::shared_ptr<Box>> boxes_;
};

class MoovBuilder {
public:
    MoovBuilder(Mp4Builder& builder);
    virtual ~MoovBuilder();
    MvhdBuilder add_mvhd();

private:
    Mp4Builder& builder_;
};

};  // namespace cutesms