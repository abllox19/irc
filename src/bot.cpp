/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:47 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/24 17:57:22 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot.hpp"

Bot::Bot() {name = ":Bot!Bot@127.0.0.1 ";}

// void	handle_dcc_send(std::string message)
// {
// 	std::stringstream	ss(message);
// 	std::string			token;
// 	std::string			filename;
// 	std::string			ip;
// 	std::string			port;
// 	std::string			size;

// 	ss >> token >> token >> filename >> ip >> port >> size;
// 	if (!size.empty() && size[size.length() - 1] == '\x01')
// 		size.erase(size.length() - 1);
// }

// bool parse_dcc_send(const std::string& msg, std::string& filename, std::string& ip, std::string& port, std::string& size)
// {
// 	std::string content = msg;

// 	// Vérifie début et fin CTCP
// 	if (content.size() < 2)
// 		return false;

// 	if (content[0] != '\x01' || content[content.size() - 1] != '\x01')
// 		return false;
// 	// Enlève les \x01
// 	content.erase(0, 1);
// 	content.erase(content.size() - 1);

// 	std::stringstream ss(content);
// 	std::string dcc;
// 	std::string send;

// 	ss >> dcc >> send >> filename >> ip >> port >> size;

// 	if (dcc != "DCC" || send != "SEND")
// 		return false;

// 	if (filename.empty() || ip.empty() || port.empty())
// 		return false;

// 	return true;
// }

// int	create_dcc_socket(int port)
// {
// 	int sock = socket(AF_INET, SOCK_STREAM, 0);
// 	if (sock < 0)
// 		return (-1);

// 	int opt = 1;
// 	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
// 	sockaddr_in addr;
// 	addr.sin_family = AF_INET;
// 	addr.sin_addr.s_addr = INADDR_ANY;
// 	addr.sin_port = htons(port);
	
// 	if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
// 	{
// 		close(sock);
// 		return (-1);
// 	}
// 	if (listen(sock, 1) < 0)
// 	{
// 		close(sock);
// 		return (-1);
// 	}

// 	return (sock);
// }

// void	send_file_to_client(int client_fd, const std::string& filename)
// {
// 	std::ifstream file(filename.c_str(), std::ios::binary);
// 	if (!file.is_open())
// 	{
// 		std::cout << "File not found\n";
// 		return;
// 	}

// 	char buffer[4096];
// 	while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
// 	{
// 		ssize_t total = 0;
// 		ssize_t bytes = file.gcount();

// 		while (total < bytes)
// 		{
// 			ssize_t sent = send(client_fd, buffer + total, bytes - total, 0);
// 			if (sent <= 0)
// 				break;
// 			total += sent;
// 		}
// 	}
// 	file.close();
// }

// void Bot::start_dcc_server(const std::string& filename, int port)
// {
// 	int sock = create_dcc_socket(port);
// 	if (sock < 0)
// 		return;

// 	std::cout << "DCC waiting on port "
// 	          << port << std::endl;

// 	int client_fd = accept(sock, NULL, NULL);
// 	if (client_fd < 0)
// 	{
// 		close(sock);
// 		return;
// 	}

// 	send_file_to_client(client_fd, filename);

// 	std::cout << "File sent successfully\n";

// 	close(client_fd);
// 	close(sock);
// }

// void Bot::handle_dcc_send(const std::string& filename,
//                           const std::string& port)
// {
//     int port_num = atoi(port.c_str());
//     if (port_num <= 0)
//         return;

//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         // fils : lance le serveur DCC
//         start_dcc_server(filename, port_num);
//         exit(0);
//     }
//     // père : continue normalement
// }

// bool parse_dcc_send(const std::string& msg, std::string& filename, std::string& ip, std::string& port, std::string& size)
// {
// 	if (msg.size() < 2)
// 		return false;

// 	if (msg[0] != '\x01' || msg[msg.size() - 1] != '\x01')
// 		return false;

// 	std::string content = msg.substr(1, msg.size() - 2);

// 	std::stringstream ss(content);
// 	std::string dcc;
// 	std::string send;

// 	ss >> dcc >> send >> filename >> ip >> port >> size;

// 	if (dcc != "DCC" || send != "SEND")
// 		return false;

// 	if (filename.empty() || ip.empty() || port.empty())
// 		return false;

// 	return true;
// }

// void Bot::handle_dcc_send(const std::string& filename, const std::string& port)
// {
// 	int port_num = atoi(port.c_str());
// 	if (port_num <= 0)
// 		return;

// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		start_dcc_server(filename, port_num);
// 		exit(0);
// 	}
// }

// int create_dcc_socket(int port)
// {
//     int sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0)
//         return -1;

//     int opt = 1;
//     setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

//     sockaddr_in addr;
//     std::memset(&addr, 0, sizeof(addr));
//     addr.sin_family = AF_INET;
//     addr.sin_addr.s_addr = INADDR_ANY;
//     addr.sin_port = htons(port);

//     if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
//     {
//         close(sock);
//         return -1;
//     }

//     if (listen(sock, 1) < 0)
//     {
//         close(sock);
//         return -1;
//     }

//     return sock;
// }

// void send_file(int client_fd, const std::string& filename)
// {
// 	std::ifstream file(filename.c_str(), std::ios::binary);
// 	if (!file.is_open())
// 		return;

