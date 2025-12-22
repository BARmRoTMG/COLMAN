#pragma once

#include "IState.h"

class MenuState : public IState
{
public:
	MenuState(EntityFactory& ef, Callback startGame);

public:
	virtual void InitEntities() override;
	virtual void handleEvent(const std::string& event) override;
	virtual void update(float dt) override;

private:
	Callback m_start;
};
