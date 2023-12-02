#include "cgdk/sdk10/net.socket.h"

#include <iostream>
#if defined(_WIN32)
    #include <conio.h>
#endif

using namespace CGDK;

// 
// 설명) Network TS의 net.ip 체계
//       
//  지금 현재 표준화 중인 Network TS의 ip에 대한 구조체와 함수들을 구현한 것이다.
//  
//  제강되는 핵심 class와 함수는 다음과 같다.
//  
//    1) net::ip::address_v4
//       net::ip::address_v6
//       net::ip::make_address_v4
//       net::ip::make_address_v6
//       net::ip::make_address
//

int main()
{
    // 1. ip::address
    {
        // 1) ip address 숫자를 사용해 초기화하기
        [[maybe_unused]] net::ip::address_v4 temp_0{ {127,0,0,1} };

        // 2) ip address 문자열를 사용해 초기화하기
        [[maybe_unused]] auto temp1 = net::ip::make_address_v4("127.0.0.1"sv);

        // 3) any, loopback, boradcast와 같은이 예약된 address
        [[maybe_unused]] auto temp2 = net::ip::address_v4::any();       // 0.0.0.0
        [[maybe_unused]] auto temp3 = net::ip::address_v4::loopback();  // 127.0.0.1
        [[maybe_unused]] auto temp4 = net::ip::address_v4::broadcast(); // 255.255.255.255

        [[maybe_unused]] auto temp5 = net::ip::address_v6::any();       // ::/0
        [[maybe_unused]] auto temp6 = net::ip::address_v6::loopback();  // ::1
    }

    // 2. ip::endpoint
    //    - endpoint는 address와 port 정보를 합한 것이다.
    //    - ip::tcp::endpoint는 tcp용 주소를 지목하는 용도로 사용된다.
    //    - ip주소와 port 정보가 필요한 곳 대표적으로 socket의 accept와 connect 등에 사용된다.
    {
        // 1) ip address를 숫자로 입력
        net::ip::tcp::endpoint temp_0{ net::ip::address_v4 {{127,0,0,1}}, 100 };

        // 2) ip address를 문자열로 입력
        //    make_address_v4 혹은 make_address_v6로 문자열 ip address를 address로 바꿔준다.
        //    make_adddress를 사용하면 문자열에 따라 자동적으로 ip v4 혹은 ip v6를 구분해 준다.
        net::ip::tcp::endpoint temp_1{ net::ip::make_address_v4("127.0.0.1"sv), 100 };
        net::ip::tcp::endpoint temp_2{ net::ip::make_address_v6("::1"sv), 100 };

        // 3) any, loopback, broadcast와 같이 예약된 address로 설정할때.
        net::ip::tcp::endpoint temp_3{ net::ip::address_v4::any(), 100 };
        net::ip::tcp::endpoint temp_4{ net::ip::address_v4::loopback(), 100 };
        net::ip::tcp::endpoint temp_5{ net::ip::address_v4::broadcast(), 100 };

        net::ip::tcp::endpoint temp_6{ net::ip::address_v6::any(), 100 };
        net::ip::tcp::endpoint temp_7{ net::ip::address_v6::loopback(), 100 };

        // 4) DNS로 endpoint 얻어오기
        //    DNS는 DNS server를 통해 해당 address값을 받아와야 한다. 따라서 resolver를 사용해야 한다.
        //    resolve()는 찾은 모든 ip에 대한 결과를 돌려준다.
        {
            std::cout << "4) www.cgcii.co.kr : 100"sv << std::endl;

            net::ip::tcp::resolver::results_type temp = net::ip::tcp::resolver().resolve("www.cgcii.co.kr"sv, "100"sv);

            for (auto iter : temp)
            {
                net::ip::tcp::endpoint temp_endpoint = iter.endpoint();

                std::cout << "ip address: "sv << to_string<char>(temp_endpoint) << " port:"sv << temp_endpoint.port() << std::endl;
            }
        }

        // 5) result의 결과물은 여러 개가 전달되어 올수 있지만 그냥 endpont로 받게 되면 주소중 첫번째가 선택되어진다.
        {
            std::cout << "5) www.cgcii.co.kr : 100"sv << std::endl;

            net::ip::tcp::endpoint temp = net::ip::tcp::resolver().resolve("www.cgcii.co.kr"sv, "100");

            std::cout << "ip address: "sv << to_string<char>(temp) << " port:"sv << temp.port() << std::endl;
        }

        // 6) DNS롤 ip v4 주소를 얻기
        //   첫번째 인자로 프로토콜을 net::ip::tcp::v4()로 명시해준다.
        {
            std::cout << "6) www.cgcii.co.kr : 100"sv << std::endl;

            net::ip::tcp::endpoint temp = net::ip::tcp::resolver().resolve(net::ip::tcp::v4(), "www.cgcii.co.kr"sv, "100"sv);

            std::cout << "ip address: "sv << to_string<char>(temp) << " port:"sv << temp.port() << std::endl;
        }

        // 7) DNS롤 ip v6 주소를 얻기
        //   첫번째 인자로 프로토콜을 net::ip::tcp::v6()로 명시해준다.
        {
            std::cout << "7) www.cgcii.co.kr : 100"sv << std::endl;

            net::ip::tcp::endpoint temp = net::ip::tcp::resolver().resolve(net::ip::tcp::v6(), "www.cgcii.co.kr"sv, "100"sv);

            std::cout << "ip address: "sv << to_string<char>(temp) << " port:"sv << temp.port() << std::endl;
        }

        // 8) 주소는 BIND_ANY 혹은 0으르 넣고 포트번호만 100으로 설정하고 싶을 때
        //   tcp인지 udp인지 프로토콜과 ipv4인지 ipv6일지 정보를 넣고 포트번호 100을 넣는다. 
        {
            std::cout << "8) ipv4 : 100"sv << std::endl;

            net::ip::tcp::endpoint temp{ net::ip::tcp::v4(), 100 };

            std::cout << "ip address: "sv << to_string<char>(temp) << " port:"sv << temp.port() << std::endl;
        }

        // 9) 기타 함수들
        {
            net::ip::tcp::endpoint temp{ net::ip::address_v4 {{127,0,0,1}}, 100 };

            // - ip_v4()인지 ip_v6()인지를 얻을 수 있다.
            [[maybe_unused]] auto temp1 = temp.protocol();

            // - address 크기를 얻을 수 있다. (ip_v4인지 ip_v6인지에 따라 데이터의 크기가 다르다.)
            [[maybe_unused]] auto temp2 = temp.size();

            // - address와 port를 얻을 수 있는 함수.
            [[maybe_unused]] auto temp3 = temp.address();
            [[maybe_unused]] auto temp4 = temp.port();

            // - ip_v4인지 ip_v6()인지 확이니하는 함수
            [[maybe_unused]] auto temp5 = temp.is_v4();
            [[maybe_unused]] auto temp6 = temp.is_v6();
        }
    }
}