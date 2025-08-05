#pragma once

#include <string>
#include <filesystem>
#include <fstream>

#include <QImage>
#include <QPainter>
#include <QStandardPaths>
#include <QSize>
#include <QImage>
#include <QPainter>

#include "view.h"

namespace rbtree {

class TreeExporter {
public:
    using Path = std::filesystem::path;

    static Path GetPathInDownloads(const Path& fileName);
    static bool SaveAsPng(QImage* image, QString qFileName);

private:
    static const Path kDefaultFileName;
};

}  // namespace rbtree
