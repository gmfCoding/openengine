#ifndef OE_IMGUI
#define OE_IMGUI
#include "imgui.h"
#endif

#ifndef OE_VIEW
#define OE_VIEW
#include <string>


#define REGISTER(type, base) public:\
type(ViewSystem* pOwner) : base(pOwner, #type) {} \
type(ViewSystem* pOwner, const std::string& name) : base(pOwner, name) {}\
private:

#define ViewRegister(self,base) int self::CID = Editor::Get()->GetViewSystem()->Register(#self, #base);
#define ViewHeader(self,base) class self : public base { REGISTER(self, base)

class ViewSystem;

class View 
{
    bool isDirty;
    public:
    std::string m_title;
    ViewSystem* owner;

    View(ViewSystem* pOwner, const std::string& name);

    virtual void OnDrawGUI() = 0;
    virtual void AddToViewSystem();
    void SetDirty(bool state);

    virtual ImGuiWindowFlags GetFlags();
};

#endif