#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

//using boost::asio::ip::tcp;

/*int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3) // если аргументы не заданы или заданы не все
        {
            std::cout << "Usage: sync_client <server> <path>\n";
            std::cout << "Example:\n";
            std::cout << "  sync_client www.boost.org /LICENSE_1_0.txt\n";
            return 1;
        }

        boost::asio::io_service io_service; // основной класс asio

        // Получаем список конечных точек для указанного сервера
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "http");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        // Перебираем эти конечные точки и пробуем подключиться
        tcp::socket socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error) // подключиться не удалось
            throw boost::system::system_error(error);

        // Формируем запрос к веб-серверу. Указываем "Connection: close" что бы
        // сервер закрыл соединение как только отправит нам данные. Это
        // позволит нам узнать что отправка завершенна как только возникнет EOF
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << argv[2] << " HTTP/1.0\r\n";
        request_stream << "Host: " << argv[1] << "\r\n";*/
//        request_stream << "Accept: */*\r\n";
/*        request_stream << "Connection: close\r\n\r\n";

        // Отправляем сформированный запрос веб-серверу.
        boost::asio::write(socket, request);

        // Читаем ответ сервер. streambuf response примет все данные
        // он сам будет увеличиваться по мере поступления данных от сервера.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Проверяем что бы не было ошибок.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") // ошибка
        {
            std::cout << "Invalid response\n";
            return 1;
        }
        if (status_code != 200) // если код ответа не 200, то это тоже ошибка
        {
            std::cout << "Response returned with status code " << status_code << "\n";
            return 1;
        }

        // Читаем ответ. Он закончится пустой строкой.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Парсим заголовки
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            std::cout << header << "\n";
        std::cout << "\n";

        // Выводим в лог
        if (response.size() > 0)
            std::cout << &response;

        // Теперь читаем до конца
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error))
            std::cout << &response;

        if (error != boost::asio::error::eof) // ошибка
            throw boost::system::system_error(error);
    }
    catch (std::exception& e) // возникло исключение
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}*/

using namespace boost::asio;
io_service service;
ip::udp::socket sock(service);
boost::asio::ip::udp::endpoint sender_ep;
char buff[512];
void on_read(const boost::system::error_code & err, std::size_t
read_bytes)
{
    std::cout << "read " << read_bytes << std::endl;
    sock.async_receive_from(buffer(buff), sender_ep, on_read);
}
int main(int argc, char* argv[])
{
    ip::udp::endpoint ep( ip::address::from_string("127.0.0.1"),
                          8001);
    sock.open(ep.protocol());
    sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    sock.bind(ep);
    sock.async_receive_from(buffer(buff,512), sender_ep, on_read);
    service.run();
}
