#include "main_window.h"

namespace rbtree {

const QString MainWindow::kWindowTitle = "Red-Black Tree Visualization";

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
const QString MainWindow::kViewSaveStr = "Save as PNG";

const QString MainWindow::kPauseStr = "Pause";

const QString MainWindow::kRateComment = "Frame rate:";
const QString MainWindow::kScaleComment = "Picture scaling:";
const QString MainWindow::kStartMessage =
    "Hello! Create your Red Black Tree!\nIf you want to save picture: enter the name of "
    "the picture and push Save Button";

MainWindow::MainWindow(QWidget* parent)
    : insertButton(kInsertStr, this),
      deleteButton(kDeleteStr, this),
      findButton(kFindStr, this),
      resetButton(kResetStr, this),
      statusResetButton(kStatusResetStr, this),

      rateSlider(Qt::Horizontal, this),

      pauseButton(kPauseStr, this),

      scaleSlider(Qt::Horizontal, this),

      messageLabel(kStartMessage, this),

      viewSaveButton(kViewSaveStr, this),

      QMainWindow(parent) {
    this->setWindowTitle(kWindowTitle);

    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    this->setStyleSheet(kStartStyleSheet);
    this->setPalette(lightPalette);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(&treeView);

    mainLayout->addWidget(scrollArea, kHalvesProportion.left);

    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Кнопки
    rightLayout->addWidget(&keyEdit);
    rightLayout->addWidget(&insertButton);
    rightLayout->addWidget(&deleteButton);
    rightLayout->addWidget(&findButton);
    rightLayout->addWidget(&resetButton);
    rightLayout->addWidget(&statusResetButton);

    // Ползунок таймера
    rateSlider.setRange(Animator::kRateRange.from, Animator::kRateRange.to);
    rateSlider.setValue(Animator::kStartRate);

    QLabel* rateLabel = new QLabel(kRateComment, this);
    QWidget* rateWidget = new QWidget(this);
    QVBoxLayout* rateGroupLayout = new QVBoxLayout(rateWidget);
    rateGroupLayout->setContentsMargins(0, 0, 0, 0);
    rateGroupLayout->addWidget(rateLabel);
    rateGroupLayout->addWidget(&rateSlider);
    rateWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(rateWidget);

    // Кнопка паузы

    pauseButton.setCheckable(true);
    rightLayout->addWidget(&pauseButton);

    // Ползунок масштабирования
    scaleSlider.setRange(TreeView::kScaleRange.from, TreeView::kScaleRange.to);
    scaleSlider.setValue(TreeView::kStartScale);

    QLabel* scaleLabel = new QLabel(kScaleComment, this);
    QWidget* scaleWidget = new QWidget(this);
    QVBoxLayout* scaleGroupLayout = new QVBoxLayout(scaleWidget);
    scaleGroupLayout->setContentsMargins(0, 0, 0, 0);
    scaleGroupLayout->addWidget(scaleLabel);
    scaleGroupLayout->addWidget(&scaleSlider);
    scaleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(scaleWidget);

    // Окошко с сообщением
    messageLabel.setWordWrap(true);

    QFrame* messageFrame = new QFrame(this);
    QVBoxLayout* frameLayout = new QVBoxLayout(messageFrame);
    frameLayout->addWidget(&messageLabel);

    frameLayout->setContentsMargins(kContentMargins, kContentMargins, kContentMargins,
                                    kContentMargins);

    frameLayout->setAlignment(&messageLabel, Qt::AlignCenter);

    messageFrame->setFrameShape(QFrame::StyledPanel);
    messageFrame->setFrameShadow(QFrame::Raised);
    messageFrame->setLineWidth(2);
    messageFrame->setMinimumHeight(115);

    rightLayout->addWidget(messageFrame);

    // Ввод названия файла и кнопка для сохранения
    rightLayout->addWidget(&fileNameEdit);
    rightLayout->addWidget(&viewSaveButton);

    // Вся панель настроек
    rightPanel->setFixedWidth(kRightPanelWidth);

    mainLayout->addWidget(rightPanel, kHalvesProportion.right);

    resize(kWindowShape.w, kWindowShape.h);
}

}  // namespace rbtree
