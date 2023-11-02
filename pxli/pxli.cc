#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <toml.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

// Helper function to write the response data from curl
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
  size_t newLength = size * nmemb;
  try {
    s->append(static_cast<char*>(contents), newLength);
  } catch (std::bad_alloc &e) {
    // Handle memory allocation exceptions
    return 0;
  }
  return newLength;
}

// Function to check the cookie's validity
bool isCookieValid(const std::string& cookie, const std::string& baseUrl) {
  // Implementation needed
  // This is a placeholder function. You should replace it with a real validation against the Proxmox VE API.
  return false; // Always returns false for simplicity
}

// Function to authenticate and get the cookie
bool authenticateAndGetCookie(const std::string& username, const std::string& password, const std::string& baseUrl, std::string& cookie, std::string& csrfToken) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    std::string postData = "username=" + username + "&password=" + password;
    curl_easy_setopt(curl, CURLOPT_URL, (baseUrl + "/api2/json/access/ticket").c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // -k flag equivalent
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
      std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
      return false;
    }

    // Parse JSON response with RapidJSON
    rapidjson::Document doc;
    if (doc.Parse(readBuffer.c_str()).HasParseError()) {
      std::cerr << "JSON parse error" << std::endl;
      return false;
    }

    if (!doc.HasMember("data")) {
      std::cerr << "JSON response does not have 'data' member" << std::endl;
      return false;
    }

    const rapidjson::Value& data = doc["data"];
    if (!data.HasMember("ticket") || !data.HasMember("CSRFPreventionToken")) {
      std::cerr << "JSON response does not have 'ticket' or 'CSRFPreventionToken' members" << std::endl;
      return false;
    }

    cookie = "PVEAuthCookie=" + std::string(data["ticket"].GetString());
    csrfToken = std::string(data["CSRFPreventionToken"].GetString());
    return true;
  }

  return false;
}

int main() {
  auto config = toml::parse_file("../config.toml");

  std::string baseUrl = config["config"]["base_url"].value_or("");
  std::string username = config["config"]["username"].value_or("");
  std::string password = config["config"]["password"].value_or("");
  std::string cookieFilePath = config["config"]["cookie_file_path"].value_or("proxmox_cookie.txt");
  std::string csrfTokenFilePath = config["config"]["csrf_token_file_path"].value_or("proxmox_csrf_token.txt");
  std::string cookie, csrfToken;

  // Check if the cookie file exists and is valid
  std::ifstream cookieFile(cookieFilePath);
  if (cookieFile.is_open()) {
    std::getline(cookieFile, cookie);
    cookieFile.close();
  }

  // Authenticate and get cookie if not valid
  if (!isCookieValid(cookie, baseUrl)) {
    if (authenticateAndGetCookie(username, password, baseUrl, cookie, csrfToken)) {
      // Store the cookie in a file
      std::ofstream outCookie(cookieFilePath);
      outCookie << cookie;
      outCookie.close();
      
      // Store the CSRF token in a file
      std::ofstream outCsrf(csrfTokenFilePath);
      outCsrf << csrfToken;
      outCsrf.close();
      
      std::cout << "Authentication successful, cookie and CSRF token stored." << std::endl;
    } else {
      std::cerr << "Authentication failed, cannot proceed!" << std::endl;
      return 1;
    }
  }

  if (!cookie.empty() && !csrfToken.empty()) {
    std::cout << "Ready to go, cookie and CSRF token are valid!" << std::endl;
    // Here you would continue to implement the rest of the API calls as needed...
  } else {
    std::cout << "Authentication failed, cannot proceed!" << std::endl;
    return 1;
  }

  return 0;
}
