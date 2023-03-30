#pragma once

#include "server.hpp"

enum channel_properties { disabled_n, enabled_n };

class channel {
	public:
		typedef std::map<std::string, class user *> for_kick;
		channel(std::string name, std::string passwd = "", std::string topic = "");
		std::string passwrd(void);
		void broadcast(std::string msg);
		
		std::string users_list();
		void notif_new_client_joined(user *sender);
		
		for_kick kick_list() { return map_users_for_kick; }
		void insert_users(user *user);
		void insert_in_kick_list(user *user);
		void part_user(user *user);
		// enum channel_properties out_side_msg = enabled_n;

		const std::string &name() const { return name_; }
		const std::string &topic() const { return topic_; }
		void set_topic(const std::string &top) {topic_ = top;}

		std::vector<std::string> get_admins_list() { return admin_names; }

		int 	how_many_usr() const {return users_fd.size();}
		bool	check_if_user_in(user *user_to_check);

		std::vector<int> users_fd;
	private:
		for_kick map_users_for_kick;
		std::vector<std::string> admin_names;
		std::vector<std::string> r_user_names;
		std::string name_,  passwd,topic_;
};

void	send_msg(std::string, user *user);
std::string get_tim();

std::ostream &operator<<(std::ostream &oss, const class channel chan);
typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
extern std::vector<std::string> channels_name;