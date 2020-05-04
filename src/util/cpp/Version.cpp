#include <cmath>
#include <sstream>
#include <optional>
#include "Version.h"

namespace {
    template<class T>
    constexpr bool isSizeIn10Bit(T num) {
        return 0 <= num && num < 1024;
    }

    template<class T>
    constexpr std::optional<uint16_t> wrapWithSizeCheck(T num) {
        if (isSizeIn10Bit(num)) {
            return num;
        } else {
            return std::nullopt;
        }
    }

    constexpr std::optional<uint32_t> compile(uint16_t major, uint16_t minor, uint16_t patch) {
        if (isSizeIn10Bit(major) && isSizeIn10Bit(minor) && isSizeIn10Bit(patch)) {
            return ((major) << 22) | ((minor) << 12) | (patch);
        } else {
            return std::nullopt;
        }
    }

    constexpr std::optional<uint16_t> pullMajor(uint32_t versionNumber) {
        return wrapWithSizeCheck(versionNumber >> 22);
    }

    constexpr std::optional<uint16_t> pullMinor(uint32_t versionNumber) {
        return wrapWithSizeCheck((versionNumber >> 12) & 0x3ff);
    }

    constexpr std::optional<uint16_t> pullPatch(uint32_t versionNumber) {
        return wrapWithSizeCheck(versionNumber & 0xfff);
    }
}

Version::Version(uint16_t major, uint16_t minor, uint16_t patch) : versionNumber(0) {
    auto result = compile(major, minor, patch);
    if (result.has_value()) versionNumber = result.value();
    else throw std::runtime_error("Version number is too big!");
}

void Version::setMajor(uint16_t major) {
    auto result = compile(major, getMinor(), getPatch());
    if (result.has_value()) versionNumber = result.value();
    else throw std::runtime_error("Version number is too big!");
}

uint16_t Version::getMajor() const noexcept {
    return pullMajor(versionNumber).value();
}

void Version::setMinor(uint16_t minor) {
    auto result = compile(getMajor(), minor, getPatch());
    if (result.has_value()) versionNumber = result.value();
    else throw std::runtime_error("Version number is too big!");
}

uint16_t Version::getMinor() const noexcept {
    return pullMinor(versionNumber).value();
}

void Version::setPatch(uint16_t patch) {
    auto result = compile(getMajor(), getMinor(), patch);
    if (result.has_value()) versionNumber = result.value();
    else throw std::runtime_error("Version number is too big!");
}

uint16_t Version::getPatch() const noexcept {
    return pullPatch(versionNumber).value();
}

std::string to_string(const Version &v) noexcept {
    std::stringstream ss;
    ss << std::to_string(v.getMajor()) << "."
       << std::to_string(v.getMinor()) << "."
       << std::to_string(v.getPatch());
    return ss.str();
}
