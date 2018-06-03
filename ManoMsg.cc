// This Test Port skeleton source file was generated by the
// TTCN-3 Compiler of the TTCN-3 Test Executor version CRL 113 200/6 R4A
// for dark (dark@development) on Wed May 23 15:46:39 2018

// Copyright (c) 2000-2018 Ericsson Telecom AB

// You may modify this file. Complete the body of empty functions and
// add your member functions here.

#include "ManoMsg.hh"
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "yaml-cpp/yaml.h" // yaml-cpp >=0.6 needed
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>


namespace ServiceProfiling__PortType {

ManoMsg::ManoMsg(const char *par_port_name)
	: ManoMsg_BASE(par_port_name)
{
	debug = true;

	vnf_path = "/home/dark/son-examples/service-projects/sonata-empty-service-emu/sources/vnf/";
	nsd_path = "/home/dark/son-examples/service-projects/";

	gatekeeper_rest_url = "http://172.17.0.2:5000";
	vimemu_rest_url = "http://172.17.0.2:5001";
	rest_username = "admin";
	rest_password = "admin";

	//sfc_service_instance_uuid = "";
	//sfc_service_uuid = "";
}

ManoMsg::~ManoMsg()
{

}

void ManoMsg::set_parameter(const char * /*parameter_name*/,
	const char * /*parameter_value*/)
{

}

/*void ManoMsg::Handle_Fd_Event(int fd, boolean is_readable,
	boolean is_writable, boolean is_error) {}*/

void ManoMsg::Handle_Fd_Event_Error(int /*fd*/)
{

}

void ManoMsg::Handle_Fd_Event_Writable(int /*fd*/)
{

}

void ManoMsg::Handle_Fd_Event_Readable(int /*fd*/)
{

}

/*void ManoMsg::Handle_Timeout(double time_since_last_call) {}*/

void ManoMsg::user_map(const char * /*system_port*/)
{
	curl = curl_easy_init();

    if(curl) {
        // Setup curl options
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, replyToMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replyBuffer);

        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, "Content-Type: application/json");
        chunk = curl_slist_append(chunk, "Expect:");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        //curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

        if(debug) {
        	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

        // authentication
        curl_easy_setopt(curl, CURLOPT_USERNAME, rest_username.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, rest_password.c_str());

        // Test url if gatekeeper api is running
        setURL(gatekeeper_rest_url + "/instantiations");

        performRestRequest();
    }

}

void ManoMsg::user_unmap(const char * /*system_port*/)
{
	curl_easy_cleanup(curl);
	curl_slist_free_all(chunk);
}

void ManoMsg::user_start()
{

}

void ManoMsg::user_stop()
{

}

void ManoMsg::outgoing_send(const ServiceProfiling__Types::Setup__SFC& send_par)
{
	if(!sfc_service_instance_uuid.empty() && !sfc_service_uuid.empty()) {
		stopSfcService(sfc_service_uuid, sfc_service_instance_uuid);
	}

	std::string service_name = std::string(((const char*)send_par.service__name()));
	std::string filepath = nsd_path + service_name;

	log("Create SFC from %s", filepath.c_str());

	sfc_service_uuid = uploadPackage(filepath);

	sfc_service_instance_uuid = startSfcService(sfc_service_uuid);

	log("SFC created and running");
}

void ManoMsg::outgoing_send(const ServiceProfiling__Types::Add__VNF& send_par)
{
	std::string vnf_name = std::string(((const char*)send_par.name()));
	std::string vnf_cp = std::string(((const char*)send_par.connection__point()));
	std::string vnf_image = std::string(((const char*)send_par.image()));

	log("Setting up VNF %s with connection point %s from image %s", vnf_name.c_str(), vnf_cp.c_str(), vnf_image.c_str());

	startVNF(vnf_name, vnf_image);
	// TODO: does not work
	//connectVnfToSfc(vnf_name, vnf_cp);
}

void ManoMsg::outgoing_send(const ServiceProfiling__Types::Start__CMD& /*send_par*/)
{

}

void ManoMsg::outgoing_send(const ServiceProfiling__Types::ResourceConfiguration& send_par)
{
	std::string vnf_name = std::string(((const char*)send_par.function__id()));

	log("Setting resource configuration of VNF %s", vnf_name.c_str());

	std::string filename = vnf_path + vnf_name + "/" + vnf_name + "-vnfd.yml";

	YAML::Node file = YAML::LoadFile(filename);



	std::ofstream fout(filename);
	fout << file;
}

size_t ManoMsg::replyToMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ManoMsg::setURL(std::string url) {
	log("Next request to %s.", url.c_str());
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}

void ManoMsg::performRestRequest() {
	log("Perform request");
	CURLcode res;

	/* We have to overwrite the last reply or the new reply from the server will be appended to the previous reply */
	replyBuffer = "";

	res = curl_easy_perform(curl);
	log("replyBuffer: %s", replyBuffer.c_str());
	if(res != CURLE_OK) {
		long response_code;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
		TTCN_error("curl_easy_perform() failed with http code %ld: %s\n", response_code, curl_easy_strerror(res));
	}

	log("End perform request");
}

