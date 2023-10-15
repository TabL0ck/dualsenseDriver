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
