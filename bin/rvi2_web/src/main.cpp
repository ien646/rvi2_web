#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGLWidget.h>

#include <rvi/runtime.hpp>

#include "GL.h"

class App : public Wt::WApplication
{
private:
    const Wt::WEnvironment& _env;
    GL* _gl;

public:
    App(const Wt::WEnvironment& env)
        : _env(env)
        , Wt::WApplication(env)
    { 
        this->setTitle("TEST");
        _gl = root()->addWidget(std::make_unique<GL>());
    }
};

int main(int argc, char **argv)
{
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
    {
        return std::make_unique<App>(env);
    });
}