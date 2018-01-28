#include "http_parser.h"

sot_verb_t get_verb(char *request);
char* get_endpoint(char *request);

t_sot_parsed http_parse(size_t size, char *request){
	t_sot_parsed response;

	response.verb = get_verb(request);
	response.endpoint = get_endpoint(request);
	response._raw = request;

	return response;
}

sot_verb_t get_verb(char *request){
	switch(request[0]){
		case 'G' :
			return set_verb_GET;
		case 'P' :
			return set_verb_POST;
		default:
			return set_verb_invalid;
	}
}

char* get_endpoint(char *request){
	char *save = string_duplicate(request);
	strtok_r(save, " ", &save);
	return strtok_r(save, " ", &save);
}