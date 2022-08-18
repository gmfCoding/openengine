#include <string>
namespace oestd 
{
    template<typename ... Args>
    std::string format( const std::string& format, Args ... args);
}
