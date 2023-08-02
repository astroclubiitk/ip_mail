#include <string>
#include <ctime>

class Time
{
  private:
    std::string current;

  public:
    Time();

    std::string now();
};