#include "controllers.h"

namespace app {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit)
    : tree_(tree), keyEdit_(keyEdit) {
}

void TreeController::HandleInsert() {
    // todo
}

void TreeController::HandleDelete() {
    // todo
}

void TreeController::HandleFind() {
    // todo
}

void TreeController::HandleReset() {
    // todo
}

TimerController::TimerController(Animator* animator, QSlider* intervalSlider)
    : animator_(animator), intervalSlider_(intervalSlider) {
}

void TimerController::HandleTimerChange() {
    // todo
}

}  // namespace app
