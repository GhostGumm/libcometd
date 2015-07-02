#include <jansson.h>

#include "cometd_internal.h"
#include "zetaclient.h"
#include "listingEntryInfo.h"
#include "ListingGdaInfo.h"
#include "comet_message.h"
#include "putGdaInfo.h"
#include "getGdaInfo.h"
#include "HashMaps.h"
#include "messageEntryInfo.h"
#include "stackListingInfo.h"
#include "queueInfo.h"
#include "handler.h"
#include "CommandParsingInfo.h"

/*#pong*/

zeta_handshake_manager_t * hr;
zeta_client_t * cr;

OwnerRessource*  fillRessource()
{
  OwnerRessource *res = malloc(sizeof(OwnerRessource));
  res->owner = "toto";
  res->ressource = "stack";

  return res;
}

HashMaps   *fillUsers()
{
  HashMaps *list = HashMapInit();
  list->type = "string";
  list->key = "test3";
  list->value = "OvWudbZchXdOa-uoMGZNfA";
  list = AddKeyValue(list);
  list->key = "test4";
  list->type = "string";
  list->value = "tfXrOlDf9CYWF88akl73Lg";
  while (list->prev != NULL)
    list = list->prev;
  return (list);
}

HashMaps   *fillActions()
{
  HashMaps *list = HashMapInit();
  list->type = "string";
  list->key = "action";
  list->value = "grant";
  list = AddKeyValue(list);
  list->type = "string";
  list->key = "action";
 list->value = "revoke";
 list = AddKeyValue(list);
  list->type = "string";
  list->key = "action";
  list->value = "grant";
  while (list->prev != NULL)
    list = list->prev;
  return (list);
}

HashMaps   *fillMap()
{
  HashMaps *list = HashMapInit();
  list->type = "string";
  list->key = "test1";
  list->value = "listener1";
  list = AddKeyValue(list);
  list->key = "test2";
  list->type = "string";
  list->value = "listener2";
  list = AddKeyValue(list);
  list->key = "test3";
  list->type = "string";
  list->value = "listener3";
  while (list->prev != NULL)
    list = list->prev;
  return (list);
}

const char *  parse_game(json_t *source)
{
  return (json_string_value(json_object_get(source, "next_move")));
}

bool execute_callback(cometd_client_t *client, cometd_message *message)
{
  printf("execute callback\n");
  
  exit(0);
}

bool comand_callback(cometd_client_t *client, cometd_message *message)
{
  char *c;
  c =  CommandParsinginfo(message);
  start_game(c[0]);
  return (true);
}

bool ping_callback(cometd_client_t *client, cometd_message *message)
{
  printf("Ping callback lets pong : \n\n");
  GdaParsingInfo(message);

  //cometd_pong_request(cr->cometClient, hr, "2v_u", "Game", "true", "ShDmD1_ZFwNnmmjLxJCroA", "resource1", "uid", "ShDmD1_ZFwNnmmjLxJCroA");  
  return false;
}

bool pong_callback(cometd_client_t *client, cometd_message *message)
{
  printf("It ponged well let's execute : \n\n");
  
  GdaParsingInfo(message);
  //cometd_execute_request(cr->cometClient, hr, "2v_u" ,"the magic toto", fillMap(), "ShDmD1_ZFwNnmmjLxJCroA", "resource0","ShDmD1_ZFwNnmmjLxJCroA", "resource1");
  return false;
}

int main(int argc, char** argv) {
  
  int argn = 1;
  const char * server = "http://m.zpush.ovh:8080/str/strd";
  const char * login = "test2";
  const char * resource = "zetaTuto";
  const char * businessId = "GmY-HuzW";
  const char * deploymentId = "KZyH";
  const char * Zpfs = "p8qU";
  const char * gda  = "IFa0";
  const char * echo = "w3FQ";
  const char * Zpfs2 = "9LDy";
  const char * Zpfs3 = "2vC3";
  const char * password = "password";
  const char * msging = "RSVu";
  const char * stackId  = "cKXj";
  const char * remoteId = "";
  const char * queueId = "aHqx";
  const char * groupe = "2v_u";
  const char * macro = "57C3";
  const char * game = "";
  HashMaps *data = HashMapInit();
  
  signal(SIGINT, signal_callback_handler);
  
  initBoard(board);
  setBufferedInput(false);

	printf("Starting test program for user %s and resource %s\n", login, resource);
	if (cometd_init()) {
	  printf("cometd_init failed\n");
	} else {
		zeta_handshake_manager_t * hm = zeta_create_mem_handshake_manager(businessId, deploymentId, login, password);
		hr = hm;
		zeta_client_t * client = zeta_create_client(server, cometd_create_long_polling_transport(), businessId, hm, "resource1");
		cr = client;
		if (client) {
		  printf("client created\n");
		  cometd_channel_subscribe(client->cometClient, execute_callback, "/service/GmY-HuzW/2v_u/execute");
		  cometd_channel_subscribe(client->cometClient, comand_callback, "/service/GmY-HuzW/2v_u/command");
		  cometd_channel_subscribe(client->cometClient, ping_callback, "/service/GmY-HuzW/2v_u/ping");
	      
		  //cometd_channel_subscribe(client->cometClient, comand_callback, "/service/GmY-HuzW/2v_u/command");
		  int i = 0;
		  if (!zeta_handshake(client)) {
		    printf("cometd_handshake OK\n");
		    cometd_client_impl* cli = (cometd_client_impl*)client->cometClient;
		    while (!cometd_main_loop(client->cometClient)) {
		      puts("---------Echo request---------");
		      //cometd_ping_request(client->cometClient, hm, groupe, "Game");
		      //cometd_execute_request();
		      puts("---------Echo Request---------");
		      //printf("cometd_main_loop OK\n");
		      //if (!(i++ % 10))
		      //cometd_send_chat_message(client, "this is a chat message", buddy);
		      if (i == 25)
			cometd_disconnect(client->cometClient);
		    }	
		  }else
		    printf("cometd_handshake failed\n");
		}
	}
	return 0;
}

