#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGLWidget.h>

#include <rvi/runtime.hpp>

#include "cozy_widget.hpp"

class App : public Wt::WApplication
{
private:
    const Wt::WEnvironment& _env;
    cozy_widget* _gl;

public:
    App(const Wt::WEnvironment& env)
        : _env(env)
        , Wt::WApplication(env)
    { 
        this->setTitle("TEST");
        _gl = root()->addWidget(std::make_unique<cozy_widget>());
    }
};

int main(int argc, char **argv)
{
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
    {
        return std::make_unique<App>(env);
    });
}