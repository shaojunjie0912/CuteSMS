#include <base/net_buffer.h>
#include <protocol_mp4/mdat.h>

namespace cutesms {

MdatBox::MdatBox() : Box(BOX_TYPE_MDAT) {}

MdatBox::~MdatBox() {}

}  // namespace cutesms
