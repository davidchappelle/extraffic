#include <stdlib.h>
#include <boost/program_options.hpp>


namespace po = boost::program_options;


int main(int argc, char** argv)
{
    po::options_description description("Program for accessing the flow database");

    description.add_options()
        ("help", "program explanation")
        ;

    po::variables_map variables;
    po::store(po::parse_command_line(argc, argv, description), variables);
    po::notify(variables);

    if(variables.count("help"))
    {
        std::cout << description << std::endl;
        return 1;
    }

    return 0;
}
