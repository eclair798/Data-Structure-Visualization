#include "exporter.h"

namespace rbtree {

const TreeExporter::Path TreeExporter::kDefaultFileName = "RBTreeVisualization.png";

TreeExporter::Path TreeExporter::GetPathInDownloads(const Path& fileName) {
    auto downloads =
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation).toStdString();
    return Path(downloads) / fileName;
}

bool TreeExporter::SaveAsPng(QImage* image, QString qFileName) {
    Path fileName = Path(qFileName.toStdString());
    if (!image) {
        return false;
    }
    if (fileName.empty()) {
        fileName = kDefaultFileName;
    }

    Path fullPath = GetPathInDownloads(fileName);
    if (fullPath.extension() != ".png") {
        fullPath += ".png";
    }

    return image->save(QString::fromStdString(fullPath.string()), "PNG");
}

}  // namespace rbtree
