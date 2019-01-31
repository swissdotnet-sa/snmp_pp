#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <snmp_pp/vb.h>
#include "snmp_pp/uxsnmp.h"

#include "snmp_pp/snmperrs.h"

#include "snmp_pp/config_snmp_pp.h"
#include "snmp_pp/snmpmsg.h"

using boost::asio::ip::udp;

using namespace Snmp_pp;

class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 10162))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,
                        std::size_t bytes_transferred)
    {
        if (!error)
        {
            std::cout << "[" << ++count << "] Received: " << bytes_transferred << "\n";
            if (bytes_transferred == MAX_SNMP_PACKET + 1)
            {
                // Message is too long...
                std::cout << "Received message is ignored (packet too long)\n";
            }

            std::cout << "address: "<< remote_endpoint_.address() << '\n';
            std::cout << "port: "<< remote_endpoint_.port() << '\n';

            SnmpMessage snmpmsg;
            snmpmsg.load(recv_buffer_.data(), bytes_transferred);

            std::cout << "Is v3: " << snmpmsg.is_v3_message() << '\n';
            if (!snmpmsg.is_v3_message())
            {
                Pdu pdu;
                OctetStr community_name;
                snmp_version version;
                int returncode = snmpmsg.unload(pdu, community_name, version);
                if (returncode != SNMP_CLASS_SUCCESS)
                {
                    std::cout << "Error while unloading.\n";
                }
                else
                {
                    std::cout << "community: " << community_name.get_printable() << '\n';
                    std::cout << "version: " << version << '\n';

                    int pdu_error = pdu.get_error_status();
                    if (pdu_error){
                        std::cout << "Response contains error: "
                                  << Snmp::error_msg(pdu_error)<< std::endl;
                    }
                    Oid id;
                    pdu.get_notify_id(id);
                    std::cout << "ID:  " << id.get_printable() << std::endl;
                    std::cout << "Type:" << pdu.get_type() << std::endl;

                    Vb nextVb;

                    for (int i=0; i<pdu.get_vb_count(); i++)
                    {
                        pdu.get_vb(nextVb, i);

                        std::cout << "Oid: " << nextVb.get_printable_oid() << std::endl
                                  << "Val: " <<  nextVb.get_printable_value() << std::endl;
                    }
                    if (pdu.get_type() == sNMP_PDU_INFORM) {
                        std::cout << "pdu type: " << pdu.get_type() << std::endl;
//                        std::cout << "sending response to inform: " << std::endl;
//                        nextVb.set_value("This is the response.");
//                        pdu.set_vb(nextVb, 0);
//                        snmp->response(pdu, target);
                    }
                    std::cout << std::endl;
                }
            }

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
                     const boost::system::error_code& /*error*/,
                     std::size_t /*bytes_transferred*/)
    {
    }

    int count = 0;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<unsigned char, MAX_SNMP_PACKET + 1> recv_buffer_;
};

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}