// 	char buffer[4096];

// 	while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
// 	{
// 		int bytes = file.gcount();
// 		int total = 0;

// 		while (total < bytes)
// 		{
// 			int sent = send(client_fd,
// 							buffer + total,
// 							bytes - total,
// 							0);
// 			if (sent <= 0)
// 				break;
// 			total += sent;
// 		}
// 	}

// 	file.close();
// }

// void Bot::start_dcc_server(const std::string& filename, int port)
// {
// 	int sock = create_dcc_socket(port);
// 	if (sock < 0)
// 		return;

// 	std::cout << "DCC waiting on port "
// 			<< port << std::endl;

// 	int client_fd = accept(sock, NULL, NULL);
// 	if (client_fd < 0)
// 	{
// 		close(sock);
// 		return;
// 	}

// 	send_file(client_fd, filename);

// 	std::cout << "File sent successfully\n";

// 	close(client_fd);
// 	close(sock);
// }


void Bot::sendPrivMsg(Client& client, const std::string& msg)
{
	// size_t pos = msg.find(" :");
	// if (pos == std::string::npos)
	// 	return;

	// std::string content = msg.substr(pos + 2);

	// std::string filename, ip, port, size;
	// if (parse_dcc_send(content, filename, ip, port, size))
	// {
	// 	std::cout << "DCC SEND detected!" << std::endl;
	// 	handle_dcc_send(filename, port);
	// PRIVMSG Job :DCC SEND banned_word.txt 127001 5001 123
	// }

	std::string irc = name + " PRIVMSG " + client.get_nickname() + " :" + msg + "\r\n";

	send(client.get_fd_client(), irc.c_str(), irc.size(), 0);
}

void Bot::cmdHello(Client& client)
{
	sendPrivMsg(client, "Hello " + client.get_nickname() + " 👋");
}

void Bot::cmdTime(Client& client)
{
	std::time_t now = std::time(NULL);
	sendPrivMsg(client, std::string("Server time: ") + std::ctime(&now));
}

void Bot::cmdUsers(Client& client, Chanel* server)
{
	if (!server)
	{
		std::cout << "Server pointer is NULL" << std::endl;
		return;
	}

	std::vector<Client> clients = server->get_user();
	std::string irc = name + " chanel users :";
	for (size_t i = 0; i < clients.size(); i++)
	{
		irc += "\n";
		irc += clients[i].get_nickname();
	}
	irc += "\r\n";
	send(client.get_fd_client(), irc.c_str(), irc.size(), 0);
}

void Bot::cmdJoke(Client& client, int& i)
{
	std::vector<std::string> jokes;

		jokes.push_back("Pourquoi les programmeurs aiment le noir ? Parce que la lumière attire les bugs 🐛.");
		
		jokes.push_back("Un développeur C ne dort pas, il segfault.");
		
		jokes.push_back("Pourquoi Git est mauvais en couple ? Il n'arrive pas à commit.");
		
		jokes.push_back("Il y a 10 types de personnes : celles qui comprennent le binaire et les autres.");
		
		jokes.push_back("Pourquoi les développeurs confondent Halloween et Noël ? Parce que OCT 31 == DEC 25.");
		
		jokes.push_back("Un bug, c'est juste une fonctionnalité non documentée.");
		
		jokes.push_back("Je ne dis pas que mon code est parfait… mais il compile.");
		
		jokes.push_back("Pourquoi le code ne marche pas ? Parce que ça marche sur ma machine.");
		
		jokes.push_back("Un développeur sans café, c'est comme un serveur sans RAM.");
		
		jokes.push_back("Ctrl+C et Ctrl+V ont fait plus de choses ensemble que certains couples.");
		
		jokes.push_back("Pourquoi le programmeur a quitté sa copine ? Elle n'avait pas assez de commit.");
		
		jokes.push_back("99 bugs dans le code, 99 bugs… Tu en corriges un, tu relances… 127 bugs dans le code.");
		
		jokes.push_back("Le code, c'est comme l'humour. Si tu dois l'expliquer, c'est qu'il est mauvais.");
		
		jokes.push_back("Stack Overflow, c'est Google pour les développeurs honnêtes.");
		
		jokes.push_back("Un développeur ne meurt jamais… il passe juste en production.");
		
		jokes.push_back("Pourquoi les devs aiment Linux ? Parce qu'ils ont le contrôle… ou du moins ils le croient.");
		
		jokes.push_back("Chez 42, on ne dort pas… on segfault collectivement.");
		
		jokes.push_back("Mon code ne bug pas, il surprend.");
		
		jokes.push_back("Un bon développeur regarde des deux côtés avant de traverser une one-way hash.");
		
		jokes.push_back("Pourquoi les threads se disputent ? Parce qu'ils ne sont pas synchronisés.");

	sendPrivMsg(client, jokes[i]);
	i = (i + 1) % jokes.size();
}



void Bot::handleMessage(Client& client, std::string &cmd, Chanel* chanel)
{
	static int i = 0;

	std::cout << cmd << std::endl;
	if (cmd == "hello")
		cmdHello(client);
	else if (cmd == "time")
		cmdTime(client);
	else if (cmd == "users")
	{
		if (chanel)
			cmdUsers(client, chanel);
	}
	else if (cmd == "joke")
		cmdJoke(client, i);
}


