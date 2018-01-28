/*
 * Copyright (C) 2018 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SERVER_H_
#define SERVER_H_

    #include "http_parser.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <unistd.h>
	#include <commons/log.h>

	typedef struct {
		char*  port;
        void(*handler)(t_sot_parsed, void(*writer)(char*));
		t_log_level log_level;
	} t_sot_server_config;

	/**
	* @NAME: run_server
	* @DESC: levanta un servidor HTTP
	* @PARAMS:
	* 		config - La configuracion del servidor
	*/
	void run_server(t_sot_server_config config);

#endif /* SERVER_H_ */