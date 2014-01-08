/**\file
 * \brief Main function and related functionality
 *
 * Contains the main() function, which sets things up so that verthandi can run
 * as intended.
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
 *
 * \see Project Documentation: http://ef.gy/documentation/verthandi
 * \see Project Source Code: http://github.com/machinelady/verthandi.git
 */

#include <verthandi/http.h>

#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace boost::asio;
using namespace boost;
using namespace std;

/**\brief Main function
 *
 * The main entry point for any programme; with verthandi this function will set
 * up the requested socket by launching an HTTP server on it that serves data
 * from the given SQLite3 database file.
 *
 * Note that this programme does not fork itself to the background.
 *
 * \param[in] argc The number of arguments in argv.
 * \param[in] argv Command line arguments.
 *
 * \returns Zero on success, nonzero on failure.
 */
int main (int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: " << argv[0] << " <socket> <database>\n";
            return 1;
        }

        io_service io_service;

        verthandi::http::server s(io_service, argv[1], argv[2]);

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
