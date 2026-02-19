/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abllox <abllox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:30 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/19 16:21:58 by abllox           ###   ########.fr       */
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
		void cmdUsers(Client& client, Chanel* server);
		void cmdJoke(Client& client, int& i);

	public:
		Bot();

		void handleMessage(Client& client, std::string& cmd, Chanel* chanel);
};
