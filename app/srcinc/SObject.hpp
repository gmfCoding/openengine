#include <map>
#include <string>

#ifndef OE_SPROPERTY_FIELD
#define OE_SPROPERTY_FIELD
struct SPropertyField
{
    std::string type;
    int size;
    int offset;

    SPropertyField(int pSize, const std::string& pType, int pOffset);

    void ImGuiDraw(const std::string& name, void* obj);
    void* GetPtr(void* obj);
};

struct SPropertyConstructInfo{
    std::string name;
    std::string type;
    int size;
    size_t offset;
};

class SObject
{
public:
    std::string name;
    std::map<std::string, SPropertyField> properties;
    SObject(std::initializer_list<SPropertyConstructInfo> init);
};
#endif