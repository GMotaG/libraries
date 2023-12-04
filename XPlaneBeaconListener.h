/*
  * XPlaneBeaconListener.h
  *
  *  Created on: Jul 27, 2017
  *      Author: shahada
  *
  *  Copyright (c) 2017-2018 Shahada Abubakar.
  *
  *  This file is part of libXPlane-UDP-Client.
  *
  *  This program is free software: you can redistribute it and/or
  *  modify it under the terms of the Lesser GNU General Public
  *  License as  published by the Free Software Foundation, either
  *  version 3 of the  License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  *
  *  See the GNU General Public License for more details.
  *
  */
 
 #ifndef XPLANEUDPCLIENT_SRC_XPLANEBEACONLISTENER_H_
 #define XPLANEUDPCLIENT_SRC_XPLANEBEACONLISTENER_H_
 
 #include <cstdint>
 #include <set>
 #include <time.h>
 #include <map>
 #include <list>
 #include <mutex>
 #include <functional>
 
 
 class XPlaneBeaconListener {
 
 private:
     XPlaneBeaconListener(); // private so it cannot be called
     XPlaneBeaconListener(XPlaneBeaconListener const &) {}; // private so it cannot be called
     XPlaneBeaconListener & operator= (XPlaneBeaconListener const &) { abort();};
 
 public:
 
     void setDebug (int _debug) {
         debug = _debug;
     }
 
     class XPlaneServer {
     public:
         time_t received;
         std::string prologue;
         uint8_t beaconMajorVersion;
         uint8_t beaconMinorVersion;
         int32_t applicationHostId;
         int32_t versionNumber;
         int32_t role;
         uint16_t receivePort;
         std::string name;
         std::string host;
         XPlaneServer () {};
         XPlaneServer (time_t time, char * mesg, char * host);
         std::string toString();
     };
 
     static XPlaneBeaconListener * getInstance() {
         if (!instance) {
             instance = new XPlaneBeaconListener ();
         }
         return instance;
     }
 
     virtual ~XPlaneBeaconListener();
 
     void get (std::list<XPlaneBeaconListener::XPlaneServer> & ret);
 
     void registerNotificationCallback (std::function<void(XPlaneServer server, bool exists)> callback);
 
 protected:
 
     bool quitFlag;
     bool isRunning;
     int debug;
 
     static XPlaneBeaconListener * instance;
 
     void runListener ();
 
     std::map<std::string, XPlaneServer> cachedServers;
     std::mutex cachedServersMutex;
 
     std::list<std::function<void(XPlaneServer server, bool exists)>> callbacks;
 
     void checkForExpiredServers ();
 
 };
 
 #endif /* XPLANEUDPCLIENT_SRC_XPLANEBEACONLISTENER_H_ */
