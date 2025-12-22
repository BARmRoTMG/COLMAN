#pragma once

#include "IState.h"
#include <unordered_map>
#include <string>

class StateMachine
{
public:
    template<typename T, typename... Args>
    void registerState( const std::string& name, Args&&... args )
    {
        // construct state and store it
        m_states[name] = std::make_unique<T>( std::forward<Args>( args )... );
    }

    void changeState( const std::string& name )
    {
        m_current = m_states[name].get();
    }

    IState* currentState() const { return m_current; }

private:
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states;
    IState* m_current = nullptr;
};