void ManoMsg::log(const char *fmt, ...) {
	if (debug) {
		va_list ap;
		va_start(ap, fmt);
		TTCN_Logger::begin_event(TTCN_DEBUG);
		TTCN_Logger::log_event("ManoMsg Test Port (%s): ", get_name());
		TTCN_Logger::log_event_va_list(fmt, ap);
		TTCN_Logger::end_event();
		va_end(ap);
	}
}

std::string ManoMsg::uploadPackage(std::string filepath) {
	log("Upload package from %s", filepath.c_str());

	setURL(gatekeeper_rest_url + "/packages");

	curl_mime *mime = curl_mime_init(curl);
	curl_mimepart *part = curl_mime_addpart(mime);
	curl_mime_filedata(part, filepath.c_str());
	curl_mime_name(part, "package");

	curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

	performRestRequest();
	curl_mime_free(mime);

	// Disable POST
	curl_easy_setopt(curl, CURLOPT_MIMEPOST, nullptr);

	std::string service_uuid = getJsonValueFromReply("service_uuid");

	return service_uuid;
}

std::string ManoMsg::startSfcService(std::string service_uuid) {
	log("Start service with uuid %s", service_uuid.c_str());

	Json::Value request;
	request["service_uuid"] = service_uuid;

	std::string document = getJsonDocument(request);

	setURL(gatekeeper_rest_url + "/instantiations");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, document.c_str());
	performRestRequest();

	std::string service_instance_uuid = getJsonValueFromReply("service_instance_uuid");
	return service_instance_uuid;
}


void ManoMsg::stopSfcService(std::string service_uuid, std::string service_instance_uuid) {
	log("Stop service with uuid %s and instance uuid %s", service_uuid.c_str(), service_instance_uuid.c_str());

	Json::Value request;
	request["service_uuid"] = service_uuid;
	request["service_instance_uuid"] = service_instance_uuid;

	std::string document = getJsonDocument(request);
	log("Request: %s", document.c_str());

	setURL(gatekeeper_rest_url + "/instantiations");
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, document.c_str());
	performRestRequest();

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, nullptr);

	log("Stopped service");
}

void ManoMsg::startVNF(std::string vnf_name, std::string vnf_image) {
	log("Start measurement point VNF with name %s from image %s", vnf_name.c_str(), vnf_image.c_str());
	//curl_easy_setopt(curl, CURLOPT_PUT, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

	setURL(vimemu_rest_url + "/restapi/compute/" + "dc1/" + vnf_name); // TODO: dc1 configureable

	Json::Value request_vnf;
	request_vnf["image"] = vnf_image;
	std::string document_vnf = getJsonDocument(request_vnf);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, document_vnf.c_str());

	performRestRequest();

	//curl_easy_setopt(curl, CURLOPT_PUT, 0L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, nullptr);
	log("Measurement point VNF created");
}

void ManoMsg::connectVnfToSfc(std::string vnf_name, std::string vnf_cp) {
	log("Connect %s to connection point %s", vnf_name.c_str(), vnf_cp.c_str());
	//curl_easy_setopt(curl, CURLOPT_PUT, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

	setURL(vimemu_rest_url + "/restapi/network");

	Json::Value request_net;
	request_net["vnf_src_name"] = vnf_name; // + ":" + vnf_name + "-eth0";
	request_net["vnf_dst_name"] = vnf_cp;
	//request_net["vnf_src_interface"] = vnf_name + "-eth0";
	//request_net["vnf_dst_interface"] = vnf_cp;
	request_net["bidirectional"] = "True";
	request_net["cookie"] = "10";
	request_net["priority"] = "1000";
	///restapi/network?priority=1000&bidirectional=True&cookie=10&vnf_src_name=client&vnf_dst_name=empty_vnf1

	std::string document_net = getJsonDocument(request_net);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, document_net.c_str());

	performRestRequest();

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, nullptr);
	//curl_easy_setopt(curl, CURLOPT_PUT, 0L);

	log("Connected to connection point");
}

std::string ManoMsg::getJsonValueFromReply(std::string key) {
	Json::Value reply;
	Json::Reader reader;

	bool parseSucessful = reader.parse(replyBuffer.c_str(), reply);
	if(!parseSucessful) {
		TTCN_error("Could not parse reply from MANO system: %s\n", reader.getFormattedErrorMessages().c_str());
	}

	std::string value = reply[key].asString();
	log("Current %s is %s", key.c_str(), value.c_str());

	return value;
}

std::string ManoMsg::getJsonDocument(Json::Value jsonv) {
	Json::StreamWriterBuilder wbuilder;
	std::string document = Json::writeString(wbuilder, jsonv);

	log("JSON Payload: %s", document.c_str());

	return document;
}

} /* end of namespace */

