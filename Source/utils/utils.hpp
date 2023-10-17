#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <cstring>
#include <iostream>
#include <wchar.h>

/**
 * Compare two serial numbers
 * @param s pointer to dualsense serial number string
 * @param dev pointer to each dev serial number string
 * @ret serial numbers are equal or not
 */
bool compare_serial(const char *s, const wchar_t *dev);
void printStructByBytes(uint8_t *obj, uint32_t len);
#endif
