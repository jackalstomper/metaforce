#include "Runtime/CGameAllocator.hpp"
#include <new>

namespace urde {
logvisor::Module AllocLog("urde::CGameAllocator");

#pragma GCC diagnostic ignored "-Wclass-memaccess"

u32 CGameAllocator::GetFreeBinEntryForSize(size_t len) {
  size_t bin = 0;
  size_t binSize = 32;
  while (true) {
    if (binSize > 0x200000) {
      return 15;
    }
    if (len < binSize) {
      break;
    }
    binSize <<= 1;
    ++bin;
  }
  return bin;
}
bool CGameAllocator::Initialize() { return true; }
} // namespace urde
