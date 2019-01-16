#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>

class App : public Wt::WApplication
{
private:
	const Wt::WEnvironment& _env;

public:
	App(const Wt::WEnvironment& env)
		: _env(env)
		, Wt::WApplication(env)
	{ 
		this->setTitle("TEST");
		auto* cp = root()->addWidget(std::make_unique<Wt::WText>());		
	}
};

int main(int argc, char **argv)
{
	Wt::WRun(argc, argv, [](const Wt::WEnvironment& env)
	{
		return std::make_unique<App>(env);
	});
}