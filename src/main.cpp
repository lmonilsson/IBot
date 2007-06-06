#include <string>
#include <iostream>

#include <boost/program_options.hpp>

#include "IRCBot.h"

struct BotOptions
{
	std::string address;
	unsigned short port;
	
	std::string nickname;
	std::string channel;
	
	char command_char;
};

bool parse_commandline(int argc, char *argv[], BotOptions &options)
{
	namespace po = boost::program_options;
	
	po::options_description desc;
	desc.add_options()
		("help", "show options")
		("host", po::value<std::string>(&options.address), "the address of the IRC server")
		("port", po::value<unsigned short>(&options.port)->default_value(6667), "the port to connect to")
		("nick", po::value<std::string>(&options.nickname)->default_value("Amon"), "the nickname the bot should use")
		("channel", po::value<std::string>(&options.channel), "the channel the bot should be in")
		("commandchar", po::value<char>(&options.command_char)->default_value('!'), "the character the bot should react on");
	
	po::variables_map vm;
	
	try
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	}
	catch(const po::error &e)
	{
		std::cout << e.what() << std::endl << std::endl;
		std::cout << desc << std::endl;
		
		return false;
	}
	
	if(vm.count("help") > 0)
	{
		std::cout << desc << std::endl;
		return false;
	}
	
	return true;
}

int main(int argc, char *argv[])
{
	BotOptions options;
	
	if(!parse_commandline(argc, argv, options))
		return 0;
	
	IRC::IRCBot bot(options.address, options.port, options.nickname, options.channel, options.command_char);
	bot.run();
}
