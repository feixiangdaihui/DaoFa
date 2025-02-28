// Fill out your copyright notice in the Description page of Project Settings.


#include "General/ElementSetting.h"

GElementRestrain UElementSetting::GetElementRestrain(GElement self, GElement other)
{
	if (self == GElement::NOELEMENT || other == GElement::NOELEMENT)
		return GElementRestrain::Neutral;
	else if (int(self) - int(other) == -1 || (self == GElement::Earth && other == GElement::Matel))
		return GElementRestrain::Positive;
	else if (int(self) - int(other) == 1 || (self == GElement::Matel && other == GElement::Earth))
		return GElementRestrain::Negative;
	else
		return GElementRestrain::Neutral;
}

float UElementSetting::GetElementRestrainMultiplier(GElement self, GElement other)
{
	GElementRestrain restrain = GetElementRestrain(self, other);
	switch (restrain)
	{
	case GElementRestrain::Negative:
		return ELEMENTRESTRAINNEGATIVE;
	case GElementRestrain::Neutral:
		return 1.0f;
	case GElementRestrain::Positive:
		return ELEMENTRESTRAINPOSITIVE;
	default:
		return 1.0f;
	}
}

