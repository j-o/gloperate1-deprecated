#include <gloperate/stages/ColorGradientPreparationStage.h>

#include <gloperate/base/ColorGradientList.h>
#include <gloperate/tools/ColorGradientPreparation.h>

namespace gloperate
{

ColorGradientPreparationStage::ColorGradientPreparationStage()
{
    addInput("gradients", gradients);
    addInput("pixmapSize", pixmapSize);

    addOutput("names", names);
    addOutput("pixmaps", pixmaps);
}

ColorGradientPreparationStage::~ColorGradientPreparationStage()
{
}

void ColorGradientPreparationStage::process()
{
    ColorGradientPreparation preparation(gradients.data(), pixmapSize.data());

    names.data() = preparation.names();
    pixmaps.data() = preparation.pixmaps();

    invalidateOutputs();
}

} // namespace gloperate
