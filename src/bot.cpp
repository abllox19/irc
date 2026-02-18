/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:47 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/17 17:04:16 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

void Bot::sendPrivMsg(Client& client, const std::string& msg)
{
	std::string irc =
		":" + name +
		" PRIVMSG " +
		client.getNickname() +
		" :" + msg + "\r\n";

	send(client.getFd(), irc.c_str(), irc.size(), 0);
}

void Bot::cmdHello(Client& client)
{
	sendPrivMsg(client, "Hello " + client.getNickname() + " 👋");
}

void Bot::cmdTime(Client& client)
{
	std::time_t now = std::time(NULL);
	sendPrivMsg(client, std::string("Server time: ") + std::ctime(&now));
}

void Bot::cmdUsers(Client& client, Server& server)
{
	
	sendPrivMsg(client, "Users command not implemented yet 👀");
}

void Bot::cmdJoke(Client& client, int& i)
{
	const std::vector<std::string> jokes = {

		"Pourquoi les programmeurs aiment le noir ? Parce que la lumière attire les bugs 🐛.",
		
		"Un développeur C ne dort pas, il segfault.",
		
		"Pourquoi Git est mauvais en couple ? Il n’arrive pas à commit.",
		
		"Il y a 10 types de personnes : celles qui comprennent le binaire et les autres.",
		
		"Pourquoi les développeurs confondent Halloween et Noël ? Parce que OCT 31 == DEC 25.",
		
		"Un bug, c’est juste une fonctionnalité non documentée.",
		
		"Je ne dis pas que mon code est parfait… mais il compile.",
		
		"Pourquoi le code ne marche pas ? Parce que ça marche sur ma machine.",
		
		"Un développeur sans café, c’est comme un serveur sans RAM.",
		
		"Ctrl+C et Ctrl+V ont fait plus de choses ensemble que certains couples.",
		
		"Pourquoi le programmeur a quitté sa copine ? Elle n’avait pas assez de commit.",
		
		"99 bugs dans le code, 99 bugs… Tu en corriges un, tu relances… 127 bugs dans le code.",
		
		"Le code, c’est comme l’humour. Si tu dois l’expliquer, c’est qu’il est mauvais.",
		
		"Stack Overflow, c’est Google pour les développeurs honnêtes.",
		
		"Un développeur ne meurt jamais… il passe juste en production.",
		
		"Pourquoi les devs aiment Linux ? Parce qu’ils ont le contrôle… ou du moins ils le croient.",
		
		"Chez 42, on ne dort pas… on segfault collectivement.",
		
		"Mon code ne bug pas, il surprend.",
		
		"Un bon développeur regarde des deux côtés avant de traverser une one-way hash.",
		
		"Pourquoi les threads se disputent ? Parce qu’ils ne sont pas synchronisés."
	};

	sendPrivMsg(client, jokes[i]);
	i = (i + 1) % jokes.size();
}



void Bot::handleMessage(Client& client, const ParsedCommand& cmd)
{
	if (cmd.getCommand() != "PRIVMSG")
		return;

	const std::string& msg = cmd.getTrailing();

	if (msg == "!hello")
		cmdHello(client);
	else if (msg == "!time")
		cmdTime(client);
	else if (msg == "!users")
		cmdUsers(client);
	else if (msg == "!joke")
		cmdJoke(client);
}


