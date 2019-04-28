#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGLWidget.h>
#include <Wt/WHBoxLayout.h>

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
        Wt::WApplication::instance()->useStyleSheet("css/main.css");
        this->setTitle("TEST");

        auto layout = root()->setLayout(std::make_unique<Wt::WHBoxLayout>());
        _gl = layout->addWidget(std::make_unique<cozy_widget>());
    }
};

int main(int argc, char **argv)
{
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
    {
        return std::make_unique<App>(env);
    });
}