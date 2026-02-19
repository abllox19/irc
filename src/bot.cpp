/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abllox <abllox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:47 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/19 17:04:29 by abllox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

Bot::Bot() {name = ":Bot!Bot@127.0.0.1 ";}

void Bot::sendPrivMsg(Client& client, const std::string& msg)
{
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
	std::vector<Client> clients;
	clients = server->get_user();
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


