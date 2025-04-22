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

#include "geom_tree.h"
#include "view.h"

namespace rbtree {

class TreeExporter {
public:
    using String = std::string;
    using Path = std::filesystem::path;

    static Path GetPathInDownloads(const String& fileName);
    static bool SaveToPng(TreeView* view, String fileName);

private:
    static const String kDefaultFileName;
};

}  // namespace rbtree
