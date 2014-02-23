/**\file
 * \brief Project abstraction
 *
 * Contains templates that provide access to projects in Verthandi's database. A
 * project is a single entry in the 'projects' table.
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

#if !defined(VERTHANDI_PROJECT_H)
#define VERTHANDI_PROJECT_H

#include <ef.gy/render-xml.h>
#include <ef.gy/maybe.h>

#include <verthandi/object.h>

#include <ostream>
#include <string>

namespace verthandi
{
    /**\brief A project
     *
     * Contains a single row of the 'projects' table in the database. The row is
     * identified by a numeric ID, which is why this class derives from the
     * verthandi::object template.
     *
     * \tparam db The database access class to use, e.g. efgy::database::sqlite
     */
    template <typename db>
    class project : public object<db>
    {
        public:
            /**\copydoc object<db>::object
             *
             * In instances of the task type, the pID is assumed to refer to the
             * contents of the tasks.id column, and the corresponding row is
             * automatically retrieved when an instance of the class is
             * initialised.
             */
            project (db &pDatabase, const typename db::id &pID)
                : object<db>(pDatabase, pID) { sync(); }

            /**\brief Project name
             *
             * Corresponds to the projects.name field in the database.
             */
            std::string name;

            efgy::maybe<std::string> description;
            efgy::maybe<double> deadline;
            efgy::maybe<int> urgency;
            efgy::maybe<int> importance;

            using object<db>::id;
            using object<db>::valid;

        protected:
            using object<db>::database;

            /**\brief Retrieve project data from database
             *
             * Selects the project's data from the database and stores the data
             * in the class instance.
             *
             * \returns 'true' if the project instance is now in a valid state,
             *          false otherwise.
             */
            bool sync (void)
            {
                typename db::statement select("select name, description, deadline, urgency, importance from projects where id=?1", database);
                select.bind(1, id);
                if (select.step() && select.row)
                {
                    select.get(0, name);
                    description.nothing = !select.get(1, description.just);
                    deadline.nothing    = !select.get(2, deadline.just);
                    urgency.nothing     = !select.get(3, urgency.just);
                    importance.nothing  = !select.get(4, importance.just);
                    return (valid = true);
                }
                return (valid = false);
            }
    };

    /**\brief Serialise project to stream
     *
     * Writes an XML representation of a project to a C++ stream object.
     *
     * \tparam C  Character type of the stream.
     * \tparam db Database type of the task instance.
     *
     * \param[out] out The stream to write to.
     * \param[in]  p   The task instance to write to the stream.
     *
     * \returns A reference to the 'out' parameter, as is customary with C++
     *          streams.
     */
    template <typename C, typename db>
    efgy::render::oxmlstream<C> operator << (efgy::render::oxmlstream<C> out, const project<db> &p)
    {
        if (!p.valid)
        {
            out.stream << "<project id='" << p.id << "' status='invalid'/>";
        }
        else
        {
            out.stream << "<project id='" << p.id << "' name='" << p.name << "'";
            if (p.deadline)
            {
                out.stream << " deadline='" << p.deadline.just << "'";
            }
            if (p.urgency)
            {
                out.stream << " urgency='" << p.urgency.just << "'";
            }
            if (p.importance)
            {
                out.stream << " importance='" << p.importance.just << "'";
            }
            if (p.description)
            {
                out.stream << ">" << p.description.just << "</project>";
            }
            else
            {
                out.stream << "/>";
            }
        }
        return out;
    }
};

#endif
