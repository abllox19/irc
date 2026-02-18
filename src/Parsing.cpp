/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:58:47 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/18 17:12:02 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parsing.hpp"

void parse(const std::string& line, ParsedCommand& parse)
{
	std::stringstream	ss;
	std::string			token;
	std::string			str = line;

	parse.command.clear();
	parse.params.clear();
	parse.trailing.clear();
	parse.ban = false;

	size_t pos = str.find(" :");
	if (pos != std::string::npos)
	{
		parse.trailing = str.substr(pos + 2);
		str = str.substr(0, pos);
	}

	ss.str(str);
	while (ss >> token)
	{
		if (parse.command.empty())
			parse.command = token;
		else
			parse.params.push_back(token);
	}
	parse.params.push_back(parse.trailing);
	
}


void botfilterMessage(ParsedCommand& parse, std::string& message, const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	std::string banned;
	while (std::getline(file, banned))
	{
		if (banned.empty())
			continue;
		
		size_t pos = 0;
		while ((pos = message.find(banned, pos)) != std::string::npos)
		{
			if ((pos == 0 || message[pos - 1] == (' ')) && (pos + banned.size() >= message.size() || message[pos + banned.size()] == ' '))
			{
				std::string mask(banned.size(), '*');
				message.replace(pos, banned.size(), mask);
				pos += mask.size();

				parse.ban = true;
				std::cout << "WARNING: be polite please, respect the channel rules" << std::endl;
			}
			else
				pos++;
		}
	}
}

// int main()
// {
//     ParsedCommand parse;
//     std::string str = "combrecon ";

//     parse.command.clear();
// 	parse.params.clear();
// 	parse.trailing.clear();
// 	parse.ban = false;
    
//     botfilterMessage(parse, str, "banned_word.txt");
// }

// IRCMessage  parseIRCMessage(const std::string& rawInput){
//     IRCMessage  msg;

//     std::string line = rawInput;
//     if (line.size() >= 2 && line.substr(line.size() - 2) == "\r\n")
//         line = line.substr(0, line.size() - 2);
//     else if (!line.empty() && (line[line.size() - 1] == '\n' || line[line.size() - 1] == '\r'))
//         line.erase(line.size() - 1);
    
//     std::istringstream iss(line);
//     std::string token;

//     if (!line.empty() && line[0] == ':'){
//             iss >> token;
//             msg.prefix = token.substr(1);
//     }

//     if (!(iss >> msg.command)){
//             msg.command = "";
//             return msg;
//     }

//     while (iss >> token){
//         if (token[0] == ':'){
//             std::string param = token.substr(1);
//             std::string rest;
//             while (iss >> rest)
//                 param += " " + rest;
//             msg.params.push_back(param);
//             break;
//         } else {
//             msg.params.push_back(token);
//         }
//     }
//     return msg;
// }


// void    handleIRCMessage(const IRCMessage& msg){
//     const std::string&  cmd = msg.command;

//     if (cmd == "PING"){
//         if (!msg.params.empty()){
//             std::cout << "PING :" << msg.params[0] << "\r\n";
//         }
//     } else if (cmd == "PONG"){
//         std::cout << "Received PONG from server\n";
//     } else if (cmd == "PRIVMSG"){
//         if (msg.params.size() >= 2){
//             std::string from = msg.prefix;
//             std::string target = msg.params[0];
//             std::string message = msg.params[1];

//             std::cout << "Message from "<< from << " to " << target << ": " << message << "\n";
//         }
//     } else if (cmd == "NOTICE"){
//         if (msg.params.size() >= 2){
//             std::string from = msg.prefix;
//             std::string target = msg.params[0];
//             std::string message = msg.params[1];

//             std::cout << "Notice from "<< from << " to " << target << ": " << message << "\n";
//         }
//     } else if (cmd == "JOIN"){
//         if (!msg.params.empty()){
//             std::cout << msg.prefix << " joined " << msg.params[0] << "\n";
//         }
//     } else if (cmd == "PART"){
//         if (!msg.params.empty()){
//             std::cout << msg.prefix << " left " << msg.params[0] << "\n";
//         }
//     } else if (cmd == "QUIT"){
//         std::string reason = (msg.params.empty() ? "" : msg.params[0]);
//         std::cout << msg.prefix << " quit IRC (" << reason << ")\n";
//     } else if (cmd =="NICK"){
//         if (!msg.params.empty()){
//             std::cout << msg.prefix << " is now known as " << msg.params[0] << "\n";
//         }
//     } else if (cmd == "TOPIC"){
//         if (msg.params.size() >= 2){
//             std::cout << msg.prefix << " changed topic on " << msg.params[0] << " to: " << msg.params[1] << "\n";
//         }
//     } else if (cmd == "MODE"){
//         if (msg.params.size() >= 2){
//             std::string target = msg.params[0];
//             std::string modes = msg.params[1];

//             std::cout << msg.prefix << " set mode on " << target << ": " << modes << "\n";
//             bool    adding = true;
//             for (size_t i = 0; i < modes.size(); i++){
//                 char c = modes[i];
//             if (c == '+'){
//                 adding = true;
//             } else if (c == '-') {
//                 adding = false;
//             }
//             else {
//                 std::string action = adding ? "enabled": "disabled";
//                 std::string description;

//                 switch (c){
//                     case 'i':
//                         description = "Invite-only channel";
//                         break;
//                     case 't':
//                         description = "Only channel operators can change the topic";
//                         break;
//                     case 'k':
//                         description = "Channel key (password) required to join";
//                         break;
//                     case 'o':
//                         description = "Give/take channel operator privileges";
//                         break;
//                     case 'l':
//                         description = "Set/remove user limit";
//                         break;
//                     default:
//                         description = "Unknown mode";
//                         break;
//                 }
//                 std::cout << " Mode '" << c << "' " << action << ": " << description << "\n";
//             }
//             }
//         }
//     } else if (cmd == "001"){
//         if (!msg.params.empty())
//             std::cout << "Connected: " << msg.params.back() << "\n";
//     } else if (cmd == "433"){
//         std::cout << "Error: Nickname is already in use.\n";
//     } else {
//         std::cout << "Unhandled command [" << cmd << "]\n";
//         std::cout << "Params: ";
//         for (std::vector<std::string>::const_iterator it = msg.params.begin(); it != msg.params.end(); it++){
//             std::cout << "[" << *it << "] ";
//         }
//         std::cout << "\n";
//     }
// }


