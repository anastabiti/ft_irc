/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:11:23 by archid            #+#    #+#             */
/*   Updated: 2023/03/22 09:18:15 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "server.hpp"
#include "../headers/client.hpp"

void authenthic(const std::string &msg, const int fd)
{
    
    client *tmp = NULL;

    tmp = map_clients.at(fd);
    if (msg.find("NICK ") != std::string::npos && tmp->nickname().empty())
    {
        if (msg.length() > 6){
            tmp->nickname(msg.substr(5));
            std::cout << "nick name set\n";
            return ;
        }
    }

    if (msg.find("USER ") != std::string::npos && tmp->username().empty()) {
        if (msg.length() > 6)
        {
            tmp->username(msg.substr(5));
            std::cout << "user set\n";
            return ;
        }
    }

    if (msg.find("PASS ") != std::string::npos)
    {
        if (msg.length() > 6){
            std::string tmp1 = msg.substr(5);
            if (tmp1 == "123")
            {
                return ;
            }
            std::cerr << "464 " << "PASS" << " :Password incorrect" << tmp1 <<"|"<< std::endl;
    }
    send(fd, "wrong arg\n", 10, 0);
}
}