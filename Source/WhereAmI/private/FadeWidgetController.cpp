// Fill out your copyright notice in the Description page of Project Settings.


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


