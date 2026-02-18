/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:30 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/18 18:01:44 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Parsing.hpp"
#include <ctime>


class Bot
{
	private:
		std::string name;

		void sendPrivMsg(Client& client, const std::string& msg);

		void cmdHello(Client& client);
		void cmdTime(Client& client);
		void cmdUsers(Client& client, Server& server);
		void cmdJoke(Client& client, int& i);

	public:
		Bot(const std::string& name);

		void handleMessage(Client& client, const ParsedCommand& cmd);
};
