#ifndef RECURVIS_VERSION_H
#define RECURVIS_VERSION_H

#include <cstdint>
#include <string>

class Version {
private:
    uint32_t versionNumber;

public:
    Version(uint16_t major, uint16_t minor, uint16_t patch);

    virtual ~Version() = default;

    virtual void setMajor(uint16_t major);

    [[nodiscard]] virtual uint16_t getMajor() const noexcept;

    virtual void setMinor(uint16_t minor);

    [[nodiscard]] virtual uint16_t getMinor() const noexcept;

    virtual void setPatch(uint16_t patch);

    [[nodiscard]] virtual uint16_t getPatch() const noexcept;
};

std::string to_string(const Version &v) noexcept;

#endif //RECURVIS_VERSION_H
