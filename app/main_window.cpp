#include "main_window.h"

namespace rbtree {

const QString MainWindow::kInsertStr = "Insert";
const QString MainWindow::kDeleteStr = "Delete";
const QString MainWindow::kFindStr = "Find";
const QString MainWindow::kResetStr = "Reset";

const QString MainWindow::kRateComment = "Frame rate:";
const QString MainWindow::kScaleComment = "Picture scaling:";
const QString MainWindow::kStartMessage = "Hello! Create your Red Black Tree!";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    treeView = std::make_unique<TreeView>(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(treeView.get());

    mainLayout->addWidget(scrollArea, 3);

    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Поле для ввода
    keyEdit = std::make_unique<QLineEdit>(this);

    // Кнопки
    insertButton = std::make_unique<QPushButton>(kInsertStr, this);
    deleteButton = std::make_unique<QPushButton>(kDeleteStr, this);
    findButton = std::make_unique<QPushButton>(kFindStr, this);
    resetButton = std::make_unique<QPushButton>(kResetStr, this);

    rightLayout->addWidget(keyEdit.get());
    rightLayout->addWidget(insertButton.get());
    rightLayout->addWidget(deleteButton.get());
    rightLayout->addWidget(findButton.get());
    rightLayout->addWidget(resetButton.get());

    // Ползунок таймера
    rateSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    rateSlider->setRange(kRateRange.first, kRateRange.second);
    rateSlider->setValue(kStartRate);

    QLabel* rateLabel = new QLabel(kRateComment, this);

    QWidget* rateWidget = new QWidget(this);
    QVBoxLayout* rateGroupLayout = new QVBoxLayout(rateWidget);
    rateGroupLayout->setContentsMargins(0, 0, 0, 0);
    rateGroupLayout->addWidget(rateLabel);
    rateGroupLayout->addWidget(rateSlider.get());
    rateWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(rateWidget);

    // Ползунок масштабирования
    scaleSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    scaleSlider->setRange(kScaleRange.first, kScaleRange.second);
    scaleSlider->setValue(kStartScale);

    QLabel* scaleLabel = new QLabel(kScaleComment, this);

    QWidget* scaleWidget = new QWidget(this);
    QVBoxLayout* scaleGroupLayout = new QVBoxLayout(scaleWidget);
    scaleGroupLayout->setContentsMargins(0, 0, 0, 0);
    scaleGroupLayout->addWidget(scaleLabel);
    scaleGroupLayout->addWidget(scaleSlider.get());
    scaleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(scaleWidget);

    // Окошко с сообщением
    messageLabel = std::make_unique<QLabel>(kStartMessage, this);
    messageLabel->setWordWrap(true);

    QFrame* messageFrame = new QFrame(this);
    QVBoxLayout* frameLayout = new QVBoxLayout(messageFrame);
    frameLayout->addWidget(messageLabel.get());
    frameLayout->setContentsMargins(kContentMargins, kContentMargins, kContentMargins,
                                    kContentMargins);

    messageFrame->setFrameShape(QFrame::StyledPanel);
    messageFrame->setFrameShadow(QFrame::Raised);
    messageFrame->setLineWidth(2);

    rightLayout->addWidget(messageFrame);

    // Вся панель настроек
    rightPanel->setFixedWidth(kRightPanelWidth);
    mainLayout->addWidget(rightPanel);

    resize(kWindowShape.first, kWindowShape.second);
}

}  // namespace rbtree
