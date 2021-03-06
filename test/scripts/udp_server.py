#!/usr/bin/python
#
# udp_server.py: UDP server
#
# Created by Sandesh Kumar Sodhi, December 2017
# Copyright (c) [2017] Juniper Networks, Inc. All rights reserved.
#
# All rights reserved.
#
# Notice and Disclaimer: This code is licensed to you under the Apache
# License 2.0 (the "License"). You may not use this code except in compliance
# with the License. This code is not an official Juniper product. You can
# obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Third-Party Code: This code may depend on other components under separate
# copyright notice and license terms. Your use of the source code for those
# components is subject to the terms and conditions of the respective license
# as noted in the Third-Party source code file.
#


import SocketServer
#import hexdump
PKTIO_IP = "172.18.0.20"
PKTIO_PORT = 64014

class UDPHandler(SocketServer.BaseRequestHandler):

    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        print "{} wrote:".format(self.client_address[0])
        print data
        #hexdump.dump(data, sep=":")
        socket.sendto(data.upper(), (PKTIO_IP, PKTIO_PORT))

if __name__ == "__main__":
    HOST, PORT = "172.18.0.3", 64015
    print "Listening on " + str(HOST) + ":" + str(PORT)
    server = SocketServer.UDPServer((HOST, PORT), UDPHandler)
    server.serve_forever()

