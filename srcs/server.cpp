// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             //
//   Updated: 2023/03/05 03:18:21 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "server.hpp"

namespace yairc {
  int server::num_connections_ = NUM_CONNECTIONS;

  server::server(const char *host, int port) : addr_(setup_address(host, port)) {
	if ((sock_fd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0
		|| ((bind(sock_fd_, addr_, sizeof(struct sockaddr))) < 0)) {
	  exception_handler();
	}


  }

} // namespace yairc
