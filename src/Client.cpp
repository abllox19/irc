/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:47:47 by asoumare          #+#    #+#             */
/*   Updated: 2026/02/27 15:40:16 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"
#include "../include/Chanel.hpp"


Client::Client(int fd_client, char *ip): fd(fd_client), authenticated(false) {
    this->ip = std::string(ip);
}
//Client::Client() : id(0), nickname("nickname"), username("username"), chanelname("void") {}

Client::~Client() {}

 // getter

std::string Client::get_ip(void)
{
    return ip;
}

std::string Client::get_nickname(void)
{
    return nickname;
}

std::string Client::get_username(void)
{
    return username;
}

std::vector<std::string> Client::get_chanelname(void)
{
    return chanelname;
}

 // setter

void Client::set_nickname(std::string nickname)
{
    this->nickname = nickname;
}

void Client::set_username(std::string username)
{
    this->username = username;
}

void Client::set_chanelname(std::string chanel_name)
{
    chanelname.push_back(chanel_name);
}


int Client::get_fd_client(void)
{
    return this->fd;
}

// authenticated

bool Client::is_authenticated()
{
    return authenticated;
}

void Client::set_authenticated(bool value)
{
    authenticated = value;
}


// ft utile

std::string send_prefix(Client client)
{
    std::string prefix = ":" + client.get_nickname() + "!" + client.get_username() + "@" + client.get_ip() + " ";
    return prefix;
}

void send_msg(Client client, std::vector<std::string> msg, int fd, std::string cmd)
{
    std::string txt = send_prefix(client) + cmd + " " + msg[0] + " : ";
    send(fd, txt.c_str(), txt.size(), 0);

    for (size_t i = 1; i < msg.size(); i++)
    {
        send(fd, msg[i].c_str(), strlen(msg[i].c_str()), 0);
        send(fd, " ", 1, 0);
    }

    send(fd, "\r\n", 2, 0);
}

void change_nickname(std::vector<Client>& clients, std::string nick, int i)
{
    if (nick == "" || nick[0] == '#')
    {
        send(clients[i].get_fd_client(), "Erreur: pseudo invalide (vide) ou (#)\n", 38, 0);
        return;
    }

    if (!clients[i].get_nickname().empty())
    {
        send(clients[i].get_fd_client(), "vous ne pouvez pas changer de nickname !\n", 41, 0); // pas obliger
        return;
    }

    for (size_t j = 0; j < clients.size(); j++)
    {
        if (j != (size_t)i && clients[j].get_nickname() == nick)
        {
            std::string txt = ":server 433 * " + nick + " :Nickname is already in use\n";
            send(clients[i].get_fd_client(), txt.c_str(), txt.size(), 0);
            return;
        }
    }

    clients[i].set_nickname(nick);
    send(clients[i].get_fd_client(), "vous avez changé de pseudo !\n", 30, 0);
    std::cout << "Client " << clients[i].get_fd_client() 
              << " a changé son pseudo en: " << nick << std::endl;
}


void change_username(Client &clients, std::string user, Client &client) // ajouter le -> <hostname> <servername> :<realname>
{
    user.erase(user.find_last_not_of(" \r\n") + 1);
    
    if (user.empty())
        send(clients.get_fd_client(), "Erreur: pseudo invalide\n", 25, 0);
    else
    {
        clients.set_username(user);
        std::string txt = ":server 001 " + user + " :Welcome to the IRC server " + send_prefix(client) + "\n";
        send(clients.get_fd_client(), txt.c_str(), txt.size(), 0);
        std::cout << "Client " << clients.get_fd_client() << " a changé son pseudo en: " << user << std::endl;
    }
}

void join_chanel(Client &client, Chanel *chanel, std::string mdp) // ajoute les bool et le MDP
{
    std::vector<Client> users = chanel->get_user();

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].get_nickname() == client.get_nickname())
        {
            std::string txt = "Vous êtes déjà dans ce channel !\n";
            send(client.get_fd_client(), txt.c_str(), txt.size(), 0);
            return;
        }
    }
    if (chanel->get_invite() == true)
        send(client.get_fd_client(), "chanel sur invitation uniqument !\n", 34, 0);
    else if (chanel->get_size() > 0 && chanel->get_user().size() >= chanel->get_size())
        send(client.get_fd_client(), "le chanel est plein !\n", 22, 0);
    else if (chanel->get_mdp() != "" && chanel->get_mdp() != mdp)
        send(client.get_fd_client(), "le mot de pass est incorect !\n", 30, 0);
    else
    {
        std::string txt = ":" + client.get_nickname() + " JOIN :" + chanel->get_name() + "\n";
        for (size_t i = 0; i < users.size(); i++)
            send(users[i].get_fd_client(), txt.c_str(), txt.size(), 0);
        chanel->add_user(client);
        send(client.get_fd_client(), "Vous avez rejoint le channel !\n", 32, 0);
        client.set_chanelname(chanel->get_name());
        std::vector<std::string> test = client.get_chanelname();
        for (size_t i = 0; i < test.size(); i++)
            std::cout << test[i] << std::endl;

    }
}

void part_chanel(Client &client, Chanel *chanel, const std::string &name)
{
    if (!chanel)
    {
        send(client.get_fd_client(), "Channel introuvable !\n", 23, 0);
        std::cout << "Channel introuvable : " << name << std::endl;
        return;
    }

    std::vector<Client>& users = chanel->get_user();

    for (size_t i = 0; i < users.size(); ++i)
    {
        if (client.get_nickname() == users[i].get_nickname())
        {
            std::string txt = ":" + client.get_nickname() + " PART " + chanel->get_name() + "\n";

            for (size_t j = 0; j < users.size(); ++j)
                send(users[j].get_fd_client(), txt.c_str(), txt.size(), 0);

            chanel->del_user(client.get_nickname());
            chanel->del_modo(client.get_nickname());

            send(client.get_fd_client(), "Vous avez quitté le channel.\n", 31, 0);
            std::cout << "Client " << client.get_nickname() << " a quitté le channel " << name << std::endl;
            
            if (chanel->get_user().empty())
            {
                // std::cout << "Client " << client.get_nickname() << " a quitté le channel " << name << std::endl;
                chanel->del_chanel();
            }

            return;
        }
    }

    send(client.get_fd_client(), "Vous n'êtes pas dans ce channel !\n", 35, 0);
    std::cout << "Client " << client.get_nickname() << " a essayé de quitter " << name << " sans y être.\n";
}

bool parse_dcc_send(const std::string& msg, std::string& filename, std::string& ip, std::string& port, std::string& size)
{
	if (msg.size() < 2)
		return false;
    
    if (msg.find("DCC SEND") == std::string::npos)
    {
        return false;
    }
    
	std::stringstream ss(msg);
	std::string dcc;
	std::string send;

	ss >> dcc >> send >> filename >> ip >> port >> size;

	if (dcc != "DCC" || send != "SEND")
		return false;

	if (filename.empty() || ip.empty() || port.empty())
		return false;

	return true;
}
// PRIVMSG Job :\x01DCC SEND banned_word.txt 127001 5001 123\x01
//  PRIVMSG Job :DCC SEND banned_word.txt 127001 5001 123

// bool parse_dcc_send(const std::string& msg, std::string& filename, std::string& ip, std::string& port, std::string& size)
// {
//     std::string clean = msg;

//     if (!clean.empty() && clean[0] == '\x01') {
//         clean = clean.substr(1);
//     }
//     if (!clean.empty() && clean[clean.size() - 1] == '\x01') {
//         clean = clean.substr(0, clean.size() - 1);
//     }

//     if (clean.find("DCC SEND") == std::string::npos) {
//         return false;
//     }

//     std::stringstream ss(clean);
//     std::string dcc, send;

//     ss >> dcc >> send >> filename >> ip >> port >> size;

//     if (dcc != "DCC" || send != "SEND") {
//         return false;
//     }

//     if (filename.empty() || ip.empty() || port.empty()) {
//         return false;
//     }

//     return true;
// }

int create_dcc_socket(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return -1;

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        close(sock);
        return -1;
    }

    if (listen(sock, 1) < 0)
    {
        close(sock);
        return -1;
    }

    return sock;
}

void send_file(int client_fd, const std::string& filename)
{
	std::ifstream file(filename.c_str(), std::ios::binary);
	if (!file.is_open())
		return;

	char buffer[4096];

	while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
	{
		int bytes = file.gcount();
		int total = 0;

		while (total < bytes)
		{
			int sent = send(client_fd, buffer + total, bytes - total, 0);
			if (sent <= 0)
				break;
			total += sent;
		}
	}
	file.close();
}

void start_dcc_server(const std::string& filename, int port)
{
	int sock = create_dcc_socket(port);
	if (sock < 0)
		return;

	std::cout << "DCC waiting on port "
			<< port << std::endl;

	int client_fd = accept(sock, NULL, NULL);
	if (client_fd < 0)
	{
		close(sock);
		return;
	}

	send_file(client_fd, filename);
    
	std::cout << "File sent successfully\n";

	close(client_fd);
	close(sock);
}

void handle_dcc_send(const std::string& filename, const std::string& port)
{
	int port_num = atoi(port.c_str());
	if (port_num <= 0)
		return;

	pid_t pid = fork();
	if (pid == 0)
	{
		start_dcc_server(filename, port_num);
		exit(0);
	}
}

void privmsg(std::vector<Client> clients, std::vector<std::string> msg, Client client, std::vector<Chanel> chanels, std::string cmd)
{
    std::string filename, ip, port, size;
    
    if (parse_dcc_send(msg[1], filename, ip, port, size))
    {
        std::cout << "DCC SEND detected!" << std::endl;
        std::cout << "File: " << filename << ", Port: " << port << std::endl;
        int port_num = atoi(port.c_str());
        start_dcc_server(filename, port_num);
    }
    
    if (!msg.empty() && !msg[0].empty() && msg[0][0] == '#')
    {
        std::string name = msg[0];
        for (size_t i = 0; i < chanels.size(); ++i)
        {
            if (chanels[i].get_name() == name)
            {
                send_in_chanel(msg, client, chanels[i]);
                return;
            }
        }
        std::string err = ":server 403 " + client.get_nickname() +
                        " " + name + " :No such channel\r\n";
        send(client.get_fd_client(), err.c_str(), err.size(), 0);
    }

    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].get_nickname() == msg[0])
        {
            send_msg(client, msg, clients[i].get_fd_client(), cmd);
            return;
        }
    }
    std::string txt = ":server 401 " + client.get_nickname() + " " + msg[0] + " :No such nick/channel\n";
    send(client.get_fd_client(), txt.c_str(), txt.size(), 0);
}

bool check_modo(Chanel *chanel, Client client)
{
    std::vector<std::string> modo = chanel->get_modo();
    for (size_t j = 0; j < modo.size(); j++)
    {
        if (client.get_nickname() == modo[j])
            return true;
    }

    std::string reply = ":server 482 " + client.get_nickname() + " " + chanel->get_name() + " :You're not channel operator\r\n";
    send(client.get_fd_client(), reply.c_str(), reply.size(), 0);
    return false;
}


void send_in_chanel(std::vector<std::string> msg, Client client, Chanel chanel)
{
    std::vector<Client> user = chanel.get_user();
    for (size_t i = 0; i < user.size(); i++)
    {
        if (client.get_nickname() == user[i].get_nickname())
        {
            for (size_t i = 0; i < user.size(); i++)
                if (client.get_nickname() != user[i].get_nickname())
                    send_msg(client, msg, user[i].get_fd_client(), "PRIVMSG");
            return ;
        }
    }
    send(client.get_fd_client(), "Vous n'êtes pas dans ce channel !\n", 35, 0);
}

void send_action(Client client, int fd, std::string cmd, std::string dest, std::string msg)
{
    std::string txt = send_prefix(client) + cmd + " " + dest;
    send(fd, txt.c_str(), txt.size(), 0);

    if (msg != "NULL")
    {
        send(fd, " : ", 3, 0);
        send(fd, msg.c_str(), strlen(msg.c_str()), 0);
    }

    send(fd, "\r\n", 2, 0);
}

void mode_cmd(std::vector<std::string> cdm, Chanel *chanel)
{
    if (cdm.size() < 2)
    {
        std::cerr << "Erreur: commande MODE incomplète." << std::endl;
        return;
    }

    const std::string &mode = cdm[1];
    if (mode.size() < 2)
    {
        std::cerr << "Erreur: mode '" << mode << "' invalide." << std::endl;
        return;
    }

    if (mode[1] == 'i' && mode.size() == 2)
    {
        std::cout << "mode i" << std::endl;
        chanel->chanel_only_invite(mode[0] == '+');
    }
    else if (mode[1] == 't' && mode.size() == 2)
    {
        std::cout << "mode t" << std::endl;
        chanel->set_topic(mode[0] == '+');
    }
    else if (mode[1] == 'k' && mode.size() == 2)
    {
        std::cout << "mode k" << std::endl;
        if (mode[0] == '+')
        {
            if (cdm.size() < 3)
            {
                std::cerr << "Erreur: mot de passe manquant pour +k." << std::endl;
                return;
            }
            chanel->set_mdp(cdm[2]);
        }
        else
            chanel->set_mdp("");
    }
    else if (mode[1] == 'o' && mode.size() == 2)
    {
        std::cout << "mode o" << std::endl;
        if (cdm.size() < 3)
        {
            std::cerr << "Erreur: nom d'utilisateur manquant pour +o/-o." << std::endl;
            return;
        }
        if (mode[0] == '+')
            chanel->add_modo(cdm[2]);
        else
            chanel->del_modo(cdm[2]);
    }
    else if (mode[1] == 'l' && mode.size() == 2)
    {
        std::cout << "mode l" << std::endl;
        if (mode[0] == '+')
        {
            if (cdm.size() < 3)
            {
                std::cerr << "Erreur: limite manquante pour +l." << std::endl;
                return;
            }
            chanel->set_size(cdm[2]);
        }
        else
            chanel->set_size("-1");
    }
    else
    {
        std::cerr << "Mode inconnu : " << mode << std::endl;
    }
}
