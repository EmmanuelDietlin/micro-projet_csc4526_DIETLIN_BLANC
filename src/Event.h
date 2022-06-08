#pragma once
#include "signals.h"

/**
Classe abstraitre repr�sentant un �v�nement.
Est parente de tous les �v�nements du jeu.
Peut �tre ex�cut� via la m�thode "execute"
*/
class Event {
protected:
	explicit Event() = default;
	explicit Event(const Event&) = default;
	virtual ~Event() = default;
public:
	virtual void execute() = 0;
};