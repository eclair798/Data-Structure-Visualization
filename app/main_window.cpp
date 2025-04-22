#include "main_window.h"

namespace rbtree {

const QString MainWindow::kStartStyleSheet = R"(
        QPushButton, QLineEdit {
            background-color: white;
            border: 1px solid #cccccc;
            border-radius: 4px;
            padding: 4px;
        }
        QWidget {
            background-color: white;
        }

        QPushButton:hover {
            border: 1px solid #aaaaaa;
        }
        QPushButton:pressed {
            border: 1px solid #888888;
        }        
        
        QScrollArea {
            border: 1px solid #cccccc;
            border-radius: 4px;
            padding: 4px;
        }
        QScrollBar:horizontal, QScrollBar:vertical {
            background: #f0f0f0; 
            border: none;
            height: 10px;
            width: 10px;
            margin: 0px;
        }
    
        QScrollBar::handle:horizontal, QScrollBar::handle:vertical {
            background: #c0c0c0;
            border-radius: 5px;
            min-width: 20px;
            min-height: 20px;
        }
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;         /* Убираем стрелочки */
            background: none;
        }
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical,
        QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {
            border: none;
            background: none;
        }
        
    )";

const QString MainWindow::kInsertStr = "Insert";
const QString MainWindow::kDeleteStr = "Delete";
const QString MainWindow::kFindStr = "Find";
const QString MainWindow::kResetStr = "Reset";
const QString MainWindow::kStatusResetStr = "Reset Statuses";
const QString MainWindow::kViewSaveStr = "Save in PNG";

const QString MainWindow::kPauseStr = "Pause";

const QString MainWindow::kRateComment = "Frame rate:";
const QString MainWindow::kScaleComment = "Picture scaling:";
const QString MainWindow::kStartMessage =
    "Hello! Create your Red Black Tree!\nIf you want to save picture: enter the name of "
    "the picture and push Save Button";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    this->setStyleSheet(kStartStyleSheet);
    this->setPalette(lightPalette);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    treeView = std::make_unique<TreeView>(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(treeView.get());

    mainLayout->addWidget(scrollArea, kHalvesProportion.first);

    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Поле для ввода
    keyEdit = std::make_unique<QLineEdit>(this);

    // Кнопки
    insertButton = std::make_unique<QPushButton>(kInsertStr, this);
    deleteButton = std::make_unique<QPushButton>(kDeleteStr, this);
    findButton = std::make_unique<QPushButton>(kFindStr, this);
    resetButton = std::make_unique<QPushButton>(kResetStr, this);
    statusResetButton = std::make_unique<QPushButton>(kStatusResetStr, this);

    rightLayout->addWidget(keyEdit.get());
    rightLayout->addWidget(insertButton.get());
    rightLayout->addWidget(deleteButton.get());
    rightLayout->addWidget(findButton.get());
    rightLayout->addWidget(resetButton.get());
    rightLayout->addWidget(statusResetButton.get());

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

    // кнопка паузы

    pauseButton = std::make_unique<QPushButton>(kPauseStr, this);
    pauseButton->setCheckable(true);
    rightLayout->addWidget(pauseButton.get());

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

    frameLayout->setAlignment(messageLabel.get(), Qt::AlignCenter);

    messageFrame->setFrameShape(QFrame::StyledPanel);
    messageFrame->setFrameShadow(QFrame::Raised);
    messageFrame->setLineWidth(2);
    messageFrame->setMinimumHeight(115);

    rightLayout->addWidget(messageFrame);

    // Ввод названия файла и кнопка для сохранения

    fileNameEdit = std::make_unique<QLineEdit>(this);
    viewSaveButton = std::make_unique<QPushButton>(kViewSaveStr, this);
    rightLayout->addWidget(fileNameEdit.get());
    rightLayout->addWidget(viewSaveButton.get());

    // Вся панель настроек
    rightPanel->setFixedWidth(kRightPanelWidth);

    mainLayout->addWidget(rightPanel, kHalvesProportion.second);

    resize(kWindowShape.first, kWindowShape.second);
}

}  // namespace rbtree
