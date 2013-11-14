#include <string>
#include <stdlib.h>
#include <boost/program_options.hpp>


#include "extraffic/dissect/Dissector.hpp"


namespace options = boost::program_options;


using extraffic::dissect::Dissector;


int main(int argc, char** argv)
{
    try
    {
        options::options_description description("Dissects tcp/udp packet captures as json");

        description.add_options()
            ("help,h", "Displays this help message")
            ("capture-file,c", options::value<std::string>()->required(), "Specifies the capture file to dissect")
            ("output-file,o", options::value<std::string>(), "Specifies the output file to write the dissected flow to")
            ;

        options::variables_map variables;

        try
        {
            options::store(options::parse_command_line(argc, argv, description), variables);

            if(variables.count("help"))
            {
                std::cout << description << std::endl;
                return 0;
            }

            options::notify(variables);

            Dissector dissector(variables["capture-file"].as<std::string>());
            dissector.dissect();
        }
        catch (boost::program_options::required_option& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl;
            return 2;
        }
        catch(boost::program_options::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl;
            return 2;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
