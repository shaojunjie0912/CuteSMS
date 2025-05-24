#include <protocol_mp4/styp.h>

namespace cutesms {

StypBox::StypBox() : FtypBox() { type_ = BOX_TYPE_STYP; }

StypBox::~StypBox() {}
}  // namespace cutesms