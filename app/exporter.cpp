#include "exporter.h"

namespace rbtree {

const TreeExporter::String TreeExporter::kDefaultFileName = "RBTreeVisualisation.png";

TreeExporter::Path TreeExporter::GetPathInDownloads(const String& fileName) {
    auto downloads =
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation).toStdString();
    return Path(downloads) / fileName;
}

bool TreeExporter::SaveToPng(TreeView* view, String fileName) {
    if (!view) {
        return false;
    }
    if (fileName.empty()) {
        fileName = kDefaultFileName;
    }

    QSize realTreeSize = view->TreeSize();
    QImage image(realTreeSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    view->render(&painter);
    painter.end();

    Path fullPath = GetPathInDownloads(fileName);
    if (fullPath.extension() != ".png") {
        fullPath += ".png";
    }

    return image.save(QString::fromStdString(fullPath.string()), "PNG");
}

}  // namespace rbtree
