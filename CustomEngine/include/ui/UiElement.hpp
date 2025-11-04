#pragma once

class UiElement{
    public:

    virtual void Update(float dt)=0;
    virtual void Draw()const = 0;

    void SetVisible(bool v){visible=v;}
    bool IsVisible()const{return visible;}
    int GetZOrder()const {return zIndex;}

    virtual ~UiElement() = default;
    
    protected:
        bool visible=true;
        int zIndex=0;
};