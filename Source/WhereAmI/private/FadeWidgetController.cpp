#include "FadeWidgetController.h"

void UFadeWidgetController::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFadeWidgetController::PlayFadeAnimation()
{
	if (FadeInOUT)
	{
		PlayAnimation(FadeInOUT);
	}
}


