#pragma once
#include "IState.h"

class PauseState : public IState
{
public:
    PauseState( EntityFactory& ef, Callback resumeGame );

public:
    virtual void InitEntities() override;
    virtual void handleEvent( const std::string& event ) override;
    virtual void update( float dt ) override;

private:
    Callback    m_resume;
};
