/* Copyright (c) 2012 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "sliderrecipe.h"

#include <bb/cascades/Container>
#include <bb/cascades/Textstyle>
#include <bb/cascades/Systemdefaults>
#include <bb/cascades/Label>
#include <bb/cascades/Slider>
#include <bb/cascades/StackLayout>

using namespace bb::cascades;

SliderRecipe::SliderRecipe(Container *parent) :
        CustomControl(parent)
{
    // The recipe Container.
    Container *recipeContainer = new Container();
    StackLayout *recipeLayout = new StackLayout();
    recipeLayout->setLeftPadding(20.0);
    recipeLayout->setRightPadding(20.0);
    recipeContainer->setLayout(recipeLayout);

    // A Label is used to present the current value (with one digit precision).
    mValueLabel = new Label();
    mValueLabel->setText((const QString) "value: 0");
    mValueLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    mValueLabel->textStyle()->setColor(Color::Gray) ;

    // Create a Slider and connect a slot to the signal for Slider value changing.
    Slider *slider = new Slider();
    connect(slider, SIGNAL(valueChanging(float)), this, SLOT(onSliderValueChanging(float)));

    // Add the controls to the recipe Container and set it as root.
    recipeContainer->add(mValueLabel);
    recipeContainer->add(slider);

    setRoot(recipeContainer);
}

void SliderRecipe::onSliderValueChanging(float value)
{
    // Convert the value to only have one decimal number.
    float valueOneDec = (float) (((int) (value * 10)) / 10.0f);

    // Create a Qt string from the number.
    QString newValue = NULL;
    newValue.setNum(valueOneDec, 'g', 1);

    // Present the new value in the Label.
    mValueLabel->setText((const QString) "value: " + newValue);
}
