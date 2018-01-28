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

#ifndef HTTP_PARSER_H_
#define HTTP_PARSER_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <commons/string.h>

	/**
	 * Define los posibles verbos que entiende SOT
	 */
	typedef enum {
		set_verb_POST,
		set_verb_GET,
        set_verb_invalid
	} sot_verb_t;

	typedef struct {
		sot_verb_t verb;
		char* endpoint;
		char* _raw;
	} t_sot_parsed;


	/**
	* @NAME: http_parse
	* @DESC: descifra una conexcion HTTP
	* @PARAMS:
	* 		request - El string que llego al servidor
	*/
	t_sot_parsed http_parse(size_t  size, char *request);

#endif /* HTTP_PARSER_H_ */