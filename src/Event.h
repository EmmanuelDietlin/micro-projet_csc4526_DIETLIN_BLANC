#pragma once
#include "signals.h"

/**
Classe abstraitre représentant un évènement.
Est parente de tous les évènements du jeu.
Peut être exécuté via la méthode "execute"
*/
class Event {
protected:
	explicit Event() = default;
	explicit Event(const Event&) = default;
	virtual ~Event() = default;
public:
	virtual void execute() = 0;
};