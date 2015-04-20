#include <gloperate-qtwidgets/TimePlayerWidget.h>
#include "ui_TimePlayerWidget.h"

#include <QProxyStyle>

#include <gloperate/tools/VirtualTimeController.h>


using namespace gloperate;


namespace gloperate_qtwidgets
{

namespace
{

// based on http://stackoverflow.com/a/26281608
class DirectJumpSliderStyle : public QProxyStyle {
public:
    DirectJumpSliderStyle(QStyle* style = 0)
    : QProxyStyle(style)
    {
    }

    DirectJumpSliderStyle(const QString& key)
    : QProxyStyle(key)
    {
    }

    virtual int styleHint(StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
        {
            return Qt::LeftButton;
        }
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

}  // anonymous namespace


TimePlayerWidget::TimePlayerWidget(VirtualTimeController* controller, QWidget* parent)
: QWidget(parent)
, ui(new Ui::TimePlayerWidget)
, m_uiUpdate(false)
, m_controller(controller)
{
    ui->setupUi(this);
    ui->timeSlider->setStyle(new DirectJumpSliderStyle(ui->timeSlider->style()));

    m_controller->setLoop(ui->loopCheckBox->isChecked());

    connect(ui->playPauseButton, &QPushButton::clicked, this, &TimePlayerWidget::togglePlayPause);
}

void TimePlayerWidget::togglePlayPause()
{
    m_controller->setActive(!m_controller->active());
}

void TimePlayerWidget::updateTimeUI(double time)
{
    const auto time = m_controller->time();
    const auto duration = m_controller->duration();
    const auto progress = time / duration;

    m_uiUpdate = true;
    ui->timeSlider->setValue(progress * ui->timeSlider->maximum());
    ui->timeSpinBox->setValue(time / 1000.0);
    ui->remainingTimeLabel->setText(QString::number((duration - time) / 1000.0, 'f', 3));
    m_uiUpdate = false;
}

void TimePlayerWidget::updateDurationUI(double duration)
{
    ui->timeSpinBox->setMaximum(duration / 1000.0);
}

void TimePlayerWidget::updateSpeedUI(double speed)
{
    m_uiUpdate = true;
    const auto scaledSpeed = 61.7356 * std::log(speed + 0.0499157);
    ui->speedSlider->setValue(scaledSpeed);
    ui->speedSpinBox->setValue(speed);
    m_uiUpdate = false;
}

void TimePlayerWidget::updateActiveUI(bool active)
{
    if (active)
    {
        ui->playPauseButton->setText("Pause");
    }
    else
    {
        ui->playPauseButton->setText("Play");
    }
}

void TimePlayerWidget::updateLoopUI(bool loop)
{
    ui->loopCheckBox->setChecked(loop);
}

void TimePlayerWidget::on_loopCheckBox_toggled(bool checked)
{
    m_controller->setLoop(checked);
}

void TimePlayerWidget::on_timeSlider_valueChanged(int value)
{
    if (!m_uiUpdate)
    {
        const auto progress = static_cast<double>(value) / static_cast<double>(ui->timeSlider->maximum());
        m_controller->setTime(progress * m_controller->duration());
    }
}

void TimePlayerWidget::on_timeSlider_sliderPressed()
{
    m_activeWhenSliderDown = m_controller->active();
    if (m_activeWhenSliderDown)
    {
        m_controller->setActive(false);
    }
}

void TimePlayerWidget::on_timeSlider_sliderReleased()
{
    if (m_activeWhenSliderDown)
    {
        m_controller->setActive(true);
    }
}

void TimePlayerWidget::on_timeSpinBox_valueChanged(double value)
{
    if (!m_uiUpdate)
    {
        m_controller->setTime(value * 1000.0);
    }
}

void TimePlayerWidget::on_speedSlider_valueChanged(int value)
{
    if (!m_uiUpdate)
    {
        const auto scaledValue = -0.0499157 + std::pow(1.01633, value);
        m_controller->setSpeed(scaledValue);
    }
}

void TimePlayerWidget::on_speedSpinBox_valueChanged(double value)
{
    if (!m_uiUpdate)
    {
        m_controller->setSpeed(value);
    }
}

}  // namespace gloperate_qtwidgets
