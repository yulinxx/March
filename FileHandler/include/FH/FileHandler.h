#ifndef FILEIO_H
#define FILEIO_H

#include "Ut/XCEntity/XCEntity.h"
#include <vector>
#include <string>

#include "FileHandlerAPI.h"
//#include "algw/algw.h"
#include "Ut/Vec.h"

using namespace XC;

class FILEHANDLER_API FileHandler final
{
public:
    static bool importDXF(const std::string& filePath, std::vector<XCEntity>& entities) noexcept;
    static bool exportDXF(const std::string& filePath, const std::vector<XCEntity>& entities) noexcept;

    static bool importDWG(const std::string& filePath, std::vector<XCEntity>& entities) noexcept;
    static bool exportDWG(const std::string& filePath, const std::vector<XCEntity>& entities) noexcept;

    void test(Ut::Vec2d& v)
    {
        v.x() = 1.0f;
        v.y() = 2.0f;
    }
};

#endif // FILEIO_H