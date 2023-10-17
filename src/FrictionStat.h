#pragma once
#include "Force.h"
class FrictionStat :
    public Force
{
    public: //TODO: voir la duration puisque cette force dépend de contact ou non, donc ptet comment la delete facilement apres collision?
		float friction;
		float normal;
		FrictionStat(Vector direction_, float friction_, float normal_, float duration_);
		Vector value() override;
};

