
#include "pistache/endpoint.h"
#include "pistache/client.h"
#include "include/rapidjson/document.h"
#include <string>
#include <cstring>
#include <regex.h>
#include <vector>

#include "Sender.h"

#define CRAWL_HOST "127.0.0.1"
#define CRAWL_PORT 9877

using namespace Pistache;

class Listener : public Http::Handler
{
public:
	HTTP_PROTOTYPE(Listener);

	void onRequest(const Http::Request &request, Http::ResponseWriter response);

private:
	Sender sender;
	std::vector<std::string> blacklist;
};