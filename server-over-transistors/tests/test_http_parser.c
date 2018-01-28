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
#include <sot/http_parser.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cspecs/cspec.h>

context (http_parser) {

    describe ("parser") {

        it ("should parse a GET request as such") {
            char * request = "GET / HTTP/1.0 ....";
            t_sot_parsed parsed = http_parse(strlen(request), request);

        
            should_int( parsed.verb ) be equal to(set_verb_GET);
        } end

        it ("should parse a POST request as such") {
            char * request = "POST / HTTP/1.0 ....";
            t_sot_parsed parsed = http_parse(strlen(request), request);

            
            should_int( parsed.verb ) be equal to(set_verb_POST);
        } end

    } end

}