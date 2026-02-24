/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:42:30 by jmafueni          #+#    #+#             */
/*   Updated: 2026/02/24 15:48:23 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Parsing.hpp"
# include <ctime>
# include <pthread.h>
# include <fstream>
# include <arpa/inet.h>
# include <unistd.h>

// En haut de bot.hpp
class Client;
class Chanel;

class Bot
{
	private:
		std::string name;

		void sendfile(Client& sender, Client& target, const std::string& msg);
		void	handle_dcc_send(const std::string& filename, const std::string& port);
		void	start_dcc_server(const std::string& filename, int port);
		void	sendPrivMsg(Client& client, const std::string& msg);
		void	cmdHello(Client& client);
		void	cmdTime(Client& client);
		void	cmdUsers(Client& client, Chanel* server);
		void	cmdJoke(Client& client, int& i);

	public:
		Bot();

		void handleMessage(Client& client, std::string& cmd, Chanel* chanel);
};
