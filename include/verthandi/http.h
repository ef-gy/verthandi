/**\file
 * \brief Main process (HTTP)
 *
 * The main entry point for verthandi; currently only provides an HTTP XML
 * interface using efgy::net::http.
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

#if !defined(VERTHANDI_HTTP_H)
#define VERTHANDI_HTTP_H

#include <ef.gy/http.h>

#include <verthandi/project.h>
#include <verthandi/task.h>
#include <verthandi/data-sqlite-verthandi.h>

#include <sstream>

namespace verthandi
{
    /**\brief HTTP-related templates
     *
     * This namespace groups together all sorts of templates that are related to
     * handling HTTP queries.
     */
    namespace http
    {
        /**\brief HTTP responder
         *
         * A functor that processes HTTP requests and generates proper replies
         * to valid queries.
         *
         * \tparam db The database access class to use, e.g.
         *            efgy::database::sqlite
         */
        template <typename db>
        class responder;

        /**\brief Verthandi state class
         *
         * Contains the state that is necessary to generate HTTP replies in the
         * responder class.
         */
        template <typename db>
        class state
        {
            public:
                /**\brief Construct with database file
                 *
                 * This default constructor initialises an instance of the
                 * database class at the given location.
                 */
                state (void *aux)
                    : sql((const char *)aux, verthandi::data::sqlite::verthandi)
                    {}

                /**\brief Database connection
                 *
                 * Contains the proper, initialised database connection that the
                 * constructor establishes.
                 */
                db sql;
        };

        /**\brief Default server
         *
         * The default HTTP server type, configured to use an SQLite database.
         */
        typedef efgy::net::http::server<responder<efgy::database::sqlite>,state<efgy::database::sqlite>> server;

        /**\brief Default session
         *
         * The default HTTP session type, configured to use an SQLite database.
         */
        typedef efgy::net::http::session<responder<efgy::database::sqlite>,state<efgy::database::sqlite>> session;

        template <typename db>
        class responder
        {
            public:
                /**\brief Main entry point
                 *
                 * This is the main entry point for HTTP requests to verthandi.
                 * This method will thus provide the services of a request
                 * dispatcher, based on the request parameters.
                 *
                 * \param[out] a Data for the current request.
                 *
                 * \returns 'true' if the request was handled successfully.
                 *          This function cannot fail right now, so it will
                 *          always return 'true'.
                 */
                bool operator () (session &a)
                {
                    std::ostringstream s("");

                    static const std::regex rproject("/verthandi/project/(\\d+)");
                    static const std::regex rtask("/verthandi/task/(\\d+)");
                    std::smatch matches;

                    if (std::regex_match(a.resource, matches, rproject))
                    {
                        int projectID = 0;
                        std::stringstream is(matches[1]);
                        is >> projectID;

                        s << "<?xml version='1.0' encoding='utf-8'?>"
                             "<verthandi xmlns='http://verthandi.org/2014/verthandi'>";
                        s << efgy::render::XML() << project<db>(a.state->sql, projectID);
                        s << "</verthandi>";
                    }
                    else if (std::regex_match(a.resource, matches, rtask))
                    {
                        int taskID = 0;
                        std::stringstream is(matches[1]);
                        is >> taskID;

                        s << "<?xml version='1.0' encoding='utf-8'?>"
                             "<verthandi xmlns='http://verthandi.org/2014/verthandi'>";
                        s << efgy::render::XML() << task<db>(a.state->sql, taskID);
                        s << "</verthandi>";
                    }
                    else
                    {
                        s << "<?xml version='1.0' encoding='utf-8'?>"
                             "<verthandi xmlns='http://verthandi.org/2014/verthandi'>"
                          << "<resource>" << a.resource << "</resource>"
                          << "</verthandi>";
                    }

                    a.reply (200, "Content-Type: text/xml; charset=utf-8\r\n", s.str());

                    return true;
                }
        };
    };
};

#endif
