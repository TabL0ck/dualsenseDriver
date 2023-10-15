#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <wchar.h>

/**
 * Compare two serial numbers
 * @param s pointer to dualsense serial number string
 * @param dev pointer to each dev serial number string
 * @ret serial numbers are equal or not
 */
bool compare_serial(const char *s, const wchar_t *dev);
#endif
