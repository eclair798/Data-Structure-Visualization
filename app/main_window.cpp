#include "main_window.h"

namespace rbtree {

const QString MainWindow::kInsertStr = "Insert";
const QString MainWindow::kDeleteStr = "Delete";
const QString MainWindow::kFindStr = "Find";
const QString MainWindow::kResetStr = "Reset";

const QString MainWindow::kTimerComment = "Time between frames:";
const QString MainWindow::kScaleComment = "Picture scaling:";
const QString MainWindow::kStartMessage = "Hello! Create your Red Black Tree!";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    treeView = std::make_unique<TreeView>(this);

    mainLayout->addWidget(treeView.get(), 3);

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
    timerSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    timerSlider->setRange(kTimerRange.first, kTimerRange.second);
    timerSlider->setValue(kStartTimer);

    QLabel* timerLabel = new QLabel(kTimerComment, this);

    QWidget* timerWidget = new QWidget(this);
    QVBoxLayout* timerGroupLayout = new QVBoxLayout(timerWidget);
    timerGroupLayout->setContentsMargins(0, 0, 0, 0);
    timerGroupLayout->addWidget(timerLabel);
    timerGroupLayout->addWidget(timerSlider.get());
    timerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(timerWidget);

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
