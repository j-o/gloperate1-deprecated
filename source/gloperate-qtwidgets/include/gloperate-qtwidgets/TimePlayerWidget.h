#pragma once

#include <QWidget>
#include <QTimer>



namespace gloperate
{
class VirtualTimeController;
}  // namespace gloperate


namespace gloperate_qtwidgets
{

namespace Ui
{
class TimePlayerWidget;
}  // namespace Ui

class TimePlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimePlayerWidget(gloperate::VirtualTimeController* controller, QWidget* parent = 0);

public slots:
    void togglePlayPause();

signals:
    void timeChanged(double time);

protected slots:
    void on_loopCheckBox_toggled(bool checked);
    void on_timeSlider_valueChanged(int value);
    void on_timeSlider_sliderPressed();
    void on_timeSlider_sliderReleased();
    void on_timeSpinBox_valueChanged(double value);
    void on_speedSlider_valueChanged(int value);
    void on_speedSpinBox_valueChanged(double value);

    void updateTimeUI(double time);
    void updateDurationUI(double duration);
    void updateSpeedUI(double speed);
    void updateActiveUI(bool active);
    void updateLoopUI(bool loop);

protected:
    const QScopedPointer<Ui::TimePlayerWidget> ui;
    bool m_uiUpdate;
    bool m_activeWhenSliderDown;

    gloperate::VirtualTimeController* m_controller;
};

} // namespace gloperate_qtwidgets
