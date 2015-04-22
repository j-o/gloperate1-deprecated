#include <gloperate-qtwidgets/TimePlayerWidget.h>
#include "ui_TimePlayerWidget.h"

#include <QProxyStyle>
#include <QSignalBlocker>

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

class MultiSignalBlocker
{
public:
    MultiSignalBlocker(const std::vector<QObject*>& objs)
    {
        for (auto obj : objs)
        {
            m_blockers.emplace_back(obj);
        }
    }

private:
    std::vector<QSignalBlocker> m_blockers;
};

}  // anonymous namespace


TimePlayerWidget::TimePlayerWidget(VirtualTimeController* controller, QWidget* parent)
: QWidget(parent)
, ui(new Ui::TimePlayerWidget)
, m_controller(nullptr)
{
    ui->setupUi(this);
    ui->timeSlider->setStyle(new DirectJumpSliderStyle(ui->timeSlider->style()));

    setController(controller);

    connect(ui->playPauseButton, &QPushButton::clicked, this, &TimePlayerWidget::togglePlayPause);
}

void TimePlayerWidget::setController(gloperate::VirtualTimeController * controller)
{
    m_controllerConnections.clear();

    m_controller = controller;
    if (m_controller == nullptr)
    {
        return;
    }

    updateTimeUI(m_controller->time());
    updateDurationUI(m_controller->duration());
    updateSpeedUI(m_controller->speed());
    updateActiveUI(m_controller->active());
    updateLoopUI(m_controller->loop());

    m_controllerConnections.emplace_back(m_controller->onTimeChanged.connect(this, &TimePlayerWidget::updateTimeUI));
    m_controllerConnections.emplace_back(m_controller->onDurationChanged.connect(this, &TimePlayerWidget::updateDurationUI));
    m_controllerConnections.emplace_back(m_controller->onSpeedChanged.connect(this, &TimePlayerWidget::updateSpeedUI));
    m_controllerConnections.emplace_back(m_controller->onActiveChanged.connect(this, &TimePlayerWidget::updateActiveUI));
    m_controllerConnections.emplace_back(m_controller->onLoopChanged.connect(this, &TimePlayerWidget::updateLoopUI));
}

gloperate::VirtualTimeController * TimePlayerWidget::controller() const
{
    return m_controller;
}

void TimePlayerWidget::togglePlayPause()
{
    m_controller->setActive(!m_controller->active());
}

void TimePlayerWidget::updateTimeUI(double time)
{
    const auto duration = m_controller->duration();
    const auto progress = time / duration;

    const auto signalBlocker = MultiSignalBlocker({ ui->timeSlider, ui->timeSpinBox });

    ui->timeSlider->setValue(progress * ui->timeSlider->maximum());
    ui->timeSpinBox->setValue(time);
    ui->remainingTimeLabel->setText(QString::number((duration - time), 'f', 3));
}

void TimePlayerWidget::updateDurationUI(double duration)
{
    ui->timeSpinBox->setMaximum(duration);
}

void TimePlayerWidget::updateSpeedUI(double speed)
{
    const auto signalBlocker = MultiSignalBlocker({ ui->speedSlider, ui->speedSpinBox });

    const auto scaledSpeed = 61.7356 * std::log(speed + 0.0499157);
    ui->speedSlider->setValue(scaledSpeed);
    ui->speedSpinBox->setValue(speed);
}

void TimePlayerWidget::updateActiveUI(bool active)
{
    const auto signalBlocker = MultiSignalBlocker({ ui->playPauseButton });

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
    const auto signalBlocker = MultiSignalBlocker({ ui->loopCheckBox });

    ui->loopCheckBox->setChecked(loop);
}

void TimePlayerWidget::on_loopCheckBox_toggled(bool checked)
{
    m_controller->setLoop(checked);
}

void TimePlayerWidget::on_timeSlider_valueChanged(int value)
{
    const auto progress = static_cast<double>(value) / static_cast<double>(ui->timeSlider->maximum());
    m_controller->setTime(progress * m_controller->duration());
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
    m_controller->setTime(value);
}

void TimePlayerWidget::on_speedSlider_valueChanged(int value)
{
    const auto scaledValue = -0.0499157 + std::pow(1.01633, value);
    m_controller->setSpeed(scaledValue);
}

void TimePlayerWidget::on_speedSpinBox_valueChanged(double value)
{
    m_controller->setSpeed(value);
}

}  // namespace gloperate_qtwidgets
