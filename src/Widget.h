#pragma once
union SDL_Event;
class Widget
{
public:

    Widget();
    ~Widget();
private:

protected:

    virtual void SetupPlayerInput(SDL_Event e) = 0;
    virtual void UpdateButtonsVisually() = 0;
public:

};


