#include "utils.hpp"

bool compare_serial(const char *s, const wchar_t *dev) {
  if (!s)
    return true;

  const size_t len = wcslen(dev);

  if (strlen(s) != len)
    return false;

  for (size_t i = 0; i < len; ++i) {
    if (s[i] != dev[i])
      return false;
  }

  return true;
}

void printStructByBytes(uint8_t *obj, uint32_t len) {
  for (uint32_t i = 0; i < len; i++)
    std::cout << i << ": " << (uint32_t)obj[i] << std::endl;
}
