/**\file
 *
 * \copyright
 * Copyright (c) 2013-2014, Verthandi Project Members
 * \copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * \copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * \copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include <ef.gy/http.h>

#include <cstdlib>

#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace boost::filesystem; 
using namespace boost::iostreams;
using namespace boost::asio;
using namespace boost;
using namespace std;

class processVerthandi
{
    public:
        bool operator () (efgy::net::http::session<processVerthandi> &a)
        {
            a.reply (200,
                     "Content-Type: text/xml; charset=utf-8\r\n",
                     string("<?xml version='1.0' encoding='utf-8'?>"
                            "<verthandi xmlns='http://verthandi.org/2014/verthandi'/>")
                     );

            return true;
        }
};

int main (int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <socket>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        efgy::net::http::server<processVerthandi> s(io_service, argv[1]);

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
